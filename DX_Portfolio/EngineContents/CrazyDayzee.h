#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ACrazyDayzee : public AActor
{
public:
	// constrcuter destructer
	ACrazyDayzee();
	~ACrazyDayzee();

	// delete Function
	ACrazyDayzee(const ACrazyDayzee& _Other) = delete;
	ACrazyDayzee(ACrazyDayzee&& _Other) noexcept = delete;
	ACrazyDayzee& operator=(const ACrazyDayzee& _Other) = delete;
	ACrazyDayzee& operator=(ACrazyDayzee&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;
};

