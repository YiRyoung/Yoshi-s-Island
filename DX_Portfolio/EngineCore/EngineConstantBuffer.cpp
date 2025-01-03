#include "PreCompile.h"
#include "EngineConstantBuffer.h"

std::map<int, std::map<std::string, std::shared_ptr<UEngineConstantBuffer>>> UEngineConstantBuffer::BufferMap;

UEngineConstantBuffer::UEngineConstantBuffer()
{
}

UEngineConstantBuffer::~UEngineConstantBuffer()
{
}

std::shared_ptr<UEngineConstantBuffer> UEngineConstantBuffer::CreateOrFind(int _Byte, const std::string_view& _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (true == BufferMap.contains(_Byte))
	{
		if (true == BufferMap[_Byte].contains(UpperName))
		{
			return BufferMap[_Byte][UpperName];
		}
	}

	std::shared_ptr<UEngineConstantBuffer> NewRes = std::make_shared<UEngineConstantBuffer>();
	NewRes->ResCreate();
	BufferMap[_Byte][UpperName] = NewRes;

	return nullptr;
}

void UEngineConstantBuffer::ResCreate()
{
}
