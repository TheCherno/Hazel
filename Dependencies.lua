
-- Hazel Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/Hazel/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/Hazel/vendor/yaml-cpp/include"
IncludeDir["GLFW"] = "%{wks.location}/Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Hazel/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Hazel/vendor/imgui"
IncludeDir["ImGuizmo"] = "%{wks.location}/Hazel/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/Hazel/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/Hazel/vendor/entt/include"

if VULKAN_SDK ~= nil then

	IncludeDir["SPIRV_Cross"] = "%{wks.location}/Hazel/vendor/SPIRV-Cross"
	IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

	LibraryDir = {}

	LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
	LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/Hazel/vendor/VulkanSDK/Lib"
	LibraryDir["VulkanSDK_DebugDLL"] = "%{wks.location}/Hazel/vendor/VulkanSDK/Bin"

	Library = {}

	Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
	Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

	Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
	Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
	Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
	Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

	Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
	Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
	Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
	
else

	IncludeDir["shaderc"] = "%{wks.location}/Hazel/vendor/shaderc/libshaderc/include/"
	IncludeDir["SPIRV_Cross"] = "%{wks.location}/Hazel/vendor/SPIRV-Cross"

	Library = {}

	Library["ShaderC"] = "shaderc"
	Library["ShaderC_Util"] = "shaderc_util"

	Library["SPIRV"] = "SPIRV"
	Library["SPIRV_Cross"] = "spirv-cross"
	Library["SPIRV_Cross_MachineIndependent"] = "MachineIndependent"
	Library["SPIRV_Cross_OSDependent"] = "OSDependent"
	Library["SPIRV_Cross_GenericCodeGen"] = "GenericCodeGen"
	Library["SPIRV_Cross_OGLCompiler"] = "OGLCompiler"

	Library["SPIRV_Tools_SPIRV_Tools"] = "SPIRV-Tools"
	Library["SPIRV_Tools_Opt"] = "SPIRV-Tools-opt"

	group "spirv_shaderc"
		include "Hazel/vendor/SPIRV-Cross"
		include "Hazel/vendor/shaderc"
	group ""

end
