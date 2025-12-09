#pragma once
#include <memory>
#include <vector>
#include <QVector3D>

#include "Component/GComponent.h"
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
		void AddCommponent(GComponent* component);
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<GComponent, T>>>
		T* GetComponentByName() {
			for (auto& component : m_components) {
				if (T* res = dynamic_cast<T*>(component.get())) {
					return res;
				}

			}
			return nullptr;
		}
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<GComponent, T>>>
		T* GetComponentByName(const std::string& name) {
			for (auto& component : m_components) {
				if (component && component->GetName() == name) {
					if (T* res = dynamic_cast<T*>(component.get())) {
						return res;
					}
				}
			}
			return nullptr;
		}
	protected:
		LTransform m_transform;
		std::vector<std::unique_ptr<GComponent>> m_components;
		std::vector<std::unique_ptr<GActor>> m_children;
	private:
		GActor* m_parent = nullptr;
		bool m_isAlive = true;
		friend class GLevel;
	};
}

