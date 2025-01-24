#include "PreCompile.h"
#include "YoshiCollision.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "Yoshi.h"
#include "Platforms.h"

YoshiCollision::YoshiCollision() {}

YoshiCollision::YoshiCollision(AYoshi* _Yoshi) : Yoshi(_Yoshi) {}

YoshiCollision::~YoshiCollision() {}

bool YoshiCollision::CheckPointColor(ECheckDir _Dir, UColor _Color)
{
	FVector NextPos = FVector::ZERO;
	FVector Scale = Yoshi->YoshiRenderer->GetTransformRef().Scale;
	UColor Color = UColor::WHITE;

	switch (_Dir)
	{
	case ECheckDir::LEFT:
		NextPos = Yoshi->GetActorLocation() + FVector::LEFT + FVector{ -Scale.X * 0.5f, 0.0f };
		Color = Yoshi->GetColor(NextPos);
		break;
	case ECheckDir::RIGHT:
		NextPos = Yoshi->GetActorLocation() + FVector::RIGHT + FVector{ Scale.X * 0.5f, 0.0f };
		Color = Yoshi->GetColor(NextPos);
		break;
	case ECheckDir::UP:
		NextPos = Yoshi->GetActorLocation() + FVector::UP + FVector{ 0.0f, Scale.Y * 1.0f };
		Color = Yoshi->GetColor(NextPos);
		break;
	case ECheckDir::DOWN:
		NextPos = Yoshi->GetActorLocation() + FVector::DOWN;
		Color = Yoshi->GetColor(NextPos);
		break;
	case ECheckDir::NONE:
		Color = Yoshi->GetColor(Yoshi->GetActorLocation());
		break;
	}

	bool Result = (_Color.operator==(Color)) ? true : false;
	return Result;
}

bool YoshiCollision::CheckLineColor(ECheckDir _Dir, UColor _Color)
{
	FVector NextStartPos = FVector::ZERO;
	FVector NextEndPos = FVector::ZERO;

	switch (_Dir)
	{
	case ECheckDir::LEFT:
		NextStartPos = Yoshi->GetActorLocation() + FVector{ Yoshi->Scale.X * -0.5f, Yoshi->Scale.Y };
		NextEndPos = Yoshi->GetActorLocation() + FVector{ Yoshi->Scale.X * -0.5f, 0.0f };

		for (int y = static_cast<int>(NextEndPos.Y); y <= static_cast<int>(NextStartPos.Y); y++)
		{
			UColor NextColor = Yoshi->GetColor({ NextStartPos.X, static_cast<float>(y) });
			if (NextColor.operator==(_Color))
			{
				return true;
			}
		}
		break;

	case ECheckDir::RIGHT:
		NextStartPos = Yoshi->GetActorLocation() + FVector::RIGHT + FVector{ Yoshi->Scale.X * 0.5f, Yoshi->Scale.Y };
		NextEndPos = Yoshi->GetActorLocation() + FVector::RIGHT + FVector{ Yoshi->Scale.X * 0.5f, 0.0f };

		for (int y = static_cast<int>(NextEndPos.Y); y <= static_cast<int>(NextStartPos.Y); y++)
		{
			UColor NextColor = Yoshi->GetColor({ NextStartPos.X, static_cast<float>(y) });
			if (NextColor.operator==(_Color))
			{
				return true;
			}
		}
		break;

	case ECheckDir::UP:
		NextStartPos = Yoshi->GetActorLocation() + FVector::UP + FVector{ Yoshi->Scale.X * -0.5f, Yoshi->Scale.Y };
		NextEndPos = Yoshi->GetActorLocation() + FVector::UP + FVector{ Yoshi->Scale.X * 0.5f, Yoshi->Scale.Y };

		for (int x = static_cast<int>(NextStartPos.X); x <= static_cast<int>(NextEndPos.X); x++)
		{
			UColor NextColor = Yoshi->GetColor({ static_cast<float>(x), NextStartPos.Y });
			if (NextColor.operator==(_Color))
			{
				return true;
			}
		}
		break;

	case ECheckDir::DOWN:
		NextStartPos = Yoshi->GetActorLocation() + FVector::DOWN + FVector{ Yoshi->Scale.X * -0.5f, 0.0f };
		NextEndPos = Yoshi->GetActorLocation() + FVector::DOWN + FVector{ Yoshi->Scale.X * 0.5f, 0.0f };

		for (int x = static_cast<int>(NextStartPos.X); x <= static_cast<int>(NextEndPos.X); x++)
		{
			UColor NextColor = Yoshi->GetColor({ static_cast<float>(x), NextStartPos.Y });
			if (NextColor.operator==(_Color))
			{
				return true;
			}
		}
		break;

	case ECheckDir::NONE:
		NextStartPos = Yoshi->GetActorLocation();
		NextEndPos = Yoshi->GetActorLocation() + FVector{ 0.0f, Yoshi->Scale.Y * 0.5f };

		for (int y = static_cast<int>(NextStartPos.Y); y <= static_cast<int>(NextEndPos.Y); y++)
		{
			UColor NextColor = Yoshi->GetColor({ NextStartPos.X, static_cast<float>(y) });
			if (NextColor.operator==(_Color))
			{
				return true;
			}
		}
		break;
	}

	return false;
}

