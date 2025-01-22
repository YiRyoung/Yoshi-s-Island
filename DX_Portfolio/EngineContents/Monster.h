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
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	void ChangeState(EMonsterState _CurMonsterState);

	EColorType MonsterColor = EColorType::NONE;
	EMonsterState CurMonsterState = EMonsterState::IDLE;
	FVector MonsterScale = FVector::ZERO;

	void MosnterFSM(float _DeltaTime);
	void Gravity(float _DeltaTime);

	virtual void IdleStart();
	virtual void Idle(float _DeltaTime);
	virtual void WalkStart();
	virtual void Walk(float _DeltaTime);
	virtual void AttackStart();
	virtual void Attack(float _DeltaTime);
	virtual void HurtStart();
	virtual void Hurt(float _DeltaTime);

private:

};

