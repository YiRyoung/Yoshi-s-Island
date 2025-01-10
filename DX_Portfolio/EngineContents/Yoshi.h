#pragma once
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/Actor.h>

#include "ContentsEnum.h"

// Ό³Έν :
class AYoshi : public APawn
{
public:
	// constrcuter destructer
	AYoshi();
	~AYoshi();

	// delete Function
	AYoshi(const AYoshi& _Other) = delete;
	AYoshi(AYoshi&& _Other) noexcept = delete;
	AYoshi& operator=(const AYoshi& _Other) = delete;
	AYoshi& operator=(AYoshi&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetYoshiRenderer() const
	{
		return YoshiRenderer;
	}

	FVector GetCheckPos() const
	{
		return NextPos;
	}

	void SetColor(UColor _Color)
	{
		Color = _Color;
	}
		

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> YoshiRenderer;
	EDirection Dir = EDirection::MAX;
	EPlayerState State = EPlayerState::MAX;
	FVector NextPos = { 0, 0, 0 };
	UColor Color = { 255, 255, 255, 255 };
	float Speed = 300.0f;

	void SetAnimations();
	void SetDirection();

	void SetNextPos(float _DeltaTime);

	void PlayerFSM(float _DeltaTime);
	void Gravity(float _DeltaTime);

	int CurIdleAnim();
	void IdleStart(float _DeltaTime);
	void Idle(float _DeltaTime);
	void LookUpStart(float _DeltaTime);
	void LookUpEnd(float _DeltaTime);
	void BendStart(float _DeltaTime);
	void BendEnd(float _DeltaTime);
	void MoveStart(float _DeltaTime);
	void Move(float _DeltaTime);
	void JumpStart(float _DeltaTime);
	void Jump(float _DeltaTime);
};

