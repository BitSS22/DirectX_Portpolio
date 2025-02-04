#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleLogo.h"
#include "Monster.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include "MyGameInstance.h"
#include <EngineCore/EngineRenderTarget.h>
#include "JHJEffect.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/Collision.h>

class TestWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		if (true == ImGui::Button("WindowButton"))
		{
			std::shared_ptr<AMonster> NewMonster = GetWorld()->SpawnActor<AMonster>();
			NewMonster->SetActorLocation({ 300.0f, 200.0f, 0.0f });
		}

		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine(); // 한간 띄기
		ImGui::Text("test");

	}
};

ATitleGameMode::ATitleGameMode()
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
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);
	Camera->GetCameraComponent()->SetProjectionType(EProjectionType::Perspective);


	{
		Logo = GetWorld()->SpawnActor<ATitleLogo>();
	}


	{
		std::shared_ptr<AMonster> NewMonster = GetWorld()->SpawnActor<AMonster>();
		NewMonster->SetActorLocation({ 300.0f, 0.0f, 0.0f });
	}

	// InvenWidget = GetWorld()->GetHUD()->CreateWidget<UWidget>();


}

ATitleGameMode::~ATitleGameMode()
{

}

void ATitleGameMode::BeginPlay()
{
	AGameMode::BeginPlay();

	// 최종버전 타겟에 사용하겠다.
	// 

	{
		// UEngineRenderTarget* CamTarget = GetWorld()->GetCamera(EEngineCameraType::MainCamera)->GetCameraComponent()->GetCameraTarget();
		// CamTarget->AddEffect<UJHJEffect>();
	}

	{
		UEngineRenderTarget* LastTarget = GetWorld()->GetLastRenderTarget();
		LastTarget->AddEffect<UJHJEffect>();

		// 포스트 이펙트 켜고 끄기.
		std::shared_ptr<UPostEffect> Effect = LastTarget->GetPostEffect(0);
		Effect->IsActive = false;
	}

}

void ATitleGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

	if (nullptr == Logo && true == Logo->IsDestroy())
	{
		Logo = nullptr;
	}

	GetWorld()->GetMainCamera()->EngineFreeCameraUpdate(_DeltaTime);

	std::vector<UCollision*> Collision;
	if (true == GetWorld()->GetMainCamera()->GetCameraComponent()->CheckPickCollision("Monster", Collision))
	{
		int a = 0;
	}


	if (UEngineInput::IsDown('K'))
	{
		UEngineRenderTarget* LastTarget = GetWorld()->GetLastRenderTarget();

		// 포스트 이펙트 켜고 끄기.
		std::shared_ptr<UPostEffect> Effect = LastTarget->GetPostEffect(0);
		Effect->IsActive = true;
	}


	if (UEngineInput::IsDown('P'))
	{
		std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
		Camera->FreeCameraOn();
	}


}


void ATitleGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();


	GetGameInstance<MyGameInstance>()->InvenWidget = InvenWidget;

	{
		std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
		}

		Window->SetActive(true);
	}

	{
		std::shared_ptr<TestWindow> Window = UEngineGUI::FindGUIWindow<TestWindow>("TestWindow");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
		}

		Window->SetActive(true);
	}
}