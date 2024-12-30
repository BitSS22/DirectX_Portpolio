#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include "PlayLevel.h"
#include <EngineCore/Mesh.h>
#include "Vertex.h"
#include "EngineCore/VertexBuffer.h"
#include "EngineCore/IndexBuffer.h"

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


	std::vector<PolygonVertex> VectexBuffer = {};
	VectexBuffer.reserve(6);

	for (int i = 0; i < 6; ++i)
		VectexBuffer.push_back(PolygonVertex(FVector::AngleToVectorRad(360.f / (i + 1) * i), FVector(1.0f, 0.0f, 0.0f, 1.0f)));

	UVertexBuffer::Create("Polygon", VectexBuffer);


	std::vector<unsigned int> Indexs = {};
	Indexs.reserve(6);

	Indexs.push_back(0);
	Indexs.push_back(1);
	Indexs.push_back(2);

	Indexs.push_back(2);
	Indexs.push_back(3);
	Indexs.push_back(1);

	UIndexBuffer::Create("Polygon", Indexs);

	UMesh::Create("Polygon");

	UEngineCore::CreateLevel<APlayLevel, APawn>("PlayLevel");
	UEngineCore::OpenLevel("PlayLevel");
}

void UContentsCore::EngineTick(float _DeltaTime)
{
}

void UContentsCore::EngineEnd()
{
}