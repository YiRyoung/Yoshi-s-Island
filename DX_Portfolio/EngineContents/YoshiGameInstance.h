#pragma once
#include <EngineCore/GameInstance.h>

// Ό³Έν :
class AYoshiGameInstance : public UGameInstance
{
public:
	// constrcuter destructer
	AYoshiGameInstance();
	~AYoshiGameInstance();

	// delete Function
	AYoshiGameInstance(const AYoshiGameInstance& _Other) = delete;
	AYoshiGameInstance(AYoshiGameInstance&& _Other) noexcept = delete;
	AYoshiGameInstance& operator=(const AYoshiGameInstance& _Other) = delete;
	AYoshiGameInstance& operator=(AYoshiGameInstance&& _Other) noexcept = delete;

	int YellowCoin = 0;
	int EggCount = 0;
};

