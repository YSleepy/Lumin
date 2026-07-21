#include "LInputManager.h"

#include "LLog.h"
#include "QDebug"

namespace Lumin
{
	void LInputManager::SetKeyPressed(int key, bool pressed)
	{
		CHECK_CONDITION_RETURN(key >= 0 && key < MAX_KEYS, "Invalid key");
		m_keys[key] = pressed;
	}

	bool LInputManager::IsKeyPressed(int key)
	{
		CHECK_CONDITION_RETURN_VALUE(key >= 0 && key < MAX_KEYS, false, "Invalid key");
		return m_keys[key];
	}

	void LInputManager::SetButton(uint32_t button, bool pressed)
	{
		if (pressed)
		{
			m_mouseButtons |= button;
		}
		else
		{
			m_mouseButtons &= ~button;
		}
	}

	bool LInputManager::IsButtonPressed(uint32_t button) const
	{
		return (m_mouseButtons & button) != 0;
	}

	bool LInputManager::AreButtonsPressed(uint32_t buttons) const
	{
		return (m_mouseButtons & buttons) == buttons;
	}

	bool LInputManager::AnyButtonPressed() const
	{
		return m_mouseButtons != 0;
	}

	uint32_t LInputManager::GetPressedButtons() const
	{
		return m_mouseButtons;
	}

	void LInputManager::SetMouseOldPos(const QVector2D& pos)
	{
		m_mouseOldPos = pos;
	}

	const QVector2D& LInputManager::GetMouseOldPos() const
	{
		return m_mouseOldPos;
	}

	void LInputManager::SetMouseNewPos(const QVector2D& pos)
	{
		m_mouseNewPos = pos;
	}

	const QVector2D& LInputManager::GetMouseNewPos() const
	{
		return m_mouseNewPos;
	}
}
