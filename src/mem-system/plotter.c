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
#define KEEP_TEMP 0 
#define THREEDIM 0

int mem_snap_period = 0;
int mem_snapshot_block_size = 0;

struct snapshot_t *snapshot_create(char *name)
{
	struct snapshot_t *snapshot;

	snapshot = xcalloc(1, sizeof(struct snapshot_t));
	snapshot->last_snapshot = 0;
	snapshot->mem_snapshot_region_size = 1;
	snapshot->partial_snapshot = 0;
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
	snprintf(snapshot->file_name, sizeof snapshot->file_name,
			"%s_accesses", name);
	snapshot->snapshot = file_open_for_write(snapshot->file_name);
	if (!snapshot->snapshot)
		fatal(" cannot write on snapshot file");

	snapshot->mem_regions = list_create();

	return snapshot;
}

void snapshot_free(struct snapshot_t * snapshot)
{
	if (snapshot)
	{
		for (int i=0; i < list_count(snapshot->mem_regions); i++)
		{
			free(list_get(snapshot->mem_regions , i));
		}
		list_free(snapshot->mem_regions);

		free(snapshot);
	}
}

void snapshot_record(struct snapshot_t *snapshot,
		long long cycle, unsigned int addr)
{
	if (!snapshot)
		return;

	if (snapshot->partial_snapshot)
		return;

	if (cycle > (snapshot->last_snapshot + 1) * mem_snap_period)
	{
		for (int i = 0; i < list_count(snapshot->mem_regions) ; i++)
		{
			int * element_value = list_get(snapshot->mem_regions, i);

			fprintf(snapshot->snapshot, "%lld %d %d \n" ,
					snapshot->last_snapshot * mem_snap_period,
					i * snapshot->mem_snapshot_region_size, * element_value);
			fprintf(snapshot->snapshot, "%lld %d %d \n" ,
					snapshot->last_snapshot * mem_snap_period,
					(i + 1) * snapshot->mem_snapshot_region_size,
					* element_value);
		}
		fprintf(snapshot->snapshot, "\n");

		for (int i = 0; i < list_count(snapshot->mem_regions); i++)
		{
			int * element_value = list_get(snapshot->mem_regions, i);

			fprintf(snapshot->snapshot, "%lld %d %d \n" ,
					(snapshot->last_snapshot + 1) * mem_snap_period,
					i  * snapshot->mem_snapshot_region_size, * element_value);
			fprintf(snapshot->snapshot, "%lld %d %d \n" ,
					(snapshot->last_snapshot + 1) * mem_snap_period,
					(i + 1)  * snapshot->mem_snapshot_region_size,
					* element_value);

			if ( snapshot->max_accesses < * element_value)
				snapshot->max_accesses = * element_value;

			* element_value = 0;
		}
		fprintf(snapshot->snapshot, "\n");

		snapshot->last_snapshot++;
	}

	// calculate the maximum address accessed
	snapshot->max_address = snapshot->max_address < addr ? addr :
			snapshot->max_address;

	// Assuming a 2D array: time_sample x (max_address/region_size)
	// if the elements in the 2D array grow bigger than 100000 abort recording.
	// But show the element that we recorded so far.
	if ((cycle / mem_snap_period) * (snapshot->max_address /
			snapshot->mem_snapshot_region_size) > MEM_SNAPSHOT_LIMIT)
	{
		warning("%s: The memory snapshot file grow too big. \n"
				"Recording stops, and the resulting image is partial.\n"
				"For full results, either increase the snapshot period,\n"
				"or the snapshot region size and try again \n",
				snapshot->file_name);
		snapshot->partial_snapshot = 1;
	}

	// If current element (address) is outside the range of the 2D array,
	// a new row should be added. 
	// first calculate the index of the current element
	int current_element = addr >> snapshot->snapshot_blocks_in_bits;

	// if the index is bigger that count of the list, we should
	// add a new row.
	if (list_count(snapshot->mem_regions) <= current_element)
	{
		while (list_count(snapshot->mem_regions) != current_element + 1)
		{
			int * new_element = xcalloc(1, sizeof(int));
			list_add(snapshot->mem_regions, new_element);
		}
	}

	// Now the current element is increased one, because of the access
	int * temp = list_get(snapshot->mem_regions, current_element);
	* temp = (*temp) + 1;

	if (snapshot->max_address < addr)
	{
		snapshot->max_address = addr;
	}
}

