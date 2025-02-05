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

	ScaleBlockDownCollision = CreateDefaultSubObject<UCollision>();
	ScaleBlockDownCollision->SetupAttachment(RootComponent);
	ScaleBlockDownCollision->SetCollisionProfileName("ScaleBlockDownCollision");
	ScaleBlockDownCollision->SetScale3D({ 48.0f, 10.0f });
	ScaleBlockDownCollision->SetWorldLocation(FVector{ 0.0f, -24.0f + 5.0f });

	ScaleBlockUpCollision = CreateDefaultSubObject<UCollision>();
	ScaleBlockUpCollision->SetupAttachment(RootComponent);
	ScaleBlockUpCollision->SetCollisionProfileName("ScaleBlockUpCollision");
	ScaleBlockUpCollision->SetScale3D({ 48.0f, 10.0f });
	ScaleBlockUpCollision->SetWorldLocation(FVector{ 0.0f, 24.0f - 5.0f });

	ScaleBlockLeftCollision = CreateDefaultSubObject<UCollision>();
	ScaleBlockLeftCollision->SetupAttachment(RootComponent);
	ScaleBlockLeftCollision->SetCollisionProfileName("ScaleBlockLeftCollision");
	ScaleBlockLeftCollision->SetScale3D({ 10.0f, 48.0f });
	ScaleBlockLeftCollision->SetWorldLocation(FVector{ -24.0f + 5.0f, 0.0f });
}


void AScaleBlock::ScaleUp(FVector _Pos, float _DeltaTime)
{
	if (IsScaleMove)
	{
		ScaleBlockRenderer->SetScale3D(CurScale);
		ScaleBlockDownCollision->SetScale3D({ CurScale.X, 10.0f, 1.0f });
		ScaleBlockUpCollision->SetScale3D({ CurScale.X, 10.0f, 1.0f });
		ScaleBlockLeftCollision->SetScale3D({ 10.0f, CurScale.Y, 1.0f });
		
		CurScale += FVector{ 50.0f, 50.0f } * _DeltaTime;
		SetActorLocation(_Pos);
		AddActorLocation(FVector::UP * 75.0f * _DeltaTime);

		ScaleBlockDownCollision->SetWorldLocation(_Pos - FVector{0.0f, CurScale.Y * 0.4f});
		ScaleBlockUpCollision->SetWorldLocation(_Pos + FVector{0.0f, CurScale.Y * 0.5f});
		ScaleBlockLeftCollision->SetWorldLocation(_Pos - FVector{ CurScale.X * 0.41f, 0.0f});

		if (CurScale.X > 96.0f)
		{
			CurScale.X = 96.0f;
			CurScale.Y = 96.0f;
			IsScaleMove = false;
			IsBigger = true;
		}
	}
}

void AScaleBlock::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	
	SetCollisionLink();
}

void AScaleBlock::SetCollisionLink()
{
	{
		std::vector<UCollision*> YoshiBody;
		if (ScaleBlockDownCollision->CollisionCheck("HeadCollision", YoshiBody))
		{
			if (!IsBigger)
			{
				IsScaleMove = true;
			}

			YoshiBody[0]->GetActor<AYoshi>()->ChangeState(EPlayerState::FALL);
		}
	}
}

