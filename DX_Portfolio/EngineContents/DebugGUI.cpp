#include "PreCompile.h"
#include "DebugGUI.h"

#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineGUI.h>

#include "YoshiGameInstance.h"
#include "ContentsEnum.h"
#include "Yoshi.h"

UDebugGUI::UDebugGUI()
{
}

UDebugGUI::~UDebugGUI()
{
}

void UDebugGUI::OnGUI()
{
	if (ImGui::Button("FreeCamera"))
	{
		GetWorld()->GetMainCamera()->FreeCameraSwitch();
	}
	ImGui::NewLine();


	std::string EggCount = "EggCount : " + std::to_string(GetWorld()->GetMainPawn<AYoshi>()->GetGameInstance<AYoshiGameInstance>()->EggCount);
	EggCount = UEngineString::AnsiToUTF8(EggCount);
	ImGui::Text(EggCount.c_str());
	ImGui::NewLine();

	std::string CurStateName;
	switch (GetWorld()->GetMainPawn<AYoshi>()->GetCurState())
	{
	case EPlayerState::IDLE:
		CurStateName = "IDLE";
		break;
	case EPlayerState::LOOKUP:
		CurStateName = "LOOKUP";
		break;
	case EPlayerState::BEND:
		CurStateName = "BEND";
		break;
	case EPlayerState::WALK:
		CurStateName = "WALK";
		break;
	case EPlayerState::RUN:
		CurStateName = "RUN";
		break;
	case EPlayerState::JUMP:
		CurStateName = "JUMP";
		break;
	case EPlayerState::STAYUP:
		CurStateName = "STAYUP";
		break;
	case EPlayerState::FALL:
		CurStateName = "FALL";
		break;
	case EPlayerState::STICK:
		CurStateName = "STICK";
		break;
	case EPlayerState::THROW:
		CurStateName = "THROW";
		break;
	}
	ImGui::Text("CurState : ");
	ImGui::SameLine();
	ImGui::Text(CurStateName.c_str());

	if (ImGui::Button("SwitchIsWithBaby"))
	{
		GetWorld()->GetMainPawn<AYoshi>()->SwitchIsWithBaby();
	}

	std::string IsWithBabyString;
	bool CheckVari0 = GetWorld()->GetMainPawn<AYoshi>()->GetIsWithBaby();
	(true == CheckVari0) ? IsWithBabyString = "true" : IsWithBabyString = "false";

	std::string CurIsWithBady = UEngineString::AnsiToUTF8(IsWithBabyString);
	ImGui::SameLine();
	ImGui::Text(CurIsWithBady.c_str());

	if (ImGui::Button("SwitchIsAim"))
	{
		GetWorld()->GetMainPawn<AYoshi>()->SwitchIsAim();
	}

	std::string IsAimString;
	bool CheckVari1 = GetWorld()->GetMainPawn<AYoshi>()->GetIsAim();
	(true == CheckVari1) ? IsAimString = "true" : IsAimString = "false";

	std::string CurIsAim = UEngineString::AnsiToUTF8(IsAimString);
	ImGui::SameLine();
	ImGui::Text(CurIsAim.c_str());

	if (ImGui::Button("SwitchIsHold"))
	{
		GetWorld()->GetMainPawn<AYoshi>()->SwitchIsHold();
	}

	std::string IsHoldString;
	bool CheckVari2 = GetWorld()->GetMainPawn<AYoshi>()->GetIsHold();
	(true == CheckVari2) ? IsHoldString = "true" : IsHoldString = "false";

	std::string CurIsHold = UEngineString::AnsiToUTF8(IsHoldString);
	ImGui::SameLine();
	ImGui::Text(CurIsHold.c_str());
}

