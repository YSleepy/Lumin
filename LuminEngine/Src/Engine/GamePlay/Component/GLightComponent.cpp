#include "GLightComponent.h"


namespace Lumin
{
	GLightComponent::GLightComponent(const std::string& name) : GComponent(name)
	{
	}

	GLightComponent::~GLightComponent()
	{
	}

	void GLightComponent::Tick(float deltaTime)
	{
	}

	void GLightComponent::SetColor(float r, float g, float b)
	{
		m_Color = QVector3D(r, g, b);
	}

	void GLightComponent::SetColor(const QVector3D& color)
	{
		m_Color = color;
	}

	QVector3D GLightComponent::GetColor()
	{
		return m_Color;
	}
}

