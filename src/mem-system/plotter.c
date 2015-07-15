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
#include <unistd.h>

#include <lib/esim/esim.h>
#include <lib/mhandle/mhandle.h>
#include <lib/util/debug.h>
#include <lib/util/file.h>
#include <lib/util/list.h>
#include <lib/util/string.h>

#include "mem-system.h"
#include "module.h"
#include "plotter.h"

#define MEM_SNAPSHOT_LIMIT 1000000

int mem_snap_period = 0;
int mem_snapshot_block_size = 0;

struct mem_system_snapshot_t *mem_system_snapshot_create(void)
{
	struct mem_system_snapshot_t *snapshot;

	snapshot = xcalloc(1, sizeof(struct mem_system_snapshot_t));
	snapshot->last_snapshot = 0;
	snapshot->mem_snapshot_region_size = 1;

	snapshot->snapshot_blocks_in_bits = 0;

	int x = mem_snapshot_block_size;
	if ((x == 0) || ((x & (x - 1)) != 0))
	{
		fatal("%s: choose the memory snapshot block size as a "
				"power of two value\n",__FUNCTION__);
	}
	while (x >> 1)
	{
		x = x >> 1;
		snapshot->snapshot_blocks_in_bits++;
		snapshot->mem_snapshot_region_size <<= 1;
	}


	/* Create a temp file for load access */
	snprintf(snapshot->load_file_name, sizeof snapshot->load_file_name,
			"mem_snapshot_load_accesses");
	snapshot->snapshot_load = file_open_for_write(snapshot->load_file_name);
	if (!snapshot->snapshot_load)
		fatal("Mem_snapshot_load: cannot write on snapshot file");

	/* Create a temp file for store accesses */
	snprintf(snapshot->store_file_name, sizeof snapshot->store_file_name,
			"mem_snapshot_store_accesses");
	snapshot->snapshot_store = file_open_for_write(snapshot->store_file_name);
	if (!snapshot->snapshot_store)
		fatal("Mem_snapshot_store: cannot write on snapshot file");

	snapshot->mem_regions_loads = list_create();
	snapshot->mem_regions_stores = list_create();

	return snapshot;
}

void mem_system_snapshot_free(struct mem_system_snapshot_t * snapshot)
{
	if (snapshot)
	{
		for (int i=0; i < list_count(snapshot->mem_regions_loads); i++)
		{
			free(list_get(snapshot->mem_regions_loads , i));
		}
		list_free(snapshot->mem_regions_loads);

		for (int i=0; i < list_count(snapshot->mem_regions_stores); i++)
		{
			free(list_get(snapshot->mem_regions_stores, i));
		}
		list_free(snapshot->mem_regions_stores);
		free(snapshot);
	}
}

