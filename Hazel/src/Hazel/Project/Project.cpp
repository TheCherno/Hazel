#include "hzpch.h"
#include "Hazel/Project/Project.h"

#include "Hazel/Project/ProjectSerializer.h"

namespace Hazel {

  Ref<Project> Project::New(void)
  {
    s_ActiveProject = CreateRef<Project>();
    return s_ActiveProject;
  }

  Ref<Project> Project::Load(const std::filesystem::path& path)
  {
    Ref<Project> project = CreateRef<Project>();

    ProjectSerializer serializer(project);
    if (serializer.Deserialize(path)) {
      project->m_ProjectDirectory = path.parent_path();
      s_ActiveProject = project;
      return s_ActiveProject;
    } // if (serializer.Deserialize(path)) {

    return nullptr;
  }

  bool Project::SaveActive(const std::filesystem::path& path)
  {
    ProjectSerializer serializer(s_ActiveProject);
    if (serializer.Serialize(path)) {
      s_ActiveProject->m_ProjectDirectory = path.parent_path();
      return true;
    } // if (serializer.Serialize(path)) {

    return false;
  }

}
