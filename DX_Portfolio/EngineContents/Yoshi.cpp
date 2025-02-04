#include "PreCompile.h"
#include "Yoshi.h"

#include <EngineBase/EngineRandom.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "YoshiState.h"
#include "CrossHair.h"
#include "Monster.h"

#include "Platforms.h"
#include "ThrowEgg.h"
#include "JumpBall.h"

AYoshi::AYoshi()
{
	YoshiInit();
}

AYoshi::~AYoshi()
{
	if (State != nullptr)
	{
		delete State;
		State = nullptr;
	}
}

void AYoshi::BeginPlay()
{
	APawn::BeginPlay();
	YoshiScale = YoshiRenderer->GetTransformRef().Scale;

	SetAnimation();
	State->CreateFSM();
	SetCollision();

	CrossHair = GetWorld()->SpawnActor<ACrossHair>();
	CrossHair->InitCrossHair(this);
}

void AYoshi::Tick(float _DeltaTime)
{
	APawn::Tick(_DeltaTime);

	State->UpdateFSM(_DeltaTime);
	State->Gravity(_DeltaTime);
	SetAnimDir();

	MoveSlope(_DeltaTime);
	MoveCamera(_DeltaTime);

	SetCollisionsCheck();
	SetCrossHair();

	UEngineDebug::OutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
}

void AYoshi::YoshiInit()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	State = new YoshiState(this);

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -560.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	YoshiRenderer = CreateDefaultSubObject<USpriteRenderer>();
	YoshiRenderer->SetupAttachment(RootComponent);
	YoshiRenderer->SetAutoScaleRatio(3.0f);

	// Unused
	YoshiRenderer->CreateAnimation("Idle0", "YoshiAndMario.png", { 7, 8, 9, 10, 11, 10, 9, 8 }, 0.15f);
	YoshiRenderer->ChangeAnimation("Idle0");
}

#pragma region Camera Funcs
void AYoshi::CameraBoundary(FVector _StageScale)
{
	Camera->SetActorLocation({ GetActorLocation().X, GetActorLocation().Y, -520.0f });

	FVector ResultCameraPos = { 0.0f, 0.0f, 0.0f };
	FVector ScreenSize = UEngineCore::GetScreenScale();
	FVector MapSize = _StageScale;
	FVector CameraPos = Camera->GetActorLocation() + CameraPivot;

	// SetBoundary
	if ((ScreenSize.X * 0.5f) >= CameraPos.X)
	{
		ResultCameraPos.X = ScreenSize.X * 0.5f;
	}
	else if (MapSize.X - (ScreenSize.X * 0.5f) <= CameraPos.X)
	{
		ResultCameraPos.X = MapSize.X - (ScreenSize.X * 0.5f);
	}
	else
	{
		ResultCameraPos.X = GetWorld()->GetMainPawn()->GetActorLocation().X + CameraPivot.X;
	}

	if ((ScreenSize.Y * -0.5f) <= CameraPos.Y)
	{
		ResultCameraPos.Y = (ScreenSize.Y * -0.5f);
	}
	else if ((-MapSize.Y + (ScreenSize.Y * 0.5f)) >= CameraPos.Y)
	{
		ResultCameraPos.Y = (-MapSize.Y + (ScreenSize.Y * 0.5f));
	}
	else
	{
		ResultCameraPos.Y = GetWorld()->GetMainPawn()->GetActorLocation().Y + CameraPivot.Y;
	}

	Camera->SetActorLocation({ ResultCameraPos.X, ResultCameraPos.Y + 160.0f, -520.0f });
}