void mem_system_snapshot_record(struct mem_system_snapshot_t *snapshot,
		long long cycle, unsigned int addr, int type)
{

	snapshot->max_address = snapshot->max_address < addr ? addr :
			snapshot->max_address;

	if ((cycle / mem_snap_period) * (snapshot->max_address /
			snapshot->mem_snapshot_region_size) > MEM_SNAPSHOT_LIMIT)
	{
		warning("%s: The memory snapshot file grow too big. \n"
				"Either increase the snapshot period, or the snapshot "
				"region size and try again \n", __FUNCTION__);
		mem_snap_period = 0;
		return;
	}
	if (cycle > (snapshot->last_snapshot + 1) * mem_snap_period)
	{
		for (int i = 0; i < list_count(snapshot->mem_regions_loads) ; i++)
		{
			int * element_value = list_get(snapshot->mem_regions_loads, i);

			fprintf(snapshot->snapshot_load, "%lld %d %d \n" ,
					snapshot->last_snapshot * mem_snap_period,
					i * snapshot->mem_snapshot_region_size, * element_value);
			fprintf(snapshot->snapshot_load, "%lld %d %d \n" ,
					snapshot->last_snapshot * mem_snap_period,
					(i + 1) * snapshot->mem_snapshot_region_size,
					* element_value);
		}
		fprintf(snapshot->snapshot_load, "\n");

		for (int i = 0; i < list_count(snapshot->mem_regions_loads); i++)
		{
			int * element_value = list_get(snapshot->mem_regions_loads, i);

			fprintf(snapshot->snapshot_load, "%lld %d %d \n" ,
					(snapshot->last_snapshot + 1) * mem_snap_period,
					i  * snapshot->mem_snapshot_region_size, * element_value);
			fprintf(snapshot->snapshot_load, "%lld %d %d \n" ,
					(snapshot->last_snapshot + 1) * mem_snap_period,
					(i + 1)  * snapshot->mem_snapshot_region_size,
					* element_value);

			if ( snapshot->max_accesses < * element_value)
				snapshot->max_accesses = * element_value;

			* element_value = 0;
		}
		fprintf(snapshot->snapshot_load, "\n");

		for (int i = 0; i < list_count(snapshot->mem_regions_stores) ; i++)
		{
			int * element_value = list_get(snapshot->mem_regions_stores, i);

			fprintf(snapshot->snapshot_store, "%lld %d %d \n" ,
					snapshot->last_snapshot * mem_snap_period,
					i * snapshot->mem_snapshot_region_size, * element_value);
			fprintf(snapshot->snapshot_store, "%lld %d %d \n" ,
					snapshot->last_snapshot * mem_snap_period,
					(i + 1) * snapshot->mem_snapshot_region_size,
					* element_value);
		}
		fprintf(snapshot->snapshot_store, "\n");

		for (int i = 0; i < list_count(snapshot->mem_regions_stores); i++)
		{
			int * element_value = list_get(snapshot->mem_regions_stores, i);

			fprintf(snapshot->snapshot_store, "%lld %d %d \n" ,
					(snapshot->last_snapshot + 1) * mem_snap_period,
					i  * snapshot->mem_snapshot_region_size, * element_value);
			fprintf(snapshot->snapshot_store, "%lld %d %d \n" ,
					(snapshot->last_snapshot + 1) * mem_snap_period,
					(i + 1)  * snapshot->mem_snapshot_region_size,
					* element_value);

			if ( snapshot->max_accesses < * element_value)
				snapshot->max_accesses = * element_value;

			* element_value = 0;
		}
		fprintf(snapshot->snapshot_store, "\n");

		snapshot->last_snapshot ++;
	}

	int current_element = addr >> snapshot->snapshot_blocks_in_bits;

	struct list_t *chosen_list;

	if (type == 0)
		chosen_list = snapshot->mem_regions_loads;
	else if (type == 1)
		chosen_list = snapshot->mem_regions_stores;
	else
		fatal("unspecified type for snapshot");


	if (list_count(chosen_list) <= current_element)
	{
		while (list_count(chosen_list) != current_element + 1)
		{
			int * new_element = xcalloc(1, sizeof(int));
			list_add(chosen_list, new_element);
		}
	}

	int * temp = list_get(chosen_list, current_element);
	* temp = (*temp) + 1;

	if (snapshot->max_address < addr)
	{
		snapshot->max_address = addr;
	}
}

