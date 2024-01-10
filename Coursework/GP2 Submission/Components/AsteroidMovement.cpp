#include "AsteroidMovement.h"
#include "TransformComponent.h"

void AsteroidMovement::onUpdate()
{
    TransformComponent& transform = entity.get()->GetComponent<TransformComponent>();
    TransformComponent& playerTransform = player.GetComponent<TransformComponent>();

    glm::vec3 diff = *playerTransform.getPos() - *transform.getPos();
    float movementSpeed = 0.01f; // Adjust this value to control the speed of movement

    glm::vec3 movement = diff * movementSpeed;
    transform.setPos(*transform.getPos() + movement);
}
