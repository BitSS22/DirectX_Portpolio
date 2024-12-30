#pragma once
#include <EngineCore/Renderer.h>

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

public:

private:

public:

};

