#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class APlayLevel : public AActor
{
public:
	// constrcuter destructer
	APlayLevel();
	~APlayLevel();

	// delete Function
	APlayLevel(const APlayLevel& _Other) = delete;
	APlayLevel(APlayLevel&& _Other) noexcept = delete;
	APlayLevel& operator=(const APlayLevel& _Other) = delete;
	APlayLevel& operator=(APlayLevel&& _Other) noexcept = delete;


protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

	std::shared_ptr<class ACenter> Center = nullptr;

};

