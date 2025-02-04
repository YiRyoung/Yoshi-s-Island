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
	Renderer->CreateAnimation("Sing", "CrazyDazee.png", 10, 12, 0.7f, false);
	Renderer->CreateAnimation("Walk", "CrazyDazee.png", 0, 9, 0.07f);
	Renderer->ChangeAnimation("Idle");
}

ACrazyDayzee::~ACrazyDayzee()
{
}

