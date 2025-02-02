#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AThrowEgg : public AActor
{
public:
	// constrcuter destructer
	AThrowEgg();
	~AThrowEgg();

	// delete Function
	AThrowEgg(const AThrowEgg& _Other) = delete;
	AThrowEgg(AThrowEgg&& _Other) noexcept = delete;
	AThrowEgg& operator=(const AThrowEgg& _Other) = delete;
	AThrowEgg& operator=(AThrowEgg&& _Other) noexcept = delete;

	void SetThrowDir(FVector _Value)
	{
		ThrowDir = _Value;
	}

	void Init();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;
	std::shared_ptr<class UTimeEventComponent> TimeEvent;

	FVector ThrowDir = FVector::ZERO;
	float ThrowSpeed = 400.0f;

	void ReflectMove(float _DeltaTime);
	void DestroyEgg();
};

