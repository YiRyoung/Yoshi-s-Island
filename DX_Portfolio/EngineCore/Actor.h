#pragma once
#include <EngineBase/Object.h>

// Ό³Έν :
class AActor : public UObject
{
public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	void CreateDefaultSubObject()
	{

	}

protected:

private:
	// std::list<std::shared_ptr<class UActorComponent>>
	std::shared_ptr<class USceneComponent> RootComponent;
	// std::list<std::shared_ptr<class USceneComponent>> SceneComponentLists;

	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;
};

