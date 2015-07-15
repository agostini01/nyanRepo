/*
 *  Multi2Sim
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
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MEM_SYSTEM_NMOESI_WT_H
#define MEM_SYSTEM_NMOESI_WT_H


/* NMOESI Event-Driven Simulation */

extern int EV_MOD_NMOESI_LOAD_WT;
extern int EV_MOD_NMOESI_LOAD_LOCK_WT;
extern int EV_MOD_NMOESI_LOAD_ACTION_WT;
extern int EV_MOD_NMOESI_LOAD_MISS_WT;
extern int EV_MOD_NMOESI_LOAD_UNLOCK_WT;
extern int EV_MOD_NMOESI_LOAD_FINISH_WT;

extern int EV_MOD_NMOESI_STORE_WT;
extern int EV_MOD_NMOESI_STORE_LOCK_WT;
extern int EV_MOD_NMOESI_STORE_ACTION_WT;
extern int EV_MOD_NMOESI_STORE_UNLOCK_WT;
extern int EV_MOD_NMOESI_STORE_FINISH_WT;

extern int EV_MOD_NMOESI_NC_STORE_WT;
extern int EV_MOD_NMOESI_NC_STORE_LOCK_WT;
extern int EV_MOD_NMOESI_NC_STORE_ACTION_WT;
extern int EV_MOD_NMOESI_NC_STORE_MISS_WT;
extern int EV_MOD_NMOESI_NC_STORE_UNLOCK_WT;
extern int EV_MOD_NMOESI_NC_STORE_MERGE_WT;
extern int EV_MOD_NMOESI_NC_STORE_FINISH_WT;

extern int EV_MOD_NMOESI_FIND_AND_LOCK_READ_WT;
extern int EV_MOD_NMOESI_FIND_AND_LOCK_PORT_READ_WT;
extern int EV_MOD_NMOESI_FIND_AND_LOCK_ACTION_READ_WT;
extern int EV_MOD_NMOESI_FIND_AND_LOCK_FINISH_READ_WT;

extern int EV_MOD_NMOESI_FIND_AND_LOCK_WRITE_WT;
extern int EV_MOD_NMOESI_FIND_AND_LOCK_PORT_WRITE_WT;
extern int EV_MOD_NMOESI_FIND_AND_LOCK_ACTION_WRITE_WT;
extern int EV_MOD_NMOESI_FIND_AND_LOCK_FINISH_WRITE_WT;

extern int EV_MOD_NMOESI_WRITE_REQUEST_WT;
extern int EV_MOD_NMOESI_WRITE_REQUEST_RECEIVE_WT;
extern int EV_MOD_NMOESI_WRITE_REQUEST_ACTION_WT;
extern int EV_MOD_NMOESI_WRITE_REQUEST_EXCLUSIVE_WT;
extern int EV_MOD_NMOESI_WRITE_REQUEST_UPDOWN_WT;
extern int EV_MOD_NMOESI_WRITE_REQUEST_UPDOWN_FINISH_WT;
extern int EV_MOD_NMOESI_WRITE_REQUEST_DOWNUP_WT;
extern int EV_MOD_NMOESI_WRITE_REQUEST_DOWNUP_FINISH_WT;
extern int EV_MOD_NMOESI_WRITE_REQUEST_REPLY_WT;
extern int EV_MOD_NMOESI_WRITE_REQUEST_FINISH_WT;

extern int EV_MOD_NMOESI_WRITE_DATA_WT;
extern int EV_MOD_NMOESI_WRITE_DATA_RECEIVE_WT;
extern int EV_MOD_NMOESI_WRITE_DATA_ACTION_WT;
extern int EV_MOD_NMOESI_WRITE_DATA_BLOCK_WT;
extern int EV_MOD_NMOESI_WRITE_DATA_LOWER_WT;
extern int EV_MOD_NMOESI_WRITE_DATA_DONE_WT;
extern int EV_MOD_NMOESI_WRITE_DATA_REPLY_WT;
extern int EV_MOD_NMOESI_WRITE_DATA_FINISH_WT;

extern int EV_MOD_NMOESI_READ_REQUEST_WT;
extern int EV_MOD_NMOESI_READ_REQUEST_RECEIVE_WT;
extern int EV_MOD_NMOESI_READ_REQUEST_ACTION_WT;
extern int EV_MOD_NMOESI_READ_REQUEST_UPDOWN_WT;
extern int EV_MOD_NMOESI_READ_REQUEST_UPDOWN_MISS_WT;
extern int EV_MOD_NMOESI_READ_REQUEST_UPDOWN_FINISH_WT;
extern int EV_MOD_NMOESI_READ_REQUEST_DOWNUP_WT;
extern int EV_MOD_NMOESI_READ_REQUEST_DOWNUP_WAIT_FOR_REQS_WT;
extern int EV_MOD_NMOESI_READ_REQUEST_DOWNUP_FINISH_WT;
extern int EV_MOD_NMOESI_READ_REQUEST_REPLY_WT;
extern int EV_MOD_NMOESI_READ_REQUEST_FINISH_WT;

extern int EV_MOD_NMOESI_PEER_SEND_WT;
extern int EV_MOD_NMOESI_PEER_RECEIVE_WT;
extern int EV_MOD_NMOESI_PEER_REPLY_WT;
extern int EV_MOD_NMOESI_PEER_FINISH_WT;

extern int EV_MOD_NMOESI_MESSAGE_WT;
extern int EV_MOD_NMOESI_MESSAGE_RECEIVE_WT;
extern int EV_MOD_NMOESI_MESSAGE_ACTION_WT;
extern int EV_MOD_NMOESI_MESSAGE_REPLY_WT;
extern int EV_MOD_NMOESI_MESSAGE_FINISH_WT;


void mod_handler_nmoesi_find_and_lock_read_wt(int event, void *data);
void mod_handler_nmoesi_find_and_lock_write_wt(int event, void *data);
void mod_handler_nmoesi_load_wt(int event, void *data);
void mod_handler_nmoesi_store_wt(int event, void *data);
void mod_handler_nmoesi_nc_store_wt(int event, void *data);
void mod_handler_nmoesi_write_data_wt(int event, void *data);
void mod_handler_nmoesi_write_request_wt(int event, void *data);
void mod_handler_nmoesi_read_request_wt(int event, void *data);
void mod_handler_nmoesi_peer_wt(int event, void *data);
void mod_handler_nmoesi_message_wt(int event, void *data);


#endif

