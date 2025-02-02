#include "PreCompile.h"
#include "EggList.h"

#include "YoshiGameInstance.h"
#include "ThrowEgg.h"

AEggList::AEggList()
{
	Eggs.reserve(7);
}

AEggList::~AEggList()
{
}

void AEggList::BeginPlay()
{
	AActor::BeginPlay();
}

void AEggList::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

