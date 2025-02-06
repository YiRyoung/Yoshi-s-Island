#pragma once

#include <EngineBase/FSMStateManager.h>
#include <EngineCore/TimeEventComponent.h>
#include <EnginePlatform/EngineSound.h>

#include "ContentsEnum.h"

// Ό³Έν :
class YoshiState
{
public:
	// constrcuter destructer
	YoshiState() {}
	YoshiState(class AYoshi* _Yoshi) : Yoshi(_Yoshi) {}
	~YoshiState() {}

	// delete Function
	YoshiState(const YoshiState& _Other) = delete;
	YoshiState(YoshiState&& _Other) noexcept = delete;
	YoshiState& operator=(const YoshiState& _Other) = delete;
	YoshiState& operator=(YoshiState&& _Other) noexcept = delete;

	void ChangeFSM(EPlayerState _NextState)
	{
		FSM.ChangeState(_NextState);
	}

	void CreateFSM();
	void UpdateFSM(float _DeltaTime)
	{
		FSM.Update(_DeltaTime);
	}

	void Gravity(float _DeltaTime);
protected:

private:
	class AYoshi* Yoshi;
	UFSMStateManager FSM;
	USoundPlayer SoundPlayer;

#pragma region Wrapping Functions
	bool IsPress(int _KeyCode);
	bool IsPressTime(int _KeyCode, float _Time);
	bool IsDown(int _KeyCode);
	bool IsUp(int _KeyCode);
	bool IsFree(int _KeyCode);

	void ChangeAnimation(std::string _AnimName);
#pragma endregion

	void ChangeDefence();
};

