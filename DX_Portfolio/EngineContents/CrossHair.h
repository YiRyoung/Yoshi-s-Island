#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ACrossHair : public AActor
{
public: 
	// constrcuter destructer
	ACrossHair();
	~ACrossHair();

	// delete Function
	ACrossHair(const ACrossHair& _Other) = delete;
	ACrossHair(ACrossHair&& _Other) noexcept = delete;
	ACrossHair& operator=(const ACrossHair& _Other) = delete;
	ACrossHair& operator=(ACrossHair&& _Other) noexcept = delete;

	void Init(class AYoshi* _Yoshi);

protected:
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> CrossHairRenderer;

	float Radius = 200.0f;
	float StartAngle = 0.0f;
	float Speed = 35.0f;
};