void snapshot_dump(struct snapshot_t * snapshot)
{
	if (mem_snap_period == 0)
		return;

	// Last accesses
	for (int i = 0; i < list_count(snapshot->mem_regions) ; i++)
	{
		int *element_value = list_get(snapshot->mem_regions, i);

		fprintf(snapshot->snapshot, "%lld %d %d \n" ,
				snapshot->last_snapshot * mem_snap_period,
				i * snapshot->mem_snapshot_region_size, * element_value);
		fprintf(snapshot->snapshot, "%lld %d %d \n" ,
				snapshot->last_snapshot * mem_snap_period,
				(i + 1) * snapshot->mem_snapshot_region_size, * element_value);
	}
	fprintf(snapshot->snapshot, "\n");

	for (int i = 0; i < list_count(snapshot->mem_regions); i++)
	{
		int *element_value = list_get(snapshot->mem_regions, i);

		fprintf(snapshot->snapshot, "%lld %d %d \n" ,
				(snapshot->last_snapshot + 1) * mem_snap_period,
				i  * snapshot->mem_snapshot_region_size, * element_value);
		fprintf(snapshot->snapshot, "%lld %d %d \n" ,
				(snapshot->last_snapshot + 1) * mem_snap_period,
				(i + 1)  * snapshot->mem_snapshot_region_size, * element_value);

		if ( snapshot->max_accesses < * element_value)
			snapshot->max_accesses = * element_value;

		* element_value = 0;
	}
	fprintf(snapshot->snapshot, "\n");
	fclose(snapshot->snapshot);

	/* Run the script */
	FILE *script_file;
	char cmd[MAX_PATH_SIZE];

	char script_file_name[MAX_PATH_SIZE];
	char plot_file_name[MAX_PATH_SIZE];

	/* Create plot file */
	for (int i = 0; i < THREEDIM + 1; i++)
	{
		snprintf(plot_file_name, MAX_PATH_SIZE, "%d_%d_%dD_%s.ps",
				mem_snap_period, snapshot->mem_snapshot_region_size,
				i+2 ,snapshot->file_name);
		if (!file_can_open_for_write(plot_file_name))
		{
			fatal("%s: cannot write GPU occupancy calculation plot",
					plot_file_name);
		}

		script_file = file_create_temp(script_file_name,
				MAX_PATH_SIZE);
		fprintf(script_file, "unset origin\n");
		fprintf(script_file, "unset label\n");
		fprintf(script_file, "set term postscript eps enhanced color\n");
		fprintf(script_file, "set ticslevel 0\n");
		fprintf(script_file, "set nohidden3d\n");
		fprintf(script_file, "set size square\n");
		fprintf(script_file, "unset key\n");
		fprintf(script_file, "set origin 0,-0.1\n");
		switch(i%2)
		{
		case 1:
			/* 3D view */
			fprintf(script_file, "set view 30,40,0.5\n");
			break;
		case 0:
		default:
			/* 2D view */
			fprintf(script_file, "set view 0,0, 0.5\n");
		}

		fprintf(script_file, "set pm3d\n");
		fprintf(script_file, "set palette defined "
				"(0 \"white\", 0.0001 \"black\", "
				"10 \"gray\", 60 \"cyan\", 100 \"blue\")\n");
		fprintf(script_file, "set colorbox vertical user origin "
				".2,.28 size 0.03, 0.26\n");
		fprintf(script_file, "unset surface\n");
		fprintf(script_file, "set cbtics font \"Helvettica, 6\"\n");
		if (snapshot->partial_snapshot)
			fprintf(script_file, "set xlabel 'Time (cycles) -- PARTIAL' "
					"font \"Helvettica,7\" tc rgb \"red\"\n");
		else
			fprintf(script_file, "set xlabel 'Time (cycles)' "
					"font \"Helvettica,7\"\n");

		fprintf(script_file, "set xtics font \"Helvettica, 6\"\n");
		fprintf(script_file, "set xtics offset -0.5,-0.2\n");
		fprintf(script_file, "set ylabel 'Address (Hex)' "
				"rotate by 135 offset 2, 0 font \"Helvettica, 7\"\n");
		fprintf(script_file, "set ytics offset 1.5,0\n");
		fprintf(script_file, "set ytics font \"Helvettica, 8\"\n");
		fprintf(script_file, "set mytics 4\n");
		fprintf(script_file, "unset ztics\n");
		fprintf(script_file, "set label \"Number of Accesses\" "
				"font \"Helvetica,7\" at screen 0.27, "
				"screen 0.35 rotate by 90\n");
		fprintf(script_file, "splot \"%s\" with lines\n",
				snapshot->file_name);
		fprintf(script_file, "unset multiplot\n");
		fclose(script_file);

		/* Plot */
		sprintf(cmd, "gnuplot %s > %s", script_file_name, plot_file_name);
		int err = system(cmd);
		if (err)
			warning("could not execute gnuplot\nEither gnuplot is "
					"not installed or is not the supported version\n");

		/* Remove temporary files */
		unlink(script_file_name);
	}
	if (!KEEP_TEMP)
		unlink(snapshot->file_name);

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
