#include "PreCompile.h"
#include "Center.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "PolygonRenderer.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineConstantBuffer.h>

ACenter::ACenter()
{
	std::shared_ptr<UDefaultSceneComponent> Root = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Root;
	Center = this;

	Polygon = CreateDefaultSubObject<UPolygonRenderer>();
	Polygon->SetupAttachment(RootComponent);
	Polygon->SetRelativeScale3D({ 100.f, 100.f, 100.f });
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



	FVector Dir = {};

	if (UEngineInput::IsPress('W'))
		Dir.Y += 1.f;
	if (UEngineInput::IsPress('A'))
		Dir.X -= 1.f;
	if (UEngineInput::IsPress('S'))
		Dir.Y -= 1.f;
	if (UEngineInput::IsPress('D'))
		Dir.X += 1.f;
	if (UEngineInput::IsPress('Q'))
		Dir.Z += 1.f;
	if (UEngineInput::IsPress('E'))
		Dir.Z -= 1.f;

	AddActorRotation(Dir * 100.f * _DeltaTime);

	Dir = { 0.f, 0.f, 0.f, 1.f };




	if (UEngineInput::IsPress(VK_UP))
		Dir.Y += 1.f;
	if (UEngineInput::IsPress(VK_LEFT))
		Dir.X -= 1.f;
	if (UEngineInput::IsPress(VK_DOWN))
		Dir.Y -= 1.f;
	if (UEngineInput::IsPress(VK_RIGHT))
		Dir.X += 1.f;
	if (UEngineInput::IsPress('O'))
		Dir.Z -= 1.f;
	if (UEngineInput::IsPress('P'))
		Dir.Z += 1.f;

	AddRelativeLocation(Dir * 100.f * _DeltaTime);

	Dir = { 0.f, 0.f, 0.f, 1.f };
}