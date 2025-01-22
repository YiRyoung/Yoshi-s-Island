#include "PreCompile.h"
#include "Yoshi.h"

#include <EngineBase/EngineRandom.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/Collision.h>

AYoshi::AYoshi()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Collision = new YoshiCollision(this);
	State = new YoshiState(this);

	YoshiRenderer = CreateDefaultSubObject<USpriteRenderer>();
	YoshiRenderer->SetupAttachment(RootComponent);
	YoshiRenderer->SetAutoScaleRatio(3.0f);
	YoshiRenderer->SetRelativeLocation({ 0, 0, -10 });

	SetAnimations();
	PlayIdleAnim(true);
}

AYoshi::~AYoshi()
{
	if (Collision != nullptr) 
	{ 
		delete Collision;
		Collision = nullptr;
	}

	if (State != nullptr) 
	{
		delete State;
		State = nullptr;
	}
}

void AYoshi::BeginPlay()
{
	AActor::BeginPlay();
	Scale = YoshiRenderer->GetTransformRef().Scale;

	SetCollision();
	SetDebugCollision();
}

void AYoshi::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	SetAnimDir();
	State->StateFunc(_DeltaTime);
	Collision->MoveSlopeUp(_DeltaTime);

	UEngineDebug::OutPutString(std::to_string(static_cast<int>(CurState)));
}

void AYoshi::SetAnimations()
{
	YoshiRenderer->CreateAnimation("Idle0", "YoshiAndMario.png", {7, 8, 9, 10, 11, 10, 9, 8}, 0.15f);
	YoshiRenderer->CreateAnimation("Idle1", "YoshiAndMario.png", { 3, 4, 5, 4, 5}, 0.2f);
	YoshiRenderer->CreateAnimation("Idle2", "YoshiAndMario.png", {2, 1, 0, 0, 0, 1, 2}, 0.15f);
	
	YoshiRenderer->CreateAnimation("Walk", "YoshiAndMario.png", 40, 52, 0.08f);
	YoshiRenderer->CreateAnimation("Run", "YoshiAndMario.png", 53, 57, 0.04f);

	YoshiRenderer->CreateAnimation("LookUpStart", "YoshiAndMario.png", 12, 13, 0.3f, false);
	YoshiRenderer->CreateAnimation("LookUpEnd", "YoshiAndMario.png", 13, 12, 0.1f, false);
	
	YoshiRenderer->CreateAnimation("BendStart", "YoshiAndMario.png", 14, 17, 0.05f, false);
	YoshiRenderer->CreateAnimation("BendEnd", "YoshiAndMario.png", 17, 14, 0.04f, false);

	YoshiRenderer->CreateAnimation("Jump", "YoshiAndMario.png", 75, 76, 0.1f, false);
	YoshiRenderer->CreateAnimation("Fall", "YoshiAndMario.png", 77, 79, 0.07f, false);
	YoshiRenderer->CreateAnimation("StayUp", "YoshiAndMario.png", 80, 83, 0.04f);

	YoshiRenderer->CreateAnimation("Stick_Right", "YoshiStick_Right.png", { 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0}, 0.028f, false);
	YoshiRenderer->CreateAnimation("Stick_Up", "YoshiStick_Upper.png", { 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0}, 0.028f, false);
}

void AYoshi::SetAnimDir()
{
	if (UEngineInput::IsDown(VK_LEFT))
	{
		RootComponent->SetScale3D({ -1, 1, 1 });
	}
	else if (UEngineInput::IsDown(VK_RIGHT))
	{
		RootComponent->SetScale3D({ 1, 1, 1 });
	}
}

int AYoshi::SetIdleAnimNum()
{
	UEngineRandom Random;
	int RandomValue = Random.RandomInt(0, 9);

	if (RandomValue == 0) { return 2; }
	else if (RandomValue == 1) { return 1; }
	else { return 0; }
}

void AYoshi::PlayIdleAnim(bool _IsStart)
{
	int AnimNum = SetIdleAnimNum();
	YoshiRenderer->ChangeAnimation("Idle" + std::to_string(AnimNum));
}

void AYoshi::SetCollision()
{
	HeadCollision = CreateDefaultSubObject<UCollision>();
	HeadCollision->SetupAttachment(RootComponent);
	HeadCollision->SetCollisionProfileName("HeadCollision");
	HeadCollision->SetScale3D({ Scale.X * 0.8f, Scale.Y * 0.3f });
	HeadCollision->SetRelativeLocation({ 0.0f, Scale.Y * 0.8f });

	BodyCollision = CreateDefaultSubObject<UCollision>();
	BodyCollision->SetupAttachment(RootComponent);
	BodyCollision->SetCollisionProfileName("BodyCollision");
	BodyCollision->SetScale3D({ Scale.X * 0.8f, Scale.Y * 0.4f });
	BodyCollision->SetRelativeLocation({ 0.0f, Scale.Y * 0.4f });
	
	FootCollision = CreateDefaultSubObject<UCollision>();
	FootCollision->SetupAttachment(RootComponent);
	FootCollision->SetCollisionProfileName("FootCollision");
	FootCollision->SetScale3D({ Scale.X * 0.8f, Scale.Y * 0.2f });
	FootCollision->SetRelativeLocation({ 0.0f, Scale.Y * 0.05f });
}

void AYoshi::SetDebugCollision()
{
	DebugDownCollision = CreateDefaultSubObject<UCollision>();
	DebugDownCollision->SetupAttachment(RootComponent);
	DebugDownCollision->SetCollisionProfileName("DebugCollision");
	DebugDownCollision->SetScale3D({ 5.0f, 5.0f });

	DebugLeftCollision = CreateDefaultSubObject<UCollision>();
	DebugLeftCollision->SetupAttachment(RootComponent);
	DebugLeftCollision->SetCollisionProfileName("DebugCollision");
	DebugLeftCollision->SetScale3D({ 5.0f, 5.0f });
	DebugLeftCollision->SetRelativeLocation({ Scale.X * -0.5f, Scale.Y * 0.5f });

	DebugRightCollision = CreateDefaultSubObject<UCollision>();
	DebugRightCollision->SetupAttachment(RootComponent);
	DebugRightCollision->SetCollisionProfileName("DebugCollision");
	DebugRightCollision->SetScale3D({ 5.0f, 5.0f });
	DebugRightCollision->SetRelativeLocation({ Scale.X * 0.5f, Scale.Y * 0.5f });

	DebugUpCollision = CreateDefaultSubObject<UCollision>();
	DebugUpCollision->SetupAttachment(RootComponent);
	DebugUpCollision->SetCollisionProfileName("DebugCollision");
	DebugUpCollision->SetScale3D({ 5.0f, 5.0f });
	DebugUpCollision->SetRelativeLocation({ 0.0f, Scale.Y });
}

void AYoshi::Play(std::string_view _Name)
{
	SoundPlayer = UEngineSound::Play(_Name);
}
