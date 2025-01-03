#include "PreCompile.h"
#include "Vertex.h"

UEngineInputLayOutInfo PolygonVertex::Info = {};

class VertexInit
{
public:
	VertexInit()
	{
		PolygonVertex::Info.AddInputLayout("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	}
};

VertexInit InitData = {};
