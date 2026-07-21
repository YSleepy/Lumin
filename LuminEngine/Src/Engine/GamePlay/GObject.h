#pragma once
#include <string>
#include "pre.h"

namespace Lumin
{
	class ENGINE_API GObject
	{
	public:
		GObject();
		virtual ~GObject();
		uint32_t MakeObjectId();
	protected:
		uint32_t m_objectId;
		std::string m_objectName;
	};
}
