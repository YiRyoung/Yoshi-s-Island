#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ASelectGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ASelectGameMode();
	~ASelectGameMode();

	// delete Function
	ASelectGameMode(const ASelectGameMode& _Other) = delete;
	ASelectGameMode(ASelectGameMode&& _Other) noexcept = delete;
	ASelectGameMode& operator=(const ASelectGameMode& _Other) = delete;
	ASelectGameMode& operator=(ASelectGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class ASelect> Select;
};