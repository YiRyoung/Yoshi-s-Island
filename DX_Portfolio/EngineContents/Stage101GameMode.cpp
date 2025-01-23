#include "PreCompile.h"
#include "Stage101GameMode.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/CameraActor.h>

#include "Stage101.h"
#include "ShyGuy.h"
#include "RotatePlatform.h"
#include "Platforms.h"

#include "ContentsEnum.h"

AStage101GameMode::AStage101GameMode()
{
}

AStage101GameMode::~AStage101GameMode()
{
}

void AStage101GameMode::BeginPlay()
{
	AActor::BeginPlay();

	Stage = GetWorld()->SpawnActor<AStage101>();
	Stage->SetActorLocation({ 12288 * 0.5f, 2241 * -0.5f });

	GetWorld()->GetMainPawn()->SetActorLocation({ 100.0f, -1850.0f, static_cast<float>(EOrderNum::PLAYER)});
	Stage->SwitchColStage();

	RotatePlatform = GetWorld()->SpawnActor<ARotatePlatform>();
	RotatePlatform->SetActorLocation({ 400.0f, -1780.0f, -2.0f });

	ShyGuy = GetWorld()->SpawnActor<AShyGuy>();
	ShyGuy->SetActorLocation({ 200.0f, -1850.0f, static_cast<float>(EOrderNum::PLAYER) });

	GetWorld()->CreateCollisionProfile("HeadCollision");
	GetWorld()->CreateCollisionProfile("BodyCollision");
	GetWorld()->CreateCollisionProfile("FootCollision");

	GetWorld()->CreateCollisionProfile("MonsterHeadCollision");
	GetWorld()->CreateCollisionProfile("MonsterBodyCollision");

	GetWorld()->CreateCollisionProfile("PlatformCollision");

	GetWorld()->CreateCollisionProfile("DebugCollision");

	GetWorld()->LinkCollisionProfile("FootCollision", "MonsterHeadCollision");
	GetWorld()->LinkCollisionProfile("PlatformCollision", "FootCollision");
}

void AStage101GameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown('V'))
	{
		Stage->SwitchColStage();
	}

	if (UEngineInput::IsDown('F'))
	{
		GetWorld()->GetMainCamera()->FreeCameraSwitch();
	}
}

