#pragma once

// Ό³Έν :
class UEngineCamera
{
public:
	// constrcuter destructer
	UEngineCamera();
	~UEngineCamera();

	// delete Function
	UEngineCamera(const UEngineCamera& _Other) = delete;
	UEngineCamera(UEngineCamera&& _Other) noexcept = delete;
	UEngineCamera& operator=(const UEngineCamera& _Other) = delete;
	UEngineCamera& operator=(UEngineCamera&& _Other) noexcept = delete;

protected:

private:

};

