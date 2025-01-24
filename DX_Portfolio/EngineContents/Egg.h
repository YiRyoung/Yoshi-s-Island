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

protected:

private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;
};

