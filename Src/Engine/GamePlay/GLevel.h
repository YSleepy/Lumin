#pragma once
#include <memory>
#include <vector>

#include "GActor.h"
#include "GObject.h"
#include "GameMode/GGameModeBase.h"

namespace Lumin
{
	class GLevel : public GObject
	{
	public:
		GLevel();
		void Tick(float deltaTime);
		void Clear();
		bool SetActorParent(GActor* actor, GActor* parent);

		GGameModeBase* GetGameMode() const;
		void SetDefaultActor(GActor* actor);
		GActor* CreateActor(const std::string& name, GActor* parent = nullptr);

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<GActor, T>>>
		T* CreateActor(std::string name, GActor* parent = nullptr)
		{
			T* actor = new T();
			actor->SetName(name);
			actor->SetParent(parent);
			if (parent == nullptr)
			{
				m_actors.push_back(std::unique_ptr<GActor>(actor));
			}
			return actor;
		}

		
	private:
		//GLevel() = default;
		std::unique_ptr<GGameModeBase> m_gameMode;
		std::vector<std::unique_ptr<GActor>> m_actors;
		friend class GWorld;
	};
}
