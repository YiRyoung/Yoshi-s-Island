#pragma once
#include <EngineCore/EngineGUIWindow.h>

// Ό³Έν :
class UKeyNoticeGUI : public UEngineGUIWindow
{
public:
	// constrcuter destructer
	UKeyNoticeGUI();
	~UKeyNoticeGUI();

	// delete Function
	UKeyNoticeGUI(const UKeyNoticeGUI& _Other) = delete;
	UKeyNoticeGUI(UKeyNoticeGUI&& _Other) noexcept = delete;
	UKeyNoticeGUI& operator=(const UKeyNoticeGUI& _Other) = delete;
	UKeyNoticeGUI& operator=(UKeyNoticeGUI&& _Other) noexcept = delete;

protected:
	void OnGUI() override;

private:
	void PrintGameGuide();
};

