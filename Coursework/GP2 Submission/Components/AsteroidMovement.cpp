#include "AsteroidMovement.h"
#include "TransformComponent.h"
#include "../Base Scripts/Time.h"

void AsteroidMovement::onUpdate()
{
    TransformComponent& transform = entity.get()->GetComponent<TransformComponent>();

    float movementSpeed = 10.0f * Time::getInstance().getDeltaTime(); // Adjust this value to control the speed of movement

    glm::vec3 movement = targetDir * movementSpeed;
    transform.setPos(*transform.getPos() + movement);
}
