#pragma once
#include <EngineCore/EngineRenderTarget.h>

// Ό³Έν :
class UJHJEffect : public UPostEffect
{
public:
	// constrcuter destructer
	UJHJEffect();
	~UJHJEffect();

	// delete Function
	UJHJEffect(const UJHJEffect& _Other) = delete;
	UJHJEffect(UJHJEffect&& _Other) noexcept = delete;
	UJHJEffect& operator=(const UJHJEffect& _Other) = delete;
	UJHJEffect& operator=(UJHJEffect&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Effect(UEngineCamera* Camera, float _DeltaTime) override;

private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;

	// URenderUnit SecondEffect;
};

