#include "PreCompile.h"
#include "Stage.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"
#include "Yoshi.h"

AStage::AStage()
{
}

AStage::~AStage()
{
}

void AStage::SetColImage(int _StageCode)
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image");
		std::string Name = "ColStage" + _StageCode;
		UEngineFile ImageFiles = Dir.GetFile(Name + ".png");

		ColImage.Load(nullptr, ImageFiles.GetPathToString());
	}

	AYoshi* Player = dynamic_cast<AYoshi*>(GetWorld()->GetMainPawn());
	Player->SetColImage(&ColImage);
}

void AStage::SwitchColStage()
{
	ColStageRenderer->SetActive(ColStageRenderer->IsActive());
}

UColor AStage::GetPixelColor(FVector _Pos)
{
	return ColImage.GetColor(_Pos, UColor{ 255, 255, 255, 255 });
}

void AStage::SetRenderer(int _OrderNum, std::string _StageName, int _FileIndex)
{
	std::shared_ptr<USpriteRenderer> Renderer;
	EOrderNum OrderNum;

	switch (_OrderNum)
	{
	case 0:
		Renderer = BackgroundRenderer;
		OrderNum = EOrderNum::BACKGROUND;
		break;
	case 1:
		Renderer = ForeBackgroundRenderer;
		OrderNum = EOrderNum::FOREBACKGROUND;
		break;
	case 2:
		Renderer = StageRenderer;
		OrderNum = EOrderNum::STAGE;
		break;
	case 4:
		Renderer = ObstacleRenderer;
		OrderNum = EOrderNum::OBSTACLE;
		break;
	case 5:
		Renderer = FrontBackgroundRenderer;
		OrderNum = EOrderNum::FRONTBACKGROUND;
		break;
	}

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetSprite(_StageName, _FileIndex);
	Renderer->SetAutoScaleRatio(3.0f);
	FVector Scale = (Renderer->GetSprite()->GetTexture()->GetTextureSize()) * Renderer->GetAutoScaleRatio();
	Renderer->SetRelativeLocation({ 0.0f, (Scale.Y * -0.5f), static_cast<float>(OrderNum) });
}

void AStage::StageRes()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Stage100");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Stage100/Stage100(Layer3)");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}
}

void AStage::StageInit()
{
}

void AStage::CameraBoundary()
{
	/*Camera->SetActorLocation({ GetWorld()->GetMainPawn()->GetActorLocation().X, GetWorld()->GetMainPawn()->GetActorLocation().Y, -520.0f });

	FVector ResultCameraPos = { 0.0f, 0.0f, 0.0f };
	FVector ScreenSize = UEngineCore::GetScreenScale();
	FVector MapSize = Stage->GetMapScale();
	FVector CameraPos = Camera->GetActorLocation();

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
		ResultCameraPos.X = GetWorld()->GetMainPawn()->GetActorLocation().X;
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
		ResultCameraPos.Y = GetWorld()->GetMainPawn()->GetActorLocation().Y;
	}

	Camera->SetActorLocation({ ResultCameraPos.X, ResultCameraPos.Y + 100.0f, -520.0f });*/
}

