#include "PreCompile.h"
#include "ScaleBlock.h"

#include "EnginePlatform/EngineInput.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "Yoshi.h"

AScaleBlock::AScaleBlock()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	InitScaleBlock();
}

AScaleBlock::~AScaleBlock()
{
}

void AScaleBlock::InitScaleBlock()
{
	ScaleBlockRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ScaleBlockRenderer->SetTexture("ScaleBlock.png");
	ScaleBlockRenderer->SetScale3D({ 48.0f, 48.0f });
	ScaleBlockRenderer->SetupAttachment(RootComponent);

	/*ScaleBlockCollision = CreateDefaultSubObject<UCollision>();
	ScaleBlockCollision->SetupAttachment(RootComponent);
	ScaleBlockCollision->SetCollisionProfileName("ScaleBlockCollision");
	ScaleBlockCollision->SetScale3D({ 48.0f, 48.0f });*/
}

void AScaleBlock::ScaleUp(FVector _Pos, float _DeltaTime)
{
	/*if (IsScaleMove)
	{
		ScaleBlockRenderer->SetScale3D(CurScale);
		ScaleBlockCollision->SetScale3D(CurScale);
		CurScale += FVector{ 50.0f, 50.0f } * _DeltaTime;
		SetActorLocation(_Pos);
		AddActorLocation(FVector::UP * 72.0f * _DeltaTime);

		if (CurScale.X > 96.0f)
		{
			CurScale.X = 96.0f;
			CurScale.Y = 96.0f;
			IsScaleMove = false;
			IsBigger = true;
		}
	}*/
}

void AScaleBlock::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}

