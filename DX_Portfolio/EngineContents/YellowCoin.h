#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AYellowCoin : public AActor
{
public:
	// constrcuter destructer
	AYellowCoin();
	~AYellowCoin();

	// delete Function
	AYellowCoin(const AYellowCoin& _Other) = delete;
	AYellowCoin(AYellowCoin&& _Other) noexcept = delete;
	AYellowCoin& operator=(const AYellowCoin& _Other) = delete;
	AYellowCoin& operator=(AYellowCoin&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetYellowCoinRenderer() const
	{
		return Renderer;
	}

	void Serialize(UEngineSerializer& _Ser);
	void DeSerialize(UEngineSerializer& _Ser);

protected:
	void Tick(float _DeltaTime);

private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;
};

