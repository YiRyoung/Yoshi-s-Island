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
	return Yoshi->Collision->CheckPointColor(_Dir, _Color);
}

bool YoshiState::CheckLineColor(ECheckDir _Dir, UColor _Color)
{
	return Yoshi->Collision->CheckLineColor(_Dir, _Color);
}

bool YoshiState::CheckForceColor(FVector _Force, UColor _Color)
{
	return Yoshi->Collision->CheckForceColor(_Force, _Color);
}

bool YoshiState::IsScreen(ECheckDir _Dir)
{
	return Yoshi->Collision->IsScreen(_Dir);
}

bool YoshiState::IsGround()
{
	return Yoshi->Collision->IsGround();
}

bool YoshiState::IsSlope()
{
	return Yoshi->Collision->IsSlope();
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

#pragma region FSM Functions
void YoshiState::StateStart()
{
	switch (Yoshi->CurState)
	{
	case EPlayerState::WALK:
		WalkStart();
		break;
	case EPlayerState::RUN:
		RunStart();
		break;
	case EPlayerState::JUMP:
		JumpStart();
		break;
	case EPlayerState::STAYUP:
		StayUpStart();
		break;
	case EPlayerState::FALL:
		FallStart();
		break;
	case EPlayerState::LOOKUP:
		LookUpStart();
		break;
	case EPlayerState::BEND:
		BendStart();
		break;
	case EPlayerState::STICK:
		StickStart();
		break;
	}
}

void YoshiState::StateFunc(float _DeltaTime)
{
	switch (Yoshi->CurState)
	{
	case EPlayerState::IDLE:
		Idle(_DeltaTime);
		break;
	case EPlayerState::WALK:
		Walk(_DeltaTime);
		break;
	case EPlayerState::RUN:
		Run(_DeltaTime);
		break;
	case EPlayerState::JUMP:
		Jump(_DeltaTime);
		break;
	case EPlayerState::FALL:
		Fall(_DeltaTime);
		break;
	case EPlayerState::STAYUP:
		StayUp(_DeltaTime);
		break;
	case EPlayerState::LOOKUP:
		LookUp(_DeltaTime);
		break;
	case EPlayerState::BEND:
		Bend(_DeltaTime);
		break;
	case EPlayerState::STICK:
		Stick(_DeltaTime);
		break;
	}
}
#pragma endregion

#pragma region Start Functions
void YoshiState::WalkStart()
{
	ChangeAnimation("Walk");
}

void YoshiState::RunStart()
{
	ChangeAnimation("Run");
}

void YoshiState::JumpStart()
{
	ChangeAnimation("Jump");
}

void YoshiState::StayUpStart()
{
	ChangeAnimation("StayUp");
}

void YoshiState::FallStart()
{
	ChangeAnimation("Fall");
}

void YoshiState::LookUpStart()
{
	ChangeAnimation("LookUpStart");
	Yoshi->CameraNum = 1;
}

void YoshiState::BendStart()
{
	ChangeAnimation("BendStart");
	Yoshi->CameraNum = 2;
}

void YoshiState::StickStart()
{
	Yoshi->GravityForce = FVector::ZERO;
	Yoshi->DirForce = FVector::ZERO;

	if (IsPressKey(VK_UP))
	{
		ChangeAnimation("Stick_Up");
	}
	else
	{
		ChangeAnimation("Stick_Right");
	}
}
#pragma endregion

#pragma region State Functions
void YoshiState::Gravity(float _DeltaTime, float _Scale)
{
	FVector GravityValue = Yoshi->GravityForce * _DeltaTime;

	if (CheckForceColor(GravityValue, UColor::BLACK))
	{
		Yoshi->AddActorLocation(GravityValue);
		Yoshi->GravityForce += FVector::DOWN * Yoshi->GravityPower * _Scale * _DeltaTime;
	}
	else if (CheckForceColor(GravityValue * 2.0f, UColor::BLACK) && IsSlope()
		&& Yoshi->CurState != EPlayerState::JUMP)
	{
		Yoshi->AddActorLocation(GravityValue * 2.0f);
		Yoshi->GravityForce += FVector::DOWN * Yoshi->GravityPower * 2.0f * _DeltaTime;
	}
	else
	{
		Yoshi->GravityForce = FVector::ZERO;
	}
}

void YoshiState::Idle(float _DeltaTime)
{
	Yoshi->PlayIdleAnim(false);
	Gravity(_DeltaTime);

	// Walk
	if (IsPressKey(VK_LEFT) || IsPressKey(VK_RIGHT))
	{
		ChangeState(EPlayerState::WALK);
		StateStart();
		return;
	}

	// LookUp
	if (IsPressTime(VK_UP, 0.3f))
	{
		ChangeState(EPlayerState::LOOKUP);
		StateStart();
		return;
	}

	// Bend
	if (IsPressTime(VK_DOWN, 0.3f))
	{
		ChangeState(EPlayerState::BEND);
		StateStart();
		return;
	}

	// Stick
	if (IsDownKey('X'))
	{
		ChangeState(EPlayerState::STICK);
		StateStart();
		return;
	}
	
	// Jump
	if (IsDownKey(VK_LCONTROL))
	{
		ChangeState(EPlayerState::JUMP);
		StateStart();
		return;
	}

	// Fall
	if (CheckPointColor(ECheckDir::DOWN, UColor::BLACK) && !IsSlope())
	{
		ChangeState(EPlayerState::FALL);
		StateStart();
		return;
	}
	
	// DeAccel
	if ((Yoshi->DirForce.X < 0.0f && !CheckPointColor(ECheckDir::LEFT, UColor::MAGENTA) && !CheckPointColor(ECheckDir::LEFT, UColor::GREEN))
		|| (Yoshi->DirForce.X > 0.0f && !CheckPointColor(ECheckDir::RIGHT, UColor::MAGENTA) && !CheckPointColor(ECheckDir::RIGHT, UColor::GREEN)))
	{
		Yoshi->DirForce.X += -Yoshi->DirForce.X * Yoshi->DeAccSpeed * _DeltaTime;
		if (Yoshi->DirForce.Length() < 0.01f)
		{
			Yoshi->DirForce.X = 0.0f;
		}
		Yoshi->AddActorLocation(Yoshi->DirForce * _DeltaTime);
	}
	else
	{
		Yoshi->DirForce.X = 0.0f;
	}
}

void YoshiState::Walk(float _DeltaTime)
{
	Gravity(_DeltaTime);

	// Stick
	if (IsDownKey('X'))
	{
		ChangeState(EPlayerState::STICK);
		StateStart();
		return;
	}

	// Run
	if (IsPressTime(VK_LEFT, 0.4f) || IsPressTime(VK_RIGHT, 0.4f))
	{
		ChangeState(EPlayerState::RUN);
		StateStart();
		return;
	}

	// Jump
	if (IsDownKey(VK_LCONTROL))
	{
		ChangeState(EPlayerState::JUMP);
		StateStart();
		return;
	}

	// Idle
	if (!IsPressKey(VK_LEFT) && !IsPressKey(VK_RIGHT))
	{
		ChangeState(EPlayerState::IDLE);
		StateStart();
		return;
	}

	// Walk
	if (IsPressKey(VK_LEFT) && IsScreen(ECheckDir::LEFT) && !CheckPointColor(ECheckDir::LEFT, UColor::MAGENTA) && !CheckPointColor(ECheckDir::LEFT, UColor::GREEN))
	{
		Yoshi->AddActorLocation(FVector::LEFT * Yoshi->Speed * _DeltaTime);
	}
	else if (IsPressKey(VK_RIGHT) && IsScreen(ECheckDir::RIGHT) && !CheckPointColor(ECheckDir::RIGHT, UColor::MAGENTA) && !CheckPointColor(ECheckDir::RIGHT, UColor::GREEN))
	{
		Yoshi->AddActorLocation(FVector::RIGHT * Yoshi->Speed * _DeltaTime);
	}
}

void YoshiState::Run(float _DeltaTime)
{
	Gravity(_DeltaTime);
	// Stick
	if (IsDownKey('X'))
	{
		ChangeState(EPlayerState::STICK);
		StateStart();
		return;
	}

	// Jump
	if (IsDownKey(VK_LCONTROL))
	{
		ChangeState(EPlayerState::JUMP);
		StateStart();
		return;
	}

	// Idle
	if (!IsPressKey(VK_LEFT) && !IsPressKey(VK_RIGHT))
	{
		ChangeState(EPlayerState::IDLE);
		StateStart();
		return;
	}

	// Run (Accel)
	FVector Force = Yoshi->DirForce * _DeltaTime;
	if (IsPressKey(VK_LEFT) && !CheckForceColor(Force, UColor::MAGENTA) && !CheckForceColor(Force, UColor::GREEN))
	{
		Yoshi->AddActorLocation(Force);
		Yoshi->DirForce += FVector::LEFT * Yoshi->AccSpeed * _DeltaTime;

		if (Yoshi->DirForce.X > Yoshi->MaxSpeed)
		{
			Yoshi->DirForce.Normalize();
			Yoshi->DirForce.X *= Yoshi->MaxSpeed;
		}
	}
	else if ((IsPressKey(VK_LEFT) && CheckForceColor(Force, UColor::MAGENTA) && CheckForceColor(Force, UColor::GREEN)))
	{
		Yoshi->DirForce.X = 0.0f;
	}

	if (IsPressKey(VK_RIGHT) && !CheckForceColor(Force, UColor::MAGENTA) && !CheckForceColor(Force, UColor::GREEN))
	{
		Yoshi->AddActorLocation(Force);
		Yoshi->DirForce += FVector::RIGHT * Yoshi->AccSpeed * _DeltaTime;

		if (Yoshi->DirForce.X > Yoshi->MaxSpeed)
		{
			Yoshi->DirForce.Normalize();
			Yoshi->DirForce.X *= Yoshi->MaxSpeed;
		}
	}
	else if (IsPressKey(VK_RIGHT) && CheckForceColor(Force, UColor::MAGENTA) && CheckForceColor(Force, UColor::GREEN))
	{
		Yoshi->DirForce.X = 0.0f;
	}
	
}

void YoshiState::Jump(float _DeltaTime)
{
	Gravity(_DeltaTime);
	
	//Stick
	if (IsDownKey('X'))
	{
		ChangeState(EPlayerState::STICK);
		StateStart();
		return;
	}

	// Fall
	if (Yoshi->JumpPower + Yoshi->GravityForce.Y < 0.0f)
	{
		Yoshi->GravityForce = FVector::ZERO;
		ChangeState(EPlayerState::FALL);
		StateStart();
	}

	// Jump
	if (!CheckPointColor(ECheckDir::UP, UColor::MAGENTA))
	{
		Yoshi->AddActorLocation(FVector::UP * Yoshi->JumpPower * _DeltaTime);
	}
	if (IsPressKey(VK_LEFT) && IsScreen(ECheckDir::LEFT) && !CheckLineColor(ECheckDir::LEFT, UColor::MAGENTA) && !CheckLineColor(ECheckDir::LEFT, UColor::GREEN))
	{
		Yoshi->AddActorLocation(FVector::LEFT * Yoshi->Speed * _DeltaTime);
	}
	else if (IsPressKey(VK_RIGHT) && IsScreen(ECheckDir::RIGHT) && !CheckLineColor(ECheckDir::RIGHT, UColor::MAGENTA) && !CheckLineColor(ECheckDir::RIGHT, UColor::GREEN))
	{
		Yoshi->AddActorLocation(FVector::RIGHT * Yoshi->Speed * _DeltaTime);
	}
}

void YoshiState::StayUp(float _DeltaTime)
{
}

void YoshiState::Fall(float _DeltaTime)
{
	Gravity(_DeltaTime);

	// Stick
	if (IsDownKey('X'))
	{
		ChangeState(EPlayerState::STICK);
		StateStart();
		return;
	}

	if (IsPressKey(VK_LEFT) && IsScreen(ECheckDir::LEFT) && !CheckLineColor(ECheckDir::LEFT, UColor::MAGENTA) && !CheckLineColor(ECheckDir::LEFT, UColor::GREEN))
	{
		Yoshi->AddActorLocation(FVector::LEFT * Yoshi->Speed * _DeltaTime);
	}
	else if (IsPressKey(VK_RIGHT) && IsScreen(ECheckDir::RIGHT) && !CheckLineColor(ECheckDir::RIGHT, UColor::MAGENTA) && !CheckLineColor(ECheckDir::RIGHT, UColor::GREEN))
	{
		Yoshi->AddActorLocation(FVector::RIGHT * Yoshi->Speed * _DeltaTime);
	}

	// Idle
	if (Yoshi->GravityForce == FVector::ZERO)
	{
		ChangeState(EPlayerState::IDLE);
		StateStart();
	}
}

void YoshiState::LookUp(float _DeltaTime)
{
	if (IsDownKey('X'))
	{
		ChangeState(EPlayerState::STICK);
		StateStart();
		return;
	}

	if (!IsPressKey(VK_UP))
	{
		ChangeAnimation("LookUpEnd");

		if (Yoshi->YoshiRenderer->IsCurAnimationEnd())
		{
			ChangeState(EPlayerState::IDLE);
			StateStart();
			return;
		}
	}
}

void YoshiState::Bend(float _DeltaTime)
{
	if (IsDownKey('X'))
	{
		ChangeState(EPlayerState::STICK);
		StateStart();
		return;
	}

	if (!IsPressKey(VK_DOWN))
	{
		ChangeAnimation("BendEnd");
	
		if (Yoshi->YoshiRenderer->IsCurAnimationEnd())
		{
			ChangeState(EPlayerState::IDLE);
			StateStart();
			return;
		}
	}
}

void YoshiState::Stick(float _DeltaTime)
{
	Gravity(_DeltaTime);

	if (IsPressKey(VK_LEFT) && IsScreen(ECheckDir::LEFT) && !CheckLineColor(ECheckDir::LEFT, UColor::MAGENTA) && !CheckLineColor(ECheckDir::LEFT, UColor::GREEN))
	{
		Yoshi->AddActorLocation(FVector::LEFT * Yoshi->Speed * _DeltaTime);
	}
	else if (IsPressKey(VK_RIGHT) && IsScreen(ECheckDir::RIGHT) && !CheckLineColor(ECheckDir::RIGHT, UColor::MAGENTA) && !CheckLineColor(ECheckDir::RIGHT, UColor::GREEN))
	{
		Yoshi->AddActorLocation(FVector::RIGHT * Yoshi->Speed * _DeltaTime);
	}

	if (Yoshi->YoshiRenderer->IsCurAnimationEnd())
	{
		ChangeState(EPlayerState::IDLE);
		StateStart();
		return;
	}

}
#pragma endregion