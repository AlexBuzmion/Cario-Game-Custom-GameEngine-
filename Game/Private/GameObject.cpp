#include "Game/Public/GameObject.h"

GameObject::GameObject()
{
	LOG_LINE("Game Object Created");
}

GameObject::~GameObject()
{
	LOG_LINE("Game Object Destroyed");
}

void GameObject::BeginPlay()
{
	LOG_LINE("Game Object Begin Play Called");
}

void GameObject::EndPlay()
{
	LOG_LINE("Game Object End play called");
}

void GameObject::Tick(float deltaTime)
{
	LOG_LINE("Game Object Tick called");
}