void mem_system_snapshot_dump(struct mem_system_snapshot_t * snapshot)
{
	if (mem_snap_period == 0)
		return;
	// Last Load accesses
	for (int i = 0; i < list_count(snapshot->mem_regions_loads) ; i++)
	{
		int * element_value = list_get(snapshot->mem_regions_loads, i);

		fprintf(snapshot->snapshot_load, "%lld %d %d \n" ,
				snapshot->last_snapshot * mem_snap_period,
				i * snapshot->mem_snapshot_region_size, * element_value);
		fprintf(snapshot->snapshot_load, "%lld %d %d \n" ,
				snapshot->last_snapshot * mem_snap_period,
				(i + 1) * snapshot->mem_snapshot_region_size, * element_value);
	}
	fprintf(snapshot->snapshot_load, "\n");

	for (int i = 0; i < list_count(snapshot->mem_regions_loads); i++)
	{
		int * element_value = list_get(snapshot->mem_regions_loads, i);

		fprintf(snapshot->snapshot_load, "%lld %d %d \n" ,
				(snapshot->last_snapshot + 1) * mem_snap_period,
				i  * snapshot->mem_snapshot_region_size, * element_value);
		fprintf(snapshot->snapshot_load, "%lld %d %d \n" ,
				(snapshot->last_snapshot + 1) * mem_snap_period,
				(i + 1)  * snapshot->mem_snapshot_region_size, * element_value);

		if ( snapshot->max_accesses < * element_value)
			snapshot->max_accesses = * element_value;

		* element_value = 0;
	}
	fprintf(snapshot->snapshot_load, "\n");
	fclose(snapshot->snapshot_load);

	// Last store Accesses
	for (int i = 0; i < list_count(snapshot->mem_regions_stores) ; i++)
	{
		int * element_value = list_get(snapshot->mem_regions_stores, i);

		fprintf(snapshot->snapshot_store, "%lld %d %d \n" ,
				snapshot->last_snapshot * mem_snap_period,
				i * snapshot->mem_snapshot_region_size, * element_value);
		fprintf(snapshot->snapshot_store, "%lld %d %d \n" ,
				snapshot->last_snapshot * mem_snap_period,
				(i + 1) * snapshot->mem_snapshot_region_size, * element_value);
	}
	fprintf(snapshot->snapshot_store, "\n");

	for (int i = 0; i < list_count(snapshot->mem_regions_stores); i++)
	{
		int * element_value = list_get(snapshot->mem_regions_stores, i);

		fprintf(snapshot->snapshot_store, "%lld %d %d \n" ,
				(snapshot->last_snapshot + 1) * mem_snap_period,
				i  * snapshot->mem_snapshot_region_size, * element_value);
		fprintf(snapshot->snapshot_store, "%lld %d %d \n" ,
				(snapshot->last_snapshot + 1) * mem_snap_period,
				(i + 1)  * snapshot->mem_snapshot_region_size, * element_value);

		if ( snapshot->max_accesses < * element_value)
			snapshot->max_accesses = * element_value;

		* element_value = 0;
	}
	fprintf(snapshot->snapshot_store, "\n");
	fclose(snapshot->snapshot_store);

	/* Run the script - Load script */
	FILE *load_script_file;
	char cmd[MAX_PATH_SIZE];

	char load_script_file_name[MAX_PATH_SIZE];
	char plot_file_name[MAX_PATH_SIZE];

	/* Create plot file */
	for (int i = 0; i < 4; i++)
	{
		if (i < 2)
			snprintf(plot_file_name, MAX_PATH_SIZE, "%d_%d_%dD_loads.ps",
					mem_snap_period, snapshot->mem_snapshot_region_size,i+2);
		else
			snprintf(plot_file_name, MAX_PATH_SIZE, "%d_%d_%dD_stores.ps",
					mem_snap_period, snapshot->mem_snapshot_region_size,i);
		if (!file_can_open_for_write(plot_file_name))
		{
			fatal("%s: cannot write GPU occupancy calculation plot",
					plot_file_name);
		}

		load_script_file = file_create_temp(load_script_file_name,
				MAX_PATH_SIZE);
		fprintf(load_script_file, "unset origin\n");
		fprintf(load_script_file, "unset label\n");
		fprintf(load_script_file, "set term postscript eps enhanced color\n");
		fprintf(load_script_file, "set ticslevel 0\n");
		fprintf(load_script_file, "set nohidden3d\n");
		fprintf(load_script_file, "set size square\n");
		fprintf(load_script_file, "unset key\n");
		fprintf(load_script_file, "set origin 0,-0.1\n");
		switch(i%2)
		{
		case 1:
			/* 3D view */
			fprintf(load_script_file, "set view 30,40,0.5\n");
			break;
		case 0:
		default:
			/* 2D view */
			fprintf(load_script_file, "set view 0,0, 0.5\n");
		}

		fprintf(load_script_file, "set pm3d\n");
		fprintf(load_script_file, "set palette defined "
				"(0 \"white\", 0.0001 \"black\", "
				"10 \"gray\", 60 \"cyan\", 100 \"blue\")\n");
		fprintf(load_script_file, "set colorbox vertical user origin "
				".2,.28 size 0.03, 0.26\n");
		fprintf(load_script_file, "unset surface\n");
		fprintf(load_script_file, "set cbtics font \"Helvettica, 6\"\n");
		fprintf(load_script_file, "set xlabel 'Time (cycles)' "
				"font \"Helvettica, 7\"\n");
		fprintf(load_script_file, "set xtics font \"Helvettica, 6\"\n");
		fprintf(load_script_file, "set xtics offset -0.5,-0.2\n");
		fprintf(load_script_file, "set ylabel 'Address (Hex)' "
				"rotate by 135 offset 2, 0 font \"Helvettica, 7\"\n");
		fprintf(load_script_file, "set ytics offset 1.5,0\n");
		//	fprintf(load_script_file, "set format y \"%.X\"\n");
		fprintf(load_script_file, "set ytics font \"Helvettica, 8\"\n");
		fprintf(load_script_file, "set mytics 4\n");
		fprintf(load_script_file, "unset ztics\n");
		fprintf(load_script_file, "set label \"Number of Accesses\" "
				"font \"Helvetica,7\" at screen 0.27, "
				"screen 0.35 rotate by 90\n");
		if ( i < 2)
			fprintf(load_script_file, "splot \"%s\" with lines\n",
					snapshot->load_file_name);
		else
			fprintf(load_script_file, "splot \"%s\" with lines\n",
					snapshot->store_file_name);
		fprintf(load_script_file, "unset multiplot\n");
		fclose(load_script_file);

		/* Plot */
		sprintf(cmd, "gnuplot %s > %s", load_script_file_name, plot_file_name);
		int err = system(cmd);
		if (err)
			warning("could not execute gnuplot\nEither gnuplot is "
					"not installed or is not the supported version\n");

		/* Remove temporary files */
		unlink(load_script_file_name);
	}
	unlink(snapshot->load_file_name);
	unlink(snapshot->store_file_name);

}

