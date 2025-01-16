#pragma once
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/Actor.h>

// Ό³Έν :
class AStage100 : public AActor
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

	UColor GetPixelColor(FVector _Pos)
	{
		return ColImage.GetColor(_Pos);
	}

	void SwitchColStage();
	
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class ACameraActor> Camera;

	std::shared_ptr<class USpriteRenderer> BackgroundRenderer;
	std::shared_ptr<class USpriteRenderer> ForeBackgroundRenderer;
	std::shared_ptr<class USpriteRenderer> StageRenderer;
	std::shared_ptr<class USpriteRenderer> ColStageRenderer;
	std::shared_ptr<class USpriteRenderer> FrontBackgroundRenderer;

	UEngineWinImage ColImage;

	void Stage100Res();
	void Stage100Init();
	void CameraBoundary();
};

