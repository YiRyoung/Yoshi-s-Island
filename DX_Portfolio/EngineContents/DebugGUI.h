#pragma once
#include <EngineBase/FSMStateManager.h>

#include <EngineCore/EngineGUIWindow.h>

// Ό³Έν :
class UDebugGUI : public UEngineGUIWindow
{
public:
	// constrcuter destructer
	UDebugGUI();
	~UDebugGUI();

	// delete Function
	UDebugGUI(const UDebugGUI& _Other) = delete;
	UDebugGUI(UDebugGUI&& _Other) noexcept = delete;
	UDebugGUI& operator=(const UDebugGUI& _Other) = delete;
	UDebugGUI& operator=(UDebugGUI&& _Other) noexcept = delete;

protected:
	void OnGUI() override;

private:
	class UFSMStateManager FSM;

	void SwitchFreeCamera();
	void PrintPixelCollisionKey();
	void PrintEggCount();
	void PrintYellowCoinCount();
	void PrintCurState();
	void ChangeAnimationButtons();
};