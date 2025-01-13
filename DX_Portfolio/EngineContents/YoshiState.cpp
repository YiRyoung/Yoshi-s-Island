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

bool YoshiState::CheckColor(ECheckDir _Dir, UColor _Color)
{
	return Yoshi->GetCollision()->CheckColor(_Dir, _Color);
}

void YoshiState::ChangeAnimation(std::string_view _Name)
{
	Yoshi->GetYoshiRenderer()->ChangeAnimation(_Name);
}
#pragma endregion

void YoshiState::YoshiFSM(float _DeltaTime)
{
	switch (Yoshi->GetCurState())
	{
	case EPlayerState::IDLE:
		IdleStart(_DeltaTime);
		break;
	case EPlayerState::WALK:
		WalkStart(_DeltaTime);
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
	case EPlayerState::FALL:
		FallStart(_DeltaTime);
		break;
	}
}

void YoshiState::Gravity(float _DeltaTime, float _Scale)
{
	FVector Power = Yoshi->GetGravityForce() * _DeltaTime;
	FVector CheckPos = Yoshi->GetActorLocation() + Power;
	UColor Color = Yoshi->GetColor(CheckPos);

	if (Color != UColor::MAGENTA && Color != UColor::CYAN)
	{
		Yoshi->AddGravityForce(FVector::DOWN * Yoshi->GetGravityPower() *  _Scale * _DeltaTime);
		Yoshi->Move(Power);
	}
	else
	{
		Yoshi->SetGravityForce(FVector::ZERO);
	}
}

void YoshiState::IdleStart(float _DeltaTime)
{
	Yoshi->SetIdleAnim();
	Idle(_DeltaTime);
}

void YoshiState::Idle(float _DeltaTime)
{
	if (IsPressKey(VK_LEFT) || IsPressKey(VK_RIGHT))
	{
		Yoshi->SetCurState(EPlayerState::WALK);
		return;
	}

	if (IsDownKey('Z'))
	{
		Yoshi->SetCurState(EPlayerState::JUMP);
		return;
	}

	if (IsPressKey(VK_UP))
	{
		Yoshi->SetCurState(EPlayerState::LOOKUP);
		return;
	}

	//if (!CheckColor(ECheckDir::DOWN, UColor::MAGENTA) && !CheckColor(ECheckDir::DOWN, UColor::CYAN))
	//{
	//	Yoshi->SetCurState(EPlayerState::FALL);
	//	return;
	//}

	Gravity(_DeltaTime);
}

void YoshiState::WalkStart(float _DeltaTime)
{
	ChangeAnimation("Walk");
	Walk(_DeltaTime);
}

void YoshiState::Walk(float _DeltaTime)
{
	if (IsPressKey(VK_LEFT) && !CheckColor(ECheckDir::LEFT, UColor::WHITE) && !CheckColor(ECheckDir::LEFT, UColor::MAGENTA))
	{
		Yoshi->Move(-Yoshi->GetSpeed() * _DeltaTime, 0.0f);
		Yoshi->GetCollision()->GroundUp(_DeltaTime);
	}

	if (IsPressKey(VK_RIGHT) && !CheckColor(ECheckDir::RIGHT, UColor::WHITE) && !CheckColor(ECheckDir::RIGHT, UColor::MAGENTA))
	{
		Yoshi->Move(Yoshi->GetSpeed() * _DeltaTime, 0.0f);
		Yoshi->GetCollision()->GroundUp(_DeltaTime);
	}

	if (IsDownKey('Z'))
	{
		Yoshi->SetCurState(EPlayerState::JUMP);
		return;
	}

	if (!IsPressKey(VK_LEFT) && !IsPressKey(VK_RIGHT))
	{
		Yoshi->SetCurState(EPlayerState::IDLE);
		return;
	}

	Gravity(_DeltaTime);
}

void YoshiState::JumpStart(float _DeltaTime)
{
	float Force = Yoshi->GetJumpPower() + Yoshi->GetGravityForce().Y;

	if (Force > 0.0f)
	{
		ChangeAnimation("JumpStart");
	}
	else
	{
		if (IsPressKey('Z')) 
		{
			Yoshi->SetGravityForce(FVector::ZERO);
			Yoshi->SetCurState(EPlayerState::STAYUP);
			return;
		}

		ChangeAnimation("Fall");
	}

	Jump(_DeltaTime);
}

void YoshiState::Jump(float _DeltaTime)
{

	FVector Vector = FVector::ZERO;

	if (IsPressKey(VK_LEFT) && !CheckColor(ECheckDir::LEFT, UColor::MAGENTA))
	{
		Vector += FVector::LEFT * 0.58f;
	}
	if (IsPressKey(VK_RIGHT) && !CheckColor(ECheckDir::RIGHT, UColor::MAGENTA))
	{
		Vector += FVector::RIGHT * 0.58f;
	}
	if (CheckColor(ECheckDir::UP, UColor::MAGENTA))
	{
		Yoshi->SetCurState(EPlayerState::IDLE);
		return;
	}

	Yoshi->Move((Vector + FVector::UP)* Yoshi->GetJumpPower() * _DeltaTime);
	Gravity(_DeltaTime);

	if (Yoshi->GetGravityForce() == FVector::ZERO)
	{
		Yoshi->SetCurState(EPlayerState::IDLE);
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

	if (IsPressKey(VK_LEFT))
	{
		Vector += FVector::LEFT * Yoshi->GetSpeed() * 0.58f * _DeltaTime;
	}
	if (IsPressKey(VK_RIGHT))
	{
		Vector += FVector::RIGHT * Yoshi->GetSpeed() * 0.58f * _DeltaTime;
	}

	Yoshi->Move(Vector + FVector::UP * Yoshi->GetJumpPower() * 0.4f * _DeltaTime);
	Gravity(_DeltaTime, 0.52f);

	if (!IsPressKey('Z') ||  1.8f <= UEngineInput::IsPressTime('Z'))
	{
		Yoshi->SetCurState(EPlayerState::IDLE);
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

}

void YoshiState::BendStart(float _DeltaTime)
{
}

void YoshiState::Bend(float _DeltaTime)
{
}

void YoshiState::FallStart(float _DeltaTime)
{
	ChangeAnimation("Fall");
	Fall(_DeltaTime);
}

void YoshiState::Fall(float _DeltaTime)
{

}
