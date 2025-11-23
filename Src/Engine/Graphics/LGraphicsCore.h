#pragma once

#include <memory>

#include "LShader.h"

namespace Lumin
{
	class LGraphicsCore
	{
	public:
		std::shared_ptr<LShader> CreateShader(const char* vertexShader, const char* fragmentShader);
	};

}

