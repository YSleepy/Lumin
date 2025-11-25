#pragma once
#include "LMaterial.h"
#include "LMesh.h"

namespace Lumin
{
	class LMeshSceneComponent
	{
	public:
		LMesh* m_mesh;
		LMaterial* m_material;
	};

}

