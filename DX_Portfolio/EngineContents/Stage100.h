#pragma once
#include <EngineCore/Actor.h>

#include <EnginePlatform/EngineWinImage.h>

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

	FVector GetStageScale() const;

	void SwitchColImage();

	bool GetIsFin() const
	{
		return IsFin;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UEngineWinImage ColImage;


	std::shared_ptr<class USpriteRenderer> BackgroundRenderer;
	std::shared_ptr<class USpriteRenderer> ForeBackgroundRenderer;
	std::shared_ptr<class USpriteRenderer> StageRenderer;
	std::shared_ptr<class USpriteRenderer> ColStageRenderer;
	std::shared_ptr<class USpriteRenderer> FrontBackgroundRenderer;

	std::shared_ptr<class UCollision> EndCollision;

	bool IsFin = false;

	void Stage100Res();
	void Stage100ColRes();
	void Stage100Init();
	void EndCollisionLink();
};

