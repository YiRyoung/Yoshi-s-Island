#pragma once

#include "ContentsEnum.h"

// Ό³Έν :
class YoshiState
{
public:
	// constrcuter destructer
	YoshiState();
	YoshiState(class AYoshi* _Yoshi);
	~YoshiState();

	// delete Function
	YoshiState(const YoshiState& _Other) = delete;
	YoshiState(YoshiState&& _Other) noexcept = delete;
	YoshiState& operator=(const YoshiState& _Other) = delete;
	YoshiState& operator=(YoshiState&& _Other) noexcept = delete;

	// Wrapping Code
	bool IsPressKey(int _KeyCode);
	bool IsPressTime(int _KeyCode, float _Time);
	bool IsDownKey(int _KeyCode);
	bool IsUpKey(int _KeyCode);

	bool CheckPointColor(ECheckDir _Dir, UColor _Color);
	bool CheckLineColor(ECheckDir _Dir, UColor _Color);
	bool CheckForceColor(FVector _Force, UColor _Color);
	
	bool IsScreen(ECheckDir _Dir);
	bool IsGround();
	bool IsSlope();

	void ChangeAnimation(std::string_view _Name);
	void ChangeState(EPlayerState _NextState);

	void StateStart();
	void StateFunc(float _DeltaTime);

	void Gravity(float _DeltaTime, float _Scale = 1.0f);

	void WalkStart();
	void RunStart();
	void JumpStart();
	void StayUpStart();
	void FallStart();
	void LookUpStart();
	void BendStart();
	void StickStart();

	void Idle(float _DeltaTime);
	void Walk(float _DeltaTime);
	void Run(float _DeltaTime);
	void Jump(float _DeltaTime);
	void StayUp(float _DeltaTime);
	void Fall(float _DeltaTime);
	void LookUp(float _DeltaTime);
	void Bend(float _DeltaTime);
	void Stick(float _DeltaTime);

protected:

private:
	class AYoshi* Yoshi;
};

