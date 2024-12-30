#include "PreCompile.h"
#include "Center.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>

ACenter::ACenter()
{
	std::shared_ptr<UDefaultSceneComponent> Root = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Root;
	Center = this;
}

ACenter::~ACenter()
{
}

void ACenter::BeginPlay()
{
	AActor::BeginPlay();
}

void ACenter::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}