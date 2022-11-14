#pragma once

#include "Hazel/Core/Buffer.h"

namespace Hazel {

	class FileSystem
	{
	public:
		// TODO: move to FileSystem class
		static Buffer ReadFileBinary(const std::filesystem::path& filepath);
	};

}
