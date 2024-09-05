#include "Game/Public/Component.h"
#include "Game/Public/GameObject.h"

Component::Component(std::shared_ptr<GameObject> inOwner)
{
	mOwner = inOwner; // Assigning the owning GameObject to the component, establishing the relationship
}

std::weak_ptr<GameObject> Component::GetOwner() const {
	return mOwner;
}

Component::~Component()
{
	// No specific cleanup needed here, but destructor ensures proper cleanup if extended
};
