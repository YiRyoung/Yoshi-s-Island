#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class AStage100GameMode : public AGameMode
{
public:
	// constrcuter destructer
	AStage100GameMode();
	~AStage100GameMode();

	// delete Function
	AStage100GameMode(const AStage100GameMode& _Other) = delete;
	AStage100GameMode(AStage100GameMode&& _Other) noexcept = delete;
	AStage100GameMode& operator=(const AStage100GameMode& _Other) = delete;
	AStage100GameMode& operator=(AStage100GameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class AStage> Stage;
};
