#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>

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

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	USoundPlayer SoundPlayer;
	std::shared_ptr<class AStage100> Stage;

	std::shared_ptr<class ACrazyDayzee> CrazyDayzee1;
	std::shared_ptr<class ACrazyDayzee> CrazyDayzee2;
	std::shared_ptr<class ACrazyDayzee> CrazyDayzee3;
	std::shared_ptr<class ACrazyDayzee> CrazyDayzee4;

	std::shared_ptr<class AScaleBlock> ScaleBlock1;
	std::shared_ptr<class AScaleBlock> ScaleBlock2;
	std::shared_ptr<class ARotatePlatform> RotatePlatform;
	std::shared_ptr<class APlatforms> Platform;
	std::shared_ptr<class AJumpBall> JumpBall;
	std::shared_ptr<class ABigJumpBall> BigJumpBall;

	void SetCollisionLink();
	void InitActors();
	void SetGUI();

	void LoadMap();
};

