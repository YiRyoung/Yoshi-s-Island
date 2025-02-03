#include "PreCompile.h"
#include "KeyNoticeGUI.h"

#include <EngineCore/EngineGUI.h>

UKeyNoticeGUI::UKeyNoticeGUI()
{
}

UKeyNoticeGUI::~UKeyNoticeGUI()
{
}

void UKeyNoticeGUI::OnGUI()
{
	PrintGameGuide();
}

void UKeyNoticeGUI::PrintGameGuide()
{
	ImGui::Text("<KEY NOTICE>");
	ImGui::Text("Move : Directional key");
	ImGui::Text("Jump : Left Control");
	ImGui::Text("Aim & Throw : Z");
	ImGui::Text("Lick : X");
	ImGui::NewLine();
}