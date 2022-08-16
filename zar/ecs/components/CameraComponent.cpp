#include "CameraComponent.h"

zar::CameraComponent::~CameraComponent()
{
    spdlog::info("~CameraComponent() destroyed!");
}

zar::CameraComponent::CameraComponent(GLCamera* camera)
{
    this->obj = camera;
}

zar::CameraComponent::CameraComponent(GLCamera camera)
{
    this->obj = &camera;
}

void zar::CameraComponent::start()
{
    IComponent::start();
}

void zar::CameraComponent::update()
{
    IComponent::update();
    // spdlog::info("position: ({},{},{})", obj->position.x, obj->position.y, obj->position.z);
}
