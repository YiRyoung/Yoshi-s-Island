#include "PreCompile.h"
#include "RotatePlatform.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "Platforms.h"

ARotatePlatform::ARotatePlatform()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BoneRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BoneRenderer->SetTexture("RotatePlatform.png");
	BoneRenderer->SetScale3D({ 200.0f, 200.0f });
	BoneRenderer->SetAutoScaleRatio(3.0f);
	BoneRenderer->SetupAttachment(RootComponent);
}

ARotatePlatform::~ARotatePlatform()
{
}

void ARotatePlatform::BeginPlay()
{
	AActor::BeginPlay();

	float Angle = 0;

	for (int i = 0; i < 4; i++)
	{
		Angle = i * 90.0f;

		FVector Pos = FVector::RIGHT * 100.0f;
		Pos.RotationZDeg(Angle);
		std::shared_ptr<APlatforms> APlat = GetWorld()->SpawnActor<APlatforms>();
		APlat->SetActorLocation(GetActorLocation() + Pos);
		Platforms.push_back(APlat.get());
	}
}

void ARotatePlatform::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorRotation({ 0.0f, 0.0f, RotateSpeed * _DeltaTime });

	RotAngle += RotateSpeed * _DeltaTime;

	float Angle = 0;

	for (int i = 0; i < Platforms.size(); i++)
	{
		Angle = i * 90.0f;
		FVector Pos = FVector::RIGHT * 90.0f;
		Pos.RotationZDeg(Angle + RotAngle);
		Platforms[i]->SetActorLocation(GetActorLocation() + Pos);
		Platforms[i]->AddActorLocation({ 0.0f, 0.0f, -1.0f });
	}
}

