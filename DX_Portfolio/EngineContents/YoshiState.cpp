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
		break;
	case EPlayerState::LOOKUPSTART:
		break;
	case EPlayerState::LOOKUPEND:
		break;
	case EPlayerState::BENDSTART:
		break;
	case EPlayerState::BENDEND:
		break;
	}
}

void YoshiState::Gravity(float _DeltaTime)
{
	if (Yoshi->GetCollision()->IsAir())
	{
		FVector Power = Yoshi->GetGravityForce() * _DeltaTime;
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
}

void YoshiState::WalkStart(float _DeltaTime)
{
	ChangeAnimation("Walk");
	Walk(_DeltaTime);
}

void YoshiState::Walk(float _DeltaTime)
{
	if (IsPressKey(VK_LEFT))
	{
		if (!CheckColor(ECheckDir::LEFT, UColor::WHITE) && !CheckColor(ECheckDir::LEFT, UColor::MAGENTA))
		{
			Yoshi->Move(-Yoshi->GetSpeed() * _DeltaTime, 0.0f);
			Yoshi->GetCollision()->GroundUp(_DeltaTime);
		}
	}

	if (IsPressKey(VK_RIGHT))
	{
		if (!CheckColor(ECheckDir::RIGHT, UColor::WHITE) && !CheckColor(ECheckDir::RIGHT, UColor::MAGENTA))
		{
			Yoshi->Move(Yoshi->GetSpeed() * _DeltaTime, 0.0f);
			Yoshi->GetCollision()->GroundUp(_DeltaTime);
		}
	}

	if (!IsPressKey(VK_LEFT) && !IsPressKey(VK_RIGHT))
	{
		Yoshi->SetCurState(EPlayerState::IDLE);
		return;
	}
}
