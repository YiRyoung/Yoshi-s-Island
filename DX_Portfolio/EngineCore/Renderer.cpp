#include "PreCompile.h"
#include "Renderer.h"

URenderer::URenderer()
{
}

URenderer::~URenderer()
{
}

void URenderer::SetOrder(int _Order)
{
	int PrevOrder = GetOrder();

	UObject::SetOrder(_Order);

	ULevel* Level = GetActor()->GetWorld();

	std::shared_ptr<URenderer> RendererPtr = GetThis<URenderer>();

	Level->ChangeRenderGroup(PrevOrder, RendererPtr);
}

ENGINEAPI void URenderer::BeginPlay()
{
	SetOrder(0);

	InputAssembler1Init();
}

void URenderer::Render(float _DeltaTime)
{
	InputAssembler1Setting();
}

void URenderer::InputAssembler1Init()
{
}

void URenderer::InputAssembler1Setting()
{
}

