#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AScaleBlock : public AActor
{
public:
	// constrcuter destructer
	AScaleBlock();
	~AScaleBlock();

	// delete Function
	AScaleBlock(const AScaleBlock& _Other) = delete;
	AScaleBlock(AScaleBlock&& _Other) noexcept = delete;
	AScaleBlock& operator=(const AScaleBlock& _Other) = delete;
	AScaleBlock& operator=(AScaleBlock&& _Other) noexcept = delete;

	void InitScaleBlock();
	void ScaleUp(FVector _Pos, float _DeltaTime);

protected:
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> ScaleBlockRenderer;
	std::shared_ptr<class UCollision> ScaleBlockUpCollision;
	std::shared_ptr<class UCollision> ScaleBlockDownCollision;
	std::shared_ptr<class UCollision> ScaleBlockLeftCollision;
	std::shared_ptr<class UCollision> ScaleBlockRightCollision;

	FVector MinScale = { 48.0f, 48.0f };
	FVector MaxScale = { 96.0f, 96.0f };
	FVector CurScale = MinScale;

	bool IsBigger = false;
	bool IsScaleMove = false;

	void SetCollisionLink();
};

