#ifndef __ALLOC_H_
#define __ALLOC_H_

#include <unistd.h>
#include <stdint.h>

#define FREEBIN_NUM 8
#define MAX_ALLOC_SIZE 64

#define METADATA_SIZE 8
#define MIN_PAYLOAD_SIZE 8

#define chunk_at_offset(p, s)  ((void*)(((char*)(p)) + (s)))

struct alloc_chunk{
    int32_t prev_size;         /* metadata */
    int32_t size;              /* metadata */
    struct alloc_chunk *fd;    /* payload */
};

struct alloc_state{
    struct alloc_chunk *freebin[FREEBIN_NUM];
    int8_t is_init; 
};

void *swc_alloc(size_t size);
void swc_free(void *addr);

void init_alloc();
void *find_free_chunk(size_t size);
int make_align(size_t size);
void *mem_alloc(size_t size);
void insert_freebin(struct alloc_chunk *chunk, int index);
void debug(int index);

#endif

