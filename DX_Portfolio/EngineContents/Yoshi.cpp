#include "PreCompile.h"
#include "Yoshi.h"

#include <EngineBase/EngineRandom.h>

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
	YoshiRenderer->SetRelativeLocation({ 0, 0, -10 });

	SetAnimations();

	State = EPlayerState::IDLE;

	int AnimNum = CurIdleAnim();

	YoshiRenderer->ChangeAnimation("Idle" + std::to_string(AnimNum));

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

	if (true == IsGround())
	{
		AddActorLocation({ 0.0f, 300.0f * _DeltaTime, 0.0f });
	}
	else
	{
		Gravity(_DeltaTime);
	}

	SetDirection();
	PlayerFSM(_DeltaTime);

	UEngineDebug::OutPutString("Pos : " + std::to_string(GetActorLocation().X) + "," + std::to_string(GetActorLocation().Y));
	UEngineDebug::OutPutString("GravityPos : " + std::to_string(GravityForce.Y));
	UEngineDebug::OutPutString("CurIndex : " + std::to_string(YoshiRenderer->GetCurIndex()));

}

bool AYoshi::IsGround()
{
	FVector Pos = GetActorLocation();
	Pos.Y = -Pos.Y;
	TColor Color = ColImage->GetColor(Pos);
	
	bool Result = (true == Color.operator==({ 255, 0, 255, 255 })) ? true : false;
	return Result;
}

void AYoshi::SetAnimations()
{
	YoshiRenderer->CreateAnimation("Idle0", "YoshiAndMario.png", {7, 8, 9, 10, 11, 10, 9, 8}, 0.15f);
	YoshiRenderer->CreateAnimation("Idle1", "YoshiAndMario.png", { 3, 4, 5, 4, 5}, 0.2f);
	YoshiRenderer->CreateAnimation("Idle2", "YoshiAndMario.png", {2, 1, 0, 0, 0, 1, 2}, 0.15f);
	
	YoshiRenderer->CreateAnimation("Move", "YoshiAndMario.png", 40, 50, 0.08f);

	YoshiRenderer->CreateAnimation("LookUpStart", "YoshiAndMario.png", 12, 13, 0.3f, false);
	YoshiRenderer->CreateAnimation("LookUpEnd", "YoshiAndMario.png", 13, 12, 0.1f, false);
	
	YoshiRenderer->CreateAnimation("BendStart", "YoshiAndMario.png", 14, 17, 0.05f, false);
	YoshiRenderer->CreateAnimation("BendEnd", "YoshiAndMario.png", 17, 14, 0.04f, false);

	YoshiRenderer->CreateAnimation("JumpStart", "YoshiAndMario.png", 75, 76, 0.1f, false);
}

void AYoshi::SetDirection()
{
	if (UEngineInput::IsDown(VK_LEFT))
	{
		YoshiRenderer->SetRotation({ 0.0f, 180.0f, 0.0f });
	}
	else if (UEngineInput::IsDown(VK_RIGHT))
	{
		YoshiRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
	}
}

void AYoshi::PlayerFSM(float _DeltaTime)
{
	switch (State)
	{
	case EPlayerState::IDLE:
		IdleStart(_DeltaTime);
		break;
	case EPlayerState::LOOKUPSTART:
		LookUpStart(_DeltaTime);
		break;
	case EPlayerState::LOOKUPEND:
		LookUpEnd(_DeltaTime);
		break;
	case EPlayerState::BENDSTART:
		BendStart(_DeltaTime);
		break;
	case EPlayerState::BENDEND:
		BendEnd(_DeltaTime);
		break;
	case EPlayerState::MOVE:
		MoveStart(_DeltaTime);
		break;
	case EPlayerState::JUMP:
		JumpStart(_DeltaTime);
		break;
	}
}

