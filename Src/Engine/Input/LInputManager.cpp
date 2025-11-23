#include "LInputManager.h"

#include "LLog.h"
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
}
