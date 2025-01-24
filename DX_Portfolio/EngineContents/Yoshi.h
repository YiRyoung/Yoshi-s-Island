#pragma once
#include <EnginePlatform/EngineWinImage.h>
#include <EnginePlatform/EngineSound.h>

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

	void SetColImage(UEngineWinImage* _ColImage)
	{
		ColImage = _ColImage;
	}

	UColor GetColor(FVector _Pos)
	{
		_Pos.Y = -_Pos.Y;
		return ColImage->GetColor(_Pos);
	}

	FVector GetCameraPivot() const
	{
		return CameraPivot;
	}

	void ResetGraviryForce()
	{
		GravityForce = FVector::ZERO;
	}

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

	void SetPlatformPos(FVector _Value)
	{
		PlatformPos = _Value;
	}

	EPlayerState GetCurState() const
	{
		return CurState;
	}

	void ChangetState(EPlayerState _NextState)
	{
		CurState = _NextState;
		return;
	}

protected:
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

private:
	USoundPlayer SoundPlayer;

	UEngineWinImage* ColImage;
	YoshiCollision* Collision;
	YoshiState* State;

	std::shared_ptr<class USpriteRenderer> YoshiRenderer;
	
	std::shared_ptr<class UCollision> HeadCollision;
	std::shared_ptr<class UCollision> BodyCollision;
	std::shared_ptr<class UCollision> FootCollision;

	std::shared_ptr<ACameraActor> Camera;

	std::shared_ptr<class ACrossHair> CrossHair;

	FVector CameraPivot = FVector::ZERO;
	EPlayerState CurState = EPlayerState::IDLE;

	// Platforms
	class APlatforms* Platform = nullptr;
	FVector PlatformPos = FVector::ZERO;

	// GameManager
	int CameraNum = -1; 
	bool IsWithBaby = true;
	bool IsAim = false;
	bool IsHold = false;
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

	// Camera
	void MoveCamera(int _IsUP, float _DeltaTime);
	float MaxCameraPivotY = 100.0f;
	float MinCameraPivotY = 0.0f;

	// Animation
	void SetAnimations();
	void SetAnimDir();

	int SetIdleAnimNum();
	void PlayIdleAnim(bool _IsStart);

	// Collision
	void SetCollision();
	void SetDebugCollision();

	// Sound
	void Play(std::string_view _Name);

	// CrossHair
	void SetCrossHair();

#pragma region Debug
	std::shared_ptr<class UCollision> DebugDownCollision;
	std::shared_ptr<class UCollision> DebugLeftCollision;
	std::shared_ptr<class UCollision> DebugRightCollision;
	std::shared_ptr<class UCollision> DebugUpCollision;
#pragma endregion

};