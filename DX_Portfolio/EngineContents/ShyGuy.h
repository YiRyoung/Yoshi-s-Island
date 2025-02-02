#pragma once
#include "Monster.h"

#include <EngineBase/FSMStateManager.h>
#include "ContentsEnum.h"

// Ό³Έν :
class AShyGuy : public AMonster
{
public:
	// constrcuter destructer
	AShyGuy();
	~AShyGuy();

	// delete Function
	AShyGuy(const AShyGuy& _Other) = delete;
	AShyGuy(AShyGuy&& _Other) noexcept = delete;
	AShyGuy& operator=(const AShyGuy& _Other) = delete;
	AShyGuy& operator=(AShyGuy&& _Other) noexcept = delete;

	void SetType(EShyGuyTypes _Type)
	{
		CurType = _Type;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UFSMStateManager FSM;

	std::shared_ptr<class USpriteRenderer> ShyGuyRenderer;
	std::shared_ptr<class UCollision> ShyGuyHeadCollision;
	std::shared_ptr<class UCollision> ShyGuyBodyCollision;

	std::shared_ptr<class UTimeEventComponent> TimeEvent;

	EMonsterState CurMonsterState = EMonsterState::IDLE;
	EShyGuyTypes CurType = EShyGuyTypes::NONE;

	void Init(EShyGuyTypes _CurType);
	void SetAnimation();
	void SetCollision();
	void SetCheckCollision();
	void ChangeAnimDir();
	void CreateFSM();
};

