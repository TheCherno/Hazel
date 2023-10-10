#pragma once

#include "Hazel/Project/Project.h"
#include "Hazel/Renderer/Texture.h"

namespace Hazel {

	struct ThumbnailImage
	{
		uint64_t Timestamp;
		Ref<Texture2D> Image;
	};

	class ThumbnailCache
	{
	public:
		ThumbnailCache(Ref<Project> project);

		Ref<Texture2D> GetOrCreateThumbnail(const std::filesystem::path& path);
	private:
		Ref<Project> m_Project;

		std::map<std::filesystem::path, ThumbnailImage> m_CachedImages;
		
		// TEMP (replace with Hazel::Serialization)
		std::filesystem::path m_ThumbnailCachePath;
	};

}
