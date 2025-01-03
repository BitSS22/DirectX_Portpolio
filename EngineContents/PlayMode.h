#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class APlayMode : public AActor
{
public:
	// constrcuter destructer
	APlayMode();
	~APlayMode();

	// delete Function
	APlayMode(const APlayMode& _Other) = delete;
	APlayMode(APlayMode&& _Other) noexcept = delete;
	APlayMode& operator=(const APlayMode& _Other) = delete;
	APlayMode& operator=(APlayMode&& _Other) noexcept = delete;


protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

	std::shared_ptr<class ACenter> Center = nullptr;

};

