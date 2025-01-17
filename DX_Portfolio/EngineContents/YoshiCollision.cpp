#include "PreCompile.h"
#include "YoshiCollision.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "Yoshi.h"

YoshiCollision::YoshiCollision() {}

YoshiCollision::YoshiCollision(AYoshi* _Yoshi) : Yoshi(_Yoshi) {}

YoshiCollision::~YoshiCollision() {}

bool YoshiCollision::CheckColor(ECheckDir _Dir, UColor _Color)
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
		NextPos = Yoshi->GetActorLocation() + FVector::DOWN + FVector{ 0.0f, Scale.Y * -0.5f };
		Color = Yoshi->GetColor(NextPos);
		break;
	}

	bool Result = (_Color.operator==(Color)) ? true : false;
	return Result;
}

void YoshiCollision::GroundUp(float _DeltaTime)
{
	UColor Color = Yoshi->GetColor(Yoshi->GetActorLocation());
	if (Color.operator==(UColor::CYAN))
	{

		Yoshi->Move(0.0f, 300.0f * _DeltaTime);
	}
}