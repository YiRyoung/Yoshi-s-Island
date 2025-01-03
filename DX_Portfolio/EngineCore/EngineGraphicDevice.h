#pragma once
#include <wrl.h>
#include <d3d11_4.h> // directx 11 버전4용 헤더
#include <d3dcompiler.h> // 쉐이더 컴파일러용 인터페이스
#include <EnginePlatform/EngineWindow.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "dxguid")

#pragma comment(lib, "DXGI") 

// 설명 :
class UEngineGraphicDevice
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineGraphicDevice();
	ENGINEAPI ~UEngineGraphicDevice();

	// delete Function
	UEngineGraphicDevice(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice(UEngineGraphicDevice&& _Other) noexcept = delete;
	UEngineGraphicDevice& operator=(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice& operator=(UEngineGraphicDevice&& _Other) noexcept = delete;

	void CreateDeviceAndContext();

	void CreateBackBuffer(const UEngineWindow& _Window);

	IDXGIAdapter* GetHighPerFormanceAdapter();

	ENGINEAPI void Release();

	void RenderStart();

	void RenderEnd();

	ENGINEAPI ID3D11Device* GetDevice()
	{
		return Device.Get();
	}

	ENGINEAPI ID3D11DeviceContext* GetContext()
	{
		return Context.Get();
	}

	ENGINEAPI ID3D11RenderTargetView* GetRTV()
	{
		return RTV.Get();
	}

protected:

private:
	Microsoft::WRL::ComPtr<ID3D11Device> Device = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> Context = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter> MainAdapter = nullptr;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> DXBackBufferTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RTV = nullptr;

	ENGINEAPI void DefaultResourcesInit();

	ENGINEAPI void MeshInit();
	ENGINEAPI void BlendInit();
	ENGINEAPI void ShaderInit();
};

