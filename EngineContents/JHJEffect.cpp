#include "PreCompile.h"
#include "JHJEffect.h"

UJHJEffect::UJHJEffect()
{
}

UJHJEffect::~UJHJEffect()
{
}

void UJHJEffect::Init()
{
	UPostEffect::Init();
	// 포스트 이펙트의 시작은 원본 타겟을 복사하는 것으로 시작한다.
	CopyTarget = std::make_shared<UEngineRenderTarget>();
	CopyTarget->CreateTarget(UEngineCore::GetScreenScale());

	// Renderer에서 만들어진 랜더유닛은 

	RenderUnit.SetMesh("FullRect");
	RenderUnit.SetMaterial("JHJEffect");

	
}

void UJHJEffect::Effect(UEngineCamera* _Camera, float _DeltaTime)
{
	UPostEffect::Effect(_Camera, _DeltaTime);
	// 기존 타겟을 Copy합니다.
	ResultTarget->CopyTo(CopyTarget);

	// 리절트 타겟이 랜더링 대상이 되었다.
	ResultTarget->Setting();
	// 리절트 타겟이 랜더링 대상이 되었다.
	RenderUnit.SetTexture("ImageTexture", CopyTarget->GetTexture());
	RenderUnit.Render(_Camera, _DeltaTime);
	RenderUnit.Reset();

}