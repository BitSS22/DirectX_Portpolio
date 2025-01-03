#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineCore.h>
#include "PlayMode.h"
#include <EngineCore/EngineVertex.h>
#include <EngineCore/EngineVertexBuffer.h>
#include <EngineCore/EngineVertexShader.h>


CreateContentsCoreDefine(UContentsCore);

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}


void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	FVector WindowSize = { 768.f, 480.f };

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	_Data.WindowPos = FVector((width - WindowSize.X) / 2.f, (height - WindowSize.Y) / 2.f);
	_Data.WindowSize = WindowSize;

	// CreateMesh
	


	UEngineCore::CreateLevel<APlayMode, APawn>("PlayLevel");
	UEngineCore::OpenLevel("PlayLevel");
}

void UContentsCore::EngineTick(float _DeltaTime)
{
}

void UContentsCore::EngineEnd()
{
}