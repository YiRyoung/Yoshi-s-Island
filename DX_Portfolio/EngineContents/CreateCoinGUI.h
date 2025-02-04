#pragma once
#include <EngineCore/EngineGUIWindow.h>

// Ό³Έν :
class UCreateCoinGUI : public UEngineGUIWindow
{
public:
	// constrcuter destructer
	UCreateCoinGUI();
	~UCreateCoinGUI();

	// delete Function
	UCreateCoinGUI(const UCreateCoinGUI& _Other) = delete;
	UCreateCoinGUI(UCreateCoinGUI&& _Other) noexcept = delete;
	UCreateCoinGUI& operator=(const UCreateCoinGUI& _Other) = delete;
	UCreateCoinGUI& operator=(UCreateCoinGUI&& _Other) noexcept = delete;

protected:
	void OnGUI() override;

private:
	int SelectItem = 0;
	int ObjectItem = -1;

	void CreateYellowCoin();
	void SaveAndLoad();
};

