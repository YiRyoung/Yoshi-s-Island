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

	bool CheckColor(ECheckDir _Dir, UColor _Color);
	
	bool IsAir();

	void GroundUp(float _DeltaTime);

protected:

private:
	class AYoshi* Yoshi;
};

