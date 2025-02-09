#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AMarioBubble : public AActor
{
public:
	// constrcuter destructer
	AMarioBubble();
	~AMarioBubble();

	// delete Function
	AMarioBubble(const AMarioBubble& _Other) = delete;
	AMarioBubble(AMarioBubble&& _Other) noexcept = delete;
	AMarioBubble& operator=(const AMarioBubble& _Other) = delete;
	AMarioBubble& operator=(AMarioBubble&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;
};

