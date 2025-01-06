#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineCore.h>
#include "PlayMode.h"
#include "Vertex.h"
#include <EngineCore/EngineVertexBuffer.h>
#include <EngineCore/Mesh.h>
#include <EngineCore/EngineMaterial.h>


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

	// Create VertexBuffer
	const int VertexCount = 8;
	std::vector<PolygonVertex> Vertexes = {};
	Vertexes.reserve(VertexCount);

	Vertexes.push_back(PolygonVertex(float4(-0.5f, 0.5f, 0.5f, 1.0f), float4(1.0f, 0.0f, 0.0f, 1.0f)));
	Vertexes.push_back(PolygonVertex(float4(0.5f, 0.5f, 0.5f, 1.0f), float4(0.0f, 1.0f, 0.0f, 1.0f)));

	Vertexes.push_back(PolygonVertex(float4(-0.5f, 0.5f, -0.5f, 1.0f), float4(0.0f, 0.0f, 1.0f, 1.0f)));
	Vertexes.push_back(PolygonVertex(float4(0.5f, 0.5f, -0.5f, 1.0f), float4(1.0f, 1.0f, 0.0f, 1.0f)));

	Vertexes.push_back(PolygonVertex(float4(-0.5f, -0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 1.0f, 1.0f)));
	Vertexes.push_back(PolygonVertex(float4(0.5f, -0.5f, -0.5f, 1.0f), float4(0.0f, 1.0f, 1.0f, 1.0f)));

	Vertexes.push_back(PolygonVertex(float4(-0.5f, -0.5f, 0.5f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f)));
	Vertexes.push_back(PolygonVertex(float4(0.5f, -0.5f, 0.5f, 1.0f), float4(0.0f, 0.0f, 0.0f, 1.0f)));

	UEngineVertexBuffer::Create("Polygon", Vertexes);

	// Create IndexBuffer
	const int IndexCount = 36;
	std::vector<unsigned int> Indexes = {};
	Indexes.reserve(IndexCount);

	Indexes.push_back(0);
	Indexes.push_back(1);
	Indexes.push_back(2);

	Indexes.push_back(2);
	Indexes.push_back(1);
	Indexes.push_back(3);

	Indexes.push_back(2);
	Indexes.push_back(3);
	Indexes.push_back(4);

	Indexes.push_back(4);
	Indexes.push_back(3);
	Indexes.push_back(5);

	Indexes.push_back(4);
	Indexes.push_back(5);
	Indexes.push_back(6);

	Indexes.push_back(6);
	Indexes.push_back(5);
	Indexes.push_back(7);

	Indexes.push_back(6);
	Indexes.push_back(7);
	Indexes.push_back(0);

	Indexes.push_back(0);
	Indexes.push_back(7);
	Indexes.push_back(1);

	Indexes.push_back(0);
	Indexes.push_back(2);
	Indexes.push_back(6);

	Indexes.push_back(6);
	Indexes.push_back(2);
	Indexes.push_back(4);

	Indexes.push_back(3);
	Indexes.push_back(1);
	Indexes.push_back(5);

	Indexes.push_back(5);
	Indexes.push_back(1);
	Indexes.push_back(7);

	UEngineIndexBuffer::Create("Polygon", Indexes);

	// Create Mesh
	UMesh::Create("Polygon");

	

	// Create Meterial
	std::shared_ptr<UEngineMaterial>Material = UEngineMaterial::Create("Polygon");
	Material->SetPixelShader("Shader.fx");
	Material->SetVertexShader("Shader.fx");

	UEngineCore::CreateLevel<APlayMode, APawn>("PlayLevel");
	UEngineCore::OpenLevel("PlayLevel");
}

void UContentsCore::EngineTick(float _DeltaTime)
{
}

void UContentsCore::EngineEnd()
{
}