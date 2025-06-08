#include "PreCompile.h"
#include "YoshiState.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "YoshiGameInstance.h"
#include "Yoshi.h"

#pragma region Wrapping Functions
bool YoshiState::IsPress(int _KeyCode)
{
	return UEngineInput::IsPress(_KeyCode);
}

bool YoshiState::IsPressTime(int _KeyCode, float _Time)
{
	bool Result = (UEngineInput::IsPressTime(_KeyCode) >= _Time) ? true : false;
	return Result;
}

bool YoshiState::IsDown(int _KeyCode)
{
	return UEngineInput::IsDown(_KeyCode);
}

bool YoshiState::IsUp(int _KeyCode)
{
	return UEngineInput::IsUp(_KeyCode);
}

bool YoshiState::IsFree(int _KeyCode)
{
	return UEngineInput::IsFree(_KeyCode);
}
void YoshiState::ChangeAnimation(std::string _AnimName)
{
	Yoshi->YoshiRenderer->ChangeAnimation(_AnimName);
}
void YoshiState::ChangeDefence()
{
	Yoshi->IsDefence = false;
	Yoshi->BodyCollision->SetActive(true);
	Yoshi->FootCollision->SetActive(true);
}
void YoshiState::Gravity(float _DeltaTime)
{
	FVector GravityValue = Yoshi->GravityForce * _DeltaTime;

	if (Yoshi->ScaleBlock == nullptr && Yoshi->CheckForceColor(GravityValue, UColor::BLACK))
	{
		Yoshi->AddActorLocation(GravityValue);
		Yoshi->GravityForce += FVector::DOWN * Yoshi->GravityPower * _DeltaTime;
	}
	else
	{
		Yoshi->GravityForce = FVector::ZERO;
	}
}
#pragma endregion