void AYoshi::MoveCamera(float _DeltaTime)
{
	switch (CameraNum)
	{
	case 1:
		// UP
		CameraPivot += FVector::UP * _DeltaTime * 100.0f;
		if (CameraPivot.Y > MaxCameraPivotY)
		{
			CameraPivot.Y = MaxCameraPivotY;
			CameraNum = -1;
		}
		break;
	case 2:
		// DOWN
		CameraPivot += FVector::DOWN * _DeltaTime * 100.0f;

		if (CameraPivot.Y < MinCameraPivotY)
		{
			CameraPivot.Y = MinCameraPivotY;
			CameraNum = -1;
		}
		break;
	}
}
#pragma endregion

#pragma region Animation Funcs
void AYoshi::SetAnimation()
{
#pragma region WithBabyMario And NotHold
	// Not Aim
	YoshiRenderer->CreateAnimation("MNH_Idle0", "YoshiAndMario.png", { 7, 8, 9, 10, 11, 10, 9, 8 }, 0.15f);
	YoshiRenderer->CreateAnimation("MNH_Idle1", "YoshiAndMario.png", { 3, 4, 5, 4, 5 }, 0.2f);
	YoshiRenderer->CreateAnimation("MNH_Idle2", "YoshiAndMario.png", { 2, 1, 0, 0, 0, 1, 2 }, 0.15f);

	YoshiRenderer->CreateAnimation("MNH_Walk", "YoshiAndMario.png", { 40, 41, 42, 43, 44, 45, 44, 43, 42, 41 }, 0.08f);
	YoshiRenderer->CreateAnimation("MNH_Run", "YoshiAndMario.png", 53, 57, 0.04f);

	YoshiRenderer->CreateAnimation("MNH_Jump", "YoshiAndMario.png", 75, 76, 0.1f, false);
	YoshiRenderer->CreateAnimation("MNH_Fall", "YoshiAndMario.png", 77, 79, 0.07f, false);
	YoshiRenderer->CreateAnimation("MNH_StayUp", "YoshiAndMario.png", 80, 83, 0.04f);

	YoshiRenderer->CreateAnimation("MNH_LookUpStart", "YoshiAndMario.png", 12, 13, 0.3f, false);
	YoshiRenderer->CreateAnimation("MNH_LookUpEnd", "YoshiAndMario.png", 13, 12, 0.1f, false);

	YoshiRenderer->CreateAnimation("MNH_BendStart", "YoshiAndMario.png", 14, 17, 0.05f, false);
	YoshiRenderer->CreateAnimation("MNH_BendEnd", "YoshiAndMario.png", 17, 14, 0.04f);

	// Aim
	YoshiRenderer->CreateAnimation("MNH_AimIdle", "YoshiAndMario.png", 119, 119, 0.028f, false);	// Jump & Fall && LookUp°ú µ¿ÀÏ
	YoshiRenderer->CreateAnimation("MNH_AimWalk", "YoshiAndMario.png", 119, 124, 0.08f);
	YoshiRenderer->CreateAnimation("MNH_AimStayUp", "YoshiAndMario.png", 126, 128, 0.07f);

	// Attack
	YoshiRenderer->CreateAnimation("MNH_Stick_RightStart", "YoshiAndMarioStick_Right.png", 0, 5, 0.04f, false);
	YoshiRenderer->CreateAnimation("MNH_Stick_RightEnd", "YoshiAndMarioStick_Right.png", 4, 0, 0.04f, false);

	YoshiRenderer->CreateAnimation("MNH_Stick_UpStart", "YoshiAndMarioStick_Upper.png", 0, 5, 0.04f, false);
	YoshiRenderer->CreateAnimation("MNH_Stick_UPEnd", "YoshiAndMarioStick_Upper.png", 4, 0, 0.04f, false);
	
	YoshiRenderer->CreateAnimation("MNH_Throw", "YoshiAndMario.png", 131, 134, 0.04f, false);


#pragma endregion

#pragma region WithBabyMario And Hold
	YoshiRenderer->CreateAnimation("MH_Idle0", "YoshiAndMario.png", { 23, 24, 25, 26, 27, 26, 25, 24 }, 0.15f);
	YoshiRenderer->CreateAnimation("MH_Idle1", "YoshiAndMario.png", { 20, 21, 22, 21, 22 }, 0.2f);
	YoshiRenderer->CreateAnimation("MH_Idle2", "YoshiAndMario.png", { 20, 19, 18, 18, 18, 19, 20 }, 0.15f);

	YoshiRenderer->CreateAnimation("MH_Walk", "YoshiAndMario.png", 59, 65, 0.15f);
	YoshiRenderer->CreateAnimation("MH_Run", "YoshiAndMario.png", 69, 73, 0.04f);

	YoshiRenderer->CreateAnimation("MH_Jump", "YoshiAndMario.png", 85, 86, 0.1f, false);
	YoshiRenderer->CreateAnimation("MH_Fall", "YoshiAndMario.png", 87, 89, 0.07f, false);
	YoshiRenderer->CreateAnimation("MH_StayUp", "YoshiAndMario.png", 90, 92, 0.07f);

	YoshiRenderer->CreateAnimation("MH_LookUpStart", "YoshiAndMario.png", 28, 29, 0.3f, false);
	YoshiRenderer->CreateAnimation("MH_LookUpEnd", "YoshiAndMario.png", 29, 28, 0.1f, false);

	YoshiRenderer->CreateAnimation("MH_BendStart", "YoshiAndMario.png", 38, 39, 0.05f, false);
	YoshiRenderer->CreateAnimation("MH_BendEnd", "YoshiAndMario.png", 39, 37, 0.04f, false);
	
	YoshiRenderer->CreateAnimation("MH_Eat", "YoshiAndMario.png", 30, 35, 0.07f, false);
	YoshiRenderer->CreateAnimation("MH_Spit", "YoshiAndMarioStick_Right.png", 0, 0, false);

	// Aim
	YoshiRenderer->CreateAnimation("MH_AimIdle", "YoshiAndMario.png", 144, 144, 0.028f, false);
	YoshiRenderer->CreateAnimation("MH_AimWalk", "YoshiAndMario.png", 144, 149, 0.08f);
	YoshiRenderer->CreateAnimation("MH_AimStayUp", "YoshiAndMario.png", 152, 153, 0.07f);
	
	// Attack
	YoshiRenderer->CreateAnimation("MH_Throw", "YoshiAndMario.png", {  149, 150, 153 }, 0.1f);
#pragma endregion

#pragma region Yoshi And NotHold
	YoshiRenderer->CreateAnimation("YNH_Idle0", "Yoshi(Not_Hold).png", 17, 10, 0.15f);
	YoshiRenderer->CreateAnimation("YNH_Idle1", "Yoshi(Not_Hold).png", { 27, 26, 25, 26, 25, 24 }, 0.2f);
	YoshiRenderer->CreateAnimation("YNH_Idle2", "Yoshi(Not_Hold).png", { 23, 22, 21, 20, 20, 20, 19, 18, 23 }, 0.15f);

	YoshiRenderer->CreateAnimation("YNH_Walk", "Yoshi(Not_Hold).png", 9, 0, 0.08f);
	YoshiRenderer->CreateAnimation("YNH_Run", "Yoshi(Not_Hold).png", 38, 37, 0.04f);

	YoshiRenderer->CreateAnimation("YNH_Jump", "Yoshi(Not_Hold).png", 30, 30, false);
	YoshiRenderer->CreateAnimation("YNH_Fall", "Yoshi(Not_Hold).png", 29, 28, 0.07f, false);
	YoshiRenderer->CreateAnimation("YNH_StayUp", "Yoshi(Not_Hold).png", 42, 40, 0.07f);

	YoshiRenderer->CreateAnimation("YNH_LookUpStart", "Yoshi(Not_Hold).png", 88, 88, false);

	YoshiRenderer->CreateAnimation("YNH_BendStart", "Yoshi(Not_Hold).png", 35, 34, 0.05f, false);
	YoshiRenderer->CreateAnimation("YNH_BendEnd", "Yoshi(Not_Hold).png", 34, 36, 0.04f, false);

	// Aim
	YoshiRenderer->CreateAnimation("YNH_AimIdle", "Yoshi(Not_Hold).png", 52, 52, false);
	YoshiRenderer->CreateAnimation("YNH_AimWalk", "Yoshi(Not_Hold).png", 52, 48);
	YoshiRenderer->CreateAnimation("YNH_AimStayUp", "Yoshi(Not_Hold).png", 55, 53, 0.07f);

	// Attack
	YoshiRenderer->CreateAnimation("YNH_Stick_RightStart", "YoshiStick_Right.png", 0, 5, 0.04f, false);
	YoshiRenderer->CreateAnimation("YNH_Stick_RightEnd", "YoshiStick_Right.png", 4, 0, 0.04f, false);

	YoshiRenderer->CreateAnimation("YNH_Stick_UpStart", "YoshiStick_Upper.png", 0, 5, 0.04f, false);
	YoshiRenderer->CreateAnimation("YNH_Stick_UpEnd", "YoshiStick_Upper.png", 4, 0, 0.04f, false);
	
	YoshiRenderer->CreateAnimation("YNH_Throw", "Yoshi(Not_Hold).png", 64, 60, 0.04f, false);

#pragma endregion

#pragma region Yoshi And Hold
	YoshiRenderer->CreateAnimation("YH_Idle0", "Yoshi(Hold).png", 16, 10, 0.15f);
	YoshiRenderer->CreateAnimation("YH_Idle1", "Yoshi(Hold).png", { 26, 25, 24, 25, 24, 23 }, 0.2f);
	YoshiRenderer->CreateAnimation("YH_Idle2", "Yoshi(Hold).png", { 22, 21, 20, 19, 19, 19, 18, 17 }, 0.15f);

	YoshiRenderer->CreateAnimation("YH_Walk", "Yoshi(Hold).png", { 4, 3, 2, 1, 0, 1, 2, 3 }, 0.08f);
	YoshiRenderer->CreateAnimation("YH_Run", "Yoshi(Hold).png", 37, 36, 0.04f);

	YoshiRenderer->CreateAnimation("YH_Jump", "Yoshi(Hold).png", 29, 29, false);
	YoshiRenderer->CreateAnimation("YH_Fall", "Yoshi(Hold).png", 28, 27, 0.07f, false);
	YoshiRenderer->CreateAnimation("YH_StayUp", "Yoshi(Hold).png", 41, 39, 0.07f);

	YoshiRenderer->CreateAnimation("YH_LookUpStart", "Yoshi(Hold).png", 64, 64, false);

	YoshiRenderer->CreateAnimation("YH_BendStart", "Yoshi(Hold).png", 34, 33, 0.05f, false);
	YoshiRenderer->CreateAnimation("YH_BendEnd", "Yoshi(Hold).png", 33, 34, 0.05f, false);
	
	YoshiRenderer->CreateAnimation("YH_Eat", "Yoshi(Hold).png", 35, 32, 0.05f, false);
	YoshiRenderer->CreateAnimation("YH_Spit", "YoshiStick_Right.png", 0, 0, false);

	// Aim
	YoshiRenderer->CreateAnimation("YH_AimIdle", "Yoshi(Hold).png", 51, 51, false);
	YoshiRenderer->CreateAnimation("YH_AimWalk", "Yoshi(Hold).png", 51, 47);
	YoshiRenderer->CreateAnimation("YH_AimStayUp", "Yoshi(Hold).png", 54, 52, 0.07f);

	// Attack
	YoshiRenderer->CreateAnimation("YH_Throw", "Yoshi(Hold).png", 63, 59, 0.04f);
#pragma endregion
}
void AYoshi::SetAnimDir()
{
	if (!IsAim)
	{
		if (UEngineInput::IsDown(VK_LEFT))
		{
			RootComponent->SetScale3D({ -1, 1, 1 });
		}
		else if (UEngineInput::IsDown(VK_RIGHT))
		{
			RootComponent->SetScale3D({ 1, 1, 1 });
		}
	}
}
int AYoshi::IdleAnimNum()
{
	UEngineRandom Random;
	int RandomValue = Random.RandomInt(0, 9);

	if (RandomValue == 0) { return 2; }
	else if (RandomValue == 1) { return 1; }
	else { return 0; }
}
void AYoshi::PlayIdleAnim()
{
	int AnimNum = IdleAnimNum();

	if (IsWithBaby && !IsHold)
	{
		YoshiRenderer->ChangeAnimation("MNH_Idle" + std::to_string(AnimNum));
	}
	else if (IsWithBaby && IsHold)
	{
		YoshiRenderer->ChangeAnimation("MH_Idle" + std::to_string(AnimNum));
	}
	else if (!IsWithBaby && !IsHold)
	{
		YoshiRenderer->ChangeAnimation("YNH_Idle" + std::to_string(AnimNum));
	}
}
#pragma endregion

