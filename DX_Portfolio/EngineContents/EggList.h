#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AEggList : public AActor
{
public:
	// constrcuter destructer
	AEggList();
	~AEggList();

	// delete Function
	AEggList(const AEggList& _Other) = delete;
	AEggList(AEggList&& _Other) noexcept = delete;
	AEggList& operator=(const AEggList& _Other) = delete;
	AEggList& operator=(AEggList&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::vector<class AThrowEgg*> Eggs;
	int EggCount = 0;
};

