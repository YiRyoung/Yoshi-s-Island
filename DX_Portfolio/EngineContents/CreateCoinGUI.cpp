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
	SaveAndLoad();
}

void UCreateCoinGUI::CreateYellowCoin()
{
	{
		if (UEngineInput::IsDown(VK_LBUTTON))
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
	if (true == ImGui::Button("Save"))
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Data");
		std::string InitPath = Dir.GetPathToString();

		OPENFILENAME ofn;       // common dialog box structure
		char szFile[260] = { 0 };       // if using TCHAR macros
		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = nullptr;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = ("All\0*.*\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrDefExt = "MapData";
		ofn.lpstrInitialDir = InitPath.c_str();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetSaveFileNameA(&ofn) == TRUE)
		{
			std::list<std::shared_ptr<AYellowCoin>> AllCoinList = GetWorld()->GetAllActorListByClass<AYellowCoin>();

			UEngineSerializer Ser;

			Ser << static_cast<int>(AllCoinList.size());

			for (std::shared_ptr<AYellowCoin> Actor : AllCoinList)
			{
				Actor->Serialize(Ser);
			}


			UEngineFile NewFile = Dir.GetFile(ofn.lpstrFile);
			NewFile.FileOpen("wb");
			NewFile.Write(Ser);
		}
	}

	if (true == ImGui::Button("Load"))
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Data");
		std::string InitPath = Dir.GetPathToString();

		OPENFILENAME ofn;       // common dialog box structure
		char szFile[260] = { 0 };       // if using TCHAR macros
		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = nullptr;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = ("All\0*.*\0Text\0*.MapData\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = InitPath.c_str();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			UEngineFile NewFile = Dir.GetFile(ofn.lpstrFile);
			UEngineSerializer Ser;

			NewFile.FileOpen("rb");
			NewFile.Read(Ser);

			int CoinCount = 0;
			Ser >> CoinCount;

			for (size_t i = 0; i < CoinCount; i++)
			{
				std::shared_ptr<AYellowCoin> NewMon = nullptr;
				NewMon = GetWorld()->SpawnActor<AYellowCoin>();
				
				NewMon->DeSerialize(Ser);
			}

		}
	}
}
