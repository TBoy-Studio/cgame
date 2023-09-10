#include <memory.h>

// ------------------------------------------------------------------
// ------------------------------------------------------------------
/*
    ALLIGNED ALLOCATOR FUNCTIONS
*/
static inline uintptr_t _mem_align_pointer(uintptr_t address, size_t align)
{
    const size_t mask = align - 1;
    assert((align & mask) == 0);
    return (address + mask) & ~mask;
}

void *mem_create_aligned_alloc(size_t bytes, size_t align)
{
    // Calculate actual allocation size
    size_t actual_bytes = bytes + align;

    // Allocate
    unsigned char *p_raw_mem = (unsigned char *)malloc(actual_bytes);

    // Allign
    unsigned char *p_alligned_mem = (unsigned char *)_mem_align_pointer((uintptr_t)p_raw_mem, align);
    if(p_alligned_mem == p_raw_mem) p_alligned_mem += align;

    // Store allignment shift
    ptrdiff_t shift = p_alligned_mem - p_raw_mem;
    assert(shift > 0 && shift <= 256);
    p_alligned_mem[-1] = shift & 0xFF;

    return p_alligned_mem;
}

void mem_free_aligned(void *p_mem)
{
    if(p_mem)
    {
        unsigned char *p_alligned_mem = (unsigned char *)p_mem;

        ptrdiff_t shift = p_alligned_mem[-1];

        if(shift == 0) shift = 256;

        unsigned char *p_raw_mem = p_alligned_mem - shift;
        free(p_raw_mem);
    }
}

// ------------------------------------------------------------------
// ------------------------------------------------------------------
/*
    ------------------
    | POOL ALLOCATOR |
    ------------------
    Create a pool allocator for num elements of element_size
*/
PoolAllocator mem_pool_create(size_t element_size, size_t num)
{
    // In order to store free list inside pool 
    // element_size needs to be large enough to hold a pointer type
    assert(element_size >= sizeof(void*));

    PoolAllocator pool;

    // Calculate alloc size
    size_t actual_bytes = element_size * num;

    // Allocate
    pool.memory = malloc(actual_bytes);
    pool.next_free = pool.memory;
    pool.element_size = element_size;
    pool.num_elements = num;

    // Build free list in the memory blocks
    unsigned char *free_list = pool.memory;
    for(size_t i = 0; i < num - 1; i++)
    {
        // This feels like a crime
        *(void **)free_list = free_list + element_size;
        free_list += element_size;
    }
    // Last element's next pointer should be null 
    *(void**)free_list = 0x0;

    return pool;
}

/*
    Get a pointer to a free spot in this pool
*/
void *mem_pool_element_new(PoolAllocator *pool)
{
    // Get the next free location in the pool
    void *element = pool->next_free;

    // Get the next pointer of this new element
    // This will be the new next free element
    pool->next_free = *(void**)pool->next_free;

    return element;
}

/*
    Remove the element at the specified index from this pool.
*/
void *mem_pool_element_free(PoolAllocator *pool, size_t index)
{
    // Get the current next pointer
    void *current_next = pool->next_free;

    // Get pointer to address of the element as pointer to a pointer
    void **element = pool->memory + index * pool->element_size;

    // Write the current next pointer to this element 
    *element = current_next;

    // Update pool's next pointer to point to this element
    // which is now open for business
    pool->next_free = element;

}

/*
    Frees all memory associated with this PoolAllocator
    All pointers in the struct will become NULL 
*/
void mem_pool_free(PoolAllocator *pool)
{
    free(pool->memory);

    // Reset all values
    pool->memory = 0;
    pool->element_size = 0;
    pool->next_free = 0;
    pool->num_elements = 0;
}

// ------------------------------------------------------------------
// ------------------------------------------------------------------
/*
    -------------------
    | STACK ALLOCATOR |
    -------------------
    Create a stack allocator with size bytes
*/
StackAllocator mem_stack_create(size_t bytes)
{
    StackAllocator allocator = {
        .memory = malloc(bytes),
        .size = bytes,
        .top = 0
    };
    return allocator;
}

/*
    Create block of size bytes on stack
*/
void *mem_stack_alloc(StackAllocator*allocator, size_t bytes)
{
    // Make sure allocation fits
    assert((allocator->top + bytes) < allocator->size);

    // Save current marker
    StackMarker current_top = allocator->top;

    // Increase stack pointer
    allocator->top += bytes;

    // Return pointer to the memory block
    return allocator->memory + current_top;
}

/*
    Get the current top of the stack
*/
inline StackMarker mem_stack_get_marker(StackAllocator *allocator)
{
    return allocator->top;
}

/*
    Free stack memory up to specified marker
*/
inline void mem_stack_rollback(StackAllocator *allocator, StackMarker marker)
{
    allocator->top = marker;
}

/*
    Clear all stack memory
*/
inline void mem_stack_clear(StackAllocator* allocator)
{
    allocator->top = 0;
}

/*
    Frees all memory associated with this stack allocator
    All pointers in the struct will become NULL
*/
inline void mem_stack_free(StackAllocator* allocator)
{
    free(allocator->memory);

    allocator->memory = 0;
    allocator->size = 0;
    allocator->top = 0;
}