#pragma region Pixel Collision Funcs
bool AYoshi::CheckPointColor(ECheckDir _Dir, UColor _Color)
{
	FVector NextPos = FVector::ZERO;
	FVector Scale = YoshiRenderer->GetTransformRef().Scale;
	UColor Color = UColor::WHITE;

	switch (_Dir)
	{
	case ECheckDir::LEFT:
		NextPos = GetActorLocation() + FVector::LEFT + FVector{ -Scale.X * 0.5f, 0.0f };
		Color = GetColor(NextPos);
		break;
	case ECheckDir::RIGHT:
		NextPos = GetActorLocation() + FVector::RIGHT + FVector{ Scale.X * 0.5f, 0.0f };
		Color = GetColor(NextPos);
		break;
	case ECheckDir::UP:
		NextPos = GetActorLocation() + FVector::UP + FVector{ 0.0f, Scale.Y * 1.0f };
		Color = GetColor(NextPos);
		break;
	case ECheckDir::DOWN:
		NextPos = GetActorLocation() + FVector::DOWN;
		Color = GetColor(NextPos);
		break;
	case ECheckDir::NONE:
		Color = GetColor(GetActorLocation());
		break;
	}

	bool Result = (_Color.operator==(Color)) ? true : false;
	return Result;
}
bool AYoshi::CheckLineColor(ECheckDir _Dir, UColor _Color)
{
	FVector NextStartPos = FVector::ZERO;
	FVector NextEndPos = FVector::ZERO;

	switch (_Dir)
	{
	case ECheckDir::LEFT:
		NextStartPos = GetActorLocation() + FVector{ YoshiScale.X * -0.5f, YoshiScale.Y };
		NextEndPos = GetActorLocation() + FVector{ YoshiScale.X * -0.5f, 0.0f };

		for (int y = static_cast<int>(NextEndPos.Y); y <= static_cast<int>(NextStartPos.Y); y++)
		{
			UColor NextColor = GetColor({ NextStartPos.X, static_cast<float>(y) });
			if (NextColor.operator==(_Color))
			{
				return true;
			}
		}
		break;

	case ECheckDir::RIGHT:
		NextStartPos = GetActorLocation() + FVector::RIGHT + FVector{ YoshiScale.X * 0.5f,  YoshiScale.Y };
		NextEndPos = GetActorLocation() + FVector::RIGHT + FVector{ YoshiScale.X * 0.5f, 0.0f };

		for (int y = static_cast<int>(NextEndPos.Y); y <= static_cast<int>(NextStartPos.Y); y++)
		{
			UColor NextColor = GetColor({ NextStartPos.X, static_cast<float>(y) });
			if (NextColor.operator==(_Color))
			{
				return true;
			}
		}
		break;

	case ECheckDir::UP:
		NextStartPos = GetActorLocation() + FVector::UP + FVector{ YoshiScale.X * -0.5f,  YoshiScale.Y };
		NextEndPos = GetActorLocation() + FVector::UP + FVector{ YoshiScale.X * 0.5f,  YoshiScale.Y };

		for (int x = static_cast<int>(NextStartPos.X); x <= static_cast<int>(NextEndPos.X); x++)
		{
			UColor NextColor = GetColor({ static_cast<float>(x), NextStartPos.Y });
			if (NextColor.operator==(_Color))
			{
				return true;
			}
		}
		break;

	case ECheckDir::DOWN:
		NextStartPos = GetActorLocation() + FVector::DOWN + FVector{ YoshiScale.X * -0.5f, 0.0f };
		NextEndPos = GetActorLocation() + FVector::DOWN + FVector{ YoshiScale.X * 0.5f, 0.0f };

		for (int x = static_cast<int>(NextStartPos.X); x <= static_cast<int>(NextEndPos.X); x++)
		{
			UColor NextColor = GetColor({ static_cast<float>(x), NextStartPos.Y });
			if (NextColor.operator==(_Color))
			{
				return true;
			}
		}
		break;

	case ECheckDir::NONE:
		NextStartPos = GetActorLocation();
		NextEndPos = GetActorLocation() + FVector{ 0.0f,  YoshiScale.Y * 0.5f };

		for (int y = static_cast<int>(NextStartPos.Y); y <= static_cast<int>(NextEndPos.Y); y++)
		{
			UColor NextColor = GetColor({ NextStartPos.X, static_cast<float>(y) });
			if (NextColor.operator==(_Color))
			{
				return true;
			}
		}
		break;
	}

	return false;
}
bool AYoshi::CheckForceColor(FVector _Force, UColor _Color)
{
	FVector NextPos = GetActorLocation() + _Force;
	UColor Color = GetColor(NextPos);

	if (Color.operator==(_Color))
	{
		return true;
	}

	return false;
}

