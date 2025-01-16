#pragma once
#include <EngineCore/Actor.h>

#include <EnginePlatform/EngineWinImage.h>

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

	FVector GetMapScale() const
	{
		return MapScale;
	}

	UColor GetPixelColor(FVector _Pos);

	void SetStageNum(int _Num)
	{
		StageNum = _Num;
	}

	void SetRenderer(int _OrderNum, std::string _StageName, int _FileIndex);
	void SetColImage(int _StageCode);
	void SwitchColStage();

protected:

private:
	std::shared_ptr<class ACameraActor> Camera;

	std::shared_ptr<class USpriteRenderer> BackgroundRenderer;
	std::shared_ptr<class USpriteRenderer> ForeBackgroundRenderer;
	std::shared_ptr<class USpriteRenderer> StageRenderer;
	std::shared_ptr<class USpriteRenderer> ColStageRenderer;
	std::shared_ptr<class USpriteRenderer> ObstacleRenderer;
	std::shared_ptr<class USpriteRenderer> FrontBackgroundRenderer;

	UEngineWinImage ColImage;
	FVector MapScale = { 0.0f, 0.0f, 0.0f };

	void StageRes();
	void StageInit();
	void CameraBoundary();

	int StageNum = 0;
};

