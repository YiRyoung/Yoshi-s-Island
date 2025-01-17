#pragma once
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/Actor.h>

// Ό³Έν :
class AStage101 : public AActor
{
public:
	// constrcuter destructer
	AStage101();
	~AStage101();

	// delete Function
	AStage101(const AStage101& _Other) = delete;
	AStage101(AStage101&& _Other) noexcept = delete;
	AStage101& operator=(const AStage101& _Other) = delete;
	AStage101& operator=(AStage101&& _Other) noexcept = delete;

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

	void Stage101Res();
	void Stage101Init();
	void CameraBoundary();
};

