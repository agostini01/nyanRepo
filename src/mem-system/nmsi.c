/*
 *  Copyright (C) 2012  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received stack copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <assert.h>

#include <lib/esim/esim.h>
#include <lib/esim/trace.h>
#include <lib/util/debug.h>
#include <lib/util/linked-list.h>
#include <lib/util/list.h>
#include <lib/util/string.h>
#include <mem-system/memory.h>
#include <network/message.h>
#include <network/net-system.h>
#include <network/network.h>
#include <network/node.h>

#include "cache.h"
#include "directory.h"
#include "mem-system.h"
#include "mod-stack.h"
#include "plotter.h"

int cache_snapshot;


/* Events */

int EV_MOD_NMSI_LOAD;
int EV_MOD_NMSI_LOAD_LOCK;
int EV_MOD_NMSI_LOAD_ACTION;
int EV_MOD_NMSI_LOAD_MISS;
int EV_MOD_NMSI_LOAD_UNLOCK;
int EV_MOD_NMSI_LOAD_FINISH;

int EV_MOD_NMSI_STORE;
int EV_MOD_NMSI_STORE_LOCK;
int EV_MOD_NMSI_STORE_ACTION;
int EV_MOD_NMSI_STORE_UNLOCK;
int EV_MOD_NMSI_STORE_FINISH;

int EV_MOD_NMSI_NC_STORE;
int EV_MOD_NMSI_NC_STORE_LOCK;
int EV_MOD_NMSI_NC_STORE_WRITEBACK;
int EV_MOD_NMSI_NC_STORE_ACTION;
int EV_MOD_NMSI_NC_STORE_MISS;
int EV_MOD_NMSI_NC_STORE_UNLOCK;
int EV_MOD_NMSI_NC_STORE_FINISH;

int EV_MOD_NMSI_FIND_AND_LOCK;
int EV_MOD_NMSI_FIND_AND_LOCK_PORT;
int EV_MOD_NMSI_FIND_AND_LOCK_ACTION;
int EV_MOD_NMSI_FIND_AND_LOCK_FINISH;

int EV_MOD_NMSI_EVICT;
int EV_MOD_NMSI_EVICT_INVALID;
int EV_MOD_NMSI_EVICT_ACTION;
int EV_MOD_NMSI_EVICT_RECEIVE;
int EV_MOD_NMSI_EVICT_PROCESS;
int EV_MOD_NMSI_EVICT_PROCESS_FINISH;
int EV_MOD_NMSI_EVICT_PROCESS_NONCOHERENT;
int EV_MOD_NMSI_EVICT_REPLY;
int EV_MOD_NMSI_EVICT_REPLY_RECEIVE;
int EV_MOD_NMSI_EVICT_FINISH;

int EV_MOD_NMSI_WRITE_REQUEST;
int EV_MOD_NMSI_WRITE_REQUEST_RECEIVE;
int EV_MOD_NMSI_WRITE_REQUEST_ACTION;
int EV_MOD_NMSI_WRITE_REQUEST_EXCLUSIVE;
int EV_MOD_NMSI_WRITE_REQUEST_UPDOWN;
int EV_MOD_NMSI_WRITE_REQUEST_UPDOWN_FINISH;
int EV_MOD_NMSI_WRITE_REQUEST_DOWNUP;
int EV_MOD_NMSI_WRITE_REQUEST_DOWNUP_FINISH;
int EV_MOD_NMSI_WRITE_REQUEST_REPLY;
int EV_MOD_NMSI_WRITE_REQUEST_FINISH;

int EV_MOD_NMSI_READ_REQUEST;
int EV_MOD_NMSI_READ_REQUEST_RECEIVE;
int EV_MOD_NMSI_READ_REQUEST_ACTION;
int EV_MOD_NMSI_READ_REQUEST_UPDOWN;
int EV_MOD_NMSI_READ_REQUEST_UPDOWN_MISS;
int EV_MOD_NMSI_READ_REQUEST_UPDOWN_FINISH;
int EV_MOD_NMSI_READ_REQUEST_DOWNUP;
int EV_MOD_NMSI_READ_REQUEST_DOWNUP_WAIT_FOR_REQS;
int EV_MOD_NMSI_READ_REQUEST_DOWNUP_FINISH;
int EV_MOD_NMSI_READ_REQUEST_REPLY;
int EV_MOD_NMSI_READ_REQUEST_FINISH;

int EV_MOD_NMSI_INVALIDATE;
int EV_MOD_NMSI_INVALIDATE_FINISH;

int EV_MOD_NMSI_PEER_SEND;
int EV_MOD_NMSI_PEER_RECEIVE;
int EV_MOD_NMSI_PEER_REPLY;
int EV_MOD_NMSI_PEER_FINISH;

int EV_MOD_NMSI_MESSAGE;
int EV_MOD_NMSI_MESSAGE_RECEIVE;
int EV_MOD_NMSI_MESSAGE_ACTION;
int EV_MOD_NMSI_MESSAGE_REPLY;
int EV_MOD_NMSI_MESSAGE_FINISH;

int EV_MOD_NMSI_FLUSH;
int EV_MOD_NMSI_FLUSH_FINISH;


/* NMSI Protocol */