void AYoshi::Gravity(float _DeltaTime)
{
	FVector Power = GravityForce * _DeltaTime;
	FVector CheckPos = GetActorLocation() + Power;
	CheckPos.Y = -CheckPos.Y;
	UColor Color = ColImage->GetColor(CheckPos);
	
	if (false == Color.operator==({ 255, 0, 255, 255 }))
	{
		AddActorLocation(Power);
		GravityForce += FVector{ 0.0f, -1.0f, 0.0f } *GravityPower * _DeltaTime;
	}
}

int AYoshi::CurIdleAnim()
{
	UEngineRandom Random;
	int RandomValue = Random.RandomInt(0, 9);

	if (RandomValue == 0) { return 2; }
	else if (RandomValue == 1) { return 1; }
	else { return 0; }
}

void AYoshi::IdleStart(float _DeltaTime)
{
	Dir = EDirection::MAX;
	
	int AnimNum = CurIdleAnim();

	if (true == YoshiRenderer->IsCurAnimationEnd())
	{
		YoshiRenderer->ChangeAnimation("Idle" + std::to_string(AnimNum));

	}
	Idle(_DeltaTime);
}


void AYoshi::Idle(float _DeltaTime)
{

	if (true == UEngineInput::IsPress(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT))
	{
		State = EPlayerState::MOVE;
		return;
	}
	if (true == UEngineInput::IsPress(VK_UP))
	{
		State = EPlayerState::LOOKUPSTART;
		return;
	}
	if (true == UEngineInput::IsPress(VK_DOWN))
	{
		State = EPlayerState::BENDSTART;
		return;
	}

	if (true == UEngineInput::IsPress('X'))
	{
		State = EPlayerState::JUMP;
		return;
	}
}

void AYoshi::LookUpStart(float _DeltaTime)
{
	YoshiRenderer->ChangeAnimation("LookUpStart");

	if (false == UEngineInput::IsPress(VK_UP))
	{
		State = EPlayerState::LOOKUPEND;
		return;
	}
}

void AYoshi::LookUpEnd(float _DeltaTime)
{
	YoshiRenderer->ChangeAnimation("LookUpEnd");

	if (1.0f >= UEngineInput::IsPressTime(VK_UP))
	{

	}

	if (true == YoshiRenderer->IsCurAnimationEnd())
	{
		State = EPlayerState::IDLE;
		return;
	}
}

void AYoshi::BendStart(float _DeltaTime)
{
	YoshiRenderer->ChangeAnimation("BendStart");
	if (false == UEngineInput::IsPress(VK_DOWN))
	{
		State = EPlayerState::BENDEND;
		return;
	}
}

void AYoshi::BendEnd(float _DeltaTime)
{
	YoshiRenderer->ChangeAnimation("BendEnd");

	if (true == YoshiRenderer->IsCurAnimationEnd())
	{
		State = EPlayerState::IDLE;
		return;
	}
}

void AYoshi::MoveStart(float _DeltaTime)
{
	YoshiRenderer->ChangeAnimation("Move");
	Move(_DeltaTime);
}

void AYoshi::Move(float _DeltaTime)
{
	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		AddActorLocation(FVector{ Speed * _DeltaTime, 0.0f, 0.0f });
	}

	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		AddActorLocation(FVector{ -Speed * _DeltaTime, 0.0f, 0.0f });
	}

	if (false == UEngineInput::IsPress(VK_LEFT) && false == UEngineInput::IsPress(VK_RIGHT))
	{
		State = EPlayerState::IDLE;
		return;
	}

}

void AYoshi::JumpStart(float _DeltaTime)
{
	float Force = JumpPower - GravityForce.Y;
	Jump(_DeltaTime);
}

void AYoshi::Jump(float _DeltaTime)
{
	AddActorLocation({ 0.0f, (1.0f * JumpPower * _DeltaTime), 0.0f });
}

void AYoshi::JumpEnd(float _DeltaTime)
{
	State = EPlayerState::IDLE;
	return;
}

