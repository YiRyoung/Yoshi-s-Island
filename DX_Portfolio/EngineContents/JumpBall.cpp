#include "PreCompile.h"
#include "JumpBall.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "Yoshi.h"

AJumpBall::AJumpBall()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetSprite("JumpBalls.png", 0);
	Renderer->SetAutoScaleRatio(3.0f);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("JumpBallCollision");
	Collision->SetScale3D({ 51.0f, 51.0f });
	Collision->SetWorldLocation({ 0.0f, 25.5f });
}

AJumpBall::~AJumpBall()
{
}

void AJumpBall::Init(int _CaseNum)
{

}

void AJumpBall::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> FootCollisions;
	if(Collision->CollisionCheck("FootCollision", FootCollisions))
	{
		AYoshi* Yoshi = FootCollisions[0]->GetActor<AYoshi>();
		Yoshi->SetJumpBallType(1);
		RootComponent->SetScale3D({ 1.0f, 0.3f });
	}
	else
	{
		GetWorld()->GetMainPawn<AYoshi>()->SetJumpBallType(-1);
		RootComponent->SetScale3D({ 1.0f, 1.0f });
	}
}
