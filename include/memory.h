#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

typedef size_t CGameMemoryStackMarker;

typedef struct
{
    size_t size;
    CGameMemoryStackMarker top;
    void *memory;
}
CGameMemoryStackAllocator;

typedef struct
{
    size_t element_size;
    size_t num_elements;
    void *next_free;
    void *memory; 
} 
CGameMemoryPoolAllocator;

/*
    ----------------------------
    Alligned Memory Block
    ----------------------------
*/
/*
    Alloc a block of memory aligned to align bytes
*/
void *cgame_memory_alligned_alloc(size_t bytes, size_t align);
/*
    Free the alligned block of memory
*/
void cgame_memory_alligned_free(void *p_mem);

/*
    ----------------------------
    Stack allocator
    ----------------------------
*/
/*
    Alloc size bytes for use as a stack
*/
CGameMemoryStackAllocator cgame_memory_stack_create(size_t size);

/*
    Alloc specified number of bytes on this stack
*/
void *cgame_memory_stack_alloc(CGameMemoryStackAllocator *allocator, size_t bytes);

/*
    Clear any memory allocated beyond this marker
*/
void cgame_memory_stack_rollback(CGameMemoryStackAllocator *allocator, CGameMemoryStackMarker marker);

/*
    Get the current marker of this stack
*/
CGameMemoryStackMarker cgame_memory_stack_get_marker(CGameMemoryStackAllocator *allocator);

/*
    Clear everything in this stack (reset stack marker)
*/
void cgame_memory_stack_clear(CGameMemoryStackAllocator* allocator);

/*
    Free any memory associated with this stack
*/
void cgame_memory_stack_free(CGameMemoryStackAllocator *allocator);


/*
    ----------------------------
    Pool allocator
    ----------------------------
*/
/*
    Allocate a block large enough to hold a component pool for 
    the specified number of elements with certain size
*/
CGameMemoryPoolAllocator cgame_memory_pool_create(size_t element_size, size_t num);

/*
    Add single element to component pool
*/
void *cgame_memory_pool_element_add(CGameMemoryPoolAllocator *pool);

/*
    Remove single element from component pool at specified index
*/
void cgame_memory_pool_element_remove(CGameMemoryPoolAllocator *pool, size_t index);

/*
    Free memory allocated for this Pool Allocator
*/
void cgame_memory_pool_free(CGameMemoryPoolAllocator *pool);