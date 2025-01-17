#pragma once

// Ό³Έν :
class Stage101GameMode
{
public:
	// constrcuter destructer
	Stage101GameMode();
	~Stage101GameMode();

	// delete Function
	Stage101GameMode(const Stage101GameMode& _Other) = delete;
	Stage101GameMode(Stage101GameMode&& _Other) noexcept = delete;
	Stage101GameMode& operator=(const Stage101GameMode& _Other) = delete;
	Stage101GameMode& operator=(Stage101GameMode&& _Other) noexcept = delete;

protected:

private:

};

