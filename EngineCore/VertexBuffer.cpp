#include "PreCompile.h"
#include "VertexBuffer.h"

UVertexBuffer::UVertexBuffer()
{
}

UVertexBuffer::~UVertexBuffer()
{
}

std::shared_ptr<UVertexBuffer> UVertexBuffer::Create(std::string_view _Name, const void* _InitData, size_t _VertexSize, size_t _VertexCount)
{
	std::string UpperName = ToUpperName(_Name);

	if (true == Contains(UpperName))
	{
		MSGASSERT("이미 로드한 텍스처를 도 로드하려고 했습니다." + UpperName);
		return nullptr;
	}

	std::shared_ptr<UVertexBuffer> NewRes = std::make_shared<UVertexBuffer>();
	PushRes<UVertexBuffer>(NewRes, _Name, "");
	NewRes->ResCreate(_InitData, _VertexSize, _VertexCount);

	return NewRes;
}

void UVertexBuffer::ResCreate(const void* _InitData, size_t _VertexSize, size_t _VertexCount)
{
	VertexCount = static_cast<UINT>(_VertexCount);
	VertexSize = static_cast<UINT>(_VertexSize);
	BufferInfo.ByteWidth = static_cast<UINT>(_VertexSize * _VertexCount);
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA Data; // 초기값 넣어주는 용도의 구조체
	Data.pSysMem = _InitData;

	if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateBuffer(&BufferInfo, &Data, &VertexBuffer))
	{
		MSGASSERT("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void UVertexBuffer::Setting()
{
	// UINT VertexSize = sizeof(EngineVertex);
	// 이 버텍스 버퍼가 10개짜리인데 3번째 버텍스 부터 세팅해줘.
	UINT Offset = 0;
	ID3D11Buffer* ArrBuffer[1];
	ArrBuffer[0] = VertexBuffer.Get();
	UEngineCore::GetDevice().GetContext()->IASetVertexBuffers(0, 1, ArrBuffer, &VertexSize, &Offset);
	
}