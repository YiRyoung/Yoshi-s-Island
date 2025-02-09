#include "PreCompile.h"
#include "MarioBubble.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "Yoshi.h"
#include "YoshiGameInstance.h"

AMarioBubble::AMarioBubble()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetSprite("MarioBubble.png", 0);
	Renderer->SetAutoScaleRatio(2.5f);
	Renderer->CreateAnimation("Crying", "MarioBubble.png", 0, 2, 0.3f);
	Renderer->ChangeAnimation("Crying");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("BubbleCollision");
	Collision->SetScale3D({ 80.0f, 80.0f });
	Collision->SetWorldLocation({ 40.0f, 40.0f });

	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			_Other->GetActor<AYoshi>()->SetIsWithBaby(true);
			_This->GetActor<AMarioBubble>()->Destroy();
		});
}

AMarioBubble::~AMarioBubble()
{
}

