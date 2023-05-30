#pragma once

#include "AssetMetadata.h"

namespace Hazel {

	class AssetImporter
	{
	public:
		static Ref<Asset> ImportAsset(AssetHandle handle, const AssetMetadata& metadata);
	};

}
