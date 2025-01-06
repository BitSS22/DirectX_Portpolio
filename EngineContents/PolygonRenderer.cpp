#include "PreCompile.h"
#include "PolygonRenderer.h"

UPolygonRenderer::UPolygonRenderer()
{
	CreateRenderUnit();
	SetMesh("Polygon");
	SetMaterial("Polygon");

	mColor.ColorFirst = float4(1.0f, 1.0f, 1.0f, 1.0f);

	GetRenderUnit().ConstantBufferLinkData("Color", mColor);
}

UPolygonRenderer::~UPolygonRenderer()
{
}
