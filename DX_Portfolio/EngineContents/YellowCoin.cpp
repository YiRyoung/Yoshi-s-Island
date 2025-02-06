#include "PreCompile.h"
#include "YellowCoin.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "YoshiGameInstance.h"
#include "Yoshi.h"

AYellowCoin::AYellowCoin()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetSprite("Coins.png", 0);
	Renderer->SetAutoScaleRatio(3.0f);
	Renderer->CreateAnimation("YellowCoin_Idle", "Coins.png", 0, 3, 0.2f);
	Renderer->ChangeAnimation("YellowCoin_Idle");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("YellowCoinCollision");
	Collision->SetScale3D({ 36.0f, 48.0f });
	Collision->AddWorldLocation({ 18.0f, 24.0f });
}

AYellowCoin::~AYellowCoin()
{
}

void AYellowCoin::Serialize(UEngineSerializer& _Ser)
{
	_Ser << GetActorLocation();
}

void AYellowCoin::DeSerialize(UEngineSerializer& _Ser)
{
	FVector SavePos;
	_Ser >> SavePos;
	SetActorLocation(SavePos);
}

void AYellowCoin::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Yoshi;
	if(Collision->CollisionCheck("BodyCollision", Yoshi))
	{
		SoundPlayer = UEngineSound::Play("Coin.wav");
		GetWorld()->GetMainPawn<AYoshi>()->GetGameInstance<AYoshiGameInstance>()->YellowCoin += 1;
		this->Destroy();
	}
}

