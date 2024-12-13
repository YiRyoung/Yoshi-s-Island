#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::EngineStart(HINSTANCE _Instance)
{
	UEngineDebug::LeakCheck();

	UEngineWindow::EngineWindowInit(_Instance);

	UEngineWindow MainWindow;

	MainWindow.Open("MainWindow");

	// 윈도우와는 무관합니다.
	UEngineWindow::WindowMessageLoop(
		[]()
		{
			// 시작할때 하고 싶은것
			// 1. 윈도우창 크기 바꾸고 싶다.
		},
		[]()
		{
			// 엔진이 돌아갈때 하고 싶은것
		},
		[]()
		{
			// 엔진이 끝났을때 하고 싶은것.
		});


	// 게임 엔진이 시작되었다.
	// 윈도우창은 엔진이 알아서 띄워줘야 하고.

	// Window 띄워줘야 한다.

	
}