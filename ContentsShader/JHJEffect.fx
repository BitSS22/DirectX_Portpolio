#include <../EngineShader/RenderBaseData.hlsli>

struct FEngineVertex
{
	float4 POSITION : POSITION;
	float4 UV : TEXCOORD;
};

struct VertexShaderOutPut
{
	float4 SVPOSITION : SV_POSITION; // 뷰포트행렬이 곱해지는 포지션입니다.
	float4 UV : TEXCOORD; // 
};

cbuffer MyData : register(b9)
{
	float4 ScreenScale;
};



// 버텍스쉐이더를 다 만들었다.
VertexShaderOutPut JHJEffect_VS(FEngineVertex _Vertex)
{
	VertexShaderOutPut OutPut;
	OutPut.SVPOSITION = _Vertex.POSITION;
	OutPut.UV = _Vertex.UV ;
	
	return OutPut;
}


Texture2D ImageTexture : register(t1);
SamplerState ImageSampler : register(s1);

// 이미지를 샘플링해서 이미지를 보이게 만들고
float4 JHJEffect_PS(VertexShaderOutPut _Vertex) : SV_Target0
{
    float2 PixelOffset = { 1.f / 1280.f, 1.f / 720.f };
    float4 PixelColor = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
    float4 Color = PixelColor;
	
    if (PixelColor.a != 1.f)
    {
        for (int y = -2; y <= 2; ++y)
        {
            for (int x = -2; x <= 2; ++x)
            {
                float4 xyColor = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy + float2(PixelOffset.x * x, PixelOffset.y * y));
                
                if (xyColor.a >= 0.9f)
                {
                    Color = float4(1.f, 0.f, 0.f, 1.f);
                    break;
                }
            }
        }
    }
	else
    {
        Color = PixelColor;
    }
	
    return Color;
};
