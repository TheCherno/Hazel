#include "hzpch.h"
#include "ContentBrowserPanel.h"

#include <imgui/imgui.h>
#include "Hazel/Core/Application.h"

namespace Hazel {

	namespace Utils {

		static bool IsImageFile(const std::filesystem::path& path)
		{
			if (path.extension() == ".png" || path.extension() == ".jpg")
				return true;

			return false;
		}

	}

	// Once we have projects, change this
	extern const std::filesystem::path g_AssetPath = "assets";

	ContentBrowserPanel::ContentBrowserPanel()
		: m_CurrentDirectory(g_AssetPath)
	{
		m_DirectoryIcon = Texture2D::Create("Resources/Icons/ContentBrowser/DirectoryIcon.png");
		m_FileIcon = Texture2D::Create("Resources/Icons/ContentBrowser/FileIcon.png");

		auto FileAssetEvent = [this](const std::string& filepath, const filewatch::Event change_type)
		{
			switch (change_type)
			{
			case filewatch::Event::added:
			{
				Application::Get().SubmitToMainThread([this, filepath]()
				{
					if (Utils::IsImageFile(filepath))
					{
						std::filesystem::path texturePath = filepath;
						texturePath = g_AssetPath / filepath;

						m_TextureIcons[texturePath.string()] = Texture2D::Create(texturePath.string());
						HZ_WARN("{}: File Added", texturePath.string());
					}
				});

				break;
			}
			case filewatch::Event::removed:
			{
				Application::Get().SubmitToMainThread([this, filepath]()
				{
					std::filesystem::path texturePath = filepath;
					texturePath = g_AssetPath / filepath;

					m_TextureIcons.erase(texturePath.string());
					HZ_WARN("{}: File Deleted", texturePath.string());
				});

				break;
			}
			}
		};

		m_ContentBrowserFileWatcher = CreateScope<filewatch::FileWatch<std::string>>(g_AssetPath.string(), FileAssetEvent);

		// Loading Textures
		for (auto& directoryEntry : std::filesystem::recursive_directory_iterator(g_AssetPath))
		{
			const auto& path = directoryEntry.path();
			const auto& filenameString = path.string();

			if (Utils::IsImageFile(path))
				m_TextureIcons[filenameString] = Texture2D::Create(filenameString);
		}
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser");

		if (m_CurrentDirectory != std::filesystem::path(g_AssetPath))
		{
			if (ImGui::Button("Back"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		static float padding = 16.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();
			std::string filenameString = path.filename().string();
			
			ImGui::PushID(filenameString.c_str());
			Ref<Texture2D> icon = nullptr;

			if (Utils::IsImageFile(path))
				icon = m_TextureIcons[path.string()];

			else
				icon = directoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			if (icon.get() != nullptr)
				ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

			if (ImGui::BeginDragDropSource())
			{
				auto relativePath = std::filesystem::relative(path, g_AssetPath);
				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}

			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
					m_CurrentDirectory /= path.filename();

			}
			ImGui::TextWrapped(filenameString.c_str());

			ImGui::NextColumn();

			ImGui::PopID();
		}

		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);

		// TODO: status bar
		ImGui::End();
	}

}
