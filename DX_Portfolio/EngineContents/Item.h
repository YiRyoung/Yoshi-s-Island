#pragma once
#include <EngineCore/Actor.h>

#include "ContentsEnum.h"

// Ό³Έν :
class AItem : public AActor
{
public:
	// constrcuter destructer
	AItem();
	~AItem();

	// delete Function
	AItem(const AItem& _Other) = delete;
	AItem(AItem&& _Other) noexcept = delete;
	AItem& operator=(const AItem& _Other) = delete;
	AItem& operator=(AItem&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetItemRenderer() const
	{
		return Renderer;
	}

protected:

private:
	std::shared_ptr<class USpriteRenderer> Renderer;
};

