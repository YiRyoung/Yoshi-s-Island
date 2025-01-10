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

	void SetColImage(UEngineWinImage* _ColImage)
	{
		ColImage = _ColImage;
	}

protected:
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

#pragma region Status
	//Engine
	std::shared_ptr<class USpriteRenderer> YoshiRenderer;
	UEngineWinImage* ColImage;
	EDirection Dir = EDirection::MAX;
	EPlayerState State = EPlayerState::MAX;
	
	// GameManager
	bool IsWithBaby = true;

	// Speed
	bool IsAccel = false;
	float Speed = 300.0f;
	float AccSpeed = 380.0f;
	float DeAccSpeed = 10.0f;
	float MaxSpeed = 420.0f;
	FVector DirForce = { 0, 0, 0 };

	// Jump & Gravity
	float JumpPower = 420.0f;
	float GravityPower = 450.0f;
	FVector GravityForce = { 0, 0, 0 };
#pragma endregion

private:
	bool IsGround();
	void SetAnimations();
	void SetDirection();

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
	void JumpEnd(float _DeltaTime);
};

