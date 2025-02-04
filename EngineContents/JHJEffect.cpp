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
	// ����Ʈ ����Ʈ�� ������ ���� Ÿ���� �����ϴ� ������ �����Ѵ�.
	CopyTarget = std::make_shared<UEngineRenderTarget>();
	CopyTarget->CreateTarget(UEngineCore::GetScreenScale());

	// Renderer���� ������� ���������� 

	RenderUnit.SetMesh("FullRect");
	RenderUnit.SetMaterial("JHJEffect");

	
}

void UJHJEffect::Effect(UEngineCamera* _Camera, float _DeltaTime)
{
	UPostEffect::Effect(_Camera, _DeltaTime);
	// ���� Ÿ���� Copy�մϴ�.
	ResultTarget->CopyTo(CopyTarget);

	// ����Ʈ Ÿ���� ������ ����� �Ǿ���.
	ResultTarget->Setting();
	// ����Ʈ Ÿ���� ������ ����� �Ǿ���.
	RenderUnit.SetTexture("ImageTexture", CopyTarget->GetTexture());
	RenderUnit.Render(_Camera, _DeltaTime);
	RenderUnit.Reset();

}