#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ARotatePlatform : public AActor
{
public:
	// constrcuter destructer
	ARotatePlatform();
	~ARotatePlatform();

	// delete Function
	ARotatePlatform(const ARotatePlatform& _Other) = delete;
	ARotatePlatform(ARotatePlatform&& _Other) noexcept = delete;
	ARotatePlatform& operator=(const ARotatePlatform& _Other) = delete;
	ARotatePlatform& operator=(ARotatePlatform&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BoneRenderer;
	std::shared_ptr<class UCollision> DebugCollision;
	std::vector<class APlatforms*> Platforms;

	float RotAngle = 0.0f;
	float RotateSpeed = 50.0f;
};

