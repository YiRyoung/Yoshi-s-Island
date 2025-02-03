#include "PreCompile.h"
#include "CreateCoinGUI.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineGUI.h>

#include <EngineCore/CameraActor.h>
#include "YellowCoin.h"

UCreateCoinGUI::UCreateCoinGUI()
{
}

UCreateCoinGUI::~UCreateCoinGUI()
{
}

void UCreateCoinGUI::OnGUI()
{
	CreateYellowCoin();
}

void UCreateCoinGUI::CreateYellowCoin()
{
	{
		if (ImGui::Button("IsCreate"))
		{
			IsCreate = !IsCreate;
		}

		std::string str = "";
		(IsCreate) ? str = "true" : str = "false";
		ImGui::SameLine();
		ImGui::Text(str.c_str());
	}

	{
		if (IsCreate && UEngineInput::IsDown(VK_LBUTTON))
		{
			std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetMainCamera();
			FVector Pos = Camera->ScreenMousePosToWorldPos();
			Pos.Z = 0.0f;

			std::shared_ptr<AYellowCoin> NewYellowCoin;
			NewYellowCoin = GetWorld()->SpawnActor<AYellowCoin>("YellowCoin");
			NewYellowCoin->SetActorLocation(Pos);
		}
	}

	{
		if (ImGui::Button("EditObjectDelete"))
		{
			std::list<std::shared_ptr<AYellowCoin>> AllYellowCoinList = GetWorld()->GetAllActorListByClass<AYellowCoin>();
			for (std::shared_ptr<AYellowCoin> YellowCoin : AllYellowCoinList)
			{
				YellowCoin->Destroy();
			}
		}
	}

	{
		std::vector<std::shared_ptr<AYellowCoin>> AllYellowCoinList = GetWorld()->GetAllActorArrayByClass<AYellowCoin>();

		std::vector<std::string> ArrString;
		for (std::shared_ptr<class AActor> Actor : AllYellowCoinList)
		{
			ArrString.push_back(Actor->GetName());
		}

		std::vector<const char*> Arr;
		for (size_t i = 0; i < ArrString.size(); i++)
		{
			Arr.push_back(ArrString[i].c_str());
		}


		if (0 < Arr.size())
		{
			ImGui::ListBox("AllActorList", &ObjectItem, &Arr[0], static_cast<int>(Arr.size()));

			if (ObjectItem != -1)
			{

			}

			if (true == ImGui::Button("Delete"))
			{
				AllYellowCoinList[ObjectItem]->Destroy();
				ObjectItem = -1;
			}

		}
	}
}

void UCreateCoinGUI::SaveAndLoad()
{

}
