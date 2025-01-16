#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ATitle : public AActor
{
public:
	// constrcuter destructer
	ATitle();
	~ATitle();

	// delete Function
	ATitle(const ATitle& _Other) = delete;
	ATitle(ATitle&& _Other) noexcept = delete;
	ATitle& operator=(const ATitle& _Other) = delete;
	ATitle& operator=(ATitle&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetRenderer() const
	{
		return BackgroundRenderer;
	}

	bool IsEnd() const
	{
		bool Result = (EndAnimIndex != -1) ? true : false;
		return Result;
	}

	void EndAnimation(int _StartIndex);

protected:

private:
	std::shared_ptr<class ACameraActor> Camera;
	std::shared_ptr<class USpriteRenderer> BackgroundRenderer;
	std::shared_ptr<class USpriteRenderer> LogoRenderer;

	int EndAnimIndex = -1;

	void TitleRes();
	void TitleInit();
};

