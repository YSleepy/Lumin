#include "LGltfUtils.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

#include "FileSystem/LFileSystem.h"

namespace Lumin
{
	void LGltfUtils::LoadGltfFile(const char* aFilePath)
	{
		tinygltf::Node rootNode;
		tinygltf::Model model;
		std::string rPath = LFileSystem::GetEngineAssetsPath() + aFilePath;
		tinygltf::TinyGLTF loader;
		std::string err;
		std::string warn;
		bool ok = loader.LoadASCIIFromFile(&model, &err, &warn, rPath);
		if (!ok)
		{
		}
		for (auto& scene : model.scenes)
		{
			for (auto& node : scene.nodes)
			{
				//if (model.nodes[node].)
			}
		}

	}
}

