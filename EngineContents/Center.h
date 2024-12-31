#pragma once
#include <EngineCore/Actor.h>
#include <memory>
#include "PolygonRenderer.h"
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class ACenter : public AActor
{
public:
	ACenter();
	~ACenter();

	ACenter(const ACenter& _Other) = delete;
	ACenter(ACenter&& _Other) noexcept = delete;
	ACenter& operator=(const ACenter& _Other) = delete;
	ACenter& operator=(ACenter&& _Other) noexcept = delete;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

public:

private:
	inline static ACenter* Center = nullptr;
	std::shared_ptr<USpriteRenderer> Polygon = nullptr;

public:
	static ACenter* GetCenter()
	{
		return Center;
	}

};

