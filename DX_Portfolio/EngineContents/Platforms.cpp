#include "PreCompile.h"
#include "Platforms.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "Yoshi.h"
#include "RotatePlatform.h"

APlatforms::APlatforms()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Platform = CreateDefaultSubObject<USpriteRenderer>();
	Platform->SetSprite("Platforms.png", 6);
	Platform->SetAutoScaleRatio(3.0f);
	Platform->SetupAttachment(RootComponent);
}

APlatforms::~APlatforms()
{
}

void APlatforms::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetCollisionProfileName("PlatformCollision");
	Collision->SetScale3D({32 * 3.0f, 10.0f});
	Collision->SetRelativeLocation({ 0.0f, 18.0f, -3.0f });
	Collision->SetupAttachment(RootComponent);
}

void APlatforms::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	AYoshi* Yoshi = GetWorld()->GetMainPawn<AYoshi>();

	if (Yoshi->GetPlatform() == this)
	{
		Yoshi->ResetGraviryForce();
		Yoshi->SetActorLocation(Yoshi->GetPlatform()->GetActorLocation() + Yoshi->GetPlatformPos());

		std::vector<UCollision*> FootCollision;
		if (false == Collision->CollisionCheck("FootCollision", FootCollision))
		{
			Yoshi->SetPlatform(nullptr);
		}
	}
}
