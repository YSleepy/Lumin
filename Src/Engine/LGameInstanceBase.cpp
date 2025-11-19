#include "LGameInstanceBase.h"

namespace Lumin
{
	void LGameInstanceBase::SetNeedToBeClosed(bool value)
	{
		m_needToBeClosed = value;
	}

	bool LGameInstanceBase::IsNeedToBeClosed() const
	{
		return m_needToBeClosed;
	}
}
