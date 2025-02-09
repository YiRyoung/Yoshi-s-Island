#include "PreCompile.h"
#include "ItemTail.h"

#include <EngineCore/SpriteRenderer.h>

#include "Yoshi.h"
#include "YoshiGameInstance.h"
#include "Item.h"

#include "ContentsEnum.h"

AItemTail::AItemTail()
{
	ItemList.resize(7);
}

AItemTail::~AItemTail()
{
}

void AItemTail::BeginPlay()
{
	AActor::BeginPlay();

	for (int i = 0; i < 7; i++)
	{
		std::shared_ptr<AItem> Item = GetWorld()->SpawnActor<AItem>();
		ItemList[i] = Item;
	}
}

void AItemTail::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	int EggCount = GetWorld()->GetMainPawn<AYoshi>()->GetGameInstance<AYoshiGameInstance>()->EggCount;
	
	for (int i = 0; i < 7; i++)
	{
		if ((EggCount - 1) >= i)
		{
			ItemList[i]->GetItemRenderer()->SetActive(true);
		}
		else
		{
			ItemList[i]->GetItemRenderer()->SetActive(false);
		}
	}

	if (ItemList.empty()) return;

	AYoshi* Yoshi = GetWorld()->GetMainPawn<AYoshi>();
	FVector PrevPos = Yoshi->GetActorLocation();
	FVector Offset = FVector(-30.0f, 0.0f, 0.0f);

	for (size_t i = 0; i < ItemList.size(); i++)
	{
		if (ItemList[i] && ItemList[i]->IsActive())
		{
			FVector TargetPos = PrevPos + Offset;
			FVector NewPos = UEngineMath::Lerp(ItemList[i]->GetActorLocation(), TargetPos, 0.1f);
			ItemList[i]->SetActorLocation({ NewPos.X, NewPos.Y, static_cast<float>(EOrderNum::PLAYER) + i + 1});
			PrevPos = NewPos;
		}
	}
}

