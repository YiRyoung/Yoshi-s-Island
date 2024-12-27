#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>

ATitleLogo::ATitleLogo()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();

	BackgroundRenderer->CreateAnimation("Idle", "YoshiAndMario.png", 0, 6, 0.7f);
	USpriteRenderer::FrameAnimation* Animation = BackgroundRenderer->FindAnimation("Idle");
	Animation->IsAutoScale = true;
	Animation->AutoScaleRatio = 4.0f;

	BackgroundRenderer->CreateAnimation("Move", "YoshiAndMario.png", 7, 11, 0.7f);
	{
		USpriteRenderer::FrameAnimation* Animation = BackgroundRenderer->FindAnimation("Move");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 4.0f;
	}


	BackgroundRenderer->ChangeAnimation("Idle");
	BackgroundRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	BackgroundRenderer->SetupAttachment(RootComponent);

	//Child = CreateDefaultSubObject<USpriteRenderer>();
	//Child->SetSprite("YoshiAndMario.png", 2);
	//Child->SetRelativeLocation({ 100.0f, 0.0f, 0.0f });
	//Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	//Child->SetupAttachment(RootComponent);
}

ATitleLogo::~ATitleLogo()
{
}

void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsPress('A'))
	{
		AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}

	if (UEngineInput::IsPress('W'))
	{
		AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('S'))
	{
		AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('Q'))
	{
		AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	}

	if (UEngineInput::IsPress('E'))
	{
		BackgroundRenderer->ChangeAnimation("Move");
	}

	if (UEngineInput::IsPress('R'))
	{
		//Child->SetWorldLocation(FVector{ 100.0f, 0.0f , 0.0f });
	}

}
