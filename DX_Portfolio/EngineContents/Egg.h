#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AEgg : public AActor
{
public:
	// constrcuter destructer
	AEgg();
	~AEgg();

	// delete Function
	AEgg(const AEgg& _Other) = delete;
	AEgg(AEgg&& _Other) noexcept = delete;
	AEgg& operator=(const AEgg& _Other) = delete;
	AEgg& operator=(AEgg&& _Other) noexcept = delete;

	void SetThrowDir(FVector _Value)
	{
		ThrowDir = _Value;
	}

	void Init();

protected:
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;

	FVector ThrowDir = FVector::ZERO;
};

