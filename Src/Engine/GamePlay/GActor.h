#pragma once
#include <memory>
#include <vector>
#include <QVector3D>

#include "GObject.h"

namespace Lumin
{
	struct LTransform
	{
		QVector3D position = QVector3D(0, 0, 0);
		QVector3D rotation = QVector3D(0, 0, 0);
		QVector3D scale = QVector3D(1, 1, 1);
	};

	class GActor : public GObject
	{
	public:
		virtual void Tick(float deltaTime);
		void SetName(const std::string& name);
		std::string GetName();
		void SetParent(GActor* parent);
		GActor* GetParent();
		void SetPosition(const QVector3D& position);
		QVector3D GetPosition();
		void SetRotation(const QVector3D& rotation);
		QVector3D GetRotation();
		void SetScale(const QVector3D& scale);
		QVector3D GetScale();
		QMatrix4x4 GetLocalTransform(); // Transformation relative to the coordinate system of the parent node
		QMatrix4x4 GetWorldTransform(); // Transformation relative to the world coordinate system
		bool GetIsAlive();
		void MarkNextFrameDestruction();
	protected:
		LTransform m_transform;
	private:
		GActor* m_parent = nullptr;
		std::vector<std::unique_ptr<GActor>> m_children;
		bool m_isAlive = true;
		friend class GLevel;
	};
}

