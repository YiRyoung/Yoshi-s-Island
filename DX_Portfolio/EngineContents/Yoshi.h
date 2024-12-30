#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AYoshi : public AActor
{
public:
	// constrcuter destructer
	AYoshi();
	~AYoshi();

	// delete Function
	AYoshi(const AYoshi& _Other) = delete;
	AYoshi(AYoshi&& _Other) noexcept = delete;
	AYoshi& operator=(const AYoshi& _Other) = delete;
	AYoshi& operator=(AYoshi&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetYoshiRenderer() const
	{
		return YoshiRenderer;
	}

protected:

private:
	std::shared_ptr<class USpriteRenderer> YoshiRenderer;
};

