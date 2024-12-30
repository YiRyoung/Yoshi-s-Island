#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AStage : public AActor
{
public:
	// constrcuter destructer
	AStage();
	~AStage();

	// delete Function
	AStage(const AStage& _Other) = delete;
	AStage(AStage&& _Other) noexcept = delete;
	AStage& operator=(const AStage& _Other) = delete;
	AStage& operator=(AStage&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetBackgroundRenderer() const
	{
		return BackgroundRenderer;
	}

	void SetBackground(int _Index, FVector _Scale, FVector _Pos);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BackgroundRenderer;
};

