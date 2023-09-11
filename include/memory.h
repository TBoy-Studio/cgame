#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

typedef size_t StackMarker;

typedef struct
{
    size_t size;
    StackMarker top;
    void *memory;
}
StackAllocator;

typedef struct
{
    size_t element_size;
    size_t num_elements;
    void *next_free;
    void *memory; 
} 
PoolAllocator;

/*
    Alligned allocator
*/
void *mem_aligned_create(size_t bytes, size_t align);
void mem_aligned_free(void *p_mem);

/*
    Stack allocator
*/
StackAllocator mem_stack_create(size_t bytes);
void *mem_stack_alloc(StackAllocator*allocator, size_t bytes);
void mem_stack_rollback(StackAllocator *allocator, StackMarker marker);
void mem_stack_clear(StackAllocator* allocator);


/*
    Pool allocator
*/
PoolAllocator mem_pool_create(size_t element_size, size_t num);
void *mem_pool_element_new(PoolAllocator *pool);
void *mem_pool_element_free(PoolAllocator *pool, size_t index);
void mem_pool_free(PoolAllocator *pool);