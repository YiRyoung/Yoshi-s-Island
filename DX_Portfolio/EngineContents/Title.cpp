#include "PreCompile.h"
#include "Title.h"

#include <EngineCore/DefaultSceneComponent.h>

#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>

#include <EngineCore/EngineSprite.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"

ATitle::ATitle()
{
	TitleRes();
	TitleInit();
}

ATitle::~ATitle()
{
}

void ATitle::TitleRes()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Title/TitleImage");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}
}

void ATitle::TitleInit()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -560.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackgroundRenderer->SetupAttachment(RootComponent);
	BackgroundRenderer->SetAutoScaleRatio(3.0f);
	BackgroundRenderer->SetRelativeLocation({ 0.0f, 660.0 * -0.5f});

	BackgroundRenderer->CreateAnimation("Start", "TitleImage", 0, 127, 0.1f);
	BackgroundRenderer->ChangeAnimation("Start");

	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetTexture("TitleLogo.png");
	LogoRenderer->SetScale3D({ 540, 216, 1 });
	LogoRenderer->SetRelativeLocation({ 0.0f, 150.0f, static_cast<float>(EOrderNum::FRONTBACKGROUND)});
	LogoRenderer->SetupAttachment(RootComponent);
}

void ATitle::EndAnimation(int _StartIndex)
{
	EndAnimIndex = _StartIndex;
	BackgroundRenderer->CreateAnimation("End", "TitleImage", EndAnimIndex, 0, 0.008f, false);
	BackgroundRenderer->ChangeAnimation("End");
}