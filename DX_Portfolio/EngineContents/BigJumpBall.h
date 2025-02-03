#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ABigJumpBall : public AActor
{
public:
	// constrcuter destructer
	ABigJumpBall();
	~ABigJumpBall();

	// delete Function
	ABigJumpBall(const ABigJumpBall& _Other) = delete;
	ABigJumpBall(ABigJumpBall&& _Other) noexcept = delete;
	ABigJumpBall& operator=(const ABigJumpBall& _Other) = delete;
	ABigJumpBall& operator=(ABigJumpBall&& _Other) noexcept = delete;

protected:
	void Tick(float _DeltaTime);

private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;
};

