#pragma once

#include "ContentsEnum.h"
// Ό³Έν :
class YoshiCollision
{
public:
	// constrcuter destructer
	YoshiCollision();
	YoshiCollision(class AYoshi* _Yoshi);
	~YoshiCollision();

	// delete Function
	YoshiCollision(const YoshiCollision& _Other) = delete;
	YoshiCollision(YoshiCollision&& _Other) noexcept = delete;
	YoshiCollision& operator=(const YoshiCollision& _Other) = delete;
	YoshiCollision& operator=(YoshiCollision&& _Other) noexcept = delete;

	bool CheckPointColor(ECheckDir _Dir, UColor _Color);
	bool CheckLineColor(ECheckDir _Dir, UColor _Color);
	bool CheckForceColor(FVector _Force, UColor _Color);

	bool IsScreen(ECheckDir _Dir);
	bool IsGround();
	bool IsSlope();

	void SetCollisionsCheck(float _DeltaTime);
	void MoveSlopeUp(float _DeltaTime);

protected:

private:
	class AYoshi* Yoshi;
};

