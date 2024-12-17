#include "pch.h"
#include "ActorComponent.h"

UActorComponent::UActorComponent()
{
}

UActorComponent::~UActorComponent()
{
}

class AActor* UActorComponent::GetActor()
{
	return Actor;
}