#include <controller.h>

void cgame_controller_register(const CGameController *controller, CGameEntityScene *scene)
{
    CGameEntity entity = cgame_entity_create(scene);
    cgame_entity_add_component(scene, entity, CONTROLLER);
    CGameComponentController *controller_comp = cgame_entity_get_component(scene, entity, CONTROLLER);
    controller_comp->start = controller->start;
    controller_comp->update = controller->update;
}