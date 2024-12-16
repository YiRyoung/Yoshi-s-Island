#pragma once

#include <EngineBase/Object.h>

#include "EngineCore.h"

// Ό³Έν :
class ULevel : public UObject
{
public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

protected:

private:

};

