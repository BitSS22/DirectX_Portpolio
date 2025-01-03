#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineCore/EngineInputLayOutInfo.h>

struct PolygonVertex
{
public:
	static UEngineInputLayOutInfo Info;

	float4 POSITION;
};

struct Color
{
public:
	float4 ColorFirst;
	float4 ColorSecond;
	float4 ColorThird;
};