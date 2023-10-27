#pragma once

#include "Hazel/Renderer/Texture.h"

#include <filesystem>
#include "FileWatch.h"

namespace Hazel {

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path m_BaseDirectory;
		std::filesystem::path m_CurrentDirectory;
		
		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
		std::unordered_map<std::string, Ref<Texture2D>> m_TextureIcons;

		Scope<filewatch::FileWatch<std::string>> m_ContentBrowserFileWatcher;
	};

}
