#include "PreCompile.h"
#include "Select.h"

#include <EngineCore/DefaultSceneComponent.h>

#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>

#include <EngineCore/EngineSprite.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"

ASelect::ASelect()
{
	SelectRes();
	SelectInit();
}

ASelect::~ASelect()
{
}

void ASelect::SelectRes()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Select");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}
}

void ASelect::SelectInit()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -560.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackgroundRenderer->SetTexture("BlackScreen.png");
	BackgroundRenderer->SetScale3D(UEngineCore::GetScreenScale());
	BackgroundRenderer->SetRelativeLocation({ 0.0f, 0.0f, static_cast<float>(EOrderNum::BACKGROUND) });
	BackgroundRenderer->SetupAttachment(RootComponent);

	MapRenderer = CreateDefaultSubObject<USpriteRenderer>();
	MapRenderer->SetTexture("Maps.png");
	MapRenderer->SetScale3D({ 768.0f, 528.0f, 1.0f });
	MapRenderer->SetRelativeLocation({ 0.0f, -40.0f, static_cast<float>(EOrderNum::FOREBACKGROUND) });
	MapRenderer->SetupAttachment(RootComponent);

	StageRenderer = CreateDefaultSubObject<USpriteRenderer>();
	StageRenderer->SetTexture("World1.png");
	StageRenderer->SetScale3D({ 672.0f, 273.0f, 1.0f });
	StageRenderer->SetRelativeLocation({ 0.0f, 189.0f, static_cast<float>(EOrderNum::STAGE) });
	StageRenderer->SetupAttachment(RootComponent);

	UEngineSprite::CreateSpriteToMeta("Icons.png", ".sdata");
	Stage100IconRenderer = CreateDefaultSubObject<USpriteRenderer>();
	Stage100IconRenderer->SetSprite("Icons.png", 3);
	Stage100IconRenderer->SetAutoScaleRatio(3.0f);
	Stage100IconRenderer->SetRelativeLocation({ -243.0f, 146.0f, static_cast<float>(EOrderNum::COLSTAGE) });
	Stage100IconRenderer->SetupAttachment(RootComponent);

	Stage200IconRenderer = CreateDefaultSubObject<USpriteRenderer>();
	Stage200IconRenderer->SetSprite("Icons.png", 5);
	Stage200IconRenderer->SetAutoScaleRatio(3.0f);
	Stage200IconRenderer->SetRelativeLocation({ -84.0f, 146.0f, static_cast<float>(EOrderNum::COLSTAGE) });
	Stage200IconRenderer->SetupAttachment(RootComponent);

	UEngineSprite::CreateSpriteToMeta("Map Yoshi.png", ".sdata");
	Stage100YoshiRenderer = CreateDefaultSubObject<USpriteRenderer>();
	Stage100YoshiRenderer->SetAutoScaleRatio(3.0f);
	Stage100YoshiRenderer->SetRelativeLocation({ -237.0f, -170.0f, static_cast<float>(EOrderNum::COLSTAGE) });
	Stage100YoshiRenderer->CreateAnimation("Stage1_Idle", "Map Yoshi.png", { 10, 11, 12, 11 }, 0.5f);
	Stage100YoshiRenderer->CreateAnimation("Stage1_Ready", "Map Yoshi.png", { 13, 14, 15, 14 }, 0.4f);
	Stage100YoshiRenderer->ChangeAnimation("Stage1_Idle");
	Stage100YoshiRenderer->SetupAttachment(RootComponent);
}

