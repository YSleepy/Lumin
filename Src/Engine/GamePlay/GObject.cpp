#include "GObject.h"

namespace Lumin
{
	GObject::GObject()
	{
		m_objectId = MakeObjectId();
	}

	uint32_t GObject::MakeObjectId()
	{
		static uint32_t sNextObjectId = 1;
		return sNextObjectId++;
	}

}

