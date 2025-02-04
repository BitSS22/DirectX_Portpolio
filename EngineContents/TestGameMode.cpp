#include "PreCompile.h"
#include "TestGameMode.h"
#include "TitleLogo.h"
#include "Monster.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include "TestActor.h"
#include <EngineCore/EngineCore.h>
#include "TitleGameMode.h"
#include "TileMapGameMode.h"
#include "TitleHUD.h"

ATestGameMode::ATestGameMode()
{
	// 레벨마다 해주셔야 합니다.
	// 이걸 UI공유할건지 
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Player");
	// 충돌체크 해야한다.
	GetWorld()->LinkCollisionProfile("Player", "Monster");

	

	// 카메라를 일정거리 뒤로 가서 
	// 카메라 위치조정을 무조건 해줘야 할것이다.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({0.0f, 0.0f, -1000.0f, 1.0f});
	Camera->GetCameraComponent()->SetZSort(0, true);

	{
		std::shared_ptr<ATestActor> NewMonster = GetWorld()->SpawnActor<ATestActor>();
		NewMonster->SetActorRelativeScale3D({ 100.0f, 200.0f, 100.0f, 1.0f });
		NewMonster->SetActorLocation({ 0.0f, 0.0f, 0.0f });
	}


}

ATestGameMode::~ATestGameMode()
{

}

void ATestGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

	if (true == ThreadLoadingInit)
	{
		if (0 == LoadingCount)
		{
			ThreadLoadingEnd = true;
		}


		if (true == ThreadLoadingEnd)
		{
			UEngineSprite::CreateSpriteToMeta("Player.png", ".sdata");
			UEngineSprite::CreateSpriteToMeta("TileMap.png", ".sdata");


			{
				UEngineDirectory Dir;
				if (false == Dir.MoveParentToDirectory("ContentsResources"))
				{
					MSGASSERT("리소스 폴더를 찾지 못했습니다.");
					return;
				}
				Dir.Append("Image/Tevi");

				UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
			}


			{
				UEngineDirectory Dir;
				if (false == Dir.MoveParentToDirectory("ContentsResources"))
				{
					MSGASSERT("리소스 폴더를 찾지 못했습니다.");
					return;
				}
				Dir.Append("Image/TileSet");

				UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
			}


			// 이미지를 변환 
			UEngineCore::CreateLevel<ATitleGameMode, APawn, ATitleHUD>("Titlelevel");
			UEngineCore::CreateLevel<ATileMapGameMode, APawn, AHUD>("TileMapEditor");
			UEngineCore::OpenLevel("Titlelevel");
		}

	}

}

void ATestGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	if (false == ThreadLoadingEnd)
	{


		Thread.Start("Loading", [this]()
			{

				// 쓰레드 모르잖아. 뚜드려 맞는다.

				{
					// 말도 안되는 겁니다.
					// 쓰레드가 살아있으려면 이 객체도 살아있어야 한다는 것을 기억핫세요.
					// UEngineThread Thread;

					UEngineDirectory Dir;
					if (false == Dir.MoveParentToDirectory("ContentsResources"))
					{
						MSGASSERT("리소스 폴더를 찾지 못했습니다.");
						return;
					}
					Dir.Append("Image");
					// 로딩바 만들고 싶으면  100개면 10 10 10 10 10 10
					std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });

					// 로딩 개수를 구분한다.
					// 1000
					LoadingCount = static_cast<int>(ImageFiles.size());

					for (size_t i = 0; i < ImageFiles.size(); i++)
					{
						std::string FilePath = ImageFiles[i].GetPathToString();

						// IOCP 1000개의 일이라는 메모리가 있죠?
						UEngineCore::GetThreadPool().WorkQueue([this, FilePath]()
							{
								UEngineTexture::ThreadSafeLoad(FilePath);
								--(this->LoadingCount);
							});
					}

					// 언제 끝날지 모르는 쓰레드로 넘긴것.
					// 2가지 문제가 생긴다.
					// 1. 스프라이트는 텍스처가 로딩되어야 만들수 있다. 그런데 쓰레드에게 
					// 텍스처 로딩을 맡긴다는것은 위에서 텍스처가 다 로딩 안되고 내려올수 있다는 이야기가 된다.
					// 2. 참고로 이미지가 많으면 많수록 효율이 증대되는 형식
					// 이미지의 수가 적으면 오히려 로딩의 효율이 더 떨어질수 있다.
					// 3. 동기화가 안되어 있다.
				}



				{
					std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("MyMaterial");
					Mat->SetVertexShader("TestShader.fx");
					Mat->SetPixelShader("TestShader.fx");
				}


				{
					std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("MyCollisionDebugMaterial");
					Mat->SetVertexShader("EngineDebugCollisionShader.fx");
					Mat->SetPixelShader("EngineDebugCollisionShader.fx");
					// 언제나 화면에 나오는 누구도 이녀석의 앞을 가릴수 없어.
					Mat->SetDepthStencilState("CollisionDebugDepth");
					Mat->SetRasterizerState("CollisionDebugRas");
				}

				{
					std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("JHJEffect");
					Mat->SetVertexShader("JHJEffect.fx");
					Mat->SetPixelShader("JHJEffect.fx");
					// 기존 세팅된 깊이 세팅이 남아서 영향을 줄수 있으므로
					Mat->SetDepthStencilState("ALWAYS");
					
				}



				// 쓰레드 로딩 준비가 끝났다는 bool값을 또 만들어야 한다.
				ThreadLoadingInit = true;
				//for (size_t i = 0; i < 100000; i++)
				//{
				//	UEngineDebug::OutPutString("Loading.....");
				//}

				// this->LoadingEnd = true;
			});
	}
	

}