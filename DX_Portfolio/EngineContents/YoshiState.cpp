#include "PreCompile.h"
#include "YoshiState.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>

#include "Yoshi.h"

YoshiState::YoshiState() {}

YoshiState::YoshiState(AYoshi* _Yoshi) : Yoshi(_Yoshi) {}

YoshiState::~YoshiState() {}

#pragma region Wrapping Func
bool YoshiState::IsPressKey(int _KeyCode)
{
	return UEngineInput::IsPress(_KeyCode);
}

bool YoshiState::IsPressTime(int _KeyCode, float _Time)
{
	bool Result = (UEngineInput::IsPressTime(_KeyCode) >= _Time) ? true : false;
	return Result;
}

bool YoshiState::IsDownKey(int _KeyCode)
{
	return UEngineInput::IsDown(_KeyCode);
}

bool YoshiState::IsUpKey(int _KeyCode)
{
	return UEngineInput::IsUp(_KeyCode);
}

bool YoshiState::CheckPointColor(ECheckDir _Dir, UColor _Color)
{
	return Yoshi->GetCollision()->CheckPointColor(_Dir, _Color);
}

bool YoshiState::CheckLineColor(ECheckDir _Dir, UColor _Color)
{
	return Yoshi->GetCollision()->CheckLineColor(_Dir, _Color);
}

void YoshiState::ChangeAnimation(std::string_view _Name)
{
	Yoshi->YoshiRenderer->ChangeAnimation(_Name);
}
void YoshiState::ChangeState(EPlayerState _NextState)
{
	Yoshi->CurState = _NextState;
}
#pragma endregion

void YoshiState::YoshiFSM(float _DeltaTime)
{
	switch (Yoshi->CurState)
	{
	case EPlayerState::IDLE:
		IdleStart(_DeltaTime);
		break;
	case EPlayerState::WALK:
		WalkStart(_DeltaTime);
		break;
	case EPlayerState::RUN:
		RunStart(_DeltaTime);
		break;
	case EPlayerState::JUMP:
		JumpStart(_DeltaTime);
		break;
	case EPlayerState::STAYUP:
		StayUpStart(_DeltaTime);
		break;
	case EPlayerState::LOOKUP:
		LookUpStart(_DeltaTime);
		break;
	case EPlayerState::BEND:
		BendStart(_DeltaTime);
		break;
	case EPlayerState::STICK:
		StickStart(_DeltaTime);
		break;
	}
}

void YoshiState::Gravity(float _DeltaTime, float _Scale)
{
	FVector Power = (FVector::DOWN + Yoshi->GravityForce) * _DeltaTime;
	FVector CheckPos = Yoshi->GetActorLocation() + Power;

	UColor Color = Yoshi->GetColor(CheckPos);

	if (Color == UColor::BLACK)
	{
		Yoshi->GravityForce += FVector::DOWN * Yoshi->GravityPower * _Scale * _DeltaTime;
		Yoshi->AddActorLocation(Power);
	}
	else
	{
		Yoshi->GravityForce = FVector::ZERO;
	}
}

void YoshiState::IdleStart(float _DeltaTime)
{
	Yoshi->PlayIdleAnim(false);
	Idle(_DeltaTime);
}

void YoshiState::Idle(float _DeltaTime)
{
	Gravity(_DeltaTime);

	if (IsPressKey(VK_LEFT) || IsPressKey(VK_RIGHT))
	{
		ChangeState(EPlayerState::WALK);
		return;
	}

	if (IsDownKey('X'))
	{
		ChangeState(EPlayerState::STICK);
		return;
	}

	if (IsDownKey('Z'))
	{
		ChangeState(EPlayerState::JUMP);
		return;
	}
	if (IsPressKey(VK_UP))
	{
		ChangeState(EPlayerState::LOOKUP);
		return;
	}
}

void YoshiState::WalkStart(float _DeltaTime)
{
	ChangeAnimation("Walk");
	Walk(_DeltaTime);
}

void YoshiState::Walk(float _DeltaTime)
{
	if (IsPressKey(VK_LEFT) && !CheckPointColor(ECheckDir::LEFT, UColor::MAGENTA))
	{
		Yoshi->AddActorLocation({ -Yoshi->Speed * _DeltaTime, 0.0f });
	}

	if (IsPressKey(VK_RIGHT) && !CheckPointColor(ECheckDir::RIGHT, UColor::MAGENTA))
	{
		Yoshi->AddActorLocation({ Yoshi->Speed * _DeltaTime, 0.0f });
	}


	if (IsDownKey('X'))
	{
		ChangeState(EPlayerState::STICK);
		return;
	}

	if (IsDownKey('Z'))
	{
		ChangeState(EPlayerState::JUMP);
		return;
	}

	if (IsPressTime(VK_LEFT, 0.4f) || IsPressTime(VK_RIGHT, 0.4f))
	{
		ChangeState(EPlayerState::RUN);
		return;
	}

	if (!IsPressKey(VK_LEFT) && !IsPressKey(VK_RIGHT))
	{
		ChangeState(EPlayerState::IDLE);
		return;
	}

	Gravity(_DeltaTime);
}

void YoshiState::RunStart(float _DeltaTime)
{
	ChangeAnimation("Run");
	Run(_DeltaTime);
}

