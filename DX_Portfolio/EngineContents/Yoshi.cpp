#include "PreCompile.h"
#include "Yoshi.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/DefaultSceneComponent.h>

AYoshi::AYoshi()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	UEngineSprite::CreateSpriteToMeta("YoshiAndMario.png", ".sdata");
	YoshiRenderer = CreateDefaultSubObject<USpriteRenderer>();
	YoshiRenderer->SetRelativeLocation({ 0, 0, 0 });

	YoshiRenderer->CreateAnimation("Idle", "YoshiAndMario.png", 3, 2, 0.7f);
	{
		USpriteRenderer::FrameAnimation* Animation = YoshiRenderer->FindAnimation("Idle");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 3.0f;
	}
	YoshiRenderer->ChangeAnimation("Idle");
	YoshiRenderer->SetupAttachment(RootComponent);
}

AYoshi::~AYoshi()
{
}

