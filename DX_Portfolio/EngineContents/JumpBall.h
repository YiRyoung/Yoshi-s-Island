#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AJumpBall : public AActor
{
public:
	// constrcuter destructer
	AJumpBall();
	~AJumpBall();

	// delete Function
	AJumpBall(const AJumpBall& _Other) = delete;
	AJumpBall(AJumpBall&& _Other) noexcept = delete;
	AJumpBall& operator=(const AJumpBall& _Other) = delete;
	AJumpBall& operator=(AJumpBall&& _Other) noexcept = delete;

	void SetScale(FVector _Value)
	{
		RootComponent->SetScale3D(_Value);
	}

	void Init(int _CaseNum);

protected:
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;
};

