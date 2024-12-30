#pragma once
#include <EngineCore/Actor.h>

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

public:
	static ACenter* GetCenter()
	{
		return Center;
	}

};

