#include "PreCompile.h"
#include "Stage100GameMode.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>

#include "YoshiGameInstance.h"
#include "ContentsEnum.h"
#include "KeyNoticeGUI.h"
#include "DebugGUI.h"
#include "CreateCoinGUI.h"
#include "Stage100.h"

#include "Yoshi.h"
#include "CrazyDayzee.h"

#include "ScaleBlock.h"
#include "JumpBall.h"
#include "BigJumpBall.h"

#include "YellowCoin.h"

AStage100GameMode::AStage100GameMode()
{
	SetCollisionLink();
	InitActors();
}

AStage100GameMode::~AStage100GameMode()
{
}

void AStage100GameMode::BeginPlay()
{
	AGameMode::BeginPlay();

	Stage->SwitchColImage();
	GetWorld()->GetMainPawn()->SetActorLocation({ 400.0f, -2686.0f, static_cast<float>(EOrderNum::PLAYER)});
	GetWorld()->GetMainPawn<AYoshi>()->SetEggCount(GetGameInstance<AYoshiGameInstance>()->EggCount);
}

void AStage100GameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);

	GetWorld()->GetMainPawn<AYoshi>()->CameraBoundary(Stage->GetStageScale());

	ScaleBlock->ScaleUp(ScaleBlock->GetActorLocation(), _DeltaTime);


	if (UEngineInput::IsDown('P'))
	{
		Stage->SwitchColImage();
	}
}

void AStage100GameMode::LevelChangeStart()
{
	AGameMode::LevelChangeStart();
	
	SetGUI();
	LoadMap();
}

void AStage100GameMode::LevelChangeEnd()
{
	AGameMode::LevelChangeEnd();
}

void AStage100GameMode::SetCollisionLink()
{
	GetWorld()->CreateCollisionProfile("HeadCollision");
	GetWorld()->CreateCollisionProfile("BodyCollision");
	GetWorld()->CreateCollisionProfile("FootCollision");

	GetWorld()->CreateCollisionProfile("StickBodyCollision");
	GetWorld()->CreateCollisionProfile("StickCollision");

	GetWorld()->CreateCollisionProfile("MonsterHeadCollision");
	GetWorld()->CreateCollisionProfile("MonsterBodyCollision");

	GetWorld()->CreateCollisionProfile("PlatformCollision");
	GetWorld()->CreateCollisionProfile("JumpBallCollision");
	GetWorld()->CreateCollisionProfile("BigJumpBallCollision");

	GetWorld()->CreateCollisionProfile("ScaleBlockDownCollision");
	GetWorld()->CreateCollisionProfile("ScaleBlockUpCollision");
	GetWorld()->CreateCollisionProfile("ScaleBlockLeftCollision");
	
	GetWorld()->CreateCollisionProfile("YellowCoinCollision");

	GetWorld()->LinkCollisionProfile("MonsterHeadCollision", "FootCollision");
	GetWorld()->LinkCollisionProfile("MonsterBodyCollision", "BodyCollision");
	GetWorld()->LinkCollisionProfile("MonsterBodyCollision", "StickCollision");

	GetWorld()->LinkCollisionProfile("HeadCollision", "ScaleBlockDownCollision");
	GetWorld()->LinkCollisionProfile("BodyCollision", "YellowCoinCollision");
	GetWorld()->LinkCollisionProfile("FootCollision", "PlatformCollision");
	GetWorld()->LinkCollisionProfile("FootCollision", "JumpBallCollision");
	GetWorld()->LinkCollisionProfile("FootCollision", "BigJumpBallCollision");
}

void AStage100GameMode::InitActors()
{
	Stage = GetWorld()->SpawnActor<AStage100>();
	Stage->SetActorLocation({ 4608 * 0.5f, 3072 * -0.5f });

	CrazyDayzee1 = GetWorld()->SpawnActor<ACrazyDayzee>();
	CrazyDayzee1->SetActorLocation({ 880.0f, -2687.0f, static_cast<int>(EOrderNum::PLAYER) });

	CrazyDayzee2 = GetWorld()->SpawnActor<ACrazyDayzee>();
	CrazyDayzee2->SetActorLocation({ 1080.0f, -2687.0f, static_cast<int>(EOrderNum::PLAYER) });
	CrazyDayzee2->SetActorRelativeScale3D({ -1.0f, 1.0f, 1.0f });

	CrazyDayzee3 = GetWorld()->SpawnActor<ACrazyDayzee>();
	CrazyDayzee3->SetActorLocation({ 4516.2f, -908.0f, static_cast<int>(EOrderNum::PLAYER) });

	CrazyDayzee4 = GetWorld()->SpawnActor<ACrazyDayzee>();
	CrazyDayzee4->SetActorLocation({ 4378.4f, -908.0f, static_cast<int>(EOrderNum::PLAYER) });
	CrazyDayzee4->SetActorRelativeScale3D({ -1.0f, 1.0f, 1.0f });

	JumpBall = GetWorld()->SpawnActor<AJumpBall>();
	JumpBall->SetActorLocation({ 3305.0f, -2115.0f, static_cast<int>(EOrderNum::OBJECT) });

	BigJumpBall = GetWorld()->SpawnActor<ABigJumpBall>();
	BigJumpBall->SetActorLocation({ 3770.6f, -1778.0f, static_cast<int>(EOrderNum::OBJECT) });

	ScaleBlock = GetWorld()->SpawnActor<AScaleBlock>();
	ScaleBlock->SetActorLocation({ 1560.0f, -2472.7f, static_cast<int>(EOrderNum::OBJECT) });
}

void AStage100GameMode::SetGUI()
{
#ifdef _DEBUG
	std::shared_ptr<UDebugGUI> DebugWindow = UEngineGUI::FindGUIWindow<UDebugGUI>("DebugGUI");

	if (nullptr == DebugWindow)
	{
		DebugWindow = UEngineGUI::CreateGUIWindow<UDebugGUI>("DebugGUI");
	}

	DebugWindow->SetActive(true);

	std::shared_ptr<UCreateCoinGUI> CreateCoinWindow = UEngineGUI::FindGUIWindow<UCreateCoinGUI>("CreateCoinGUI");

	if (nullptr == CreateCoinWindow)
	{
		CreateCoinWindow = UEngineGUI::CreateGUIWindow<UCreateCoinGUI>("CreateCoinGUI");
	}

	CreateCoinWindow->SetActive(true);
#else
	std::shared_ptr<UKeyNoticeGUI> KeyWindow = UEngineGUI::FindGUIWindow<UKeyNoticeGUI>("KeyNoticeGUI");

	if (nullptr == KeyWindow)
	{
		KeyWindow = UEngineGUI::CreateGUIWindow<UKeyNoticeGUI>("KeyNoticeGUI");
	}

	KeyWindow->SetActive(true);
#endif
}

void AStage100GameMode::LoadMap()
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

	std::string FileName = "Stage100.Mapdata";
	std::string FilePath = Dir.GetPathToString() + "\\" + FileName;

	UEngineFile NewFile = Dir.GetFile(FilePath);
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
