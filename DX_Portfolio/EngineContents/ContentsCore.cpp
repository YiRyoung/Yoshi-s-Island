#include "PreCompile.h"
#include "ContentsCore.h"

#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/HUD.h>

#include "Yoshi.h"
#include "TitleGameMode.h"
#include "SelectGameMode.h";
#include "Stage100GameMode.h"
#include "Stage101GameMode.h"
#include "Stage102GameMode.h"

CreateContentsCoreDefine(UContentsCore);

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 768, 660 };

	LoadSprites();

	UEngineCore::CreateLevel<ATitleGameMode, APawn, AHUD>("Title");
	UEngineCore::CreateLevel<ASelectGameMode, APawn, AHUD>("Select");
	UEngineCore::CreateLevel<AStage100GameMode, AYoshi, AHUD>("Stage100");
	UEngineCore::CreateLevel<AStage101GameMode, AYoshi, AHUD>("Stage101");
	UEngineCore::CreateLevel<AStage102GameMode, AYoshi, AHUD>("Stage102");

	UEngineCore::OpenLevel("Stage101");

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

	UEngineSprite::CreateSpriteToMeta("YoshiAndMario.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("YoshiStick_Right.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("YoshiStick_Upper.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Shy Guys.png", ".sdata");
}
