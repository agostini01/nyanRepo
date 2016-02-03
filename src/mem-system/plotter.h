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

#ifndef MEM_SYSTEM_PLOTTER_H
#define MEM_SYSTEM_PLOTTER_H

struct snapshot_t
{
	long long last_snapshot;

	FILE *snapshot_load;
	char load_file_name[MAX_STRING_SIZE];
	FILE *snapshot_store;
	char store_file_name[MAX_STRING_SIZE];

	struct list_t *mem_regions_loads;
	struct list_t *mem_regions_stores;

	int max_accesses;
	int max_address;
	int mem_snapshot_region_size;
	int snapshot_blocks_in_bits;
	int partial_snapshot; 
};

struct mod_mshr_record_t
{
	FILE *access_record_file;
	char access_record_file_name[MAX_STRING_SIZE];
};

/* Memory Snapshot */
struct snapshot_t *snapshot_create(char *snapshot_name);
void snapshot_free(struct snapshot_t *snap_struct);
void snapshot_record(struct snapshot_t *snapshot_struct,
		long long cycle, unsigned int addr, int type);
void snapshot_dump(struct snapshot_t * snapshot);

/* MSHR graph */
void mem_access_record(struct mod_mshr_record_t *mshr_record, int list_size);
struct mod_mshr_record_t* mod_mshr_record_create(struct mod_t* mod);
void mod_mshr_record_free(struct mod_mshr_record_t *mshr_record);
void mod_mshr_record_dump();

#endif
