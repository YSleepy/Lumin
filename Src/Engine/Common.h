#pragma once
#include <QMatrix4x4>

namespace Lumin
{
	struct ENGINE_API CameraInfo
	{
		QMatrix4x4 ViewMatrix;
		QMatrix4x4 ProjectionMatrix;
	};
	struct ENGINE_API LightInfo
	{
		QVector3D Position;
		QVector3D Color;
	};
}
