#pragma once
#include <EngineCore/GameMode.h>

#include <EnginePlatform/EngineSound.h>

// Ό³Έν :
class AEndingGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AEndingGameMode();
	~AEndingGameMode();

	// delete Function
	AEndingGameMode(const AEndingGameMode& _Other) = delete;
	AEndingGameMode(AEndingGameMode&& _Other) noexcept = delete;
	AEndingGameMode& operator=(const AEndingGameMode& _Other) = delete;
	AEndingGameMode& operator=(AEndingGameMode&& _Other) noexcept = delete;

protected:
	void LevelChangeStart() override;

private:
	USoundPlayer SoundPlayer;

	std::shared_ptr<class AEnding> Ending;
};

