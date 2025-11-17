#include "LApplication.h"

namespace Lumin
{
	void LApplication::SetNeedToBeClosed(bool value)
	{
		m_needToBeClosed = value;
	}

	bool LApplication::IsNeedToBeClosed() const
	{
		return m_needToBeClosed;
	}
}
