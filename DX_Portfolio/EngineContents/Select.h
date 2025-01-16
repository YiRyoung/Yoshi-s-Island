#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ASelect : public AActor
{
public:
	// constrcuter destructer
	ASelect();
	~ASelect();

	// delete Function
	ASelect(const ASelect& _Other) = delete;
	ASelect(ASelect&& _Other) noexcept = delete;
	ASelect& operator=(const ASelect& _Other) = delete;
	ASelect& operator=(ASelect&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class ACameraActor> Camera;
	
	std::shared_ptr<class USpriteRenderer> BackgroundRenderer;
	std::shared_ptr<class USpriteRenderer> MapRenderer;
	std::shared_ptr<class USpriteRenderer> StageRenderer;
	
	std::shared_ptr<class USpriteRenderer> Stage100IconRenderer;
	std::shared_ptr<class USpriteRenderer> Stage200IconRenderer;

	std::shared_ptr<class USpriteRenderer> Stage100YoshiRenderer;
	std::shared_ptr<class USpriteRenderer> Stage200YoshiRenderer;

	void SelectRes();
	void SelectInit();
};

