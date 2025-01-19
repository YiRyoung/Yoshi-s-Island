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

	std::shared_ptr<ACameraActor> GetMainCamera() const
	{
		return Camera;
	}

	void SetColImage(UEngineWinImage* _ColImage)
	{
		ColImage = _ColImage;
	}

	void SetCamera(std::shared_ptr<ACameraActor> _Camera)
	{
		Camera = _Camera;
	}

	// Wrapping
	void Move(float _X, float _Y)
	{
		AddActorLocation({ _X, _Y, 0.0f });
	};

	void Move(FVector _Pos)
	{
		AddActorLocation(_Pos);
	}

#pragma region State
	std::shared_ptr<class USpriteRenderer> GetYoshiRenderer() const
	{
		return YoshiRenderer;
	}

	EPlayerState GetCurState() const
	{
		return CurState;
	}

	float GetSpeed() const
	{
		return Speed;
	}

	void SetIdleAnim();

	void SetCurState(EPlayerState _NextState)
	{
		CurState = _NextState;
	}

#pragma endregion

#pragma region Collision
	UColor GetColor(FVector _Pos)
	{
		_Pos.Y = -_Pos.Y;
		return ColImage->GetColor(_Pos);
	}

	FVector GetScale() const
	{
		return Scale;
	}

	float GetJumpPower() const
	{
		return JumpPower;
	}

	float GetGravityPower() const
	{
		return GravityPower;
	}

	FVector GetGravityForce() const
	{
		return GravityForce;
	}

	void AddGravityForce(FVector _Power)
	{
		GravityForce += _Power;
	}

	void SetGravityForce(FVector _NewForce)
	{
		GravityForce = _NewForce;
	}
#pragma endregion

protected:
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
private:
	UEngineWinImage* ColImage;
	YoshiCollision* Collision;
	YoshiState* State;

	std::shared_ptr<class USpriteRenderer> YoshiRenderer;
	
	std::shared_ptr<class UCollision> BodyCollision;

	std::shared_ptr<ACameraActor> Camera;
	EPlayerState CurState = EPlayerState::MAX;

	// GameManager
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