bool YoshiCollision::CheckForceColor(FVector _Force, UColor _Color)
{
	FVector NextPos = Yoshi->GetActorLocation() + _Force;
	UColor Color = Yoshi->GetColor(NextPos);

	if (Color.operator==(_Color))
	{
		return true;
	}

	return false;
}

bool YoshiCollision::IsScreen(ECheckDir _Dir)
{
	if (CheckPointColor(_Dir, UColor::WHITE))
	{
		return false;
	}
	return true;
}

bool YoshiCollision::IsGround()
{
	if (CheckLineColor(ECheckDir::DOWN, UColor::BLACK))
	{
		return false;
	}
	return true;
}

bool YoshiCollision::IsSlope()
{
	for (int i = 0; i < 50; i++)
	{
		FVector NextPos = Yoshi->GetActorLocation() + FVector{ 0.0f, static_cast<float>(-i) };
		UColor Color = Yoshi->GetColor(NextPos);

		if (Color.operator==(UColor::MAGENTA) || Color.operator==(UColor::YELLOW) || Color.operator==(UColor::GREEN))
		{
			return false;
		}
		if (Color.operator==(UColor::CYAN))
		{
			return true;
		}
	}
	return false;
}

void YoshiCollision::SetCollisionsCheck(float _DeltaTime)
{
	{
		std::vector<UCollision*> ColMonsters;
		if (Yoshi->FootCollision->CollisionCheck("MonsterHeadCollision", ColMonsters)
			&& Yoshi->CurState == EPlayerState::FALL)
		{
			ColMonsters[0]->GetActor()->Destroy();
		}

		if (Yoshi->BodyCollision->CollisionCheck("MonsterBodyCollision", ColMonsters))
		{
			Yoshi->YoshiRenderer->ChangeAnimation("AimIdle");
		}
	}

	{
		if (nullptr == Yoshi->Platform)
		{
			std::vector<UCollision*> Platforms;
			if (Yoshi->FootCollision->CollisionCheck("PlatformCollision", Platforms)
				&& Yoshi->CurState == EPlayerState::FALL)
			{
				Yoshi->Platform = Platforms[0]->GetActor<APlatforms>();
				Yoshi->PlatformPos = Yoshi->GetActorLocation() - Yoshi->Platform->GetActorLocation();
				Yoshi->CurState = EPlayerState::IDLE;
			}
		}
	}
}

void YoshiCollision::MoveSlopeUp(float _DeltaTime)
{
	if (IsSlope() && CheckLineColor(ECheckDir::NONE, UColor::CYAN))
	{
		Yoshi->AddActorLocation(FVector::UP * Yoshi->Speed * _DeltaTime);
	}
}