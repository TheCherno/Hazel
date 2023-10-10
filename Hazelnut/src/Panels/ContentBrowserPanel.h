#pragma once

#include "Hazel/Renderer/Texture.h"

#include "ThumbnailCache.h"

#include <map>
#include <set>
#include <filesystem>

namespace Hazel {

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel(Ref<Project> project);

		void OnImGuiRender();
	private:
		void RefreshAssetTree();
	private:
		Ref<Project> m_Project;
		Ref<ThumbnailCache> m_ThumbnailCache;

		std::filesystem::path m_BaseDirectory;
		std::filesystem::path m_CurrentDirectory;
		
		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;

		struct TreeNode
		{
			std::filesystem::path Path;
			AssetHandle Handle = 0;
			
			uint32_t Parent = (uint32_t)-1;
			std::map<std::filesystem::path, uint32_t> Children;

			TreeNode(const std::filesystem::path& path, AssetHandle handle)
				: Path(path), Handle(handle) {}
		};
				
		std::vector<TreeNode> m_TreeNodes;

		std::map<std::filesystem::path, std::vector<std::filesystem::path>> m_AssetTree;

		enum class Mode
		{
			Asset = 0, FileSystem = 1
		};

		Mode m_Mode = Mode::Asset;
	};

}
