//
// Created by chasingfar on 2018/3/11.
//
#include <stdlib.h>
#include "pre_alloc.h"

void *pre_alloc_last_ptr[CHANNEL_SIZE];
int pre_alloc_free_space[CHANNEL_SIZE];

void *pre_alloc(size_t size, unsigned int channel)
{
    if (pre_alloc_free_space[channel] < size) {
        pre_alloc_last_ptr[channel] = malloc(PRE_ALLOC_SIZE);
        pre_alloc_free_space[channel] = PRE_ALLOC_SIZE;
    }
    void *tmp = pre_alloc_last_ptr[channel];
    pre_alloc_last_ptr[channel] += size;
    pre_alloc_free_space[channel] -= size;
    return tmp;
}

void *pre_alloc_init(unsigned int channel)
{
    pre_alloc_last_ptr[channel] = malloc(PRE_ALLOC_SIZE);
    pre_alloc_free_space[channel] = PRE_ALLOC_SIZE;
}
