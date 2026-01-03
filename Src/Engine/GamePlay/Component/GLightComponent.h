#pragma once

#include "pre.h"
#include "GComponent.h"

#include <QVector3D>

namespace Lumin
{
	class ENGINE_API GLightComponent : public GComponent
	{
	public:
		GLightComponent(const std::string& name);
		~GLightComponent() override;
		void Tick(float deltaTime) override;
		void SetColor(float r, float g, float b);
		void SetColor(const QVector3D& color);
		QVector3D GetColor();
	private:
		QVector3D m_Color;
	};
}


