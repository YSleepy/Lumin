#pragma once
#include <array>

namespace Lumin
{
	constexpr int MAX_KEYS = 256;
	class LInputManager
	{
	public:
		void SetKeyPressed(int key, bool pressed);
		bool IsKeyPressed(int key);
	private:
		LInputManager() = default;
		LInputManager(const LInputManager&) = delete;
		LInputManager(LInputManager&&) = delete;
		LInputManager& operator=(const LInputManager&) = delete;
		LInputManager& operator=(LInputManager&&) = delete;
		friend class LEngine;
		bool m_keys[MAX_KEYS]{ false };
	};
}


