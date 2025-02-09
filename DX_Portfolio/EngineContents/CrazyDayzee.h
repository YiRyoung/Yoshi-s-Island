#pragma once
#include "Monster.h"

#include <EngineBase/FSMStateManager.h>

#include <EnginePlatform/EngineSound.h>

#include "ContentsEnum.h"

// Ό³Έν :
class ACrazyDayzee : public AMonster
{
public:
	// constrcuter destructer
	ACrazyDayzee();
	~ACrazyDayzee();

	// delete Function
	ACrazyDayzee(const ACrazyDayzee& _Other) = delete;
	ACrazyDayzee(ACrazyDayzee&& _Other) noexcept = delete;
	ACrazyDayzee& operator=(const ACrazyDayzee& _Other) = delete;
	ACrazyDayzee& operator=(ACrazyDayzee&& _Other) noexcept = delete;

protected:
	void Tick(float _DeltaTime) override;

private:
	USoundPlayer SoundPlayer;

	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> HeadCollision;
	std::shared_ptr<class UCollision> BodyCollision;
	
	UFSMStateManager MonsterFSM;
	EMonsterState CurState = EMonsterState::IDLE;

	void UpdateMonsterFSM(float _DeltaTime)
	{
		MonsterFSM.Update(_DeltaTime);
	}

	void CreateMonsterFSM();

	void Init();
	void SetAnimation();
	void SetCollision();
	void SetCollisionLink(float _DeltaTime);
};