void YoshiState::CreateFSM()
{
	FSM.CreateState(EPlayerState::IDLE,
		[this](float _DeltaTime)
		{
			// Animation
			if (Yoshi->YoshiRenderer->IsCurAnimationEnd())
			{
				if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					Yoshi->PlayIdleAnim();
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					Yoshi->PlayIdleAnim();
				}
			}

			// Fall
			if (nullptr == Yoshi->Platform && nullptr == Yoshi->ScaleBlock && Yoshi->CheckForceColor(FVector::DOWN * 10.0f, UColor::BLACK) && !Yoshi->IsSlope())
			{
				FSM.ChangeState(EPlayerState::FALL);
				return;
			}

			// Walk
			if (IsPress(VK_LEFT) || IsPress(VK_RIGHT))
			{
				FSM.ChangeState(EPlayerState::WALK);
				return;
			}

			// Jump
			if (IsDown(VK_LCONTROL))
			{
				FSM.ChangeState(EPlayerState::JUMP);
				return;
			}

			// LookUp
			if (IsPress(VK_UP))
			{
				FSM.ChangeState(EPlayerState::LOOKUP);
				return;
			}

			// Bend
			if (IsPress(VK_DOWN) && !Yoshi->IsHold)
			{
				FSM.ChangeState(EPlayerState::BEND);
				return;
			}

			// Stick
			if (IsDown('X') && !Yoshi->IsHold)
			{
				Yoshi->StickDir = 2;
				FSM.ChangeState(EPlayerState::STICK);
				return;
			}

			if (IsDown('Z'))
			{
				if (Yoshi->GetGameInstance<AYoshiGameInstance>()->EggCount > 0)
				{
					// Aim
					if (!Yoshi->IsAim)
					{
						Yoshi->IsAim = true;
						FSM.ChangeState(EPlayerState::IDLE);
						return;
					}
					else  // Throw
					{
						Yoshi->IsAim = false;
						SoundPlayer.Off();
						FSM.ChangeState(EPlayerState::THROW);
						return;
					}
				}
			}

			// Eat
			if (Yoshi->IsHold && IsPress(VK_DOWN))
			{
				FSM.ChangeState(EPlayerState::EAT);
				return;
			}

			// DeAccel
			if ((Yoshi->ScaleCollisionType != 2 && Yoshi->DirForce.X < 0.0f && !Yoshi->CheckPointColor(ECheckDir::LEFT, UColor::WHITE) && !Yoshi->CheckPointColor(ECheckDir::LEFT, UColor::MAGENTA) && !Yoshi->CheckPointColor(ECheckDir::LEFT, UColor::GREEN))
				|| (Yoshi->ScaleCollisionType != 1 && Yoshi->DirForce.X > 0.0f && !Yoshi->CheckPointColor(ECheckDir::RIGHT, UColor::WHITE) && !Yoshi->CheckPointColor(ECheckDir::RIGHT, UColor::MAGENTA) && !Yoshi->CheckPointColor(ECheckDir::RIGHT, UColor::GREEN)))
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
		},
		[this]()
		{
			Yoshi->CurState = EPlayerState::IDLE;

			if (Yoshi->IsWithBaby)	// M
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MNH_AimIdle");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					int AnimNum = Yoshi->IdleAnimNum();
					ChangeAnimation("MNH_Idle" + std::to_string(AnimNum));
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MH_AimIdle");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					int AnimNum = Yoshi->IdleAnimNum();
					ChangeAnimation("MH_Idle" + std::to_string(AnimNum));
				}
			}
			else   // Y
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YNH_AimIdle");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					int AnimNum = Yoshi->IdleAnimNum();
					ChangeAnimation("YNH_Idle" + std::to_string(AnimNum));
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YH_AimIdle");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					int AnimNum = Yoshi->IdleAnimNum();
					ChangeAnimation("YH_Idle" + std::to_string(AnimNum));
				}
			}
		}
	);

	FSM.CreateState(EPlayerState::WALK,
		[this](float _DeltaTime)
		{
			// Run
			if ((IsPressTime(VK_LEFT, 0.4f) || IsPressTime(VK_RIGHT, 0.4f)) && !Yoshi->IsAim)
			{
				FSM.ChangeState(EPlayerState::RUN);
				return;
			}

			// Jump
			if (IsDown(VK_LCONTROL))
			{
				FSM.ChangeState(EPlayerState::JUMP);
				return;
			}

			// Idle
			if (!IsPress(VK_LEFT) && !IsPress(VK_RIGHT))
			{
				FSM.ChangeState(EPlayerState::IDLE);
				return;
			}

			// Stick
			if (IsDown('X') && !Yoshi->IsHold)
			{
				Yoshi->StickDir = 2;
				FSM.ChangeState(EPlayerState::STICK);
				return;
			}

			if (IsDown('Z'))
			{
				// Aim
				if (!Yoshi->IsAim)
				{
					Yoshi->IsAim = true;
					FSM.ChangeState(EPlayerState::IDLE);
					return;
				}
				else  // Throw
				{
					Yoshi->IsAim = false;
					FSM.ChangeState(EPlayerState::THROW);
					return;
				}
			}

			// Walk
			if (Yoshi->ScaleCollisionType != 2 && IsPress(VK_LEFT) && !Yoshi->CheckPointColor(ECheckDir::LEFT, UColor::WHITE) &&
				!Yoshi->CheckPointColor(ECheckDir::LEFT, UColor::MAGENTA) && !Yoshi->CheckPointColor(ECheckDir::LEFT, UColor::GREEN))
			{
				if (nullptr == Yoshi->Platform)
				{
					Yoshi->AddActorLocation(FVector::LEFT * Yoshi->Speed * _DeltaTime);
				}
				else
				{
					Yoshi->PlatformPos += FVector::LEFT * Yoshi->Speed * _DeltaTime;
				}
			}
			if (Yoshi->ScaleCollisionType != 1 && IsPress(VK_RIGHT) && !Yoshi->CheckPointColor(ECheckDir::RIGHT, UColor::WHITE) &&
				!Yoshi->CheckPointColor(ECheckDir::RIGHT, UColor::MAGENTA) && !Yoshi->CheckPointColor(ECheckDir::RIGHT, UColor::GREEN))
			{
				if (nullptr == Yoshi->Platform)
				{
					Yoshi->AddActorLocation(FVector::RIGHT * Yoshi->Speed * _DeltaTime);
				}
				else
				{
					Yoshi->PlatformPos += FVector::RIGHT * Yoshi->Speed * _DeltaTime;
				}
			}
		},
		[this]()
		{
			Yoshi->CurState = EPlayerState::WALK;

			if (Yoshi->IsWithBaby)	// M
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MNH_AimWalk");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MNH_Walk");
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MH_AimWalk");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MH_Walk");
				}
			}
			else   // Y
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YNH_AimWalk");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YNH_Walk");
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YH_AimWalk");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YH_Walk");
				}
			}
		}
	);

	FSM.CreateState(EPlayerState::RUN,
		[this](float _DeltaTime)
		{
			// Idle
			if (!IsPress(VK_LEFT) && !IsPress(VK_RIGHT))
			{
				FSM.ChangeState(EPlayerState::IDLE);
				return;
			}

			// Jump
			if (IsDown(VK_LCONTROL))
			{
				FSM.ChangeState(EPlayerState::JUMP);
				return;
			}

			// Stick
			if (IsDown('X') && !Yoshi->IsHold)
			{
				Yoshi->StickDir = 2;
				FSM.ChangeState(EPlayerState::STICK);
				return;
			}

			if (IsDown('Z'))
			{
				// Aim
				if (!Yoshi->IsAim)
				{
					Yoshi->IsAim = true;
					FSM.ChangeState(EPlayerState::IDLE);
					return;
				}
				else  // Throw
				{
					Yoshi->IsAim = false;
					FSM.ChangeState(EPlayerState::THROW);
					return;
				}
			}

			// Run
			FVector Force = Yoshi->DirForce * _DeltaTime;

			if (Yoshi->ScaleCollisionType != 2 && IsPress(VK_LEFT) && !Yoshi->CheckForceColor(Force, UColor::WHITE)
				&& !Yoshi->CheckForceColor(Force, UColor::MAGENTA) && !Yoshi->CheckForceColor(Force, UColor::GREEN))
			{
				if (nullptr == Yoshi->Platform)
				{
					Yoshi->AddActorLocation(Force);
				}
				else
				{
					Yoshi->PlatformPos += Force;
				}

				Yoshi->DirForce += FVector::LEFT * Yoshi->AccSpeed * _DeltaTime;

				if (Yoshi->DirForce.X < -Yoshi->MaxSpeed)
				{
					Yoshi->DirForce.Normalize();
					Yoshi->DirForce.X *= Yoshi->MaxSpeed;
				}
			}
			else if ((IsPress(VK_LEFT) && Yoshi->CheckForceColor(Force, UColor::MAGENTA)
				&& Yoshi->CheckForceColor(Force, UColor::GREEN)))
			{
				Yoshi->DirForce.X = 0.0f;
			}

			if (Yoshi->ScaleCollisionType != 1 && IsPress(VK_RIGHT) && !Yoshi->CheckForceColor(Force, UColor::WHITE)
				&& !Yoshi->CheckForceColor(Force, UColor::MAGENTA) && !Yoshi->CheckForceColor(Force, UColor::GREEN))
			{
				if (nullptr == Yoshi->Platform)
				{
					Yoshi->AddActorLocation(Force);
				}
				else
				{
					Yoshi->PlatformPos += Force;
				}

				Yoshi->DirForce += FVector::RIGHT * Yoshi->AccSpeed * _DeltaTime;

				if (Yoshi->DirForce.X > Yoshi->MaxSpeed)
				{
					Yoshi->DirForce.Normalize();
					Yoshi->DirForce.X *= Yoshi->MaxSpeed;
				}
			}
			else if ((IsPress(VK_RIGHT) && Yoshi->CheckForceColor(Force, UColor::MAGENTA)
				&& Yoshi->CheckForceColor(Force, UColor::GREEN)))
			{
				Yoshi->DirForce.X = 0.0f;
			}
		},
		[this]()
		{
			Yoshi->CurState = EPlayerState::RUN;

			if (Yoshi->IsWithBaby)	// M
			{
				if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MNH_Run");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MH_Run");
				}
			}
			else   // Y
			{
				if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YNH_Run");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YH_Run");
				}
			}
		}
	);

	FSM.CreateState(EPlayerState::JUMP,
		[this](float _DeltaTime)
		{
			// StayUp
			if (Yoshi->IsStayUp == false && (Yoshi->JumpPower + Yoshi->GravityForce.Y) < 0.0f && IsPress(VK_LCONTROL))
			{
				Yoshi->IsStayUp = true;
				Yoshi->GravityForce = FVector::ZERO;
				Yoshi->JumpPower = 550.0f;
				FSM.ChangeState(EPlayerState::STAYUP);
				return;
			}

			// Fall
			if ((Yoshi->JumpPower + Yoshi->GravityForce.Y) < 0.0f)
			{
				Yoshi->JumpPower = 550.0f;
				Yoshi->GravityForce = FVector::ZERO;
				Yoshi->HeadCollision->SetActive(false);
				FSM.ChangeState(EPlayerState::FALL);
				return;
			}

			// Stick
			if (IsDown('X') && !Yoshi->IsHold)
			{
				if (IsPress(VK_UP))
				{
					Yoshi->StickDir = 1;
				}
				else
				{
					Yoshi->StickDir = 2;
				}

				Yoshi->JumpPower = 550.0f;
				Yoshi->GravityForce = FVector::ZERO;
				FSM.ChangeState(EPlayerState::STICK);
				return;
			}

			if (IsDown('Z'))
			{
				Yoshi->JumpPower = 550.0f;

				// Aim
				if (!Yoshi->IsAim)
				{
					Yoshi->IsAim = true;
					FSM.ChangeState(EPlayerState::IDLE);
					return;
				}
				else  // Throw
				{
					Yoshi->IsAim = false;
					FSM.ChangeState(EPlayerState::THROW);
					return;
				}
			}

			// Jump
			if (!Yoshi->CheckPointColor(ECheckDir::UP, UColor::MAGENTA))
			{
				if (nullptr == Yoshi->Platform)
				{
					Yoshi->AddActorLocation(FVector::UP * Yoshi->JumpPower * _DeltaTime);
				}
				else
				{
					Yoshi->PlatformPos += FVector::UP * Yoshi->JumpPower * _DeltaTime;
				}
			}
			else
			{
				Yoshi->HeadCollision->SetActive(false);
				FSM.ChangeState(EPlayerState::FALL);
				return;
			}

			if (Yoshi->ScaleCollisionType != 2 && IsPress(VK_LEFT) && !Yoshi->CheckLineColor(ECheckDir::LEFT, UColor::WHITE)
				&& !Yoshi->CheckLineColor(ECheckDir::LEFT, UColor::MAGENTA) && !Yoshi->CheckLineColor(ECheckDir::LEFT, UColor::GREEN))
			{
				if (nullptr == Yoshi->Platform)
				{
					Yoshi->AddActorLocation(FVector::LEFT * Yoshi->Speed * _DeltaTime);
				}
				else
				{
					Yoshi->PlatformPos += FVector::LEFT * Yoshi->Speed * _DeltaTime;
				}
			}
			if (Yoshi->ScaleCollisionType != 1 && IsPress(VK_RIGHT) && !Yoshi->CheckLineColor(ECheckDir::RIGHT, UColor::WHITE)
				&& !Yoshi->CheckLineColor(ECheckDir::RIGHT, UColor::MAGENTA) && !Yoshi->CheckLineColor(ECheckDir::RIGHT, UColor::GREEN))
			{
				if (nullptr == Yoshi->Platform)
				{
					Yoshi->AddActorLocation(FVector::RIGHT * Yoshi->Speed * _DeltaTime);
				}
				else
				{
					Yoshi->PlatformPos += FVector::RIGHT * Yoshi->Speed * _DeltaTime;
				}
			}
		},
		[this]()
		{
			SoundPlayer = UEngineSound::Play("Jump.wav");
			Yoshi->CurState = EPlayerState::JUMP;
			Yoshi->HeadCollision->SetActive(true);

			if (Yoshi->IsWithBaby)	// M
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MNH_AimIdle");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MNH_Jump");
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MH_AimIdle");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MH_Jump");
				}
			}
			else   // Y
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YNH_AimIdle");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YNH_Jump");
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YH_AimIdle");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YH_Jump");
				}
			}
		}
	);

	FSM.CreateState(EPlayerState::FALL,
		[this](float _DeltaTime)
		{
			// StayUp
			if (IsDown(VK_LCONTROL))
			{
				Yoshi->IsStayUp = true;
				Yoshi->GravityForce = FVector::ZERO;
				Yoshi->HeadCollision->SetActive(true);
				FSM.ChangeState(EPlayerState::STAYUP);
				return;
			}

			// Stick
			if (IsDown('X') && !Yoshi->IsHold)
			{
				if (IsPress(VK_UP))
				{
					Yoshi->StickDir = 1;
				}
				else
				{
					Yoshi->StickDir = 2;
				}
				FSM.ChangeState(EPlayerState::STICK);
				return;
			}

			if (IsDown('Z'))
			{
				// Aim
				if (!Yoshi->IsAim)
				{
					Yoshi->IsAim = true;
					FSM.ChangeState(EPlayerState::IDLE);
					return;
				}
				else  // Throw
				{
					Yoshi->IsAim = false;
					FSM.ChangeState(EPlayerState::THROW);
					return;
				}
			}

			// Idle
			if (!Yoshi->CheckForceColor(Yoshi->GravityForce * _DeltaTime, UColor::BLACK))
			{
				FSM.ChangeState(EPlayerState::IDLE);
				return;
			}

			if (Yoshi->ScaleCollisionType != 2 && IsPress(VK_LEFT) && !Yoshi->CheckLineColor(ECheckDir::LEFT, UColor::WHITE)
				&& !Yoshi->CheckLineColor(ECheckDir::LEFT, UColor::MAGENTA) && !Yoshi->CheckLineColor(ECheckDir::LEFT, UColor::GREEN))
			{
				Yoshi->AddActorLocation(FVector::LEFT * Yoshi->Speed * _DeltaTime);
			}
			if (Yoshi->ScaleCollisionType != 1 && IsPress(VK_RIGHT) && !Yoshi->CheckLineColor(ECheckDir::RIGHT, UColor::WHITE)
				&& !Yoshi->CheckLineColor(ECheckDir::RIGHT, UColor::MAGENTA) && !Yoshi->CheckLineColor(ECheckDir::RIGHT, UColor::GREEN))
			{
				Yoshi->AddActorLocation(FVector::RIGHT * Yoshi->Speed * _DeltaTime);
			}
		},
		[this]()
		{
			Yoshi->CurState = EPlayerState::FALL;

			if (Yoshi->IsWithBaby)	// M
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MNH_AimIdle");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MNH_Fall");
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MH_AimIdle");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MH_Fall");
				}
			}
			else   // Y
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YNH_AimIdle");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YNH_Fall");
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YH_AimIdle");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YH_Fall");
				}
			}
		}
	);

	FSM.CreateState(EPlayerState::STAYUP,
		[this](float _DeltaTime)
		{
			// Fall
			if (!IsPress(VK_LCONTROL))
			{
				Yoshi->IsStayUp = false;
				Yoshi->HeadCollision->SetActive(false);
				FSM.ChangeState(EPlayerState::FALL);
				return;
			}

			// Idle
			if (!Yoshi->CheckForceColor(Yoshi->GravityForce * _DeltaTime, UColor::BLACK))
			{
				Yoshi->IsStayUp = false;
				Yoshi->HeadCollision->SetActive(false);
				FSM.ChangeState(EPlayerState::IDLE);
				return;
			}

			// StayUp
			Yoshi->AddActorLocation(FVector::UP * Yoshi->JumpPower * 0.7f * _DeltaTime);

			if (IsPress(VK_LEFT) && !Yoshi->CheckLineColor(ECheckDir::LEFT, UColor::WHITE)
				&& !Yoshi->CheckLineColor(ECheckDir::LEFT, UColor::MAGENTA) && !Yoshi->CheckLineColor(ECheckDir::LEFT, UColor::GREEN))
			{
				Yoshi->AddActorLocation(FVector::LEFT * Yoshi->Speed * 0.6f * _DeltaTime);
			}
			if (IsPress(VK_RIGHT) && !Yoshi->CheckLineColor(ECheckDir::RIGHT, UColor::WHITE)
				&& !Yoshi->CheckLineColor(ECheckDir::RIGHT, UColor::MAGENTA) && !Yoshi->CheckLineColor(ECheckDir::RIGHT, UColor::GREEN))
			{
				Yoshi->AddActorLocation(FVector::RIGHT * Yoshi->Speed * 0.6f * _DeltaTime);
			}

		},
		[this]()
		{
			Yoshi->CurState = EPlayerState::STAYUP;

			if (Yoshi->IsWithBaby)	// M
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MNH_AimStayUp");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MNH_StayUp");
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MH_AimStayUp");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MH_StayUp");
				}
			}
			else   // Y
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YNH_AimStayUp");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YNH_StayUp");
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YH_AimStayUp");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YH_StayUp");
				}
			}
		}
	);

	FSM.CreateState(EPlayerState::LOOKUP,
		[this](float _DeltaTime)
		{
			// Stick
			if (IsDown('X') && !Yoshi->IsHold)
			{
				Yoshi->StickDir = 1;
				FSM.ChangeState(EPlayerState::STICK);
				return;
			}

			// Idle
			if (!IsPress(VK_UP))
			{
				if (Yoshi->IsWithBaby && !Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MNH_LookUpEnd");
				}
				else if (Yoshi->IsWithBaby && Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MH_LookUpEnd");
				}

				if (Yoshi->YoshiRenderer->IsCurAnimationEnd())
				{
					FSM.ChangeState(EPlayerState::IDLE);
					return;
				}
			}
		},
		[this]()
		{
			Yoshi->CurState = EPlayerState::LOOKUP;
			Yoshi->CameraNum = 1;

			if (Yoshi->IsWithBaby)	// M
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MNH_AimIdle");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MNH_LookUpStart");
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("MH_AimIdle");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("MH_LookUpStart");
				}
			}
			else   // Y
			{
				if (!Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YNH_AimIdle");
				}
				else if (!Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YNH_LookUpStart");
				}
				else if (Yoshi->IsHold && Yoshi->IsAim)
				{
					ChangeAnimation("YH_AimIdle");
				}
				else if (Yoshi->IsHold && !Yoshi->IsAim)
				{
					ChangeAnimation("YH_LookUpStart");
				}
			}
		}
	);

	FSM.CreateState(EPlayerState::BEND,
		[this](float _DeltaTime)
		{
			// Stick
			if (IsDown('X') && !Yoshi->IsHold)
			{
				Yoshi->StickDir = 2;
				FSM.ChangeState(EPlayerState::STICK);
				return;
			}

			// Idle
			if (!IsPress(VK_DOWN))
			{
				if (Yoshi->IsWithBaby)	// M
				{
					if (!Yoshi->IsHold && !Yoshi->IsAim)
					{
						ChangeAnimation("MNH_BendEnd");
					}
					else if (Yoshi->IsHold && !Yoshi->IsAim)
					{
						ChangeAnimation("MH_BendEnd");
					}
				}
				else   // Y
				{
					if (!Yoshi->IsHold && !Yoshi->IsAim)
					{
						ChangeAnimation("YNH_BendEnd");
					}
					else if (Yoshi->IsHold && !Yoshi->IsAim)
					{
						ChangeAnimation("YH_BendEnd");
					}
				}

				if (Yoshi->YoshiRenderer->IsCurAnimationEnd())
				{
					FSM.ChangeState(EPlayerState::IDLE);
					return;
				}
			}

			// Bend
			if (Yoshi->IsAim) 
			{ 
				Yoshi->IsAim = false;
				SoundPlayer.Off();
			}
		},
		[this]()
		{
			Yoshi->CurState = EPlayerState::BEND;
			Yoshi->CameraNum = 2;

			if (Yoshi->IsWithBaby)	// M
			{
				if ((!Yoshi->IsHold && Yoshi->IsAim) || (!Yoshi->IsHold && !Yoshi->IsAim))
				{
					ChangeAnimation("MNH_BendStart");
				}
				else if ((Yoshi->IsHold && Yoshi->IsAim) || (Yoshi->IsHold && !Yoshi->IsAim))
				{
					ChangeAnimation("MH_BendStart");
				}
			}
			else   // Y
			{
				if ((!Yoshi->IsHold && Yoshi->IsAim) || (!Yoshi->IsHold && !Yoshi->IsAim))
				{
					ChangeAnimation("YNH_BendStart");
				}
				else if ((Yoshi->IsHold && Yoshi->IsAim) || (Yoshi->IsHold && !Yoshi->IsAim))
				{
					ChangeAnimation("YH_BendStart");
				}
			}
		}
	);

	FSM.CreateState(EPlayerState::STICK,
		[this](float _DeltaTime)
		{
			// Animation
			// Collision Check
			Yoshi->CurState = EPlayerState::STICK;
			Yoshi->SetStickCollision();

			if (Yoshi->StickDir == 1 && Yoshi->YoshiRenderer->IsCurAnimationEnd())
			{
				ChangeAnimation("MNH_Stick_UpEnd");

				if (Yoshi->YoshiRenderer->IsCurAnimationEnd())
				{
					Yoshi->FootCollision->SetActive(true);
					Yoshi->StickCollision->SetActive(false);

					Yoshi->StickDir = 0;
					FSM.ChangeState(EPlayerState::IDLE);
					return;
				}
			}
			else if (Yoshi->StickDir == 2 && Yoshi->YoshiRenderer->IsCurAnimationEnd())
			{
				ChangeAnimation("MNH_Stick_RightEnd");

				if (Yoshi->YoshiRenderer->IsCurAnimationEnd())
				{
					Yoshi->BodyCollision->SetActive(true);
					Yoshi->FootCollision->SetActive(true);

					Yoshi->StickBodyCollision->SetActive(false);
					Yoshi->StickCollision->SetActive(false);

					Yoshi->StickDir = 0;
					FSM.ChangeState(EPlayerState::IDLE);
					return;
				}
			}

			// DeAccel
			if ((Yoshi->DirForce.X < 0.0f && !Yoshi->CheckPointColor(ECheckDir::LEFT, UColor::WHITE) &&
				!Yoshi->CheckPointColor(ECheckDir::LEFT, UColor::MAGENTA) && !Yoshi->CheckPointColor(ECheckDir::LEFT, UColor::GREEN))
				|| (Yoshi->DirForce.X > 0.0f && !Yoshi->CheckPointColor(ECheckDir::RIGHT, UColor::WHITE) &&
					!Yoshi->CheckPointColor(ECheckDir::RIGHT, UColor::MAGENTA) && !Yoshi->CheckPointColor(ECheckDir::RIGHT, UColor::GREEN)))
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
		},
		[this]()
		{
			SoundPlayer = UEngineSound::Play("Slurp.wav");

			if (Yoshi->StickDir == 1)
			{
				Yoshi->HeadCollision->SetActive(false);
				Yoshi->FootCollision->SetActive(false);
				Yoshi->StickCollision->SetActive(true);

				if ((Yoshi->IsWithBaby) && (!Yoshi->IsHold && !Yoshi->IsAim))	// M
				{
					ChangeAnimation("MNH_Stick_UpStart");
				}
				else if ((!Yoshi->IsWithBaby) && (!Yoshi->IsHold && !Yoshi->IsAim)) // Y
				{
					ChangeAnimation("YNH_Stick_UpStart");
				}
			}
			else if (Yoshi->StickDir == 2)
			{
				Yoshi->HeadCollision->SetActive(false);
				Yoshi->BodyCollision->SetActive(false);
				Yoshi->FootCollision->SetActive(false);

				Yoshi->StickBodyCollision->SetActive(true);
				Yoshi->StickCollision->SetActive(true);

				if ((Yoshi->IsWithBaby) && (!Yoshi->IsHold && !Yoshi->IsAim))	// M
				{
					ChangeAnimation("MNH_Stick_RightStart");
				}
				else if ((!Yoshi->IsWithBaby) && (!Yoshi->IsHold && !Yoshi->IsAim)) // Y
				{
					ChangeAnimation("YNH_Stick_RightStart");
				}
			}
		}
	);

	FSM.CreateState(EPlayerState::EAT,
		[this](float _DeltaTime)
		{
			if (Yoshi->YoshiRenderer->IsCurAnimationEnd())
			{
				Yoshi->IsAim = false;
				Yoshi->IsHold = false;
				SoundPlayer = UEngineSound::Play("CreateEgg.wav");

				if (Yoshi->GetGameInstance<AYoshiGameInstance>()->EggCount < 6)
				{
					Yoshi->GetGameInstance<AYoshiGameInstance>()->EggCount += 1;
				}

				FSM.ChangeState(EPlayerState::IDLE);
				return;
			}
		},
		[this]()
		{
			SoundPlayer = UEngineSound::Play("Eat.wav");

			if (Yoshi->IsWithBaby)	// M
			{
				if ((Yoshi->IsHold && Yoshi->IsAim) || (Yoshi->IsHold && !Yoshi->IsAim))
				{
					ChangeAnimation("MH_Eat");
				}
			}
			else   // Y
			{
				if ((Yoshi->IsHold && Yoshi->IsAim) || (Yoshi->IsHold && !Yoshi->IsAim))
				{
					ChangeAnimation("YH_Eat");
				}
			}
		});

	FSM.CreateState(EPlayerState::THROW,
		[this](float _DeltaTime)
		{
			if (Yoshi->YoshiRenderer->IsCurAnimationEnd())
			{
				FSM.ChangeState(EPlayerState::IDLE);
				return;
			}
		},
		[this]()
		{
			Yoshi->IsAim = false;
			SoundPlayer = UEngineSound::Play("Throw.wav");
			Yoshi->GetGameInstance<AYoshiGameInstance>()->EggCount -= 1;
			Yoshi->SpawnThrowEgg();

			if (Yoshi->IsWithBaby)	// M
			{
				if (!Yoshi->IsHold)
				{
					ChangeAnimation("MNH_Throw");
				}
				else
				{
					ChangeAnimation("MH_Throw");
				}
			}
			else   // Y
			{
				if (!Yoshi->IsHold)
				{
					ChangeAnimation("YNH_Throw");
				}
				else
				{
					ChangeAnimation("YH_Throw");
				}
			}
		});

	FSM.CreateState(EPlayerState::HURT,
		[this](float _DeltaTime)
		{
			Yoshi->AddActorLocation({ FVector::UP * Yoshi->JumpPower * 0.7f * _DeltaTime });
			if (!Yoshi->IsDefence)
			{
				FSM.ChangeState(EPlayerState::IDLE);
				return;
			}
		},
		[this]()
		{
			SoundPlayer = UEngineSound::Play("Whsiup.wav");

			if (Yoshi->IsWithBaby)
			{
				ChangeAnimation("MNH_Hurt");
			}
			else
			{
				if (Yoshi->IsHold)
				{
					ChangeAnimation("YH_Hurt");
				}
				else
				{
					ChangeAnimation("YNH_Hurt");
				}
			}

			if (Yoshi->IsWithBaby)
			{
				Yoshi->IsWithBaby = false;
				Yoshi->SpawnMarioBubble();
				Yoshi->BodyCollision->SetActive(false);
				Yoshi->FootCollision->SetActive(false);
			}
			Yoshi->TimeEvent->AddEvent(0.4f, nullptr, std::bind(&YoshiState::ChangeDefence, this), false);
		});

	FSM.ChangeState(EPlayerState::IDLE);
}