#pragma once
#include <EngineCore/Actor.h>

#include "ContentsEnum.h"

// Ό³Έν :
class AMonster : public AActor
{
public:
	// constrcuter destructer
	AMonster();
	~AMonster();

	// delete Function
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	
	std::shared_ptr<class UTimeEventComponent> TimeEvent;
	FVector MonsterScale = FVector::ZERO;

	bool CheckPointColor(ECheckDir _CheckDir, UColor _Color);
	bool CheckForceColor(FVector _Force, UColor _Color);

	bool IsStepped = false;
	void Gravity(float _DeltaTime);
	void MoveSlope(float _DeltaTime);
	void FallDown(float _DeltaTime);
	void Off();

private:
	float GravityPower = 800.0f;
	FVector GravityForce = { 0, 0, 0 };
};