void mem_access_record(struct mod_mshr_record_t* mshr_record, int list_size)
{
	/* Dump line to data file */
	if (!mshr_record)
		return;

	long long cycle = esim_domain_cycle(mem_domain_index);

	fprintf(mshr_record->access_record_file, "%lld %d\n", cycle,
			list_size);

}

void mod_mshr_record_dump()
{
	for (int i = 0; i < list_count(mem_system->mod_list); i++)
	{
		struct mod_t *mod = list_get(mem_system->mod_list, i);
		if (!mod->mshr_record)
			continue;

		fclose(mod->mshr_record->access_record_file);

		/* Run the script - Load script */
		FILE *script_file;
		char cmd[MAX_PATH_SIZE];

		char script_file_name[MAX_PATH_SIZE];
		char plot_file_name[MAX_PATH_SIZE];

		/* Create plot file */
		snprintf(plot_file_name, MAX_PATH_SIZE, "%s_mshr_record.eps",
				mod->name);

		if (!file_can_open_for_write(plot_file_name))
		{
			fatal("%s: cannot write GPU occupancy calculation plot",
					plot_file_name);
		}

		int err = 0;
		/* Generate gnuplot script for Offered Bandwidth */
		script_file = file_create_temp(script_file_name, MAX_PATH_SIZE);
		fprintf(script_file, "set term postscript eps color solid\n");
		fprintf(script_file, "set nokey\n");
		fprintf(script_file, "set title 'MSHR entry occupation - store - module %s'\n",
				mod->name);
		fprintf(script_file, "set ylabel 'MSHR entries '\n");
		fprintf(script_file, "set xlabel 'Time (cycles) '\n");
		fprintf(script_file, "unset xrange \n");
		fprintf(script_file, "unset yrange \n");
		fprintf(script_file, "set xtics font \"Helvettica, 8\" "
				"rotate by 45 offset -1,-1 \n");
		fprintf(script_file, "set size 0.65, 0.5\n");
		fprintf(script_file, "set grid ytics\n");
		/* lt is the color, lw is width, pt is the shape, ps is */
		fprintf(script_file, "plot '%s' w points lt 1 "
				"lw 1 pt 2 ps 1 \n",mod->mshr_record->access_record_file_name);
		fclose(script_file);

		/* Plot */
		sprintf(cmd, "gnuplot %s > %s", script_file_name, plot_file_name);
		err = system(cmd);
		if (err)
			warning("could not execute gnuplot, when creating network results\n");

		/* Remove temporary files */
		unlink(mod->mshr_record->access_record_file_name);
		unlink(script_file_name);
	}

}
struct mod_mshr_record_t* mod_mshr_record_create(struct mod_t *mod)
{
	struct mod_mshr_record_t *mshr_record;

	mshr_record = xcalloc(1, sizeof(struct mod_mshr_record_t));

	/* Create a temp file for load access */
	snprintf(mshr_record->access_record_file_name, sizeof mshr_record->access_record_file_name,
			"mod_%s_mshr_access",mod->name);
	mshr_record->access_record_file = file_open_for_write(
			mshr_record->access_record_file_name);
	if (!mshr_record->access_record_file)
		fatal("%s:Module mshr recorder: cannot write on snapshot file",__FUNCTION__);

	return mshr_record;
}

void mod_mshr_record_free(struct mod_mshr_record_t * mshr_record)
{
	if (mshr_record)
		free(mshr_record);
}
