#pragma once

#include <string>
#include <filesystem>

#include "Hazel/Core/Base.h"

namespace Hazel {

  struct ProjectConfig
  {
    std::string Name = "Untitled";

    std::filesystem::path StartScene;

    std::filesystem::path AssetDirectory;
    std::filesystem::path ScriptModulePath;
  };

  class Project
  {
  public:
    static const std::filesystem::path& GetProjectDirectory(void)
      {
	HZ_CORE_ASSERT(s_ActiveProject);
	return s_ActiveProject->m_ProjectDirectory;
      }

    static std::filesystem::path GetAssetDirectory(void)
      {
	HZ_CORE_ASSERT(s_ActiveProject);
	return GetProjectDirectory() / s_ActiveProject->m_Config.AssetDirectory;
      }

    // TODO(Yan): move to asset manager when we have one
    static std::filesystem::path GetAssetFileSystemPath(const std::filesystem::path& path)
      {
	HZ_CORE_ASSERT(s_ActiveProject);
	return GetAssetDirectory() / path;
      }

    ProjectConfig& GetConfig(void) { return m_Config; }

    static Ref<Project> GetActive(void) { return s_ActiveProject; }

    static Ref<Project> New(void);
    static Ref<Project> Load(const std::filesystem::path& path);
    static bool SaveActive(const std::filesystem::path& path);

  private:
    ProjectConfig m_Config;
    std::filesystem::path m_ProjectDirectory;

    inline static Ref<Project> s_ActiveProject;
  };

}
