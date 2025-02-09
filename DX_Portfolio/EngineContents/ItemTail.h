#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AItemTail : public AActor
{
public:
	// constrcuter destructer
	AItemTail();
	~AItemTail();

	// delete Function
	AItemTail(const AItemTail& _Other) = delete;
	AItemTail(AItemTail&& _Other) noexcept = delete;
	AItemTail& operator=(const AItemTail& _Other) = delete;
	AItemTail& operator=(AItemTail&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::vector<std::shared_ptr<class AItem>> ItemList;
};

