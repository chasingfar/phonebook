//
// Created by chasingfar on 2018/3/11.
//

#ifndef PHONEBOOK_PRE_ALLOC_H
#define PHONEBOOK_PRE_ALLOC_H

#define PRE_ALLOC_SIZE (32*1024)
#define CHANNEL_SIZE 16
void *pre_alloc_init(unsigned int channel);
void *pre_alloc(size_t size,unsigned int channel);
#endif //PHONEBOOK_PRE_ALLOC_H
