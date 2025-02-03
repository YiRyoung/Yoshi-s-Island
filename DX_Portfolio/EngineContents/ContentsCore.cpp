#include "PreCompile.h"
#include "ContentsCore.h"

#include <EnginePlatform/EngineSound.h>

#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/HUD.h>

#include "YoshiGameInstance.h"
#include "Yoshi.h"
#include "TitleGameMode.h"
#include "SelectGameMode.h"
#include "Stage100GameMode.h"

CreateContentsCoreDefine(UContentsCore);

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	GEngine->CreateGameInstance<AYoshiGameInstance>();

	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 768, 660 };

	LoadSprites();

	UEngineCore::CreateLevel<ATitleGameMode, APawn, AHUD>("Title");
	UEngineCore::CreateLevel<ASelectGameMode, APawn, AHUD>("Select");
	UEngineCore::CreateLevel<AStage100GameMode, AYoshi, AHUD>("Stage100");

	UEngineCore::OpenLevel("Stage100");

}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}

void UContentsCore::LoadSprites()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Sound");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".wav", ".mp3" });

		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}
	}

	UEngineSprite::CreateSpriteToMeta("YoshiAndMario.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Yoshi(Not_Hold).png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Yoshi(Hold).png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("YoshiAndMarioStick_Right.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("YoshiAndMarioStick_Upper.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("YoshiStick_Right.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("YoshiStick_Upper.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Eggs.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Shy Guys.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Platforms.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("JumpBalls.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Coins.png", ".sdata");
}
