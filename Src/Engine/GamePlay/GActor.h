#pragma once
#include <memory>
#include <vector>
#include <QVector3D>
#include <QQuaternion>

#include "Component/GComponent.h"
#include "GObject.h"
#include "pre.h"

namespace Lumin
{
	struct ENGINE_API LTransform
	{
		QVector3D position = QVector3D(0, 0, 0);
		QQuaternion rotation = QQuaternion(1, 0, 0, 0);
		QVector3D scale = QVector3D(1, 1, 1);
	};

	class ENGINE_API GActor : public GObject
	{
	public:
		GActor() = default;
		virtual ~GActor() = default;
		GActor(const GActor&) = delete;
		GActor& operator=(const GActor&) = delete;
		GActor(GActor&&) noexcept = default;
		GActor& operator=(GActor&&) noexcept = default;

		virtual void Tick(float deltaTime);
		void SetName(const std::string& name);
		std::string GetName();
		void SetParent(GActor* parent);
		GActor* GetParent();
		void SetPosition(const QVector3D& position);
		QVector3D GetPosition();
		void SetRotation(const QQuaternion& rotation);
		QQuaternion GetRotation();
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

