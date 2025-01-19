#include "PreCompile.h"
#include "YoshiCollision.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "Yoshi.h"

YoshiCollision::YoshiCollision() {}

YoshiCollision::YoshiCollision(AYoshi* _Yoshi) : Yoshi(_Yoshi) {}

YoshiCollision::~YoshiCollision() {}

FVector YoshiCollision::GetYoshiLocation()
{
    return Yoshi->GetActorLocation();
}

FVector YoshiCollision::GetYoshiScale()
{
    return Yoshi->GetScale();
}

UColor YoshiCollision::GetColor(FVector _Pos)
{
    return Yoshi->GetColor(_Pos);
}

bool YoshiCollision::CheckPointColor(ECheckDir _Dir, UColor _Color)
{
	FVector NextPos = FVector::ZERO;
	FVector Scale = Yoshi->GetYoshiRenderer()->GetTransformRef().Scale;
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
        NextStartPos = GetYoshiLocation() + FVector{ GetYoshiScale().X * -0.5f, GetYoshiScale().Y };
        NextEndPos = GetYoshiLocation() + FVector{ GetYoshiScale().X * -0.5f, 0.0f };

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
        NextStartPos = GetYoshiLocation() + FVector::RIGHT + FVector{ GetYoshiScale().X * 0.5f, GetYoshiScale().Y };
        NextEndPos = GetYoshiLocation() + FVector::RIGHT + FVector{ GetYoshiScale().X * 0.5f, 0.0f };

        for (int y = static_cast<int>(NextEndPos.Y); y <= static_cast<int>(NextStartPos.Y); y++)
        {
            UColor NextColor = GetColor({ NextStartPos.X, static_cast<float>(y) });
            if (NextColor.operator==(_Color))
            {
                return true;
            }
        }
        break;

    case ECheckDir::UP:
        NextStartPos = GetYoshiLocation() + FVector::UP + FVector{ GetYoshiScale().X * -0.5f, GetYoshiScale().Y };
        NextEndPos = GetYoshiLocation() + FVector::UP + FVector{ GetYoshiScale().X * 0.5f, GetYoshiScale().Y };

        for (int x = static_cast<int>(NextStartPos.X); x <= static_cast<int>(NextEndPos.X); x++)
        {
            UColor NextColor = GetColor({ static_cast<float>(x), NextStartPos.Y });
            if (NextColor.operator==(_Color))
            {
                return true;
            }
        }
        break;

    case ECheckDir::DOWN:
        NextStartPos = GetYoshiLocation() + FVector::DOWN + FVector{ GetYoshiScale().X * -0.5f, -3.0f };
        NextEndPos = GetYoshiLocation() + FVector::DOWN + FVector{ GetYoshiScale().X * 0.5f, -3.0f };

        for (int x = static_cast<int>(NextStartPos.X); x <= static_cast<int>(NextEndPos.X); x++)
        {
            UColor NextColor = GetColor({ static_cast<float>(x), NextStartPos.Y });
            if (NextColor.operator==(_Color))
            {
                return true;
            }
        }
        break;
    }

    return false;
}

bool YoshiCollision::IsHill()
{
    FVector NextPos = FVector::ZERO;
    FVector Scale = Yoshi->GetYoshiRenderer()->GetTransformRef().Scale;
    UColor Color = UColor::WHITE;;

    NextPos = Yoshi->GetActorLocation() + FVector::DOWN;

    for (int i = 0; i < 30; i++)
    {
        NextPos += FVector{ 0, i };
        Color = Yoshi->GetColor(NextPos);

        if (Color.operator==(UColor::CYAN))
        {
            return true;
        }
    }

    return false;
}

void YoshiCollision::GroundUp(float _DeltaTime)
{
	UColor Color = Yoshi->GetColor(Yoshi->GetActorLocation());
	if (Color.operator==(UColor::CYAN))
	{

		Yoshi->Move(0.0f, Yoshi->GetSpeed() * _DeltaTime);
	}
}