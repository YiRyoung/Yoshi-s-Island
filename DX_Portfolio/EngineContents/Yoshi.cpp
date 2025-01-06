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
	YoshiRenderer->SetupAttachment(RootComponent);
	YoshiRenderer->SetAutoScaleRatio(3.0f);
	YoshiRenderer->SetRelativeLocation({ 0, 0, 0 });

	YoshiRenderer->CreateAnimation("Idle", "YoshiAndMario.png", { 7, 8, 9, 10, 11, 10, 9, 8, 7, 8, 9, 10, 11, 10, 9, 8, 7, 8, 9, 10, 11, 10, 9, 8, 7, 8, 9, 10, 11, 10, 9, 8 }, 0.15f);
	YoshiRenderer->CreateAnimation("Move", "YoshiAndMario.png", 40, 50, 0.08f);
	YoshiRenderer->ChangeAnimation("Idle");
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

	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		YoshiRenderer->AddRelativeLocation({ Speed, 0.0f, 0.0f });
		YoshiRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
		YoshiRenderer->ChangeAnimation("Move");
	}

	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		YoshiRenderer->AddRelativeLocation({ -Speed, 0.0f, 0.0f });
		YoshiRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
		YoshiRenderer->ChangeAnimation("Move");
	}

	if (false == UEngineInput::IsPress(VK_LEFT) && false == UEngineInput::IsPress(VK_RIGHT))
	{
		YoshiRenderer->ChangeAnimation("Idle");
	}

	if (true == UEngineInput::IsPress(VK_UP))
	{
		YoshiRenderer->AddRelativeLocation({ 0.0f, Speed, 0.0f });
	}

	if (true == UEngineInput::IsPress(VK_DOWN))
	{
		YoshiRenderer->AddRelativeLocation({ 0.0f, -Speed, 0.0f });
	}

}

