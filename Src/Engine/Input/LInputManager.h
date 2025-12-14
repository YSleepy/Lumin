#pragma once
#include <array>
#include <Qt>
#include <QVector2D>

namespace Lumin
{
	constexpr int MAX_KEYS = 256;
	constexpr int MAX_MOUSE_BUTTONS = UINT32_MAX;
	class LInputManager
	{
	public:
		void SetKeyPressed(int key, bool pressed);
		bool IsKeyPressed(int key);
		void SetButton(uint32_t button, bool pressed);
		bool IsButtonPressed(uint32_t button) const;
		bool AreButtonsPressed(uint32_t buttons) const;
		bool AnyButtonPressed() const;
		uint32_t GetPressedButtons() const;
		void SetMouseOldPos(const QVector2D& pos);
		const QVector2D& GetMouseOldPos() const;
		void SetMouseNewPos(const QVector2D& pos);
		const QVector2D& GetMouseNewPos() const;

	private:
		LInputManager() = default;
		LInputManager(const LInputManager&) = delete;
		LInputManager(LInputManager&&) = delete;
		LInputManager& operator=(const LInputManager&) = delete;
		LInputManager& operator=(LInputManager&&) = delete;
		friend class LEngine;
		bool m_keys[MAX_KEYS]{ false };
		uint32_t m_mouseButtons = 0;
		QVector2D m_mouseOldPos;
		QVector2D m_mouseNewPos;
	};
}