bool AYoshi::IsSlope()
{
	for (int i = 0; i < 50; i++)
	{
		FVector NextPos = GetActorLocation() + FVector{ 0.0f, static_cast<float>(-i) };
		UColor Color = GetColor(NextPos);

		if (Color.operator==(UColor::MAGENTA) || Color.operator==(UColor::YELLOW) || Color.operator==(UColor::GREEN))
		{
			return false;
		}
		if (Color.operator==(UColor::CYAN))
		{
			return true;
		}
	}
	return false;
}

void AYoshi::MoveSlope(float _DeltaTime)
{
	if (IsSlope() && CheckLineColor(ECheckDir::NONE, UColor::CYAN))
	{
		AddActorLocation(FVector::UP * Speed * _DeltaTime);
		UEngineDebug::OutPutString("SlopeUp");
	}
	if (IsSlope() && !CheckPointColor(ECheckDir::DOWN, UColor::CYAN)
		&& CurState != EPlayerState::JUMP && CurState != EPlayerState::FALL)
	{
		AddActorLocation(FVector::DOWN * Speed * _DeltaTime);
		UEngineDebug::OutPutString("SlopeDown");
	}
}
#pragma endregion

#pragma region Collision Funcs
void AYoshi::SetCollision()
{
	HeadCollision = CreateDefaultSubObject<UCollision>();
	HeadCollision->SetupAttachment(RootComponent);
	HeadCollision->SetCollisionProfileName("HeadCollision");
	HeadCollision->SetScale3D({ YoshiScale.X * 0.8f, 8.0f });
	HeadCollision->SetRelativeLocation({ 0.0f, YoshiScale.Y - 5.0f });

	BodyCollision = CreateDefaultSubObject<UCollision>();
	BodyCollision->SetupAttachment(RootComponent);
	BodyCollision->SetCollisionProfileName("BodyCollision");
	BodyCollision->SetScale3D({ YoshiScale.X * 0.8f, YoshiScale.Y * 0.8f });
	BodyCollision->SetRelativeLocation({ 0.0f, YoshiScale.Y * 0.5f });

	FootCollision = CreateDefaultSubObject<UCollision>();
	FootCollision->SetupAttachment(RootComponent);
	FootCollision->SetCollisionProfileName("FootCollision");
	FootCollision->SetScale3D({ YoshiScale.X * 0.7f, 8.0f });
	FootCollision->SetRelativeLocation({ -4.0f, 5.0f });

	StickBodyCollision = CreateDefaultSubObject<UCollision>();
	StickBodyCollision->SetupAttachment(RootComponent);
	StickBodyCollision->SetCollisionProfileName("StickBodyCollision");
	StickBodyCollision->SetScale3D({ YoshiScale.X * 1.0f, YoshiScale.Y * 0.8f });
	StickBodyCollision->SetRelativeLocation({ YoshiScale.X * 0.6f, YoshiScale.Y * 0.4f });

	StickCollision = CreateDefaultSubObject<UCollision>();
	StickCollision->SetupAttachment(RootComponent);
	StickCollision->SetCollisionProfileName("StickCollision");

	HeadCollision->SetActive(false);
	StickBodyCollision->SetActive(false);
	StickCollision->SetActive(false);
}
void AYoshi::SetStickCollision()
{
	if (StickDir == 1)
	{
		switch (YoshiRenderer->GetCurIndex())
		{
		case 1:
			StickCollision->SetScale3D({ 8.0f, 50.0f });
			StickCollision->SetRelativeLocation({ YoshiScale.X * 0.3f, YoshiScale.Y * 0.8f});
			break;
		case 2:
			StickCollision->SetScale3D({ 8.0f, 75.0f });
			StickCollision->SetRelativeLocation({ YoshiScale.X * 0.3f, YoshiScale.Y * 0.9f });
			break;
		case 3:
			StickCollision->SetScale3D({ 8.0f, 100.0f });
			StickCollision->SetRelativeLocation({ YoshiScale.X * 0.3f, YoshiScale.Y * 1.0f });
			break;
		case 4:
			StickCollision->SetScale3D({ 8.0f, 125.0f });
			StickCollision->SetRelativeLocation({ YoshiScale.X * 0.3f, YoshiScale.Y * 1.15f });
			break;
		case 5:
			StickCollision->SetScale3D({ 8.0f, 150.0f });
			StickCollision->SetRelativeLocation({ YoshiScale.X * 0.3f, YoshiScale.Y * 1.25f });
			break;
		}
	}
	else if (StickDir == 2)
	{
		switch (YoshiRenderer->GetCurIndex())
		{
		case 1:
			StickCollision->SetScale3D({ 50.0f, 8.0f });
			StickCollision->SetRelativeLocation({ YoshiScale.X + 10.0f, YoshiScale.Y * 0.35f });
			break;
		case 2:
			StickCollision->SetScale3D({ 75.0f, 8.0f });
			StickCollision->SetRelativeLocation({ YoshiScale.X + 18.0f, YoshiScale.Y * 0.35f });
			break;
		case 3:
			StickCollision->SetScale3D({ 100.0f, 8.0f });
			StickCollision->SetRelativeLocation({ YoshiScale.X + 30.0f, YoshiScale.Y * 0.35f });
			break;
		case 4:
			StickCollision->SetScale3D({ 125.0f, 8.0f });
			StickCollision->SetRelativeLocation({ YoshiScale.X + 40.0f, YoshiScale.Y * 0.35f });
			break;
		case 5:
			StickCollision->SetScale3D({ 150.0f, 8.0f });
			StickCollision->SetRelativeLocation({ YoshiScale.X + 54.0f, YoshiScale.Y * 0.35f });
			break;
		}
	}
}
void AYoshi::SetCollisionsCheck()
{
	std::vector<UCollision*> MonsterBodys;
	if (StickCollision->CollisionCheck("MonsterBodyCollision", MonsterBodys))
	{
		IsHolding = true;

		if (StickDir == 1)
		{
			if ((IsWithBaby) && (!IsHold && !IsAim))	// M
			{
				int index = YoshiRenderer->GetCurIndex();
				YoshiRenderer->CreateAnimation("MNH_StickUpEnd", "YoshiAndMarioStick_Upper", index, 0, 0.04f, false);
				YoshiRenderer->ChangeAnimation("MNH_StickUpEnd");
			}
			else if ((!IsWithBaby) && (!IsHold && !IsAim)) // Y
			{
				YoshiRenderer->ChangeAnimation("YNH_Stick_UpStart");
			}

			IsHold = true;
			IsHolding = false;
			StickDir = 0;

			FootCollision->SetActive(true);
			StickCollision->SetActive(false);
			ChangeState(EPlayerState::IDLE);
			return;
		}
		else if (StickDir == 2)
		{
			if ((IsWithBaby) && (!IsHold && !IsAim))	// M
			{
				int index = YoshiRenderer->GetCurIndex();
				YoshiRenderer->CreateAnimation("MNH_StickRightEnd", "YoshiAndMarioStick_Right.png", index, 0, 0.04f, false);
				YoshiRenderer->ChangeAnimation("MNH_StickRightEnd");
			}
			else if ((!IsWithBaby) && (!IsHold && !IsAim)) // Y
			{
				YoshiRenderer->ChangeAnimation("YNH_Stick_RightStart");
			}

			IsHold = true;
			IsHolding = false;
			StickDir = 0;
			
			BodyCollision->SetActive(true);
			FootCollision->SetActive(true);
			
			StickBodyCollision->SetActive(false);
			StickCollision->SetActive(false);
			ChangeState(EPlayerState::IDLE);
			return;
		}
		MonsterBodys[0]->GetActor<AMonster>()->Destroy();
	}

	{
		if (nullptr == Platform)
		{
			std::vector<UCollision*> Platforms;
			if (FootCollision->CollisionCheck("PlatformCollision", Platforms)
				&& CurState == EPlayerState::FALL)
			{
				Platform = Platforms[0]->GetActor<APlatforms>();
				PlatformPos = GetActorLocation() - Platform->GetActorLocation();
				ChangeState(EPlayerState::IDLE);
				return;
			}
		}

		{
			std::vector<UCollision*> JumpBall;
			if (FootCollision->CollisionCheck("JumpBallCollision", JumpBall))
			{
				JumpPower = 550.0f * 1.4f;
			}

			std::vector<UCollision*> BigJumpBall;
			if (FootCollision->CollisionCheck("BigJumpBallCollision", BigJumpBall))
			{
				JumpPower = 550.0f * 2.4f;
			}
		}
	}
}
#pragma endregion

void AYoshi::SetCrossHair()
{
	CrossHair->SetActive(IsAim);

	if (!CrossHair->IsActive())
	{
		if (GetActorTransform().Scale.X < 0.0f)
		{
			CrossHair->SetMinAngle(90.0f);
			CrossHair->SetMaxAngle(200.0f);
			CrossHair->SetStartAngle(true);
		}
		else
		{
			CrossHair->SetMinAngle(340.0f);
			CrossHair->SetMaxAngle(450.0f);
			CrossHair->SetStartAngle(false);
		}
	}
}
void AYoshi::SpawnThrowEgg()
{
	std::shared_ptr<class AThrowEgg> Egg = GetWorld()->SpawnActor<AThrowEgg>();
	Egg->SetActorLocation(GetActorLocation());
	Egg->AddActorLocation({ 0.0f, YoshiScale.Y * 0.5f, -12.0f });
	Egg->SetThrowDir(CrossHair->GetCurAngle());
}