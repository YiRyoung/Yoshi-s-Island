#pragma once
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/Pawn.h>
#include <EngineCore/CameraActor.h>

#include "ContentsEnum.h"
#include "YoshiCollision.h"
#include "YoshiState.h"

// Ό³Έν :
class AYoshi : public APawn
{
	friend class YoshiState;
	friend class YoshiCollision;

public:
	// constrcuter destructer
	AYoshi();
	~AYoshi();

	// delete Function
	AYoshi(const AYoshi& _Other) = delete;
	AYoshi(AYoshi&& _Other) noexcept = delete;
	AYoshi& operator=(const AYoshi& _Other) = delete;
	AYoshi& operator=(AYoshi&& _Other) noexcept = delete;

	YoshiCollision* GetCollision() const
	{
		return Collision;
	}

	YoshiState* GetState() const
	{
		return State;
	}

	void SetColImage(UEngineWinImage* _ColImage)
	{
		ColImage = _ColImage;
	}

	FVector GetCameraPivot() const
	{
		return CameraPivot;
	}

	UColor GetColor(FVector _Pos)
	{
		_Pos.Y = -_Pos.Y;
		return ColImage->GetColor(_Pos);
	}

protected:
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
private:
	UEngineWinImage* ColImage;
	YoshiCollision* Collision;
	YoshiState* State;

	std::shared_ptr<class USpriteRenderer> YoshiRenderer;
	
	std::shared_ptr<class UCollision> HeadCollision;
	std::shared_ptr<class UCollision> BodyCollision;
	std::shared_ptr<class UCollision> FootCollision;

	std::shared_ptr<ACameraActor> Camera;

	FVector CameraPivot = FVector::ZERO;
	EPlayerState CurState = EPlayerState::IDLE;

	// GameManager
	bool IsCameraMove = false;
	bool IsWithBaby = true;
	FVector Scale = FVector::ZERO;

	// Speed
	bool IsAccel = false;
	float Speed = 340.0f;
	float AccSpeed = 420.0f;
	float DeAccSpeed = 10.0f;
	float MaxSpeed = 480.0f;
	FVector DirForce = { 0, 0, 0 };

	// Jump & Gravity
	float JumpPower = 550.0f;
	float GravityPower = 800.0f;
	FVector GravityForce = { 0, 0, 0 };

	// Animation
	void SetAnimations();
	void SetAnimDir();

	int SetIdleAnimNum();
	void PlayIdleAnim(bool _IsStart);

	// Collision
	void SetCollision();
	void SetDebugCollision();

#pragma region Debug
	std::shared_ptr<class UCollision> DebugDownCollision;
	std::shared_ptr<class UCollision> DebugLeftCollision;
	std::shared_ptr<class UCollision> DebugRightCollision;
	std::shared_ptr<class UCollision> DebugUpCollision;
#pragma endregion

};