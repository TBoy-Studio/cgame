#include <tengine.h>
#include <assert.h>

#define NELEMENTS 128
#define ALIGN 16

int main()
{
    //----------------------------------------------------
    // Testing Alligned
    //----------------------------------------------------
    vec4 *vectors = cgame_memory_alligned_alloc(NELEMENTS * sizeof(vec4), ALIGN);

    // Test if actually aligned
    assert((uintptr_t)vectors % ALIGN == 0);

    // Test if shift value is in accepted range
    assert(((unsigned char *)vectors)[-1] <= ALIGN);

    float value = 0.0f;
    for(size_t i = 0; i < NELEMENTS; i++)
    {
        vectors[i][0] = value;
        vectors[i][1] = value;
        vectors[i][2] = value;
        vectors[i][3] = value;

        value += 1.0f;
    }

    // Check if values are stored properly
    assert(vectors[NELEMENTS - 1][3] == 127.0f);

    cgame_memory_alligned_free(vectors);
}