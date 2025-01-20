#pragma once
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/Actor.h>

// Ό³Έν :
class AStage102 : public AActor
{
public:
	// constrcuter destructer
	AStage102();
	~AStage102();

	// delete Function
	AStage102(const AStage102& _Other) = delete;
	AStage102(AStage102&& _Other) noexcept = delete;
	AStage102& operator=(const AStage102& _Other) = delete;
	AStage102& operator=(AStage102&& _Other) noexcept = delete;

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

	void Stage102Res();
	void Stage102Init();
	void CameraBoundary();
};

