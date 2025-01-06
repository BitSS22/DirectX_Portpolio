#pragma once
#include <EngineCore/Renderer.h>

struct Color
{
public:
	float4 ColorFirst;
	float4 ColorSecond;
	float4 ColorThird;
};

class UPolygonRenderer : public URenderer
{
public:
	UPolygonRenderer();
	~UPolygonRenderer();

	UPolygonRenderer(const UPolygonRenderer& _Other) = delete;
	UPolygonRenderer(UPolygonRenderer&& _Other) noexcept = delete;
	UPolygonRenderer& operator=(const UPolygonRenderer& _Other) = delete;
	UPolygonRenderer& operator=(UPolygonRenderer&& _Other) noexcept = delete;

private:
	Color mColor = {};

public:

private:

public:

};

