#include "PreCompile.h"
#include "YoshiCollision.h"

#include "Yoshi.h"

YoshiCollision::YoshiCollision() {}

YoshiCollision::YoshiCollision(AYoshi* _Yoshi) : Yoshi(_Yoshi) {}

YoshiCollision::~YoshiCollision() {}

bool YoshiCollision::CheckColor(ECheckDir _Dir, UColor _Color)
{
	FVector NextPos = FVector::ZERO;
	UColor Color = UColor::WHITE;

	switch (_Dir)
	{
	case ECheckDir::LEFT:
		NextPos = Yoshi->GetActorLocation() + FVector::LEFT;
		Color = Yoshi->GetColor(NextPos);
		break;
	case ECheckDir::RIGHT:
		NextPos = Yoshi->GetActorLocation() + FVector::RIGHT;
		Color = Yoshi->GetColor(NextPos);
		break;
	case ECheckDir::UP:
		NextPos = Yoshi->GetActorLocation() + FVector::UP;
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

bool YoshiCollision::IsAir()
{
	if (!CheckColor(ECheckDir::DOWN, UColor::MAGENTA) && !CheckColor(ECheckDir::DOWN, UColor::CYAN))
	{
		return true;
	}
	return false;
}

void YoshiCollision::GroundUp(float _DeltaTime)
{
	UColor Color = Yoshi->GetColor(Yoshi->GetActorLocation());
	if (Color.operator==(UColor::CYAN))
	{

		Yoshi->Move(0.0f, 300.0f * _DeltaTime);
	}
}


