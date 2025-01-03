#pragma once
#include "EngineEnums.h"
#include <EngineBase/EngineFile.h>

// 설명 :
class UEngineShader
{
	friend class UEngineVertexShader;

public:
	// constrcuter destructer
	UEngineShader();
	~UEngineShader();

	// delete Function
	UEngineShader(const UEngineShader& _Other) = delete;
	UEngineShader(UEngineShader&& _Other) noexcept = delete;
	UEngineShader& operator=(const UEngineShader& _Other) = delete;
	UEngineShader& operator=(UEngineShader&& _Other) noexcept = delete;

	static void ReflectionCompile(UEngineFile& _File);

protected:
	UINT VersionHigh = 5;
	UINT VersionLow = 0;
	Microsoft::WRL::ComPtr<ID3DBlob> ShaderCodeBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> ErrorCodeBlob = nullptr; // 중간 컴파일 결과물
	std::string EntryName;

	void ShaderResCheck();
private:

};

