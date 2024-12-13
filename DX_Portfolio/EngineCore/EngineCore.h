#pragma once
#include <EngineBase/EngineDefine.h>

// Ό³Έν :
class UEngineCore
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineCore();
	ENGINEAPI virtual ~UEngineCore() = 0;

	ENGINEAPI static void EngineStart(HINSTANCE _Instance);

protected:

private:

};

