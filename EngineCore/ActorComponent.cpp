#include "pch.h"
#include "ActorComponent.h"

UActorComponent::UActorComponent()
{
}

UActorComponent::~UActorComponent()
{
}

std::shared_ptr<class AActor> UActorComponent::GetActor()
{
	return nullptr;
}