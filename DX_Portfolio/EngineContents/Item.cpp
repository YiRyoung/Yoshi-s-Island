#include "PreCompile.h"
#include "Item.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"

AItem::AItem()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetSprite("Eggs.png", 6);
	Renderer->SetAutoScaleRatio(3.0f);
}

AItem::~AItem()
{
}