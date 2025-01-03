#pragma once

// Ό³Έν :
class UEngineShaderResources
{
public:
	// constrcuter destructer
	UEngineShaderResources();
	~UEngineShaderResources();

	// delete Function
	UEngineShaderResources(const UEngineShaderResources& _Other) = delete;
	UEngineShaderResources(UEngineShaderResources&& _Other) noexcept = delete;
	UEngineShaderResources& operator=(const UEngineShaderResources& _Other) = delete;
	UEngineShaderResources& operator=(UEngineShaderResources&& _Other) noexcept = delete;

protected:

private:

};

