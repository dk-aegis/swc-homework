#include "alloc.h"

struct alloc_state astate = {
    .is_init = 0
};

void *swc_alloc(size_t size){
    if(astate.is_init == 0){
        init_alloc();
    }

    if(size < 0 || size > MAX_ALLOC_SIZE){
        return NULL;
    }

    size_t req_size = make_align(size);
    size_t alloc_size = req_size + METADATA_SIZE;

    void *addr = find_free_chunk(req_size);
    if(addr != NULL){
        return chunk_at_offset(addr, METADATA_SIZE);
    }

    addr = mem_alloc(alloc_size);
    if(addr == NULL){
        return NULL;
    }

    struct alloc_chunk *chunk = (struct alloc_chunk*)addr;
    chunk->prev_size = 0;
    chunk->size = req_size;

    return chunk_at_offset(chunk, METADATA_SIZE);
}

void *mem_alloc(size_t size){
    int err = brk(NULL);
    if(err == -1){
        return NULL;
    }

    void *addr = sbrk(size);
    if(addr == (void*)-1){
        return NULL;
    }

    return addr;
}

void swc_free(void *addr){
    if(addr == NULL){
        return;
    }

    /* double free bug! */

    addr = chunk_at_offset(addr, -METADATA_SIZE);
    struct alloc_chunk *chunk = (struct alloc_chunk*)addr;

    int index = (chunk->size / 8) - 1;
    insert_freebin(chunk, index);
}

void *find_free_chunk(size_t size){
    int index = (size / 8) - 1; 
    if(astate.freebin[index] == NULL){
        return NULL;
    }

    struct alloc_chunk *mem = astate.freebin[index];
    astate.freebin[index] = mem->fd;

    return (void*)mem;
}

int make_align(size_t size){
    if(size >= 0 && size <= 8){
        return MIN_PAYLOAD_SIZE;
    }

    int div = size / MIN_PAYLOAD_SIZE;
    int rest = size % MIN_PAYLOAD_SIZE;

    if(rest == 0){
        return size;
    }

    return (div * MIN_PAYLOAD_SIZE) + MIN_PAYLOAD_SIZE;
}

void init_alloc(){
    for(int i=0;i<FREEBIN_NUM;i++){
        astate.freebin[i] = NULL;
    }

    astate.is_init = 1;
}

void insert_freebin(struct alloc_chunk *chunk, int index){
    if(astate.freebin[index] == NULL){
        astate.freebin[index] = chunk; 
        chunk->fd = NULL;
        return;
    }
    
    struct alloc_chunk *mem = astate.freebin[index]; 
    chunk->fd = mem;
    chunk->prev_size = mem->size;
    astate.freebin[index] = chunk; 
}