void mod_handler_nmsi_load(int event, void *data)
{
	struct mod_stack_t *stack = data;
	struct mod_stack_t *new_stack;

	struct mod_t *mod = stack->mod;

	/* This activates the number of accesses in the MSHR through time */
	mem_access_record(mod->mshr_record,
			mod->access_list_count - mod->access_list_coalesced_count);

	if (event == EV_MOD_NMSI_LOAD)
	{
		struct mod_stack_t *master_stack;

		mem_debug("%lld %lld 0x%x %s load\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.new_access name=\"A-%lld\" type=\"load\" "
			"state=\"%s:load\" addr=0x%x\n",
			stack->id, mod->name, stack->addr);
		if (mem_snap_period != 0)
		{
			assert(snapshot_load);
			long long cycle = esim_domain_cycle(mem_domain_index);

			snapshot_record(snapshot_load, cycle, stack->addr);

			if (cache_snapshot && !mod->snapshot_load)
			{
				char file[MAX_STRING_SIZE];
				snprintf(file, sizeof file,
						"%s_load", mod->name);
				mod->snapshot_load = snapshot_create(file);
			}
			snapshot_record(mod->snapshot_load, cycle, stack->addr);
		}

		/* Record access */
		mod_access_start(mod, stack, mod_access_load);

		/* Coalesce access */
		master_stack = mod_can_coalesce(mod, mod_access_load, stack->addr, stack);
		if (master_stack)
		{
			mod->coalesced_reads++;
			mod_coalesce(mod, master_stack, stack);
			mod_stack_wait_in_stack(stack, master_stack, EV_MOD_NMSI_LOAD_FINISH);
			return;
		}

		/* Next event */
		esim_schedule_event(EV_MOD_NMSI_LOAD_LOCK, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_LOAD_LOCK)
	{
		struct mod_stack_t *older_stack;

		mem_debug("  %lld %lld 0x%x %s load lock\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:load_lock\"\n",
			stack->id, mod->name);

		/* If there is any older write, wait for it */
		older_stack = mod_in_flight_write(mod, stack);
		if (older_stack)
		{
			mem_debug("    %lld wait for write %lld\n",
				stack->id, older_stack->id);
			mod_stack_wait_in_stack(stack, older_stack, EV_MOD_NMSI_LOAD_LOCK);
			return;
		}

		/* If there is any older access to the same address that this access could not
		 * be coalesced with, wait for it. */
		older_stack = mod_in_flight_address(mod, stack->addr, stack);
		if (older_stack)
		{
			mem_debug("    %lld wait for access %lld\n",
				stack->id, older_stack->id);
			mod_stack_wait_in_stack(stack, older_stack, EV_MOD_NMSI_LOAD_LOCK);
			return;
		}

		/* Call find and lock */
		new_stack = mod_stack_create(stack->id, mod, stack->addr,
			EV_MOD_NMSI_LOAD_ACTION, stack);
		new_stack->blocking = 1;
		new_stack->read = 1;
		new_stack->retry = stack->retry;
		esim_schedule_event(EV_MOD_NMSI_FIND_AND_LOCK, new_stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_LOAD_ACTION)
	{
		int retry_lat;

		mem_debug("  %lld %lld 0x%x %s load action\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:load_action\"\n",
			stack->id, mod->name);

		/* Error locking */
		if (stack->err)
		{
			mod->read_retries++;
			retry_lat = mod_get_retry_latency(mod);
			mem_debug("    lock error, retrying in %d cycles\n", retry_lat);
			stack->retry = 1;
			esim_schedule_event(EV_MOD_NMSI_LOAD_LOCK, stack, retry_lat);
			return;
		}

		/* Hit */
		if (stack->state)
		{
			// assert that we never have the E state unless the
			// module is main memory
			if (stack->state == cache_block_exclusive)
				assert(mod->kind == mod_kind_main_memory);

			// It is a hit. Unlock the block 
			esim_schedule_event(EV_MOD_NMSI_LOAD_UNLOCK, stack, 0);

			return;
		}

		/* Miss */
		new_stack = mod_stack_create(stack->id, mod, stack->tag,
			EV_MOD_NMSI_LOAD_MISS, stack);
		new_stack->peer = mod_stack_set_peer(mod, stack->state);
		new_stack->target_mod = mod_get_low_mod(mod, stack->tag);
		new_stack->request_dir = mod_request_up_down;
		esim_schedule_event(EV_MOD_NMSI_READ_REQUEST, new_stack, 0);

		return;
	}

	if (event == EV_MOD_NMSI_LOAD_MISS)
	{
		int retry_lat;

		mem_debug("  %lld %lld 0x%x %s load miss\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:load_miss\"\n",
			stack->id, mod->name);

		/* Error on read request. Unlock block and retry load. */
		if (stack->err)
		{
			mod->read_retries++;
			retry_lat = mod_get_retry_latency(mod);
			dir_entry_unlock(mod->dir, stack->set, stack->way);
			mem_debug("    lock error, retrying in %d cycles\n", retry_lat);
			stack->retry = 1;
			esim_schedule_event(EV_MOD_NMSI_LOAD_LOCK, stack, retry_lat);
			return;
		}

		// Set block state to shared
		// Also set the tag of the block.
		// Here, the block was invalid so cannot be main memory
		// and main memory blocks are the only ones that can have
		// the exclusive state. 
		cache_set_block(mod->cache, stack->set, stack->way, stack->tag,
			cache_block_shared);

		/* Continue */
		esim_schedule_event(EV_MOD_NMSI_LOAD_UNLOCK, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_LOAD_UNLOCK)
	{
		mem_debug("  %lld %lld 0x%x %s load unlock\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:load_unlock\"\n",
			stack->id, mod->name);

		/* Unlock directory entry */
		dir_entry_unlock(mod->dir, stack->set, stack->way);

		/* Impose the access latency before continuing */
		esim_schedule_event(EV_MOD_NMSI_LOAD_FINISH, stack, 
			mod->latency);
		return;
	}

	if (event == EV_MOD_NMSI_LOAD_FINISH)
	{
		mem_debug("%lld %lld 0x%x %s load finish\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:load_finish\"\n",
			stack->id, mod->name);
		mem_trace("mem.end_access name=\"A-%lld\"\n",
			stack->id);

		/* Increment witness variable */
		if (stack->witness_ptr)
			(*stack->witness_ptr)++;

		/* Return event queue element into event queue */
		if (stack->event_queue && stack->event_queue_item)
			linked_list_add(stack->event_queue, stack->event_queue_item);

		/* Free the mod_client_info object, if any */
		if (stack->client_info)
			mod_client_info_free(mod, stack->client_info);

		/* Finish access */
		mod_access_finish(mod, stack);

		/* Return */
		mod_stack_return(stack);
		return;
	}

	abort();
}


void mod_handler_nmsi_store(int event, void *data)
{
	struct mod_stack_t *stack = data;
	struct mod_stack_t *new_stack;

	struct mod_t *mod = stack->mod;


	if (event == EV_MOD_NMSI_STORE)
	{
		struct mod_stack_t *master_stack;

		mem_debug("%lld %lld 0x%x %s store\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.new_access name=\"A-%lld\" type=\"store\" "
			"state=\"%s:store\" addr=0x%x\n",
			stack->id, mod->name, stack->addr);
		if (mem_snap_period != 0)
		{
			assert(snapshot_store);
			long long cycle = esim_domain_cycle(mem_domain_index);

			snapshot_record(snapshot_store, cycle, stack->addr);
			if (cache_snapshot && !mod->snapshot_store)
			{
				char file[MAX_STRING_SIZE];
				snprintf(file, sizeof file,
						"%s_store", mod->name);
				mod->snapshot_store = snapshot_create(file);
			}
			snapshot_record(mod->snapshot_store, cycle, stack->addr);
		}

		/* Record access */
		mod_access_start(mod, stack, mod_access_store);

		/* Coalesce access */
		master_stack = mod_can_coalesce(mod, mod_access_store, stack->addr, stack);
		if (master_stack)
		{
			mod->coalesced_writes++;
			mod_coalesce(mod, master_stack, stack);
			mod_stack_wait_in_stack(stack, master_stack, EV_MOD_NMSI_STORE_FINISH);

			/* Increment witness variable */
			if (stack->witness_ptr)
				(*stack->witness_ptr)++;

			return;
		}

		/* Continue */
		esim_schedule_event(EV_MOD_NMSI_STORE_LOCK, stack, 0);
		return;
	}


	if (event == EV_MOD_NMSI_STORE_LOCK)
	{
		struct mod_stack_t *older_stack;

		mem_debug("  %lld %lld 0x%x %s store lock\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:store_lock\"\n",
			stack->id, mod->name);

		/* If there is any older access, wait for it */
		older_stack = stack->access_list_prev;
		if (older_stack)
		{
			mem_debug("    %lld wait for access %lld\n",
				stack->id, older_stack->id);
			mod_stack_wait_in_stack(stack, older_stack, EV_MOD_NMSI_STORE_LOCK);
			return;
		}

		/* Call find and lock */
		new_stack = mod_stack_create(stack->id, mod, stack->addr,
			EV_MOD_NMSI_STORE_ACTION, stack);
		new_stack->blocking = 1;
		new_stack->write = 1;
		new_stack->retry = stack->retry;
		new_stack->witness_ptr = stack->witness_ptr;
		esim_schedule_event(EV_MOD_NMSI_FIND_AND_LOCK, new_stack, 0);

		/* Set witness variable to NULL so that retries from the same
		 * stack do not increment it multiple times */
		stack->witness_ptr = NULL;

		return;
	}

	if (event == EV_MOD_NMSI_STORE_ACTION)
	{
		int retry_lat;

		mem_debug("  %lld %lld 0x%x %s store action\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:store_action\"\n",
			stack->id, mod->name);

		/* Error locking */
		if (stack->err)
		{
			mod->write_retries++;
			retry_lat = mod_get_retry_latency(mod);
			mem_debug("    lock error, retrying in %d cycles\n", retry_lat);
			stack->retry = 1;
			esim_schedule_event(EV_MOD_NMSI_STORE_LOCK, stack, retry_lat);
			return;
		}

		/* Hit - state=M/E */
		if (stack->state == cache_block_modified ||
			stack->state == cache_block_exclusive)
		{
			// It can only be E if this is the main memory
			if (stack->state == cache_block_exclusive)
				assert(mod->kind == mod_kind_main_memory);

			// Schedule the unlock
			esim_schedule_event(EV_MOD_NMSI_STORE_UNLOCK, stack, 0);

			return;
		}

		/* Miss - state=S/I/N */
		// we cannot have the owned state
		assert(stack->state != cache_block_owned);

		// Send a write request to update the lower level, 
		// and possibly the other sharers
		new_stack = mod_stack_create(stack->id, mod, stack->tag,
			EV_MOD_NMSI_STORE_UNLOCK, stack);
		new_stack->peer = mod_stack_set_peer(mod, stack->state);
		new_stack->target_mod = mod_get_low_mod(mod, stack->tag);
		new_stack->request_dir = mod_request_up_down;
		esim_schedule_event(EV_MOD_NMSI_WRITE_REQUEST, new_stack, 0);

		return;
	}

	if (event == EV_MOD_NMSI_STORE_UNLOCK)
	{
		int retry_lat;

		mem_debug("  %lld %lld 0x%x %s store unlock\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:store_unlock\"\n",
			stack->id, mod->name);

		/* Error in write request, unlock block and retry store. */
		if (stack->err)
		{
			mod->write_retries++;
			retry_lat = mod_get_retry_latency(mod);
			dir_entry_unlock(mod->dir, stack->set, stack->way);
			mem_debug("    lock error, retrying in %d cycles\n", retry_lat);
			stack->retry = 1;
			esim_schedule_event(EV_MOD_NMSI_STORE_LOCK, stack, retry_lat);
			return;
		}

		/* Update tag/state and unlock */
		cache_set_block(mod->cache, stack->set, stack->way,
			stack->tag, cache_block_modified);
		dir_entry_unlock(mod->dir, stack->set, stack->way);

		/* Impose the access latency before continuing */
		esim_schedule_event(EV_MOD_NMSI_STORE_FINISH, stack, 
			mod->latency);
		return;
	}

	if (event == EV_MOD_NMSI_STORE_FINISH)
	{
		mem_debug("%lld %lld 0x%x %s store finish\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:store_finish\"\n",
			stack->id, mod->name);
		mem_trace("mem.end_access name=\"A-%lld\"\n",
			stack->id);

		/* Return event queue element into event queue */
		if (stack->event_queue && stack->event_queue_item)
			linked_list_add(stack->event_queue, stack->event_queue_item);

		/* Free the mod_client_info object, if any */
		if (stack->client_info)
			mod_client_info_free(mod, stack->client_info);

		/* Finish access */
		mod_access_finish(mod, stack);

		/* Return */
		mod_stack_return(stack);
		return;
	}

	abort();
}

void mod_handler_nmsi_nc_store(int event, void *data)
{
	struct mod_stack_t *stack = data;
	struct mod_stack_t *new_stack;

	struct mod_t *mod = stack->mod;

	/* This activates the number of accesses in the MSHR through time */
	mem_access_record(mod->mshr_record,
			mod->access_list_count - mod->access_list_coalesced_count);

	if (event == EV_MOD_NMSI_NC_STORE)
	{
		struct mod_stack_t *master_stack;

		mem_debug("%lld %lld 0x%x %s nc store\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.new_access name=\"A-%lld\" type=\"nc_store\" "
			"state=\"%s:nc store\" addr=0x%x\n", stack->id, mod->name, stack->addr);

		if (mem_snap_period != 0)
		{
			assert(snapshot_store);
			long long cycle = esim_domain_cycle(mem_domain_index);

			snapshot_record(snapshot_store, cycle, stack->addr);

			if (cache_snapshot && !mod->snapshot_store)
			{
				char file[MAX_STRING_SIZE];
				snprintf(file, sizeof file,
						"%s_store", mod->name);
				mod->snapshot_store = snapshot_create(file);
			}
			snapshot_record(mod->snapshot_store, cycle, stack->addr);
		}

		/* Record access */
		mod_access_start(mod, stack, mod_access_nc_store);

		/* Coalesce access */
		master_stack = mod_can_coalesce(mod, mod_access_nc_store, stack->addr, stack);
		if (master_stack)
		{
			mod->coalesced_nc_writes++;
			mod_coalesce(mod, master_stack, stack);
			mod_stack_wait_in_stack(stack, master_stack, 
					EV_MOD_NMSI_NC_STORE_FINISH);
			return;
		}

		/* Next event */
		esim_schedule_event(EV_MOD_NMSI_NC_STORE_LOCK, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_NC_STORE_LOCK)
	{
		struct mod_stack_t *older_stack;

		mem_debug("  %lld %lld 0x%x %s nc store lock\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:nc_store_lock\"\n",
			stack->id, mod->name);

		/* If there is any older write, wait for it */
		older_stack = mod_in_flight_write(mod, stack);
		if (older_stack)
		{
			mem_debug("    %lld wait for write %lld\n", stack->id, 
					older_stack->id);
			mod_stack_wait_in_stack(stack, older_stack, 
					EV_MOD_NMSI_NC_STORE_LOCK);
			return;
		}

		/* If there is any older access to the same address that this 
		 * access could not be coalesced with, wait for it. */
		older_stack = mod_in_flight_address(mod, stack->addr, stack);
		if (older_stack)
		{
			mem_debug("    %lld wait for write %lld\n", stack->id, 
					older_stack->id);
			mod_stack_wait_in_stack(stack, older_stack, 
					EV_MOD_NMSI_NC_STORE_LOCK);
			return;
		}

		/* Call find and lock */
		new_stack = mod_stack_create(stack->id, mod, stack->addr,
			EV_MOD_NMSI_NC_STORE_WRITEBACK, stack);
		new_stack->blocking = 1;
		new_stack->nc_write = 1;
		new_stack->retry = stack->retry;
		esim_schedule_event(EV_MOD_NMSI_FIND_AND_LOCK, new_stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_NC_STORE_WRITEBACK)
	{
		int retry_lat;

		mem_debug("  %lld %lld 0x%x %s nc store writeback\n", esim_time,
				stack->id, stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:nc_store_writeback\"\n",
				stack->id, mod->name);

		/* Error locking */
		if (stack->err)
		{
			mod->nc_write_retries++;
			retry_lat = mod_get_retry_latency(mod);
			mem_debug("    lock error, retrying in %d cycles\n", 
					retry_lat);
			stack->retry = 1;
			esim_schedule_event(EV_MOD_NMSI_NC_STORE_LOCK, stack,
					retry_lat);
			return;
		}

		/* If the block has modified data, evict it so that the 
		 * lower-level cache will have the latest copy */
		assert(stack->state != cache_block_owned);
		if (stack->state == cache_block_modified) 
		{
			stack->eviction = 1;
			new_stack = mod_stack_create(stack->id, mod, 0,
					EV_MOD_NMSI_NC_STORE_ACTION, stack);
			new_stack->set = stack->set;
			new_stack->way = stack->way;
			esim_schedule_event(EV_MOD_NMSI_EVICT, new_stack, 0);
			return;
		}

		// For the rest of states N/S/I/ and E (main memory)
		esim_schedule_event(EV_MOD_NMSI_NC_STORE_ACTION, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_NC_STORE_ACTION)
	{
		int retry_lat;

		mem_debug("  %lld %lld 0x%x %s nc store action\n", esim_time, stack->id,
				stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:nc_store_action\"\n",
				stack->id, mod->name);

		/* Error locking */
		if (stack->err)
		{
			mod->nc_write_retries++;
			retry_lat = mod_get_retry_latency(mod);
			mem_debug("    lock error, retrying in %d cycles\n", retry_lat);
			stack->retry = 1;
			esim_schedule_event(EV_MOD_NMSI_NC_STORE_LOCK, stack, retry_lat);
			return;
		}

		/* Main memory modules are a special case */
		if (mod->kind == mod_kind_main_memory)
		{
			/* For non-coherent stores, finding an E or M for the state of
			 * a cache block in the directory still requires a message to 
			 * the lower-level module so it can update its owner field.
			 * These messages should not be sent if the module is a main
			 * memory module. */
			esim_schedule_event(EV_MOD_NMSI_NC_STORE_UNLOCK, stack, 0);
			return;
		}

		// If it was exclusive, it could have been only if the
		// cache was main memory, which previous condition takes
		// care of it. 
		assert(stack->state != cache_block_exclusive ||
				stack->state != cache_block_owned);

		/* N/S are hit */
		if (stack->state == cache_block_shared || 
				stack->state == cache_block_noncoherent)
		{
			esim_schedule_event(EV_MOD_NMSI_NC_STORE_UNLOCK, stack, 0);
		}
		/* Modified state needs to call read request because we've already
		 * evicted the block so that the lower-level cache will have 
		 * the latest value before it becomes non-coherent. Same as 
		 * Invalid state */
		else
		{
			new_stack = mod_stack_create(stack->id, mod, stack->tag,
					EV_MOD_NMSI_NC_STORE_MISS, stack);
			new_stack->peer = mod_stack_set_peer(mod, stack->state);
			new_stack->nc_write = 1;
			new_stack->target_mod = mod_get_low_mod(mod, stack->tag);
			new_stack->request_dir = mod_request_up_down;
			esim_schedule_event(EV_MOD_NMSI_READ_REQUEST, new_stack, 0);
		}

		return;
	}

	if (event == EV_MOD_NMSI_NC_STORE_MISS)
	{
		int retry_lat;

		mem_debug("  %lld %lld 0x%x %s nc store miss\n", esim_time, stack->id,
				stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:nc_store_miss\"\n",
				stack->id, mod->name);

		/* Error on read request. Unlock block and retry nc store. */
		if (stack->err)
		{
			mod->nc_write_retries++;
			retry_lat = mod_get_retry_latency(mod);
			dir_entry_unlock(mod->dir, stack->set, stack->way);
			mem_debug("    lock error, retrying in %d cycles\n", retry_lat);
			stack->retry = 1;
			esim_schedule_event(EV_MOD_NMSI_NC_STORE_LOCK, stack, retry_lat);
			return;
		}

		/* Continue */
		esim_schedule_event(EV_MOD_NMSI_NC_STORE_UNLOCK, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_NC_STORE_UNLOCK)
	{
		mem_debug("  %lld %lld 0x%x %s nc store unlock\n", esim_time, stack->id,
				stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:nc_store_unlock\"\n",
				stack->id, mod->name);

		/* Set block state to non-coherent.
		 * Also set the tag of the block. */
		cache_set_block(mod->cache, stack->set, stack->way, stack->tag,
				cache_block_noncoherent);

		/* Unlock directory entry */
		dir_entry_unlock(mod->dir, stack->set, stack->way);

		/* Impose the access latency before continuing */
		esim_schedule_event(EV_MOD_NMSI_NC_STORE_FINISH, stack, 
			mod->latency);
		return;
	}

	if (event == EV_MOD_NMSI_NC_STORE_FINISH)
	{
		mem_debug("%lld %lld 0x%x %s nc store finish\n", esim_time, stack->id,
				stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:nc_store_finish\"\n",
				stack->id, mod->name);
		mem_trace("mem.end_access name=\"A-%lld\"\n",
				stack->id);

		/* Increment witness variable */
		if (stack->witness_ptr)
			(*stack->witness_ptr)++;

		/* Return event queue element into event queue */
		if (stack->event_queue && stack->event_queue_item)
			linked_list_add(stack->event_queue, stack->event_queue_item);

		/* Free the mod_client_info object, if any */
		if (stack->client_info)
			mod_client_info_free(mod, stack->client_info);

		/* Finish access */
		mod_access_finish(mod, stack);

		/* Return */
		mod_stack_return(stack);
		return;
	}

	abort();
}

void mod_handler_nmsi_find_and_lock(int event, void *data)
{
	struct mod_stack_t *stack = data;
	struct mod_stack_t *ret = stack->ret_stack;
	struct mod_stack_t *new_stack;

	struct mod_t *mod = stack->mod;


	if (event == EV_MOD_NMSI_FIND_AND_LOCK)
	{
		mem_debug("  %lld %lld 0x%x %s find and lock (blocking=%d)\n",
				esim_time, stack->id, stack->addr, mod->name,
				stack->blocking);
		mem_trace("mem.access name=\"A-%lld\" "
				"state=\"%s:find_and_lock\"\n", stack->id, mod->name);

		/* Default return values */
		ret->err = 0;

		/* If this stack has already been assigned a way, 
		 * keep using it */
		stack->way = ret->way;

		/* Get a port */
		mod_lock_port(mod, stack, EV_MOD_NMSI_FIND_AND_LOCK_PORT);
		return;
	}

	if (event == EV_MOD_NMSI_FIND_AND_LOCK_PORT)
	{
		struct mod_port_t *port = stack->port;
		struct dir_lock_t *dir_lock;

		assert(stack->port);
		mem_debug("  %lld %lld 0x%x %s find and lock port\n", esim_time,
				stack->id, stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" "
				"state=\"%s:find_and_lock_port\"\n", stack->id,
				mod->name);

		/* Set parent stack flag expressing that port has already been locked.
		 * This flag is checked by new writes to find out if it is already too
		 * late to coalesce. */
		ret->port_locked = 1;

		/* Look for block. */
		stack->hit = mod_find_block(mod, stack->addr, &stack->set,
			&stack->way, &stack->tag, &stack->state);

		/* Debug */
		if (stack->hit)
		{
			mem_debug("    %lld 0x%x %s hit: set=%d, way=%d, state=%s\n", stack->id,
				stack->tag, mod->name, stack->set, stack->way,
				str_map_value(&cache_block_state_map, stack->state));
		}

		/* Statistics */
		mod->accesses++;
		if (stack->hit)
			mod->hits++;

		if (stack->read)
		{
			mod->reads++;
			mod->effective_reads++;
			stack->blocking ? mod->blocking_reads++ : mod->non_blocking_reads++;
			if (stack->hit)
				mod->read_hits++;
		}
		else if (stack->nc_write)  /* Must go after read */
		{
			mod->nc_writes++;
			mod->effective_nc_writes++;
			stack->blocking ? mod->blocking_nc_writes++ : mod->non_blocking_nc_writes++;
			if (stack->hit)
				mod->nc_write_hits++;
		}
		else if (stack->write)
		{
			mod->writes++;
			mod->effective_writes++;
			stack->blocking ? mod->blocking_writes++ : mod->non_blocking_writes++;

			/* Increment witness variable when port is locked */
			if (stack->witness_ptr)
			{
				(*stack->witness_ptr)++;
				stack->witness_ptr = NULL;
			}

			if (stack->hit)
				mod->write_hits++;
		}
		else if (stack->message)
		{
			/* FIXME */
		}
		else 
		{
			fatal("Unknown memory operation type");
		}

		if (!stack->retry)
		{
			mod->no_retry_accesses++;
			if (stack->hit)
				mod->no_retry_hits++;
			
			if (stack->read)
			{
				mod->no_retry_reads++;
				if (stack->hit)
					mod->no_retry_read_hits++;
			}
			else if (stack->nc_write)  /* Must go after read */
			{
				mod->no_retry_nc_writes++;
				if (stack->hit)
					mod->no_retry_nc_write_hits++;
			}
			else if (stack->write)
			{
				mod->no_retry_writes++;
				if (stack->hit)
					mod->no_retry_write_hits++;
			}
			else if (stack->message)
			{
				/* FIXME */
			}
			else 
			{
				fatal("Unknown memory operation type");
			}
		}

		if (!stack->hit)
		{
			/* Find victim */
			if (stack->way < 0) 
			{
				stack->way = cache_replace_block(mod->cache, 
						stack->set);
			}
		}
		assert(stack->way >= 0);

		/* If directory entry is locked and the call to FIND_AND_LOCK 
		 * is not blocking, release port and return error. */
		dir_lock = dir_lock_get(mod->dir, stack->set, stack->way);
		if (dir_lock->lock && !stack->blocking)
		{
			mem_debug("    %lld 0x%x %s block locked at set=%d, "
					"way=%d by A-%lld - aborting\n",
					stack->id, stack->tag, mod->name, stack->set,
					stack->way, dir_lock->stack_id);
			ret->err = 1;
			mod_unlock_port(mod, port, stack);
			ret->port_locked = 0;
			mod_stack_return(stack);
			return;
		}

		/* Lock directory entry. If lock fails, port needs to be 
		 * released to prevent deadlock.  When the directory entry 
		 * is released, locking port and directory entry will be 
		 * retried. */
		if (!dir_entry_lock(mod->dir, stack->set, stack->way, 
				EV_MOD_NMSI_FIND_AND_LOCK, stack))
		{
			mem_debug("    %lld 0x%x %s block locked at set=%d, "
					"way=%d by A-%lld - waiting\n", stack->id,
					stack->tag, mod->name, stack->set, stack->way,
					dir_lock->stack_id);
			mod_unlock_port(mod, port, stack);
			ret->port_locked = 0;
			return;
		}

		/* Miss */
		if (!stack->hit)
		{
			/* Find victim */
			cache_get_block(mod->cache, stack->set, stack->way, 
					NULL, &stack->state);
			assert(stack->state || 
					!dir_entry_group_shared_or_owned(mod->dir,
							stack->set, stack->way));
			mem_debug("    %lld 0x%x %s miss -> lru: set=%d, "
					"way=%d, state=%s\n", stack->id, stack->tag,
					mod->name, stack->set, stack->way,
					str_map_value(&cache_block_state_map,
							stack->state));
		}


		/* Entry is locked. Record the transient tag so that a 
		 * subsequent lookup detects that the block is being brought.
		 * Also, update LRU counters here. */
		cache_set_transient_tag(mod->cache, stack->set, stack->way, 
				stack->tag);
		cache_access_block(mod->cache, stack->set, stack->way);

		/* Access latency */
		esim_schedule_event(EV_MOD_NMSI_FIND_AND_LOCK_ACTION, stack, mod->dir_latency);
		return;
	}

	if (event == EV_MOD_NMSI_FIND_AND_LOCK_ACTION)
	{
		struct mod_port_t *port = stack->port;

		assert(port);
		mem_debug("  %lld %lld 0x%x %s find and lock action\n", 
				esim_time, stack->id, stack->tag, mod->name);
		mem_trace("mem.access name=\"A-%lld\" "
				"state=\"%s:find_and_lock_action\"\n",
				stack->id, mod->name);

		/* Release port */
		mod_unlock_port(mod, port, stack);
		ret->port_locked = 0;

		/* On miss, evict if victim is a valid block. */
		if (!stack->hit && stack->state)
		{
			stack->eviction = 1;
			new_stack = mod_stack_create(stack->id, mod, 0,
				EV_MOD_NMSI_FIND_AND_LOCK_FINISH, stack);
			new_stack->set = stack->set;
			new_stack->way = stack->way;
			esim_schedule_event(EV_MOD_NMSI_EVICT, new_stack, 0);
			return;
		}

		/* Continue */
		esim_schedule_event(EV_MOD_NMSI_FIND_AND_LOCK_FINISH, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_FIND_AND_LOCK_FINISH)
	{
		mem_debug("  %lld %lld 0x%x %s find and lock finish (err=%d)\n", esim_time, stack->id,
			stack->tag, mod->name, stack->err);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:find_and_lock_finish\"\n",
			stack->id, mod->name);

		/* If evict produced err, return err */
		if (stack->err)
		{
			cache_get_block(mod->cache, stack->set, stack->way, NULL, &stack->state);
			assert(stack->state);
			assert(stack->eviction);
			ret->err = 1;
			dir_entry_unlock(mod->dir, stack->set, stack->way);
			mod_stack_return(stack);
			return;
		}

		/* Eviction */
		if (stack->eviction)
		{
			mod->evictions++;
			cache_get_block(mod->cache, stack->set, stack->way, NULL, &stack->state);
			/* FIXME should debug the stack state. Make sure it is invalid,
			 * shared, or exclusive */
			assert(!stack->state);
		}

		/* If this is a main memory, the block is here. A previous miss
		 * was just a miss in the directory. */
		if (mod->kind == mod_kind_main_memory && !stack->state)
		{
			stack->state = cache_block_exclusive;
			cache_set_block(mod->cache, stack->set, stack->way,
					stack->tag, stack->state);
		}

		/* Return */
		ret->err = 0;
		ret->set = stack->set;
		ret->way = stack->way;
		ret->state = stack->state;
		ret->tag = stack->tag;
		mod_stack_return(stack);
		return;
	}

	abort();
}


void mod_handler_nmsi_evict(int event, void *data)
{
	struct mod_stack_t *stack = data;
	struct mod_stack_t *ret = stack->ret_stack;
	struct mod_stack_t *new_stack;

	struct mod_t *mod = stack->mod;
	struct mod_t *target_mod = stack->target_mod;

	struct dir_t *dir;
	struct dir_entry_t *dir_entry;

	uint32_t dir_entry_tag, z;


	if (event == EV_MOD_NMSI_EVICT)
	{
		/* Default return value */
		ret->err = 0;

		/* Get block info */
		cache_get_block(mod->cache, stack->set, stack->way, &stack->tag,
				&stack->state);
		assert(stack->state || !dir_entry_group_shared_or_owned(
				mod->dir, stack->set, stack->way));
		mem_debug("  %lld %lld 0x%x %s evict (set=%d, way=%d, state=%s)\n", 
				esim_time, stack->id, stack->tag, mod->name, stack->set,
				stack->way,
				str_map_value(&cache_block_state_map, stack->state));
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:evict\"\n",
				stack->id, mod->name);

		/* Save some data */
		stack->src_set = stack->set;
		stack->src_way = stack->way;
		stack->src_tag = stack->tag;
		stack->target_mod = mod_get_low_mod(mod, stack->tag);

		/* Send write request to all sharers */
		new_stack = mod_stack_create(stack->id, mod, 0, 
				EV_MOD_NMSI_EVICT_INVALID, stack);
		new_stack->except_mod = NULL;
		new_stack->set = stack->set;
		new_stack->way = stack->way;
		esim_schedule_event(EV_MOD_NMSI_INVALIDATE, new_stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_EVICT_INVALID)
	{
		mem_debug("  %lld %lld 0x%x %s evict invalid\n", esim_time, 
				stack->id, stack->tag, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:evict_invalid\"\n",
				stack->id, mod->name);

		/* FIXME we should Update the cache state since it may have changed after its 
		 * higher-level modules were invalidated */	
		cache_get_block(mod->cache, stack->set, stack->way, NULL, &stack->state);

		/* If module is main memory, we just need to set the block 
		 * as invalid, and finish. */
		if (mod->kind == mod_kind_main_memory)
		{
			cache_set_block(mod->cache, stack->src_set, 
					stack->src_way, 0, cache_block_invalid);
			esim_schedule_event(EV_MOD_NMSI_EVICT_FINISH, 
					stack, 0);
			return;
		}

		// XXX Dana, if state is invalid (happens during invalidate?)
		// just skip to FINISH also?
		/* Just set the block to invalid if there is no data to
		 * return, and let the protocol deal with catching up later */ 
		assert(stack->state != cache_block_exclusive);
		if (mod->kind == mod_kind_cache &&
				(stack->state == cache_block_shared))

		{
			cache_set_block(mod->cache, stack->src_set,
					stack->src_way, 0, cache_block_invalid);
			stack->state = cache_block_invalid;
			esim_schedule_event(EV_MOD_NMSI_EVICT_FINISH,
					stack, 0);
			return;
		}

		/* Continue */
		esim_schedule_event(EV_MOD_NMSI_EVICT_ACTION, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_EVICT_ACTION)
	{
		int msg_size;

		mem_debug("  %lld %lld 0x%x %s evict action\n", esim_time, stack->id,
			stack->tag, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:evict_action\"\n",
			stack->id, mod->name);

		/* Get low mod */
		struct mod_t *low_mod;

		low_mod = stack->target_mod;
		assert(low_mod != mod);
		assert(low_mod == mod_get_low_mod(mod, stack->tag));

		/* Update the cache state since it may have changed after its 
		 * higher-level modules were invalidated */
		cache_get_block(mod->cache, stack->set, stack->way, NULL, &stack->state);
		
		/* State = I */
		if (stack->state == cache_block_invalid)
		{
			esim_schedule_event(EV_MOD_NMSI_EVICT_FINISH, 
					stack, 0);
			return;
		}

		/* If state is M/O/N, data must be sent to lower level mod */
		assert(stack->state != cache_block_owned);
		if (stack->state == cache_block_modified || 
				stack->state == cache_block_noncoherent)
		{
			/* Need to transmit data to low module */
			msg_size = 8 + mod->block_size;
			stack->reply = reply_ack_data;
		}
		// State S shouldn't happen since we just set that to finish
		// in the Action_invalid  
		else 
		{
			fatal("%s: Invalid cache block: %s\n", 
					__FUNCTION__, 
					str_map_value(&cache_block_state_map, 
					stack->state));
		}

		/* Get low node */
		struct net_node_t *src_node = NULL;
		struct net_node_t *dst_node;

		if (!mem_multinet || (mem_multinet && !mod->low_net_node_signal)|| msg_size > 8)
		{
			src_node = mod->low_net_node;
			dst_node = low_mod->high_net_node;
			assert(dst_node && dst_node->user_data == low_mod);
		}
		else
		{
			src_node = mod->low_net_node_signal;
			assert(low_mod->high_net_node_signal);
			dst_node = low_mod->high_net_node_signal;
			assert(dst_node && dst_node->user_data == low_mod);
		}

		/* Send message */
		stack->msg = net_try_send_ev(mod->low_net, src_node,
				dst_node, msg_size, EV_MOD_NMSI_EVICT_RECEIVE, stack, event, stack);
		if (stack->msg)
			net_trace("net.msg_access net=\"%s\" name=\"M-%lld\" access=\"A-%lld\"\n",
					mod->low_net->name, stack->msg->id, stack->id);
		return;
	}

	if (event == EV_MOD_NMSI_EVICT_RECEIVE)
	{
		mem_debug("  %lld %lld 0x%x %s evict receive (state = %s) \n", esim_time, 
				stack->id, stack->tag, target_mod->name, 
				 str_map_value(&cache_block_state_map, stack->state));
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:evict_receive\"\n",
				stack->id, target_mod->name);

		/* Receive message */
		net_receive(target_mod->high_net, target_mod->high_net_node, stack->msg);

		/* Find and lock */
		if (stack->state == cache_block_noncoherent)
		{
			new_stack = mod_stack_create(stack->id, target_mod, 
					stack->src_tag,
					EV_MOD_NMSI_EVICT_PROCESS_NONCOHERENT, stack);
		}
		else 
		{
			new_stack = mod_stack_create(stack->id, target_mod, 
					stack->src_tag, EV_MOD_NMSI_EVICT_PROCESS,
					stack);
		}

		/* FIXME It's not guaranteed to be a write */
		new_stack->blocking = 0;
		new_stack->write = 1;
		new_stack->retry = 0;
		esim_schedule_event(EV_MOD_NMSI_FIND_AND_LOCK, new_stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_EVICT_PROCESS)
	{
		mem_debug("  %lld %lld 0x%x %s evict process (state = %s) \n", esim_time, 
				stack->id, stack->tag, target_mod->name,
				str_map_value(&cache_block_state_map, stack->state));
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:evict_process\"\n",
				stack->id, target_mod->name);

		/* Error locking block */
		if (stack->err)
		{
			ret->err = 1;
			esim_schedule_event(EV_MOD_NMSI_EVICT_REPLY, 
					stack, 0);
			return;
		}

		/* If data was received, set the block to modified */
		if (stack->reply == reply_ack)
		{
			fatal("%s: We shouldn't send ack. Something wrong: "
					" state %s\n", 
					__FUNCTION__, 
					str_map_value(&cache_block_state_map, 
					stack->state));
		}
		else if (stack->reply == reply_ack_data)
		{
			if (stack->state == cache_block_exclusive)
			{
				assert(target_mod->kind == mod_kind_main_memory);
			}
			else if (stack->state == cache_block_shared)
			{
				// This is the costly part of MSI vs MOESI
				// get the low mod of the target
				// Send a write-request to that mod to update
				// its data
				new_stack = mod_stack_create(stack->id, target_mod, 
						stack->tag,
						EV_MOD_NMSI_EVICT_PROCESS_FINISH,
						stack);
				new_stack->peer = mod_stack_set_peer(mod, stack->state);
				new_stack->target_mod = mod_get_low_mod(target_mod, 
						stack->tag);
				new_stack->request_dir = mod_request_up_down;
				esim_schedule_event(EV_MOD_NMSI_WRITE_REQUEST,
						new_stack, 0);

				return;
			}
			else if (stack->state == cache_block_modified)
			{
				/* Nothing to do */
			}
			else
			{
				fatal("%s: Invalid cache block state 1: %s\n", 
						__FUNCTION__, 
						str_map_value(&cache_block_state_map, stack->state));
			}
		}
		else 
		{
			fatal("%s: Invalid cache reply: %d\n", 
					__FUNCTION__, stack->reply);
		}

		/* Continue */
		esim_schedule_event(EV_MOD_NMSI_EVICT_PROCESS_FINISH, stack, 0);
		return;
	}
	
	if (event == EV_MOD_NMSI_EVICT_PROCESS_FINISH)
	{
		// After the return, no matter how we get here, the state
		// of the target should become modified
		cache_set_block(target_mod->cache, stack->set, stack->way, 
				stack->tag, cache_block_modified);
		
		/* Remove sharer and owner */
		dir = target_mod->dir;
		for (z = 0; z < dir->zsize; z++)
		{
			/* Skip other subblocks */
			dir_entry_tag = stack->tag + 
					z * target_mod->sub_block_size;
			assert(dir_entry_tag < stack->tag + 
					target_mod->block_size);
			if (dir_entry_tag < stack->src_tag || 
					dir_entry_tag >= stack->src_tag +
					mod->block_size)
			{
				continue;
			}

			dir_entry = dir_entry_get(dir, stack->set, 
					stack->way, z);
			dir_entry_clear_sharer(dir, stack->set, stack->way, z, 
					mod->low_net_node->index);
			if (dir_entry->owner == mod->low_net_node->index)
			{
				dir_entry_set_owner(dir, stack->set, stack->way,
						z, DIR_ENTRY_OWNER_NONE);
			}
		}

		/* Unlock the directory entry */
		dir = target_mod->dir;
		dir_entry_unlock(dir, stack->set, stack->way);

		esim_schedule_event(EV_MOD_NMSI_EVICT_REPLY, stack, target_mod->latency);
		return;
	}

	if (event == EV_MOD_NMSI_EVICT_PROCESS_NONCOHERENT)
	{
		mem_debug("  %lld %lld 0x%x %s evict process noncoherent\n", 
				esim_time, stack->id, stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:evict_process_noncoherent\"\n",
				stack->id, target_mod->name);

		/* Error locking block */
		if (stack->err)
		{
			ret->err = 1;
			esim_schedule_event(EV_MOD_NMSI_EVICT_REPLY, stack, 0);
			return;
		}

		/* If data was received, set the block to modified */
		if (stack->reply == reply_ack_data)
		{
			if (stack->state == cache_block_exclusive)
			{
				assert(target_mod->kind == mod_kind_main_memory);
				cache_set_block(target_mod->cache, stack->set, stack->way, 
						stack->tag, cache_block_modified);
			}
			else if (stack->state == cache_block_modified)
			{
				/* Nothing to do */
			}
			else if (stack->state == cache_block_shared ||
					stack->state == cache_block_noncoherent)
			{
				cache_set_block(target_mod->cache, stack->set, stack->way, 
						stack->tag, cache_block_noncoherent);
			}
			else
			{
				fatal("%s: Invalid cache block state 0: %d\n", __FUNCTION__, 
						stack->state);
			}
		}
		else 
		{
			fatal("%s: Invalid cache reply: %d\n", __FUNCTION__, 
					stack->reply);
		}

		/* Remove sharer and owner */
		dir = target_mod->dir;
		for (z = 0; z < dir->zsize; z++)
		{
			/* Skip other subblocks */
			dir_entry_tag = stack->tag + z * target_mod->sub_block_size;
			assert(dir_entry_tag < stack->tag + target_mod->block_size);
			if (dir_entry_tag < stack->src_tag || 
					dir_entry_tag >= stack->src_tag + mod->block_size)
			{
				continue;
			}

			dir_entry = dir_entry_get(dir, stack->set, stack->way, z);
			dir_entry_clear_sharer(dir, stack->set, stack->way, z, 
					mod->low_net_node->index);
			if (dir_entry->owner == mod->low_net_node->index)
			{
				dir_entry_set_owner(dir, stack->set, stack->way, z, 
						DIR_ENTRY_OWNER_NONE);
			}
		}

		/* Unlock the directory entry */
		dir = target_mod->dir;
		dir_entry_unlock(dir, stack->set, stack->way);

		esim_schedule_event(EV_MOD_NMSI_EVICT_REPLY, stack, target_mod->latency);
		return;
	}

	if (event == EV_MOD_NMSI_EVICT_REPLY)
	{
		mem_debug("  %lld %lld 0x%x %s evict reply\n", esim_time, stack->id,
				stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:evict_reply\"\n",
				stack->id, target_mod->name);

		struct net_node_t *src_node;
		struct net_node_t *dst_node;
		/* Send message */
		if (!mem_multinet || (mem_multinet && !target_mod->high_net_node_signal))
		{
			src_node = target_mod->high_net_node;
			dst_node = mod->low_net_node;
		}
		else
		{
			src_node = target_mod->high_net_node_signal;
			assert(mod->low_net_node_signal);
			dst_node = mod->low_net_node_signal;
		}

		stack->msg = net_try_send_ev(target_mod->high_net, src_node,
				dst_node, 8, EV_MOD_NMSI_EVICT_REPLY_RECEIVE, stack,
				event, stack);
		if (stack->msg)
			net_trace("net.msg_access net=\"%s\" name=\"M-%lld\" access=\"A-%lld\"\n",
					target_mod->high_net->name, stack->msg->id, stack->id);
		return;

	}

	if (event == EV_MOD_NMSI_EVICT_REPLY_RECEIVE)
	{
		mem_debug("  %lld %lld 0x%x %s evict reply receive\n", esim_time, stack->id,
				stack->tag, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:evict_reply_receive\"\n",
				stack->id, mod->name);

		/* Receive message */
		net_receive(mod->low_net, mod->low_net_node, stack->msg);

		/* Invalidate block if there was no error. */
		if (!stack->err)
			cache_set_block(mod->cache, stack->src_set, stack->src_way,
					0, cache_block_invalid);

		assert(!dir_entry_group_shared_or_owned(mod->dir, stack->src_set, stack->src_way));
		esim_schedule_event(EV_MOD_NMSI_EVICT_FINISH, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_EVICT_FINISH)
	{
		mem_debug("  %lld %lld 0x%x %s evict finish\n", esim_time, stack->id,
				stack->tag, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:evict_finish\"\n",
				stack->id, mod->name);

		mod_stack_return(stack);
		return;
	}

	abort();
}


void mod_handler_nmsi_read_request(int event, void *data)
{
	struct mod_stack_t *stack = data;
	struct mod_stack_t *ret = stack->ret_stack;
	struct mod_stack_t *new_stack;

	struct mod_t *mod = stack->mod;
	struct mod_t *target_mod = stack->target_mod;

	struct dir_t *dir;
	struct dir_entry_t *dir_entry;

	uint32_t dir_entry_tag, z;

	if (event == EV_MOD_NMSI_READ_REQUEST)
	{
		struct net_t *net;
		struct net_node_t *src_node;
		struct net_node_t *dst_node;

		mem_debug("  %lld %lld 0x%x %s read request\n", esim_time, stack->id,
				stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:read_request\"\n",
				stack->id, mod->name);

		/* Default return values*/
		ret->shared = 0;
		ret->err = 0;

		/* Checks */
		assert(stack->request_dir);
		assert(mod_get_low_mod(mod, stack->addr) == target_mod ||
				stack->request_dir == mod_request_down_up);
		assert(mod_get_low_mod(target_mod, stack->addr) == mod ||
				stack->request_dir == mod_request_up_down);

		/* Get source and destination nodes */
		if (stack->request_dir == mod_request_up_down)
		{
			net = mod->low_net;

			if (!mem_multinet || (mem_multinet && !mod->low_net_node_signal))
			{
				src_node = mod->low_net_node;
				dst_node = target_mod->high_net_node;
			}
			else
			{
				src_node = mod->low_net_node_signal;
				dst_node = target_mod->high_net_node_signal;
				assert(dst_node);
			}
		}
		else
		{
			net = mod->high_net;
			if (!mem_multinet || (mem_multinet && !mod->high_net_node_signal))
			{
				src_node = mod->high_net_node;
				dst_node = target_mod->low_net_node;
			}
			else
			{
				src_node = mod->high_net_node_signal;
				dst_node = target_mod->low_net_node_signal;
				assert(dst_node);
			}
		}

		/* Send message */
		stack->msg = net_try_send_ev(net, src_node, dst_node, 8,
				EV_MOD_NMSI_READ_REQUEST_RECEIVE, stack, event, stack);
		if (stack->msg)
			net_trace("net.msg_access net=\"%s\" name=\"M-%lld\" access=\"A-%lld\"\n",
					net->name, stack->msg->id, stack->id);
		return;
	}

	if (event == EV_MOD_NMSI_READ_REQUEST_RECEIVE)
	{
		mem_debug("  %lld %lld 0x%x %s read request receive\n", 
				esim_time, stack->id, stack->addr, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:read_request_receive\"\n",
				stack->id, target_mod->name);

		/* Receive message */
		if (stack->request_dir == mod_request_up_down)
			net_receive(target_mod->high_net, 
					target_mod->high_net_node, stack->msg);
		else
			net_receive(target_mod->low_net, target_mod->low_net_node, stack->msg);
		
		/* TODO Read requests should always be able to be blocking.  
		 * It's impossible to get into a livelock situation because we 
		 * only need to hit and not have ownership.  We would never 
		 * cross paths with a request coming down-up because we would
		 * hit before that. */
		/* Find and lock */
		new_stack = mod_stack_create(stack->id, target_mod, stack->addr,
			EV_MOD_NMSI_READ_REQUEST_ACTION, stack);
		new_stack->blocking = stack->request_dir == mod_request_down_up;
		new_stack->read = 1;
		new_stack->retry = 0;
		esim_schedule_event(EV_MOD_NMSI_FIND_AND_LOCK, new_stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_READ_REQUEST_ACTION)
	{
		mem_debug("  %lld %lld 0x%x %s read request action\n", 
				esim_time, stack->id, stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:read_request_action\"\n",
				stack->id, target_mod->name);

		/* Check block locking error. If read request is down-up, 
		 * there should not have been any error while locking. */
		if (stack->err)
		{
			assert(stack->request_dir == mod_request_up_down);
			ret->err = 1;
			mod_stack_set_reply(ret, reply_ack_error);
			stack->reply_size = 8;
			esim_schedule_event(EV_MOD_NMSI_READ_REQUEST_REPLY, 
					stack, 0);
			return;
		}
		esim_schedule_event(stack->request_dir == mod_request_up_down ?
				EV_MOD_NMSI_READ_REQUEST_UPDOWN :
				EV_MOD_NMSI_READ_REQUEST_DOWNUP, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_READ_REQUEST_UPDOWN)
	{
		struct mod_t *owner;

		mem_debug("  %lld %lld 0x%x %s read request updown\n", 
				esim_time, stack->id, stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:read_request_updown\"\n",
				stack->id, target_mod->name);

		stack->pending = 1;

		/* Set the initial reply message and size.  This will be 
		 * adjusted later if a transfer occur between peers. */
		stack->reply_size = mod->block_size + 8;
		mod_stack_set_reply(stack, reply_ack_data);

		if (stack->state)
		{
			// Target state can be E only if it is a main memory
			if (stack->state == cache_block_exclusive)
				assert(target_mod->kind == mod_kind_main_memory); 

			/* Status = M/S/N
			 * Check: address is a multiple of requester's block_size
			 * Check: no sub-block requested by mod is already owned by mod */
			assert(stack->addr % mod->block_size == 0);
			dir = target_mod->dir;
			for (z = 0; z < dir->zsize; z++)
			{
				dir_entry_tag = stack->tag + z * target_mod->sub_block_size;
				assert(dir_entry_tag < stack->tag + target_mod->block_size);
				if (dir_entry_tag < stack->addr || dir_entry_tag >= stack->addr + mod->block_size)
					continue;
				dir_entry = dir_entry_get(dir, stack->set, stack->way, z);
				assert(dir_entry->owner != mod->low_net_node->index);
			}

			/* TODO If there is only sharers, should one of them
			 *      send the data to mod instead of having target_mod do it? */

			/* Send read request to owners other than mod for all sub-blocks. */
			for (z = 0; z < dir->zsize; z++)
			{
				struct net_node_t *node;

				dir_entry = dir_entry_get(dir, stack->set, 
						stack->way, z);
				dir_entry_tag = stack->tag + 
						z * target_mod->sub_block_size;

				/* No owner */
				if (!DIR_ENTRY_VALID_OWNER(dir_entry))
					continue;

				/* Owner is mod */
				if (dir_entry->owner == mod->low_net_node->index)
					continue;

				/* Get owner mod */
				node = list_get(target_mod->high_net->node_list, 
						dir_entry->owner);

				/* Owner is the mod but it is upper level */
				/* Owner is always set by the lown_net_node->index)
				so the following seems redundant, and also dangerous
				if ((mem_shared_net) && 
					(dir_entry->owner == mod->high_net_node->index))
					continue;
*/
				assert(node->kind == net_node_end);
				owner = node->user_data;
				assert(owner);

				/* Not the first sub-block */
				if (dir_entry_tag % owner->block_size)
					continue;

				/* Send read request */
				stack->pending++;
				new_stack = mod_stack_create(stack->id, 
						target_mod, dir_entry_tag,
						EV_MOD_NMSI_READ_REQUEST_UPDOWN_FINISH,
						stack);

				/* Only set peer if its a subblock that was 
				 * requested */
				if (dir_entry_tag >= stack->addr && 
						dir_entry_tag < stack->addr +
						mod->block_size)
				{
					new_stack->peer = mod_stack_set_peer(
							mod, stack->state);
				}
				new_stack->target_mod = owner;
				new_stack->request_dir = mod_request_down_up;
				esim_schedule_event(EV_MOD_NMSI_READ_REQUEST,
						new_stack, 0);
			}
			esim_schedule_event(EV_MOD_NMSI_READ_REQUEST_UPDOWN_FINISH, 
					stack, 0);

		}
		else
		{
			/* State = I */
			assert(!dir_entry_group_shared_or_owned(target_mod->dir,
					stack->set, stack->way));
			new_stack = mod_stack_create(stack->id, target_mod, 
					stack->tag,
					EV_MOD_NMSI_READ_REQUEST_UPDOWN_MISS, stack);
			/* Peer is NULL since we keep going up-down */
			new_stack->target_mod = mod_get_low_mod(target_mod, 
					stack->tag);
			new_stack->request_dir = mod_request_up_down;
			esim_schedule_event(EV_MOD_NMSI_READ_REQUEST, 
					new_stack, 0);

		}
		return;
	}

	if (event == EV_MOD_NMSI_READ_REQUEST_UPDOWN_MISS)
	{
		mem_debug("  %lld %lld 0x%x %s read request updown miss\n", esim_time, stack->id,
				stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:read_request_updown_miss\"\n",
				stack->id, target_mod->name);

		/* Check error */
		if (stack->err)
		{
			dir_entry_unlock(target_mod->dir, stack->set, stack->way);
			ret->err = 1;
			mod_stack_set_reply(ret, reply_ack_error);
			stack->reply_size = 8;
			esim_schedule_event(EV_MOD_NMSI_READ_REQUEST_REPLY, stack, 0);
			return;
		}

		/* Set block state to excl/shared depending on the return value 'shared'
		 * that comes from a read request into the next cache level.
		 * Also set the tag of the block. */
		// This happens only if the state was invalid. The main memory
		// cannot have a invalid state. 
		cache_set_block(target_mod->cache, stack->set, stack->way, stack->tag,
				cache_block_shared);
		esim_schedule_event(EV_MOD_NMSI_READ_REQUEST_UPDOWN_FINISH, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_READ_REQUEST_UPDOWN_FINISH)
	{
		int shared;

		/* Ensure that a reply was received */
		assert(stack->reply);

		/* Ignore while pending requests */
		assert(stack->pending > 0);
		stack->pending--;
		if (stack->pending)
			return;

		/* Trace */
		mem_debug("  %lld %lld 0x%x %s read request updown finish\n", esim_time, stack->id,
				stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:read_request_updown_finish\"\n",
				stack->id, target_mod->name);

		/* If blocks were sent directly to the peer, the reply size would
		 * have been decreased.  Based on the final size, we can tell whether
		 * to send more data or simply ack */
		if (stack->reply_size == 8) 
		{
			mod_stack_set_reply(ret, reply_ack);
		}
		else if (stack->reply_size > 8)
		{
			mod_stack_set_reply(ret, reply_ack_data);
		}
		else 
		{
			fatal("Invalid reply size: %d", stack->reply_size);
		}

		dir = target_mod->dir;

		// Shared is set to one since there is no exclusive state anymore
		// Still we set it to 0 so it gets set later correctly,
		// avoiding the M state
		shared = 0;

		// There is no Owned state, so 
		// Set owner to 0 for all directory entries not owned by mod.
		for (z = 0; z < dir->zsize; z++)
		{
			dir_entry = dir_entry_get(dir, stack->set, stack->way, z);
			if (dir_entry->owner != mod->low_net_node->index)
				dir_entry_set_owner(dir, stack->set, stack->way, z, 
						DIR_ENTRY_OWNER_NONE);
		}

		/* For each sub-block requested by mod, set mod as sharer, and
		 * check whether there is other cache sharing it. */
		for (z = 0; z < dir->zsize; z++)
		{
			dir_entry_tag = stack->tag + z * target_mod->sub_block_size;
			if (dir_entry_tag < stack->addr || dir_entry_tag >= stack->addr + mod->block_size)
				continue;
			dir_entry = dir_entry_get(dir, stack->set, stack->way, z);
			dir_entry_set_sharer(dir, stack->set, stack->way, z, mod->low_net_node->index);
			if (dir_entry->num_sharers > 1 || stack->nc_write || stack->shared)
				shared = 1;

			/* If the block is non-coherent, or shared,  
			 * mod (the higher-level cache) should never be exclusive */
			assert(stack->state != cache_block_owned);
			if (stack->state == cache_block_noncoherent ||
					stack->state == cache_block_shared )
				shared = 1;
		}

		/* If no sub-block requested by mod is shared by other cache, set mod
		 * as owner of all of them. Otherwise, notify requester that the block is
		 * shared by setting the 'shared' return value to true. */
		ret->shared = shared;
		if (!shared)
		{
			for (z = 0; z < dir->zsize; z++)
			{
				dir_entry_tag = stack->tag + z * target_mod->sub_block_size;
				if (dir_entry_tag < stack->addr || dir_entry_tag >= stack->addr + mod->block_size)
					continue;
				dir_entry = dir_entry_get(dir, stack->set, stack->way, z);
				dir_entry_set_owner(dir, stack->set, stack->way, z, mod->low_net_node->index);
			}
		}

		dir_entry_unlock(dir, stack->set, stack->way);

		int latency = stack->reply == reply_ack_data_sent_to_peer ? 0 : target_mod->latency;
		esim_schedule_event(EV_MOD_NMSI_READ_REQUEST_REPLY, stack, latency);
		return;
	}

	if (event == EV_MOD_NMSI_READ_REQUEST_DOWNUP)
	{
		struct mod_t *owner;

		mem_debug("  %lld %lld 0x%x %s read request downup\n", esim_time, stack->id,
			stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:read_request_downup\"\n",
				stack->id, target_mod->name);

		/* Check: state must not be invalid or shared.
		 * By default, only one pending request.
		 * Response depends on state. */
		assert(stack->state != cache_block_invalid);
		assert(stack->state != cache_block_shared);
		assert(stack->state != cache_block_noncoherent);
		stack->pending = 1;

		/* Send a read request to the owner of each subblock. */
		dir = target_mod->dir;
		for (z = 0; z < dir->zsize; z++)
		{
			struct net_node_t *node;

			dir_entry_tag = stack->tag + 
					z * target_mod->sub_block_size;
			assert(dir_entry_tag < 
					stack->tag + target_mod->block_size);
			dir_entry = dir_entry_get(dir, stack->set, 
					stack->way, z);

			/* No owner */
			if (!DIR_ENTRY_VALID_OWNER(dir_entry))
				continue;

			/* Get owner mod */
			node = list_get(target_mod->high_net->node_list, 
					dir_entry->owner);
			assert(node && node->kind == net_node_end);
			owner = node->user_data;

			/* Not the first sub-block */
			if (dir_entry_tag % owner->block_size)
				continue;

			stack->pending++;
			new_stack = mod_stack_create(stack->id, target_mod, 
					dir_entry_tag,
					EV_MOD_NMSI_READ_REQUEST_DOWNUP_WAIT_FOR_REQS,
					stack);
			new_stack->target_mod = owner;
			new_stack->request_dir = mod_request_down_up;
			esim_schedule_event(EV_MOD_NMSI_READ_REQUEST, 
					new_stack, 0);
		}

		esim_schedule_event(
				EV_MOD_NMSI_READ_REQUEST_DOWNUP_WAIT_FOR_REQS,
				stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_READ_REQUEST_DOWNUP_WAIT_FOR_REQS)
	{
		/* Ignore while pending requests */
		assert(stack->pending > 0);
		stack->pending--;
		if (stack->pending)
			return;

		mem_debug("  %lld %lld 0x%x %s read request downup wait for reqs\n", 
				esim_time, stack->id, stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:read_request_downup_wait_for_reqs\"\n",
				stack->id, target_mod->name);

		if (stack->peer)
		{
			/* Send this block (or subblock) to the peer */
			new_stack = mod_stack_create(stack->id, target_mod, 
					stack->tag,
					EV_MOD_NMSI_READ_REQUEST_DOWNUP_FINISH,
					stack);
			new_stack->peer = mod_stack_set_peer(stack->peer, 
					stack->state);
			new_stack->target_mod = stack->target_mod;
			esim_schedule_event(EV_MOD_NMSI_PEER_SEND, 
					new_stack, 0);
		}
		else 
		{
			/* No data to send to peer, so finish */
			esim_schedule_event(
					EV_MOD_NMSI_READ_REQUEST_DOWNUP_FINISH,
					stack, 0);
		}

		return;
	}

	if (event == EV_MOD_NMSI_READ_REQUEST_DOWNUP_FINISH)
	{
		mem_debug("  %lld %lld 0x%x %s read request downup finish\n", 
				esim_time, stack->id, stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:read_request_downup_finish\"\n",
				stack->id, target_mod->name);

		if (stack->reply == reply_ack_data)
		{
			/* If data was received, it was owned or modified by a 
			 * higher level cache. We need to continue to 
			 * propagate it up until a peer is found */

			if (stack->peer) 
			{
				fatal("Peer should be off for NMSI to work\n");
			}
			else
			{
				/* Set state to shared */
				cache_set_block(target_mod->cache, stack->set, 
						stack->way, stack->tag,
						cache_block_shared);

				/* State is changed to shared, set owner of 
				 * sub-blocks to 0. */
				dir = target_mod->dir;
				for (z = 0; z < dir->zsize; z++)
				{
					dir_entry_tag = stack->tag + 
							z * target_mod->sub_block_size;
					assert(dir_entry_tag < stack->tag + 
							target_mod->block_size);
					dir_entry = dir_entry_get(dir, 
							stack->set, stack->way, z);
					dir_entry_set_owner(dir, stack->set, 
							stack->way, z,
							DIR_ENTRY_OWNER_NONE);
				}

				stack->reply_size = target_mod->block_size + 8;
				mod_stack_set_reply(ret, reply_ack_data);
			}
		}
		else if (stack->reply == reply_ack)
		{
			/* Higher-level cache was exclusive with no 
			 * modifications above it */
			stack->reply_size = 8;

			/* Set state to shared */
			cache_set_block(target_mod->cache, stack->set, 
					stack->way, stack->tag, cache_block_shared);

			/* State is changed to shared, set owner of sub-blocks 
			 * to 0. */
			dir = target_mod->dir;
			for (z = 0; z < dir->zsize; z++)
			{
				dir_entry_tag = stack->tag + 
						z * target_mod->sub_block_size;
				assert(dir_entry_tag < stack->tag + 
						target_mod->block_size);
				dir_entry = dir_entry_get(dir, stack->set, 
						stack->way, z);
				dir_entry_set_owner(dir, stack->set, 
						stack->way, z,
						DIR_ENTRY_OWNER_NONE);
			}

			if (stack->peer)
			{
				fatal("Peer should be off for NMSI to work\n");
			}
			else
			{
				mod_stack_set_reply(ret, reply_ack);
				stack->reply_size = 8;
			}
		}
		else if (stack->reply == reply_none)
		{
			/* This block is not present in any higher-level 
			 * caches */

			if (stack->peer) 
			{
				fatal("Peer should be off for NMSI to work\n");
			}
			else 
			{
				if (stack->state == cache_block_exclusive)
				{
					fatal("%s: Target mod block cannot be in "
							"E state\n",
							__FUNCTION__);
				}
				else if(stack->state == cache_block_shared)
				{
					stack->reply_size = 8;
					mod_stack_set_reply(ret, reply_ack);

				}
				else if (stack->state == cache_block_modified ||
						stack->state == cache_block_noncoherent)
				{
					/* No peer exists, so data is returned 
					 * to mod */
					stack->reply_size = 
							target_mod->sub_block_size + 8;
					mod_stack_set_reply(ret, 
							reply_ack_data);
				}
				else 
				{
					fatal("Invalid cache block state: %d\n",
							stack->state);
				}

				/* Set block to shared */
				cache_set_block(target_mod->cache, stack->set, 
						stack->way, stack->tag,
						cache_block_shared);
			}
		}
		else 
		{
			fatal("Unexpected reply type: %d\n", stack->reply);
		}


		dir_entry_unlock(target_mod->dir, stack->set, stack->way);

		int latency = stack->reply == reply_ack_data_sent_to_peer ? 0 : target_mod->latency;
		esim_schedule_event(EV_MOD_NMSI_READ_REQUEST_REPLY, stack, latency);
		return;
	}

	if (event == EV_MOD_NMSI_READ_REQUEST_REPLY)
	{
		struct net_t *net;
		struct net_node_t *src_node;
		struct net_node_t *dst_node;

		mem_debug("  %lld %lld 0x%x %s read request reply\n", 
				esim_time, stack->id, stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:read_request_reply\"\n",
				stack->id, target_mod->name);

		/* Checks */
		assert(stack->reply_size);
		assert(stack->request_dir);
		assert(mod_get_low_mod(mod, stack->addr) == target_mod ||
				mod_get_low_mod(target_mod, stack->addr) == mod);

		/* Get network and nodes */
		int msg_size = stack->reply_size;
		if (stack->request_dir == mod_request_up_down)
		{
			net = mod->low_net;
			if (!mem_multinet || (mem_multinet && !target_mod->high_net_node_signal) || msg_size > 8)
			{
				src_node = target_mod->high_net_node;
				dst_node = mod->low_net_node;
			}
			else
			{
				src_node = target_mod->high_net_node_signal;
				dst_node = mod->low_net_node_signal;
				assert(dst_node);
			}
		}
		else
		{
			net = mod->high_net;
			if (!mem_multinet || (mem_multinet && !target_mod->low_net_node_signal) || msg_size > 8)
			{
				src_node = target_mod->low_net_node;
				dst_node = mod->high_net_node;
			}
			else
			{
				src_node = target_mod->low_net_node_signal;
				dst_node = mod->high_net_node_signal;
				assert (dst_node);
			}
		}

		/* Send message */
		stack->msg = net_try_send_ev(net, src_node, dst_node, msg_size,
				EV_MOD_NMSI_READ_REQUEST_FINISH, stack, event, stack);
		if (stack->msg)
			net_trace("net.msg_access net=\"%s\" name=\"M-%lld\" access=\"A-%lld\"\n",
					net->name, stack->msg->id, stack->id);
		return;
	}

	if (event == EV_MOD_NMSI_READ_REQUEST_FINISH)
	{
		mem_debug("  %lld %lld 0x%x %s read request finish\n", 
				esim_time, stack->id, stack->tag, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:read_request_finish\"\n",
				stack->id, mod->name);

		/* Receive message */
		if (stack->request_dir == mod_request_up_down)
			net_receive(mod->low_net, mod->low_net_node, 
					stack->msg);
		else
			net_receive(mod->high_net, mod->high_net_node, 
					stack->msg);

		/* Return */
		mod_stack_return(stack);
		return;
	}

	abort();
}


void mod_handler_nmsi_write_request(int event, void *data)
{
	struct mod_stack_t *stack = data;
	struct mod_stack_t *ret = stack->ret_stack;
	struct mod_stack_t *new_stack;

	struct mod_t *mod = stack->mod;
	struct mod_t *target_mod = stack->target_mod;

	struct dir_t *dir;
	struct dir_entry_t *dir_entry;

	uint32_t dir_entry_tag, z;


	if (event == EV_MOD_NMSI_WRITE_REQUEST)
	{
		struct net_t *net;
		struct net_node_t *src_node;
		struct net_node_t *dst_node;

		mem_debug("  %lld %lld 0x%x %s write request\n", esim_time, stack->id,
				stack->addr, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:write_request\"\n",
				stack->id, mod->name);

		/* Default return values */
		ret->err = 0;

		/* For write requests, we need to set the initial reply size 
		 * because in updown, peer transfers must be allowed to 
		 * decrease this value (during invalidate). If the request 
		 * turns out to be downup, then these values will get 
		 * overwritten. */
		stack->reply_size = mod->block_size + 8;
		mod_stack_set_reply(stack, reply_ack_data);

		/* Checks */
		assert(stack->request_dir);
		assert(mod_get_low_mod(mod, stack->addr) == target_mod ||
				stack->request_dir == mod_request_down_up);
		assert(mod_get_low_mod(target_mod, stack->addr) == mod ||
				stack->request_dir == mod_request_up_down);

		/* Get source and destination nodes */
		if (stack->request_dir == mod_request_up_down)
		{
			net = mod->low_net;
			if(!mem_multinet || (mem_multinet && !mod->low_net_node_signal))
			{
				src_node = mod->low_net_node;
				dst_node = target_mod->high_net_node;
			}
			else
			{
				src_node = mod->low_net_node_signal;
				dst_node = target_mod->high_net_node_signal;
				assert(dst_node);
			}
		}
		else
		{
			net = mod->high_net;
			if (!mem_multinet || (mem_multinet && !mod->high_net_node_signal))
			{
				src_node = mod->high_net_node;
				dst_node = target_mod->low_net_node;
			}
			else
			{
				src_node = mod->high_net_node_signal;
				dst_node = target_mod->low_net_node_signal;
				assert(dst_node);
			}
		}

		/* Send message */
		stack->msg = net_try_send_ev(net, src_node, dst_node, 8,
				EV_MOD_NMSI_WRITE_REQUEST_RECEIVE, stack, event, stack);
		if (stack->msg)
			net_trace("net.msg_access net=\"%s\" name=\"M-%lld\" access=\"A-%lld\"\n",
					net->name, stack->msg->id, stack->id);
		return;
	}

	if (event == EV_MOD_NMSI_WRITE_REQUEST_RECEIVE)
	{
		mem_debug("  %lld %lld 0x%x %s write request receive\n", 
				esim_time, stack->id, stack->addr, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:write_request_receive\"\n",
				stack->id, target_mod->name);

		/* Receive message */
		if (stack->request_dir == mod_request_up_down)
			net_receive(target_mod->high_net, 
					target_mod->high_net_node, stack->msg);
		else
			net_receive(target_mod->low_net, 
					target_mod->low_net_node, stack->msg);

		/* Find and lock */
		new_stack = mod_stack_create(stack->id, target_mod, stack->addr,
				EV_MOD_NMSI_WRITE_REQUEST_ACTION, stack);
		new_stack->blocking = stack->request_dir == mod_request_down_up;
		new_stack->write = 1;
		new_stack->retry = 0;
		esim_schedule_event(EV_MOD_NMSI_FIND_AND_LOCK, new_stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_WRITE_REQUEST_ACTION)
	{
		mem_debug("  %lld %lld 0x%x %s write request action\n", 
				esim_time, stack->id, stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:write_request_action\"\n",
				stack->id, target_mod->name);

		/* Check lock error. If write request is down-up, there should
		 * have been no error. */
		if (stack->err)
		{
			assert(stack->request_dir == mod_request_up_down);
			ret->err = 1;
			stack->reply_size = 8;
			esim_schedule_event(EV_MOD_NMSI_WRITE_REQUEST_REPLY,
					stack, 0);
			return;
		}

		/* FIXME If we have a down-up write request, it is possible that the
		 * block has already been evicted by the higher-level cache if
		 * it was in an unmodified state. */
		/* Invalidate the rest of upper level sharers */
		new_stack = mod_stack_create(stack->id, target_mod, 0,
			EV_MOD_NMSI_WRITE_REQUEST_EXCLUSIVE, stack);
		new_stack->except_mod = mod;
		new_stack->set = stack->set;
		new_stack->way = stack->way;
		new_stack->peer = mod_stack_set_peer(stack->peer, stack->state);
		esim_schedule_event(EV_MOD_NMSI_INVALIDATE, new_stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_WRITE_REQUEST_EXCLUSIVE)
	{
		mem_debug("  %lld %lld 0x%x %s write request exclusive\n", 
				esim_time, stack->id, stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:write_request_exclusive\"\n",
				stack->id, target_mod->name);

		if (stack->request_dir == mod_request_up_down)
			esim_schedule_event(EV_MOD_NMSI_WRITE_REQUEST_UPDOWN, 
					stack, 0);
		else
			esim_schedule_event(EV_MOD_NMSI_WRITE_REQUEST_DOWNUP, 
					stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_WRITE_REQUEST_UPDOWN)
	{
		mem_debug("  %lld %lld 0x%x %s write request updown\n", 
				esim_time, stack->id, stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:write_request_updown\"\n",
				stack->id, target_mod->name);

		/* state = M */
		if (stack->state == cache_block_exclusive)
			assert(target_mod->kind == mod_kind_main_memory);

		assert(stack->state != cache_block_owned);
		if (stack->state == cache_block_modified ||
				stack->state == cache_block_exclusive)
		{
			esim_schedule_event(
					EV_MOD_NMSI_WRITE_REQUEST_UPDOWN_FINISH,
					stack, 0);
		}
		/* state = S/I/N */
		else if (stack->state == cache_block_shared ||
				stack->state == cache_block_invalid ||
				stack->state == cache_block_noncoherent)
		{
			new_stack = mod_stack_create(stack->id, target_mod, 
					stack->tag,
					EV_MOD_NMSI_WRITE_REQUEST_UPDOWN_FINISH,
					stack);
			new_stack->peer = mod_stack_set_peer(mod, stack->state);
			new_stack->target_mod = mod_get_low_mod(target_mod, 
					stack->tag);
			new_stack->request_dir = mod_request_up_down;
			esim_schedule_event(EV_MOD_NMSI_WRITE_REQUEST, 
					new_stack, 0);
		}
		else 
		{
			fatal("Invalid cache block state: %d\n", stack->state);
		}

		return;
	}

	if (event == EV_MOD_NMSI_WRITE_REQUEST_UPDOWN_FINISH)
	{
		mem_debug("  %lld %lld 0x%x %s write request updown finish\n",
				esim_time, stack->id, stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:write_request_updown_finish\"\n",
				stack->id, target_mod->name);

		/* Ensure that a reply was received */
		assert(stack->reply);

		/* Error in write request to next cache level */
		if (stack->err)
		{
			ret->err = 1;
			mod_stack_set_reply(ret, reply_ack_error);
			stack->reply_size = 8;
			dir_entry_unlock(target_mod->dir, stack->set, 
					stack->way);
			esim_schedule_event(EV_MOD_NMSI_WRITE_REQUEST_REPLY,
					stack, 0);
			return;
		}

		/* Check that addr is a multiple of mod.block_size.
		 * Set mod as sharer and owner. */
		dir = target_mod->dir;
		for (z = 0; z < dir->zsize; z++)
		{
			assert(stack->addr % mod->block_size == 0);
			dir_entry_tag = stack->tag + 
					z * target_mod->sub_block_size;
			assert(dir_entry_tag < stack->tag + 
					target_mod->block_size);
			if (dir_entry_tag < stack->addr || 
					dir_entry_tag >= stack->addr + mod->block_size)
			{
				continue;
			}
			dir_entry = dir_entry_get(dir, stack->set, 
					stack->way, z);
			dir_entry_set_sharer(dir, stack->set, stack->way, z, 
					mod->low_net_node->index);
			dir_entry_set_owner(dir, stack->set, stack->way, z, 
					mod->low_net_node->index);
			assert(dir_entry->num_sharers == 1);
		}

		/* Set state to exclusive */
		if (target_mod->kind == mod_kind_main_memory)
			cache_set_block(target_mod->cache, stack->set, stack->way,
					stack->tag, cache_block_exclusive);
		else
			cache_set_block(target_mod->cache, stack->set, stack->way,
					stack->tag, cache_block_shared);

		/* If blocks were sent directly to the peer, the reply size 
		 * would have been decreased.  Based on the final size, we can
		 * tell whether to send more data up or simply ack */
		if (stack->reply_size == 8) 
		{
			mod_stack_set_reply(ret, reply_ack);
		}
		else if (stack->reply_size > 8)
		{
			mod_stack_set_reply(ret, reply_ack_data);
		}
		else 
		{
			fatal("Invalid reply size: %d", stack->reply_size);
		}

		/* Unlock, reply_size is the data of the size of the 
		 * requestor's block. */
		dir_entry_unlock(target_mod->dir, stack->set, stack->way);

		int latency = stack->reply == reply_ack_data_sent_to_peer ? 0 : target_mod->latency;
		esim_schedule_event(EV_MOD_NMSI_WRITE_REQUEST_REPLY, stack, latency);
		return;
	}

	if (event == EV_MOD_NMSI_WRITE_REQUEST_DOWNUP)
	{
		mem_debug("  %lld %lld 0x%x %s write request downup (state = %s)\n", 
				esim_time, stack->id, stack->tag, target_mod->name,
				str_map_value(&cache_block_state_map, stack->state));
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:write_request_downup\"\n",
				stack->id, target_mod->name);

		assert(stack->state != cache_block_invalid);
		assert(!dir_entry_group_shared_or_owned(target_mod->dir, 
				stack->set, stack->way));

		/* Compute reply size */
		// Downup writes happen only during invalidation
		// higher level module cannot be in exclusive state
		assert(stack->state != cache_block_exclusive);	
		if (stack->state == cache_block_shared)
		{
			/* Exclusive and shared states send an ack */
			stack->reply_size = 8;
			mod_stack_set_reply(ret, reply_ack);
		}
		else if (stack->state == cache_block_noncoherent ||
				stack->state == cache_block_modified)
		{
			/* Non-coherent state sends data */
			stack->reply_size = target_mod->block_size + 8;
			mod_stack_set_reply(ret, reply_ack_data);
		}
		else 
		{
			fatal("Invalid cache block state: %d\n", stack->state);
		}

		esim_schedule_event(EV_MOD_NMSI_WRITE_REQUEST_DOWNUP_FINISH,
				stack, 0);

		return;
	}

	if (event == EV_MOD_NMSI_WRITE_REQUEST_DOWNUP_FINISH)
	{
		mem_debug("  %lld %lld 0x%x %s write request downup complete\n", 
				esim_time, stack->id, stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:write_request_downup_finish\"\n",
				stack->id, target_mod->name);

		/* Set state to I, unlock*/
		cache_set_block(target_mod->cache, stack->set, stack->way, 0, 
				cache_block_invalid);
		dir_entry_unlock(target_mod->dir, stack->set, stack->way);

		int latency = ret->reply == reply_ack_data_sent_to_peer ? 0 : target_mod->latency;
		esim_schedule_event(EV_MOD_NMSI_WRITE_REQUEST_REPLY, stack, latency);
		return;
	}

	if (event == EV_MOD_NMSI_WRITE_REQUEST_REPLY)
	{
		struct net_t *net;
		struct net_node_t *src_node;
		struct net_node_t *dst_node;

		mem_debug("  %lld %lld 0x%x %s write request reply\n", esim_time, stack->id,
				stack->tag, target_mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:write_request_reply\"\n",
				stack->id, target_mod->name);

		/* Checks */
		assert(stack->reply_size);
		assert(mod_get_low_mod(mod, stack->addr) == target_mod ||
				mod_get_low_mod(target_mod, stack->addr) == mod);

		int msg_size = stack->reply_size;

		/* Get network and nodes */
		if (stack->request_dir == mod_request_up_down)
		{
			net = mod->low_net;
			if (!mem_multinet || (mem_multinet && !target_mod->high_net_node_signal) || msg_size > 8)
			{
				src_node = target_mod->high_net_node;
				dst_node = mod->low_net_node;
			}
			else
			{
				src_node = target_mod->high_net_node_signal;
				dst_node = mod->low_net_node_signal;
				assert(dst_node);
			}
		}
		else
		{
			net = mod->high_net;
			if (!mem_multinet || (mem_multinet && !target_mod->low_net_node_signal) || msg_size > 8)
			{
				src_node = target_mod->low_net_node;
				dst_node = mod->high_net_node;
			}
			else
			{
				src_node = target_mod->low_net_node_signal;
				dst_node = mod->high_net_node_signal;
				assert(dst_node);
			}
		}

		stack->msg = net_try_send_ev(net, src_node, dst_node, msg_size,
				EV_MOD_NMSI_WRITE_REQUEST_FINISH, stack, event, stack);
		if (stack->msg)
			net_trace("net.msg_access net=\"%s\" name=\"M-%lld\" access=\"A-%lld\"\n",
					net->name, stack->msg->id, stack->id);
		return;
	}

	if (event == EV_MOD_NMSI_WRITE_REQUEST_FINISH)
	{
		mem_debug("  %lld %lld 0x%x %s write request finish\n", esim_time, stack->id,
				stack->tag, mod->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:write_request_finish\"\n",
				stack->id, mod->name);

		/* Receive message */
		if (stack->request_dir == mod_request_up_down)
		{
			net_receive(mod->low_net, mod->low_net_node, stack->msg);
		}
		else
		{
			net_receive(mod->high_net, mod->high_net_node, stack->msg);
		}
		

		/* If the write request was generated from a store, we can
		 * be sure that it will complete at this point and so can
		 * increment the witness pointer to allow processing to 
		 * continue while assuring consistency.
		if (stack->request_dir == mod_request_up_down &&
				stack->witness_ptr)
		{
			(*stack->witness_ptr)++;
		}
		*/
		/* Return */
		mod_stack_return(stack);
		return;
	}

	abort();
}


void mod_handler_nmsi_peer(int event, void *data)
{
	struct mod_stack_t *stack = data;
	struct mod_t *src = stack->target_mod;
	struct mod_t *peer = stack->peer;

	if (event == EV_MOD_NMSI_PEER_SEND) 
	{
		mem_debug("  %lld %lld 0x%x %s %s peer send\n", esim_time, stack->id,
			stack->tag, src->name, peer->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:peer\"\n",
			stack->id, src->name);

		/* Send message from src to peer */
		stack->msg = net_try_send_ev(src->low_net, src->low_net_node, peer->low_net_node, 
				src->block_size + 8, EV_MOD_NMSI_PEER_RECEIVE, stack, event, stack);
		if (stack->msg)
			net_trace("net.msg_access net=\"%s\" name=\"M-%lld\" access=\"A-%lld\"\n",
					src->low_net->name, stack->msg->id, stack->id);
		return;
	}

	if (event == EV_MOD_NMSI_PEER_RECEIVE) 
	{
		mem_debug("  %lld %lld 0x%x %s %s peer receive\n", esim_time, stack->id,
				stack->tag, src->name, peer->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:peer_receive\"\n",
				stack->id, peer->name);

		/* Receive message from src */
		net_receive(peer->low_net, peer->low_net_node, stack->msg);

		esim_schedule_event(EV_MOD_NMSI_PEER_REPLY, stack, 0);

		return;
	}

	if (event == EV_MOD_NMSI_PEER_REPLY) 
	{
		mem_debug("  %lld %lld 0x%x %s %s peer reply ack\n", esim_time, stack->id,
				stack->tag, src->name, peer->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:peer_reply_ack\"\n",
				stack->id, peer->name);

		/* Send ack from peer to src */
		struct net_node_t *src_node;
		struct net_node_t *dst_node;

		if (!mem_multinet || (mem_multinet && !peer->low_net_node_signal))
		{
			src_node = peer->low_net_node;
			dst_node = src->low_net_node;
		}
		else
		{
			src_node = peer->low_net_node_signal;
			dst_node = src->low_net_node_signal;
			assert(dst_node);
		}
		stack->msg = net_try_send_ev(peer->low_net, src_node, dst_node,
				8, EV_MOD_NMSI_PEER_FINISH, stack, event, stack); 
		if (stack->msg)
			net_trace("net.msg_access net=\"%s\" name=\"M-%lld\" access=\"A-%lld\"\n",
					peer->low_net->name, stack->msg->id, stack->id);
		return;
	}

	if (event == EV_MOD_NMSI_PEER_FINISH) 
	{
		mem_debug("  %lld %lld 0x%x %s %s peer finish\n", esim_time, stack->id,
				stack->tag, src->name, peer->name);
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:peer_finish\"\n",
				stack->id, src->name);

		/* Receive message from src */
		net_receive(src->low_net, src->low_net_node, stack->msg);

		mod_stack_return(stack);
		return;
	}

	abort();
}


void mod_handler_nmsi_invalidate(int event, void *data)
{
	struct mod_stack_t *stack = data;
	struct mod_stack_t *new_stack;

	struct mod_t *mod = stack->mod;

	struct dir_t *dir;
	struct dir_entry_t *dir_entry;

	uint32_t dir_entry_tag;
	uint32_t z;

	if (event == EV_MOD_NMSI_INVALIDATE)
	{
		struct mod_t *sharer;
		int i;

		/* Get block info */
		cache_get_block(mod->cache, stack->set, stack->way, &stack->tag, &stack->state);
		mem_debug("  %lld %lld 0x%x %s invalidate (set=%d, way=%d, state=%s)\n", esim_time, stack->id,
				stack->tag, mod->name, stack->set, stack->way,
				str_map_value(&cache_block_state_map, stack->state));
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:invalidate\"\n",
				stack->id, mod->name);

		/* At least one pending reply */
		stack->pending = 1;

		/* Send write request to all upper level sharers except 'except_mod' */
		dir = mod->dir;
		for (z = 0; z < dir->zsize; z++)
		{
			dir_entry_tag = stack->tag + z * mod->sub_block_size;
			assert(dir_entry_tag < stack->tag + mod->block_size);
			dir_entry = dir_entry_get(dir, stack->set, stack->way, z);
			for (i = 0; i < dir->num_nodes; i++)
			{
				struct net_node_t *node;

				/* Skip non-sharers and 'except_mod' */
				if (!dir_entry_is_sharer(dir, stack->set, stack->way, z, i))
					continue;

				node = list_get(mod->high_net->node_list, i);

				/* In case we are sharing a network:
				 * a) we have to make sure the node we are getting 
				 * is in fact a node of the upper level */
				if ((mem_shared_net) && (mod->high_net == mod->low_net) &&
					(node == mod->low_net_node))
				{
					continue;
				}
 
				sharer = node->user_data;
				if (sharer == stack->except_mod)
					continue;

				/* Clear sharer and owner */
				dir_entry_clear_sharer(dir, stack->set, stack->way, z, i);
				if (dir_entry->owner == i)
					dir_entry_set_owner(dir, stack->set, stack->way, z, DIR_ENTRY_OWNER_NONE);

				/* Send write request upwards if beginning of block */
				if (dir_entry_tag % sharer->block_size)
					continue;
				new_stack = mod_stack_create(stack->id, mod, dir_entry_tag,
						EV_MOD_NMSI_INVALIDATE_FINISH, stack);
				new_stack->target_mod = sharer;
				new_stack->request_dir = mod_request_down_up;

				esim_schedule_event(EV_MOD_NMSI_WRITE_REQUEST, new_stack, 0);
				stack->pending++;
			}
		}
		esim_schedule_event(EV_MOD_NMSI_INVALIDATE_FINISH, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_INVALIDATE_FINISH)
	{
		mem_debug("  %lld %lld 0x%x %s invalidate finish pending = %d -- (state = %s) \n", 
				esim_time, stack->id,stack->tag, mod->name,
				stack->pending - 1,
				str_map_value(&cache_block_state_map, stack->state));
		mem_trace("mem.access name=\"A-%lld\" state=\"%s:invalidate_finish\"\n",
				stack->id, mod->name);

		/* XXX The following line updates the block state.  We must
		 * be sure that the directory entry is always locked if we
		 * allow this to happen */
		if (stack->reply == reply_ack_data)
		{
			assert(stack->state != cache_block_owned);
			if (stack->state == cache_block_noncoherent)
			{
				cache_set_block(mod->cache, stack->set, stack->way, stack->tag,
					cache_block_noncoherent);
			}
			else if (stack->state == cache_block_modified) 
			{
				cache_set_block(mod->cache, stack->set, stack->way, stack->tag,
					cache_block_modified);
			}
		}

		/* Ignore while pending */
		assert(stack->pending > 0);
		stack->pending--;
		if (stack->pending)
			return;
		mod_stack_return(stack);
		return;
	}

	abort();
}

void mod_handler_nmsi_message(int event, void *data)
{
	struct mod_stack_t *stack = data;
	struct mod_stack_t *ret = stack->ret_stack;
	struct mod_stack_t *new_stack;

	struct mod_t *mod = stack->mod;
	struct mod_t *target_mod = stack->target_mod;

	struct dir_t *dir;
	struct dir_entry_t *dir_entry;
	uint32_t z;

	if (event == EV_MOD_NMSI_MESSAGE)
	{
		struct net_t *net;
		struct net_node_t *src_node;
		struct net_node_t *dst_node;

		mem_debug("  %lld %lld 0x%x %s message\n", esim_time, stack->id,
				stack->addr, mod->name);

		stack->reply_size = 8;
		stack->reply = reply_ack;

		/* Default return values*/
		ret->err = 0;

		/* Checks */
		assert(stack->message);

		/* Get source and destination nodes */
		net = mod->low_net;
		if (!mem_multinet || (mem_multinet && !mod->low_net_node_signal))
		{
			src_node = mod->low_net_node;
			dst_node = target_mod->high_net_node;
		}
		else
		{
			src_node = mod->low_net_node_signal;
			dst_node = target_mod->high_net_node_signal;
			assert(dst_node);
		}

		/* Send message */
		stack->msg = net_try_send_ev(net, src_node, dst_node, 8,
				EV_MOD_NMSI_MESSAGE_RECEIVE, stack, event, stack);
		if (stack->msg)
			net_trace("net.msg_access net=\"%s\" name=\"M-%lld\" access=\"A-%lld\"\n",
					net->name, stack->msg->id, stack->id);
		return;
	}

	if (event == EV_MOD_NMSI_MESSAGE_RECEIVE)
	{
		mem_debug("  %lld %lld 0x%x %s message receive\n", esim_time, stack->id,
				stack->addr, target_mod->name);

		/* Receive message */
		net_receive(target_mod->high_net, target_mod->high_net_node, stack->msg);

		/* Find and lock */
		new_stack = mod_stack_create(stack->id, target_mod, stack->addr,
				EV_MOD_NMSI_MESSAGE_ACTION, stack);
		new_stack->message = stack->message;
		/* XXX Add a request direction here */
		new_stack->blocking = 0;
		new_stack->retry = 0;
		esim_schedule_event(EV_MOD_NMSI_FIND_AND_LOCK, new_stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_MESSAGE_ACTION)
	{
		mem_debug("  %lld %lld 0x%x %s clear owner action\n", esim_time, stack->id,
				stack->tag, target_mod->name);

		assert(stack->message);

		/* Check block locking error. */
		mem_debug("stack err = %u\n", stack->err);
		if (stack->err)
		{
			ret->err = 1;
			mod_stack_set_reply(ret, reply_ack_error);
			esim_schedule_event(EV_MOD_NMSI_MESSAGE_REPLY, stack, 0);
			return;
		}

		if (stack->message == message_clear_owner)
		{
			/* Remove owner */
			dir = target_mod->dir;
			for (z = 0; z < dir->zsize; z++)
			{
				/* Skip other subblocks */
				if (stack->addr == stack->tag + z * target_mod->sub_block_size)
				{
					/* Clear the owner */
					dir_entry = dir_entry_get(dir, stack->set, stack->way, z);
					assert(dir_entry->owner == mod->low_net_node->index);
					dir_entry_set_owner(dir, stack->set, stack->way, z, 
							DIR_ENTRY_OWNER_NONE);
				}
			}

		}
		else
		{
			fatal("Unexpected message");
		}

		/* Unlock the directory entry */
		dir_entry_unlock(dir, stack->set, stack->way);

		esim_schedule_event(EV_MOD_NMSI_MESSAGE_REPLY, stack, 0);
		return;
	}

	if (event == EV_MOD_NMSI_MESSAGE_REPLY)
	{
		struct net_t *net;
		struct net_node_t *src_node;
		struct net_node_t *dst_node;

		mem_debug("  %lld %lld 0x%x %s message reply\n", esim_time, stack->id,
				stack->tag, target_mod->name);

		/* Checks */
		assert(mod_get_low_mod(mod, stack->addr) == target_mod ||
				mod_get_low_mod(target_mod, stack->addr) == mod);

		int msg_size = stack->reply_size;

		/* Get network and nodes */
		net = mod->low_net;
		if (!mem_multinet || (mem_multinet && !target_mod->high_net_node_signal) || msg_size > 8)
		{
			src_node = target_mod->high_net_node;
			dst_node = mod->low_net_node;
		}
		else
		{
			src_node = target_mod->high_net_node_signal;
			dst_node = mod->low_net_node_signal;
			assert(dst_node);
		}

		/* Send message */
		stack->msg = net_try_send_ev(net, src_node, dst_node, msg_size,
				EV_MOD_NMSI_MESSAGE_FINISH, stack, event, stack);
		if (stack->msg)
			net_trace("net.msg_access net=\"%s\" name=\"M-%lld\" access=\"A-%lld\"\n",
					net->name, stack->msg->id, stack->id);
		return;
	}

	if (event == EV_MOD_NMSI_MESSAGE_FINISH)
	{
		mem_debug("  %lld %lld 0x%x %s message finish\n", esim_time, stack->id,
				stack->tag, mod->name);

		/* Receive message */
		net_receive(mod->low_net, mod->low_net_node, stack->msg);

		/* Return */
		mod_stack_return(stack);
		return;
	}

	abort();
}

void nmsi_flush_pages(struct mod_t *mod, struct mod_stack_t *stack)
{
	struct mod_stack_t *new_stack;

	int set;
	int way;
	int tag;
	int state;
//	unsigned int page_start;
//	unsigned int page_end;

//	page_start = stack->flush_page;
//	page_end = (page_start + MEM_PAGE_SIZE - 1);

	for (set = 0; set < mod->dir_num_sets; set++)
	{
		for (way = 0; way < mod->dir_assoc; way++)
		{
			cache_get_block(mod->cache, set, way, &tag, &state);

			if (!state)
				continue;

//			if (!(tag >= page_start && tag <= page_end))
//				continue;

			/* If the tag is within the page range,
			 * send an invalidation request */
			stack->pending++;
			new_stack = mod_stack_create(stack->id, mod, 
				tag, EV_MOD_NMSI_FLUSH_FINISH, stack);

//			new_stack->except_mod = NULL;
			new_stack->set = set;
			new_stack->way = way;
//			new_stack->callback_function = stack->callback_function;
//			new_stack->callback_data = stack->callback_data;
//			new_stack->witness_ptr = stack->witness_ptr;

			esim_schedule_event(EV_MOD_NMSI_INVALIDATE, 
				new_stack, 0);
		}
	}
}

void nmsi_recursive_flush(struct mod_t *mod, struct mod_stack_t *stack)
{
	struct mod_t *low_mod;

	LINKED_LIST_FOR_EACH(mod->low_mod_list)
	{
		low_mod = linked_list_get(mod->low_mod_list);
		if (low_mod->kind != mod_kind_main_memory)
		{
			nmsi_recursive_flush(low_mod, stack);
		}
		else
		{
			nmsi_flush_pages(low_mod, stack);
		}
	}
}

void mod_handler_nmsi_flush(int event, void *data)
{
	struct mod_stack_t *stack = data;

	struct mod_t *mod = stack->mod;

	if (event == EV_MOD_NMSI_FLUSH)
	{
		mem_debug("  %lld %lld 0x%x %s flush\n", esim_time, stack->id,
			stack->addr, mod->name);
		mem_trace("mem.new_access name=\"A-%lld\" type=\"flush\" "
			"state=\"%s:flush\" addr=0x%x\n",
			stack->id, mod->name, stack->addr);

		stack->pending = 1;

		if (mod->kind == mod_kind_cache)
		{
			nmsi_recursive_flush(mod, stack);
		}

		esim_schedule_event(EV_MOD_NMSI_FLUSH_FINISH, stack, 0);
		
		return;
	}

	if (event == EV_MOD_NMSI_FLUSH_FINISH)
	{
		/* Ignore while pending requests */
		assert(stack->pending > 0);
		stack->pending--;
		if (stack->pending)
			return;

		mem_trace("mem.end_access name=\"A-%lld\"\n", stack->id);

		/* Increment the witness pointer if one was provided */
//		if (stack->witness_ptr)
//		{
//			(*stack->witness_ptr)++;
//		}

		/* Execute callback if one was provided */
//		if (stack->callback_function)
//			stack->callback_function(stack->callback_data);

		/* Return */
		mod_stack_return(stack);

		return;
	}

	abort();
}
