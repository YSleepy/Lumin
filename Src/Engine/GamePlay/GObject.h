#pragma once
#include <string>

namespace Lumin
{
	class GObject
	{
	public:
		GObject();
		uint32_t MakeObjectId();
	protected:
		uint32_t m_objectId;
		std::string m_objectName;
	};
}
