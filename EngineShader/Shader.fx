struct PolygonVertex
{
    float4 POSITION : POSITION;
    float4 COLOR : COLOR;
};

struct PolygonShaderOutPut
{
    float4 SVPOSITION : SV_POSITION;
    float4 COLOR : COLOR;
};

cbuffer FTransform : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Qut;
    float4 Location;
    
    float4 RelativeScale;
    float4 RelativeRotation;
    float4 RelativeQut;
    float4 RelativeLocation;
    
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuat;
    float4 WorldLocation;

    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 LocationMat;
    float4x4 RevolveMat;
    float4x4 ParentMat;
    float4x4 LocalWorld;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};

cbuffer Color : register(b1)
{
    float4 ColorFirst;
    float4 ColorSecond;
    float4 ColorThird;
};

PolygonShaderOutPut VertexToWorld_VS(PolygonVertex _Vertex)
{
    PolygonShaderOutPut OutPut;
	
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
    OutPut.COLOR = _Vertex.COLOR;
    
    return OutPut;
}

float4 Pixel_PS(PolygonShaderOutPut _Vertex) : SV_Target0
{
    return _Vertex.COLOR;
};
