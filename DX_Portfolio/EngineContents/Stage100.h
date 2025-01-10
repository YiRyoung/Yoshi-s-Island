#pragma once
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/GameMode.h>

// Ό³Έν :
class AStage100 : public AGameMode
{
public:
	// constrcuter destructer
	AStage100();
	~AStage100();

	// delete Function
	AStage100(const AStage100& _Other) = delete;
	AStage100(AStage100&& _Other) noexcept = delete;
	AStage100& operator=(const AStage100& _Other) = delete;
	AStage100& operator=(AStage100&& _Other) noexcept = delete;

	FVector GetMapScale() const
	{
		return MapScale;
	}

	UColor GetPixelColor(FVector _Pos);
	void SetBackground();


	bool GetColStageOn() const
	{
		return ColStageRenderer->IsActive();
	}

	void SwitchColStage(bool _IsOn)
	{
		ColStageRenderer->SetActive(_IsOn);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BackgroundRenderer;
	std::shared_ptr<class USpriteRenderer> ForeBackgroundRenderer;
	std::shared_ptr<class USpriteRenderer> StageRenderer;
	std::shared_ptr<class USpriteRenderer> ColStageRenderer;
	std::shared_ptr<class USpriteRenderer> FrontBackgroundRenderer;

	FVector MapScale = { 0.0f, 0.0f, 0.0f };
	UEngineWinImage ColImage;
};

