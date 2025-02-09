#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AEnding : public AActor
{
public:
	// constrcuter destructer
	AEnding();
	~AEnding();

	// delete Function
	AEnding(const AEnding& _Other) = delete;
	AEnding(AEnding&& _Other) noexcept = delete;
	AEnding& operator=(const AEnding& _Other) = delete;
	AEnding& operator=(AEnding&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class ACameraActor> Camera;

	std::shared_ptr<class USpriteRenderer> BlackScreen;
	std::shared_ptr<class USpriteRenderer> Yoshi;
	std::vector<std::shared_ptr<class USpriteRenderer>> Renders;

	bool IsMoveUp = true;
	float Speed = 80.0f;

	void SetIsMoveUp();
	void FontMoving(float _DeltaTime);
};