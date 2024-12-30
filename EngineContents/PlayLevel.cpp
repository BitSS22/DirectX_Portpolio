#include "PreCompile.h"
#include "PlayLevel.h"
#include "Center.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>

class TestWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		ImGui::Button("WindowButton");
		ImGui::SameLine(); // ÇÑ°£ ¶ç±â
		ImGui::Text("test");

	}
};

APlayLevel::APlayLevel()
{
	Center = GetWorld()->SpawnActor<ACenter>();
	// Center->SetActorLocation({ 300.0f, 0.0f, 0.0f });

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });

	UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
}

APlayLevel::~APlayLevel()
{

}

void APlayLevel::BeginPlay()
{
	AActor::BeginPlay();
}

void APlayLevel::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);



}