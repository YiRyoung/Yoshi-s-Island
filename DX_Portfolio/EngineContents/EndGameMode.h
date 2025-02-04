#pragma once

// Ό³Έν :
class EndGameMode
{
public:
	// constrcuter destructer
	EndGameMode();
	~EndGameMode();

	// delete Function
	EndGameMode(const EndGameMode& _Other) = delete;
	EndGameMode(EndGameMode&& _Other) noexcept = delete;
	EndGameMode& operator=(const EndGameMode& _Other) = delete;
	EndGameMode& operator=(EndGameMode&& _Other) noexcept = delete;

protected:

private:

};

