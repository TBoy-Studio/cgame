#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

typedef size_t StackMarker;

typedef struct
{
    StackMarker top;
    size_t size;
    void *memory;
}
StackAllocator;

typedef struct
{
    void *next_free;
    void *memory; 
} 
PoolAllocator;

/*
    Alligned allocator
*/
void *mem_create_aligned_alloc(size_t bytes, size_t align);
void mem_free_aligned(void *p_mem);

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
PoolAllocator mem_create_pool_alloc(size_t element_size, size_t num);