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
		return CheckPos;
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
	FVector CheckPos = { 0, 0, 0 };
	UColor Color = { 255, 255, 255, 255 };
	float Speed = 10.0f;

	void PlayerFSM(float _DeltaTime);

	void IdleStart(float _DeltaTime);
	void Idle(float _DeltaTime);
	void MoveStart(float _DeltaTime);
	void Move(float _DeltaTime);

	void SetCheckPos();
};

