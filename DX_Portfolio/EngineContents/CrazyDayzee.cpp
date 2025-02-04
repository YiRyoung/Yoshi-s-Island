#include "PreCompile.h"
#include "CrazyDayzee.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

ACrazyDayzee::ACrazyDayzee()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetAutoScaleRatio(3.0f);
	Renderer->SetSprite("CrazyDazee.png", 10);

	Renderer->CreateAnimation("Idle", "CrazyDazee.png", 10, 10, false);
	Renderer->CreateAnimation("Sing", "CrazyDazee.png", { 10, 12 }, 0.4f, false);
	Renderer->CreateAnimation("Walk", "CrazyDazee.png", 0, 9, 0.07f);
	Renderer->ChangeAnimation("Idle");

	HeadCollision = CreateDefaultSubObject<UCollision>();
	HeadCollision->SetupAttachment(RootComponent);
	HeadCollision->SetCollisionProfileName("MonsterHeadCollision");
	HeadCollision->SetScale3D({ 63.0f , 75.0f * 0.3f });
	HeadCollision->SetRelativeLocation({ 0.0f, 75.0f * 0.8f });

	BodyCollision = CreateDefaultSubObject<UCollision>();
	BodyCollision->SetupAttachment(RootComponent);
	BodyCollision->SetCollisionProfileName("MonsterBodyCollision");
	BodyCollision->SetScale3D({ 63.0f , 75.0f * 0.7f });
	BodyCollision->SetRelativeLocation({ 0.0f, 75.0f * 0.3f });
}

ACrazyDayzee::~ACrazyDayzee()
{
}

void ACrazyDayzee::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> FootCollisions;
	if(HeadCollision->CollisionCheck("FootCollision", FootCollisions))
	{
		IsStepped = true;
	}
	
	if (IsStepped)
	{
		AMonster::FallDown(_DeltaTime);
	}
}

