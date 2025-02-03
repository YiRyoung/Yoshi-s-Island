#pragma once
#include <EnginePlatform/EngineWinImage.h>
#include <EnginePlatform/EngineSound.h>

#include <EngineCore/Pawn.h>
#include <EngineCore/CameraActor.h>

#include "ContentsEnum.h"
#include "YoshiState.h"

// Ό³Έν :
class AYoshi : public APawn
{
	friend class YoshiState;

public:
	// constrcuter destructer
	AYoshi();
	~AYoshi();

	// delete Function
	AYoshi(const AYoshi& _Other) = delete;
	AYoshi(AYoshi&& _Other) noexcept = delete;
	AYoshi& operator=(const AYoshi& _Other) = delete;
	AYoshi& operator=(AYoshi&& _Other) noexcept = delete;

	// Pixel Collision (Ground)
	void SetColImage(UEngineWinImage* _Image)
	{
		ColImage = _Image;
	}

	UColor GetColor(FVector _Pos)
	{
		_Pos.Y = -_Pos.Y;
		return ColImage->GetColor(_Pos);
	}

	// Camera Limit
	void CameraBoundary(FVector _StageScale);

	// FSM
	void ChangeState(EPlayerState _NextState)
	{
		State->ChangeFSM(_NextState);
	}

	// Egg
	void SetEggCount(int _Value)
	{
		EggCount = _Value;
	}

	// Platform
	class APlatforms* GetPlatform() const
	{
		return Platform;
	}
	
	void SetPlatform(class APlatforms* _Platform)
	{
		Platform = _Platform;
	}

	FVector GetPlatformPos() const
	{
		return PlatformPos;
	}

	void ResetGravityForce()
	{
		GravityForce = FVector::ZERO;
	}

	// JumpBall
	void SetJumpBallType(int _TypeIndex)
	{
		JumpBallType = _TypeIndex;
	}

	void SetJumpPower(float _Value)
	{
		JumpPower = _Value;
	}

#pragma region Debug Funcs
	UEngineWinImage* GetColImage() const
	{
		return ColImage;
	}

	EPlayerState GetCurState() const
	{
		return CurState;
	}

	bool GetIsWithBaby() const
	{
		return IsWithBaby;
	}

	void SwitchIsWithBaby()
	{
		IsWithBaby = !IsWithBaby;
		ChangeState(EPlayerState::IDLE);
		return;
	}

	bool GetIsAim() const
	{
		return IsAim;
	}

	void SwitchIsAim()
	{
		IsAim = !IsAim;
		ChangeState(EPlayerState::IDLE);
		return;
	}

	bool GetIsHold() const
	{
		return IsHold;
	}

	void SwitchIsHold()
	{
		IsHold = !IsHold;
		ChangeState(EPlayerState::IDLE);
		return;
	}
#pragma endregion


protected:
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

private:
	UEngineWinImage* ColImage;
	USoundPlayer SoundPlayer;

	class YoshiState* State = nullptr;

	std::shared_ptr<class ACameraActor> Camera;
	std::shared_ptr<class USpriteRenderer> YoshiRenderer;
	std::shared_ptr<class ACrossHair> CrossHair;

	// Init
	void YoshiInit();

	// Camera
	int CameraNum = -1;
	float MaxCameraPivotY = 100.0f;
	float MinCameraPivotY = 0.0f;
	FVector CameraPivot = FVector::ZERO;

	void MoveCamera( float _DeltaTime);

	// Animation
	bool IsHolding = false;
	bool IsWithBaby = true;
	bool IsAim = false;
	bool IsHold = false;
	FVector YoshiScale = FVector::ZERO;

	void SetAnimation();
	void SetAnimDir();

	int IdleAnimNum();
	void PlayIdleAnim();

	// Collision
	std::shared_ptr<class UCollision> HeadCollision;
	std::shared_ptr<class UCollision> BodyCollision;
	std::shared_ptr<class UCollision> FootCollision;

	std::shared_ptr<class UCollision> StickBodyCollision;
	std::shared_ptr<class UCollision> StickCollision;

	void SetCollision();
	void SetStickCollision();
	
	bool CheckPointColor(ECheckDir _Dir, UColor _Color);
	bool CheckLineColor(ECheckDir _Dir, UColor _Color);
	bool CheckForceColor(FVector _Force, UColor _Color);

	bool IsSlope();
	void MoveSlope(float _DeltaTime);

	void SetCollisionsCheck();

	// CrossHair
	void SetCrossHair();

	// ThrowEgg
	void SpawnThrowEgg();

	// Platform
	class APlatforms* Platform = nullptr;
	FVector PlatformPos = FVector::ZERO;

	// JumpBall
	int JumpBallType = -1;
	
	// Status
	int StickDir = 0;
	int EggCount = 0;
	EPlayerState CurState = EPlayerState::IDLE;

	// Speed
	bool IsAccel = false;
	float Speed = 380.0f;
	float AccSpeed = 400.0f;
	float DeAccSpeed = 20.0f;
	float MaxSpeed = 450.0f;
	FVector DirForce = { 0, 0, 0 };

	// Jump & Gravity
	bool IsStayUp = false;
	float JumpPower = 550.0f;
	float GravityPower = 800.0f;
	FVector GravityForce = { 0, 0, 0 };

};