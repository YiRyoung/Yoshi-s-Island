#pragma once
#include <EngineCore/Actor.h>

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
	std::shared_ptr<class AStage100> Stage;
	std::shared_ptr<class AYoshi> Yoshi;
	std::shared_ptr<class ACameraActor> Camera;

	class UEngineWinImage* ColImage = nullptr;
	void SetCameraBoundary();
};

