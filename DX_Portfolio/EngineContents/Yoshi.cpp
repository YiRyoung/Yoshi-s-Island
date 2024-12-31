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

	YoshiRenderer->CreateAnimation("Idle", "YoshiAndMario.png", { 7, 8, 9, 10, 11, 10, 9, 8, 7, 8, 9, 10, 11, 10, 9, 8, 7, 8, 9, 10, 11, 10, 9, 8, 7, 8, 9, 10, 11, 10, 9, 8 }, 0.15f);
	{
		USpriteRenderer::FrameAnimation* Animation = YoshiRenderer->FindAnimation("Idle");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 3.0f;
	}

	YoshiRenderer->CreateAnimation("Move", "YoshiAndMario.png", 40, 50, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = YoshiRenderer->FindAnimation("Move");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 3.0f;
	}
	YoshiRenderer->ChangeAnimation("Idle");
	YoshiRenderer->SetupAttachment(RootComponent);
}

AYoshi::~AYoshi()
{
}

void AYoshi::BeginPlay()
{
	AActor::BeginPlay();
}

void AYoshi::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == UEngineInput::IsPress('D'))
	{
		YoshiRenderer->AddRelativeLocation({ 3.0f, 0.0f, 0.0f });
		YoshiRenderer->ChangeAnimation("Move");
	}
	if (false == UEngineInput::IsPress('D'))
	{
		YoshiRenderer->ChangeAnimation("Idle");
	}
}

