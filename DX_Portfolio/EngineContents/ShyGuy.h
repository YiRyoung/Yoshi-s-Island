#pragma once
#include "Monster.h"

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class UTimeEventComponent> TimeEvent;

	void SetCollision();
	void SetAnimation();

	void ChangeAnimDir();

	void IdleStart() override;
	void WalkStart() override;
	void Walk(float _DeltaTime);
};

