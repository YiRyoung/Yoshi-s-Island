#include "PreCompile.h"
#include "BigJumpBall.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "Yoshi.h"

ABigJumpBall::ABigJumpBall()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetSprite("JumpBalls.png", 1);
	Renderer->SetAutoScaleRatio(3.0f);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("BigJumpBallCollision");
	Collision->SetScale3D({ 72.0f, 72.0f });
	Collision->SetWorldLocation({ 0.0f, 36.0f });
}

ABigJumpBall::~ABigJumpBall()
{
}

void ABigJumpBall::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> FootCollisions;
	if (Collision->CollisionCheck("FootCollision", FootCollisions))
	{
		AYoshi* Yoshi = FootCollisions[0]->GetActor<AYoshi>();
		Yoshi->SetJumpBallType(2);
		RootComponent->SetScale3D({ 1.0f, 0.3f });
	}
	else
	{
		GetWorld()->GetMainPawn<AYoshi>()->SetJumpBallType(-1);
		RootComponent->SetScale3D({ 1.0f, 1.0f });
	}
}

