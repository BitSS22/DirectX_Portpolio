#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineGraphicDevice.h>
#include <EngineCore/EngineVertex.h>
#include <EngineCore/EngineIndexBuffer.h>
#include <EngineCore/Mesh.h>
#include <EngineCore/EngineBlend.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EnginePlatform/EngineSound.h>
#include <EngineCore/EngineFont.h>

#include <EnginePlatform/EngineThread.h>



void UContentsCore::MyGSetting()
{


	int Count = 24;
	{
		std::vector<FEngineVertex> Vertexs = {
			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f },  {1.0f, 0.0f, 0.0f, 1.f} }, //빨강
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 0.0f, 0.0f, 1.f} },
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 0.0f, 1.f} },

			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f },  {1.0f, 0.0f, 1.0f, 1.0f} }, //마젠타
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 0.0f, 1.0f, 1.0f}},
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 1.0f, 1.0f} },

			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.f} }, //뒷면 빨강
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f }, {1.0f, 0.0f, 0.0f, 1.f}},
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 0.0f, 1.f}},

			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 1.0f, 1.0f} }, //뒷면 마젠타
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } ,{1.0f, 0.0f, 1.0f, 1.0f}},
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 1.0f, 1.0f} },

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 1.0f, 0.0f, 1.0f} }, //앞면 노랑
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {1.0f, 1.0f, 0.0f, 1.0f} },

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}},
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } ,  {0.0f, 1.0f, 0.0f, 1.0f}},
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {0.0f, 1.0f, 0.0f, 1.0f}},

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 1.0f, 0.0f, 1.0f} }, //
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } ,  {1.0f, 1.0f, 0.0f, 1.0f}},

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } ,  {0.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } ,  {0.0f, 1.0f, 0.0f, 1.0f} },
		};
		UEngineVertexBuffer::Create("Test", Vertexs);
	}

	{
		std::vector<unsigned int> Indexs;

		for (int i = 0; i < Count; i++)
		{
			Indexs.push_back(i);
		}

		UEngineIndexBuffer::Create("Test", Indexs);
	}

	{
		UMesh::Create("Test");
	}

	{
		UEngineDirectory CurDir;
		CurDir.MoveParentToDirectory("ContentsShader");

		std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

		for (size_t i = 0; i < ShaderFiles.size(); i++)
		{
			UEngineShader::ReflectionCompile(ShaderFiles[i]);
		}
	}

	// 로딩용 리소스
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("Test");
		Mat->SetVertexShader("TestShader.fx");
		Mat->SetPixelShader("TestShader.fx");
	}


	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Sound");
		// 로딩바 만들고 싶으면  100개면 10 10 10 10 10 10
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".wav", ".mp3" });

		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Font");

		UEngineFile FontFiles = Dir.GetFile("PFStardust.ttf");
		
		UEngineFont::Load("PFStardust", FontFiles.GetPathToString());
		// UEngineFont::Load("PFStardust", "SB 어그로 Bold");
	}

}