void YoshiState::Run(float _DeltaTime)
{
	if (IsPressKey(VK_LEFT) && !CheckPointColor(ECheckDir::LEFT, UColor::MAGENTA))
	{
		Yoshi->AddActorLocation({(-Yoshi->Speed - 80.0f) * _DeltaTime, 0.0f });
	}

	if (IsPressKey(VK_RIGHT) && !CheckPointColor(ECheckDir::RIGHT, UColor::MAGENTA))
	{
		Yoshi->AddActorLocation({ (Yoshi->Speed + 80.0f) * _DeltaTime, 0.0f });
	}

	if (IsDownKey('X'))
	{
		ChangeState(EPlayerState::STICK);
		return;
	}

	if (IsPressKey('Z'))
	{
		ChangeState(EPlayerState::JUMP);
		return;
	}

	if (!IsPressKey(VK_LEFT) && !IsPressKey(VK_RIGHT))
	{
		ChangeState(EPlayerState::IDLE);
		return;
	}

	Gravity(_DeltaTime);
}

void YoshiState::JumpStart(float _DeltaTime)
{
	float Force = Yoshi->JumpPower + Yoshi->GravityForce.Y;

	if (Force > 0.0f)
	{
		ChangeAnimation("JumpStart");
	}
	else
	{
		if (IsPressKey('Z')) 
		{
			Yoshi->GravityForce = FVector::ZERO;
			ChangeState(EPlayerState::STAYUP);
			return;
		}

		ChangeAnimation("Fall");
	}

	Jump(_DeltaTime);
}

void YoshiState::Jump(float _DeltaTime)
{

	FVector Vector = FVector::ZERO;

	if (IsPressKey(VK_LEFT) && !CheckLineColor(ECheckDir::LEFT, UColor::MAGENTA))
	{
		Vector += FVector::LEFT * 0.58f;
	}
	if (IsPressKey(VK_RIGHT) && !CheckLineColor(ECheckDir::RIGHT, UColor::MAGENTA))
	{
		Vector += FVector::RIGHT * 0.58f;
	}
	if (CheckPointColor(ECheckDir::UP, UColor::MAGENTA))
	{
		ChangeState(EPlayerState::IDLE);
		return;
	}

	Yoshi->AddActorLocation({ (Vector + FVector::UP) * Yoshi->JumpPower * _DeltaTime });
	Gravity(_DeltaTime);

	if (Yoshi->GravityForce == FVector::ZERO)
	{
		ChangeState(EPlayerState::IDLE);
		return;
	}
}

void YoshiState::StayUpStart(float _DeltaTime)
{
	ChangeAnimation("StayUp");
	StayUp(_DeltaTime);
}

void YoshiState::StayUp(float _DeltaTime)
{
	FVector Vector = FVector::ZERO;

	if (IsPressKey(VK_LEFT) && !CheckPointColor(ECheckDir::LEFT, UColor::MAGENTA))
	{
		Vector += FVector::LEFT * Yoshi->Speed * 0.58f * _DeltaTime;
	}
	if (IsPressKey(VK_RIGHT) && !CheckPointColor(ECheckDir::RIGHT, UColor::MAGENTA))
	{
		Vector += FVector::RIGHT * Yoshi->Speed * 0.58f * _DeltaTime;
	}

	Yoshi->AddActorLocation({ Vector + FVector::UP * Yoshi->JumpPower * 0.4f * _DeltaTime });
	Gravity(_DeltaTime, 0.52f);

	if (!IsPressKey('Z') ||  1.8f <= UEngineInput::IsPressTime('Z'))
	{
		ChangeState(EPlayerState::IDLE);
		return;
	}
}

void YoshiState::LookUpStart(float _DeltaTime)
{
	ChangeAnimation("LookUpStart");
	LookUp(_DeltaTime);
}

void YoshiState::LookUp(float _DeltaTime)
{
	float MaxCameraPivotY = 100.0f;
	 Yoshi->CameraPivot += FVector::UP * _DeltaTime * 100.0f;
	 if (Yoshi->CameraPivot.Y > MaxCameraPivotY)
	 {
		 Yoshi->CameraPivot.Y = MaxCameraPivotY;
		 ChangeState(EPlayerState::IDLE);
		 return;
	 }
}

void YoshiState::BendStart(float _DeltaTime)
{
	ChangeAnimation("Bend");
	Bend(_DeltaTime);
}

void YoshiState::Bend(float _DeltaTime)
{
	float MinCameraPivotY = 0.0f;
	Yoshi->CameraPivot += FVector::DOWN * _DeltaTime * 100.0f;

	if (Yoshi->CameraPivot.Y < MinCameraPivotY)
	{
		Yoshi->CameraPivot.Y = MinCameraPivotY;
		ChangeState(EPlayerState::IDLE);
		return;
	}
}

void YoshiState::StickStart(float _DeltaTime)
{
	ChangeAnimation("Stick_Right");
	Stick(_DeltaTime);
}

void YoshiState::Stick(float _DeltaTime)
{
	if (Yoshi->YoshiRenderer->IsCurAnimationEnd())
	{
		ChangeState(EPlayerState::IDLE);
		return;
	}
}
