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

		ImGui::SameLine(); // �Ѱ� ���
		ImGui::Text("test");

	}
};

ATitleGameMode::ATitleGameMode()
{
	// �������� ���ּž� �մϴ�.
	// �̰� UI�����Ұ��� 
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Player");
	// �浹üũ �ؾ��Ѵ�.
	GetWorld()->LinkCollisionProfile("Player", "Monster");



	// ī�޶� �����Ÿ� �ڷ� ���� 
	// ī�޶� ��ġ������ ������ ����� �Ұ��̴�.
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

	// �������� Ÿ�ٿ� ����ϰڴ�.
	// 

	{
		// UEngineRenderTarget* CamTarget = GetWorld()->GetCamera(EEngineCameraType::MainCamera)->GetCameraComponent()->GetCameraTarget();
		// CamTarget->AddEffect<UJHJEffect>();
	}

	{
		UEngineRenderTarget* LastTarget = GetWorld()->GetLastRenderTarget();
		LastTarget->AddEffect<UJHJEffect>();

		// ����Ʈ ����Ʈ �Ѱ� ����.
		std::shared_ptr<UPostEffect> Effect = LastTarget->GetPostEffect(0);
		Effect->IsActive = false;
	}

}

void ATitleGameMode::Tick(float _DeltaTime)
{
	// �θ� ȣ��
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

		// ����Ʈ ����Ʈ �Ѱ� ����.
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