#ifndef __BLOCK_BY_BLOCK_STRATEGY_H__
#define __BLOCK_BY_BLOCK_STRATEGY_H__

void *block_by_block_strategy_create(int num_devices, unsigned int dims, const unsigned int *groups);
int block_by_block_strategy_get_partition(void *inst, int id, int desired_groups, unsigned int *group_offset, unsigned int *group_count, long long now);
void block_by_block_strategy_destroy(void *inst);

#endif
