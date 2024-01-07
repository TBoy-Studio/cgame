#include <components/components.h>

// The amount of components is dependent on the size of the mask
const unsigned int MAX_COMPONENTS = sizeof(CGameEntityComponentMask) << 3;

const size_t component_sizes[4] = {
    sizeof(CGameComponentTransform),
    sizeof(CGameComponentMeshRenderer),
    sizeof(CGameComponentController),
    sizeof(CGameComponentRigidbody)
};