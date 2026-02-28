#pragma once
#include <QMatrix4x4>

namespace Lumin
{
	struct ENGINE_API LTransform
	{
		QVector3D position = QVector3D(0, 0, 0);
		QQuaternion rotation = QQuaternion(1, 0, 0, 0);
		QVector3D scale = QVector3D(1, 1, 1);
	};

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
