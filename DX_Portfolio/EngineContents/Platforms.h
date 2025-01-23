#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class APlatforms : public AActor
{
public:
	// constrcuter destructer
	APlatforms();
	~APlatforms();

	// delete Function
	APlatforms(const APlatforms& _Other) = delete;
	APlatforms(APlatforms&& _Other) noexcept = delete;
	APlatforms& operator=(const APlatforms& _Other) = delete;
	APlatforms& operator=(APlatforms&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> Platform;
	std::shared_ptr<class UCollision> Collision;
};