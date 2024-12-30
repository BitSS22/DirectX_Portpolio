#include "PreCompile.h"
#include "Center.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "PolygonRenderer.h"

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

	Polygon = CreateDefaultSubObject<UPolygonRenderer>();
	Polygon->SetMesh("Polygon");
	SetActorRelativeScale3D(FVector(100.f, 100.f, 1.f));
}

void ACenter::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}