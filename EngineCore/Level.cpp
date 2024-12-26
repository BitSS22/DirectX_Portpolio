#include "PreCompile.h"
#include "Level.h"
#include "Actor.h"
#include "Renderer.h"
#include "EngineCore.h"
#include "EngineCamera.h"
#include "CameraActor.h"
#include "EngineGUI.h"

// 플레이어 Renderer

// 카메라 1 Renderer
// 카메라 2 Renderer



std::shared_ptr<class ACameraActor> ULevel::SpawnCamera(int _Order)
{
	std::shared_ptr<ACameraActor> Camera = std::make_shared<ACameraActor>();

	if (true == Cameras.contains(_Order))
	{
		MSGASSERT("이미 존재하는 카메라를 또 만들려고 했습니다.");
	}

	Camera->BeginPlay();

	Cameras.insert({ _Order , Camera });
	return Camera;
}

ULevel::ULevel()
{
	SpawnCamera(0);
}

ULevel::~ULevel()
{
	BeginPlayList.clear();

	AllActorList.clear();

	Cameras.clear();
}

void ULevel::LevelChangeStart()
{

}

void ULevel::LevelChangeEnd()
{

}


void ULevel::Tick(float _DeltaTime)
{
	std::list<std::shared_ptr<class AActor>>::iterator StartIter = BeginPlayList.begin();
	std::list<std::shared_ptr<class AActor>>::iterator EndIter = BeginPlayList.end();
	for ( ; StartIter != EndIter; )
	{
		std::shared_ptr<AActor> CurActor = *StartIter;

		if (false == CurActor->IsActive())
		{
			++StartIter;
			continue;
		}

		StartIter = BeginPlayList.erase(StartIter);

		CurActor->BeginPlay();
		AllActorList.push_back(CurActor);
	}

	// 절대 Ranged for안에서는 erase 리스트의 구조가 변경될 일을 하지 말라고 했ㅅ어요.
	for (std::shared_ptr<AActor> CurActor : AllActorList)
	{
		CurActor->Tick(_DeltaTime);
	}
}

void ULevel::Render(float _DeltaTime)
{
	UEngineCore::Device.RenderStart();

	for (std::pair<const int, std::shared_ptr<ACameraActor>>& Camera : Cameras)
	{
		Camera.second->Tick(_DeltaTime);
		Camera.second->CameraComponent->Render(_DeltaTime);
	}

	if (true == UEngineWindow::IsApplicationOn())
	{
		UEngineGUI::GUIRender();

		// IMGUI가 랜더링을하면서 
		
	}
	


	UEngineCore::Device.RenderEnd();
}



void ULevel::ChangeRenderGroup(int _CameraOrder, int _PrevGroupOrder, std::shared_ptr<URenderer> _Renderer)
{
	if (false == Cameras.contains(_CameraOrder))
	{
		MSGASSERT("존재하지 않는 카메라에 랜더러를 집어넣으려고 했습니다.");
	}
	std::shared_ptr<ACameraActor> Camera = Cameras[_CameraOrder];

	Camera->CameraComponent->ChangeRenderGroup(_PrevGroupOrder, _Renderer);
}




