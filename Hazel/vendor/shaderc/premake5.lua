project "shaderc"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"libshaderc/src/shaderc.cc"
	}

	includedirs
	{
		"libshaderc/include",
		"libshaderc_util/include",
		"third_party/glslang/",
		"third_party/spirv-tools/include",
		"third_party/spirv-headers/include"
	}
	defines
	{
		"ENABLE_HLSL"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"WIN32",
			"_WINDOWS",
			"_HAS_EXCEPTIONS=0",
			"GLSLANG_OSINCLUDE_WIN32",
			"ENABLE_OPT=1"
		}

	filter "action:gmake*"
		buildoptions { "-fdiagnostics-color=always -fvisibility=hidden -fPIC -pthread" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "NDEBUG"

project "shaderc_util"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"libshaderc_util/src/args.cc",
		"libshaderc_util/src/compiler.cc",
		"libshaderc_util/src/file_finder.cc",
		"libshaderc_util/src/io_shaderc.cc",
		"libshaderc_util/src/message.cc",
		"libshaderc_util/src/resources.cc",
		"libshaderc_util/src/shader_stage.cc",
		"libshaderc_util/src/spirv_tools_wrapper.cc",
		"libshaderc_util/src/version_profile.cc"
	}

	includedirs
	{
		"libshaderc_util/include",
		"third_party/glslang/",
		"third_party/spirv-tools/include"
	}
	defines
	{
		"ENABLE_HLSL"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"WIN32",
			"_WINDOWS",
			"_HAS_EXCEPTIONS=0",
			"GLSLANG_OSINCLUDE_WIN32",
			"ENABLE_OPT=1"
		}

	filter "action:gmake*"
		buildoptions { "-fdiagnostics-color=always -fvisibility=hidden -fPIC -pthread" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "NDEBUG"

project "SPIRV-Tools-opt"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"third_party/spirv-tools/source/opt/aggressive_dead_code_elim_pass.cpp",
		"third_party/spirv-tools/source/opt/amd_ext_to_khr.cpp",
		"third_party/spirv-tools/source/opt/basic_block.cpp",
		"third_party/spirv-tools/source/opt/block_merge_pass.cpp",
		"third_party/spirv-tools/source/opt/block_merge_util.cpp",
		"third_party/spirv-tools/source/opt/build_module.cpp",
		"third_party/spirv-tools/source/opt/ccp_pass.cpp",
		"third_party/spirv-tools/source/opt/cfg_cleanup_pass.cpp",
		"third_party/spirv-tools/source/opt/cfg.cpp",
		"third_party/spirv-tools/source/opt/code_sink.cpp",
		"third_party/spirv-tools/source/opt/combine_access_chains.cpp",
		"third_party/spirv-tools/source/opt/compact_ids_pass.cpp",
		"third_party/spirv-tools/source/opt/composite.cpp",
		"third_party/spirv-tools/source/opt/const_folding_rules.cpp",
		"third_party/spirv-tools/source/opt/constants.cpp",
		"third_party/spirv-tools/source/opt/control_dependence.cpp",
		"third_party/spirv-tools/source/opt/convert_to_sampled_image_pass.cpp",
		"third_party/spirv-tools/source/opt/convert_to_half_pass.cpp",
		"third_party/spirv-tools/source/opt/copy_prop_arrays.cpp",
		"third_party/spirv-tools/source/opt/dataflow.cpp",
		"third_party/spirv-tools/source/opt/dead_branch_elim_pass.cpp",
		"third_party/spirv-tools/source/opt/dead_insert_elim_pass.cpp",
		"third_party/spirv-tools/source/opt/dead_variable_elimination.cpp",
		"third_party/spirv-tools/source/opt/decoration_manager.cpp",
		"third_party/spirv-tools/source/opt/debug_info_manager.cpp",
		"third_party/spirv-tools/source/opt/def_use_manager.cpp",
		"third_party/spirv-tools/source/opt/desc_sroa.cpp",
		"third_party/spirv-tools/source/opt/dominator_analysis.cpp",
		"third_party/spirv-tools/source/opt/dominator_tree.cpp",
		"third_party/spirv-tools/source/opt/eliminate_dead_constant_pass.cpp",
		"third_party/spirv-tools/source/opt/eliminate_dead_functions_pass.cpp",
		"third_party/spirv-tools/source/opt/eliminate_dead_functions_util.cpp",
		"third_party/spirv-tools/source/opt/eliminate_dead_members_pass.cpp",
		"third_party/spirv-tools/source/opt/feature_manager.cpp",
		"third_party/spirv-tools/source/opt/fix_storage_class.cpp",
		"third_party/spirv-tools/source/opt/flatten_decoration_pass.cpp",
		"third_party/spirv-tools/source/opt/fold.cpp",
		"third_party/spirv-tools/source/opt/folding_rules.cpp",
		"third_party/spirv-tools/source/opt/fold_spec_constant_op_and_composite_pass.cpp",
		"third_party/spirv-tools/source/opt/freeze_spec_constant_value_pass.cpp",
		"third_party/spirv-tools/source/opt/function.cpp",
		"third_party/spirv-tools/source/opt/graphics_robust_access_pass.cpp",
		"third_party/spirv-tools/source/opt/if_conversion.cpp",
		"third_party/spirv-tools/source/opt/inline_exhaustive_pass.cpp",
		"third_party/spirv-tools/source/opt/inline_opaque_pass.cpp",
		"third_party/spirv-tools/source/opt/inline_pass.cpp",
		"third_party/spirv-tools/source/opt/inst_bindless_check_pass.cpp",
		"third_party/spirv-tools/source/opt/inst_buff_addr_check_pass.cpp",
		"third_party/spirv-tools/source/opt/inst_debug_printf_pass.cpp",
		"third_party/spirv-tools/source/opt/instruction.cpp",
		"third_party/spirv-tools/source/opt/instruction_list.cpp",
		"third_party/spirv-tools/source/opt/instrument_pass.cpp",
		"third_party/spirv-tools/source/opt/interp_fixup_pass.cpp",
		"third_party/spirv-tools/source/opt/ir_context.cpp",
		"third_party/spirv-tools/source/opt/ir_loader.cpp",
		"third_party/spirv-tools/source/opt/licm_pass.cpp",
		"third_party/spirv-tools/source/opt/local_access_chain_convert_pass.cpp",
		"third_party/spirv-tools/source/opt/local_redundancy_elimination.cpp",
		"third_party/spirv-tools/source/opt/local_single_block_elim_pass.cpp",
		"third_party/spirv-tools/source/opt/local_single_store_elim_pass.cpp",
		"third_party/spirv-tools/source/opt/loop_dependence.cpp",
		"third_party/spirv-tools/source/opt/loop_dependence_helpers.cpp",
		"third_party/spirv-tools/source/opt/loop_descriptor.cpp",
		"third_party/spirv-tools/source/opt/loop_fission.cpp",
		"third_party/spirv-tools/source/opt/loop_fusion.cpp",
		"third_party/spirv-tools/source/opt/loop_fusion_pass.cpp",
		"third_party/spirv-tools/source/opt/loop_peeling.cpp",
		"third_party/spirv-tools/source/opt/loop_utils.cpp",
		"third_party/spirv-tools/source/opt/loop_unroller.cpp",
		"third_party/spirv-tools/source/opt/loop_unswitch_pass.cpp",
		"third_party/spirv-tools/source/opt/mem_pass.cpp",
		"third_party/spirv-tools/source/opt/merge_return_pass.cpp",
		"third_party/spirv-tools/source/opt/module.cpp",
		"third_party/spirv-tools/source/opt/optimizer.cpp",
		"third_party/spirv-tools/source/opt/pass.cpp",
		"third_party/spirv-tools/source/opt/pass_manager.cpp",
		"third_party/spirv-tools/source/opt/private_to_local_pass.cpp",
		"third_party/spirv-tools/source/opt/propagator.cpp",
		"third_party/spirv-tools/source/opt/reduce_load_size.cpp",
		"third_party/spirv-tools/source/opt/redundancy_elimination.cpp",
		"third_party/spirv-tools/source/opt/register_pressure.cpp",
		"third_party/spirv-tools/source/opt/relax_float_ops_pass.cpp",
		"third_party/spirv-tools/source/opt/remove_duplicates_pass.cpp",
		"third_party/spirv-tools/source/opt/remove_unused_interface_variables_pass.cpp",
		"third_party/spirv-tools/source/opt/replace_invalid_opc.cpp",
		"third_party/spirv-tools/source/opt/scalar_analysis.cpp",
		"third_party/spirv-tools/source/opt/scalar_analysis_simplification.cpp",
		"third_party/spirv-tools/source/opt/scalar_replacement_pass.cpp",
		"third_party/spirv-tools/source/opt/set_spec_constant_default_value_pass.cpp",
		"third_party/spirv-tools/source/opt/simplification_pass.cpp",
		"third_party/spirv-tools/source/opt/ssa_rewrite_pass.cpp",
		"third_party/spirv-tools/source/opt/strength_reduction_pass.cpp",
		"third_party/spirv-tools/source/opt/strip_debug_info_pass.cpp",
		"third_party/spirv-tools/source/opt/strip_reflect_info_pass.cpp",
		"third_party/spirv-tools/source/opt/struct_cfg_analysis.cpp",
		"third_party/spirv-tools/source/opt/type_manager.cpp",
		"third_party/spirv-tools/source/opt/types.cpp",
		"third_party/spirv-tools/source/opt/unify_const_pass.cpp",
		"third_party/spirv-tools/source/opt/upgrade_memory_model.cpp",
		"third_party/spirv-tools/source/opt/value_number_table.cpp",
		"third_party/spirv-tools/source/opt/vector_dce.cpp",
		"third_party/spirv-tools/source/opt/workaround1209.cpp",
		"third_party/spirv-tools/source/opt/wrap_opkill.cpp",
	}

	includedirs
	{
		"third_party/spirv-tools",
		"third_party/spirv-headers/include",
		"third_party/spirv-tools/include"
		
	}
	defines
	{
		"SPIRV_CHECK_CONTEXT",
		"SPIRV_COLOR_TERMINAL",
	}

	filter { "system:linux"}
		defines
		{
			"SPIRV_LINUX",
			"SPIRV_TIMER_ENABLED"
		}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"WIN32",
			"_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS",
			"_SCL_SECURE_NO_WARNINGS",
			"SPIRV_WINDOWS",
		}

	filter "action:gmake*"
		buildoptions { "-fdiagnostics-color=always -fPIC -fno-exceptions" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "NDEBUG"


project "SPIRV-Tools"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"third_party/spirv-tools/source/util/bit_vector.cpp",
		"third_party/spirv-tools/source/util/parse_number.cpp",
		"third_party/spirv-tools/source/util/string_utils.cpp",
		"third_party/spirv-tools/source/assembly_grammar.cpp",
		"third_party/spirv-tools/source/binary.cpp",
		"third_party/spirv-tools/source/diagnostic.cpp",
		"third_party/spirv-tools/source/disassemble.cpp",
		"third_party/spirv-tools/source/enum_string_mapping.cpp",
		"third_party/spirv-tools/source/ext_inst.cpp",
		"third_party/spirv-tools/source/extensions.cpp",
		"third_party/spirv-tools/source/libspirv.cpp",
		"third_party/spirv-tools/source/name_mapper.cpp",
		"third_party/spirv-tools/source/opcode.cpp",
		"third_party/spirv-tools/source/operand.cpp",
		"third_party/spirv-tools/source/parsed_operand.cpp",
		"third_party/spirv-tools/source/print.cpp",
		"third_party/spirv-tools/source/software_version.cpp",
		"third_party/spirv-tools/source/spirv_endian.cpp",
		"third_party/spirv-tools/source/spirv_fuzzer_options.cpp",
		"third_party/spirv-tools/source/spirv_optimizer_options.cpp",
		"third_party/spirv-tools/source/spirv_reducer_options.cpp",
		"third_party/spirv-tools/source/spirv_target_env.cpp",
		"third_party/spirv-tools/source/spirv_validator_options.cpp",
		"third_party/spirv-tools/source/table.cpp",
		"third_party/spirv-tools/source/text.cpp",
		"third_party/spirv-tools/source/text_handler.cpp",
		"third_party/spirv-tools/source/val/validate.cpp",
		"third_party/spirv-tools/source/val/validate_adjacency.cpp",
		"third_party/spirv-tools/source/val/validate_annotation.cpp",
		"third_party/spirv-tools/source/val/validate_arithmetics.cpp",
		"third_party/spirv-tools/source/val/validate_atomics.cpp",
		"third_party/spirv-tools/source/val/validate_barriers.cpp",
		"third_party/spirv-tools/source/val/validate_bitwise.cpp",
		"third_party/spirv-tools/source/val/validate_builtins.cpp",
		"third_party/spirv-tools/source/val/validate_capability.cpp",
		"third_party/spirv-tools/source/val/validate_cfg.cpp",
		"third_party/spirv-tools/source/val/validate_composites.cpp",
		"third_party/spirv-tools/source/val/validate_constants.cpp",
		"third_party/spirv-tools/source/val/validate_conversion.cpp",
		"third_party/spirv-tools/source/val/validate_debug.cpp",
		"third_party/spirv-tools/source/val/validate_decorations.cpp",
		"third_party/spirv-tools/source/val/validate_derivatives.cpp",
		"third_party/spirv-tools/source/val/validate_extensions.cpp",
		"third_party/spirv-tools/source/val/validate_execution_limitations.cpp",
		"third_party/spirv-tools/source/val/validate_function.cpp",
		"third_party/spirv-tools/source/val/validate_id.cpp",
		"third_party/spirv-tools/source/val/validate_image.cpp",
		"third_party/spirv-tools/source/val/validate_interfaces.cpp",
		"third_party/spirv-tools/source/val/validate_instruction.cpp",
		"third_party/spirv-tools/source/val/validate_layout.cpp",
		"third_party/spirv-tools/source/val/validate_literals.cpp",
		"third_party/spirv-tools/source/val/validate_logicals.cpp",
		"third_party/spirv-tools/source/val/validate_memory.cpp",
		"third_party/spirv-tools/source/val/validate_memory_semantics.cpp",
		"third_party/spirv-tools/source/val/validate_misc.cpp",
		"third_party/spirv-tools/source/val/validate_mode_setting.cpp",
		"third_party/spirv-tools/source/val/validate_non_uniform.cpp",
		"third_party/spirv-tools/source/val/validate_primitives.cpp",
		"third_party/spirv-tools/source/val/validate_scopes.cpp",
		"third_party/spirv-tools/source/val/validate_small_type_uses.cpp",
		"third_party/spirv-tools/source/val/validate_type.cpp",
		"third_party/spirv-tools/source/val/basic_block.cpp",
		"third_party/spirv-tools/source/val/construct.cpp",
		"third_party/spirv-tools/source/val/function.cpp",
		"third_party/spirv-tools/source/val/instruction.cpp",
		"third_party/spirv-tools/source/val/validation_state.cpp",
		"third_party/spirv-tools/source/util/timer.cpp"
	}

	includedirs
	{
		"third_party/spirv-tools",
		"third_party/spirv-headers/include",
		"third_party/spirv-tools/include"
	}

	defines
	{
		"SPIRV_CHECK_CONTEXT",
		"SPIRV_COLOR_TERMINAL",
	}

	filter { "system:linux"}
		defines
		{
			"SPIRV_LINUX",
			"SPIRV_TIMER_ENABLED"
		}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"WIN32",
			"_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS",
			"_SCL_SECURE_NO_WARNINGS",
			"SPIRV_WINDOWS",
		}

	filter "action:gmake*"
		buildoptions { "-fdiagnostics-color=always -fPIC -fno-rtti -fno-exceptions" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "NDEBUG"

project "MachineIndependent"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"third_party/glslang/glslang/MachineIndependent/glslang_tab.cpp",
		"third_party/glslang/glslang/MachineIndependent/attribute.cpp",
		"third_party/glslang/glslang/MachineIndependent/Constant.cpp",
		"third_party/glslang/glslang/MachineIndependent/iomapper.cpp",
		"third_party/glslang/glslang/MachineIndependent/InfoSink.cpp",
		"third_party/glslang/glslang/MachineIndependent/Initialize.cpp",
		"third_party/glslang/glslang/MachineIndependent/IntermTraverse.cpp",
		"third_party/glslang/glslang/MachineIndependent/Intermediate.cpp",
		"third_party/glslang/glslang/MachineIndependent/ParseContextBase.cpp",
		"third_party/glslang/glslang/MachineIndependent/ParseHelper.cpp",
		"third_party/glslang/glslang/MachineIndependent/PoolAlloc.cpp",
		"third_party/glslang/glslang/MachineIndependent/RemoveTree.cpp",
		"third_party/glslang/glslang/MachineIndependent/Scan.cpp",
		"third_party/glslang/glslang/MachineIndependent/ShaderLang.cpp",
		"third_party/glslang/glslang/MachineIndependent/SpirvIntrinsics.cpp",
		"third_party/glslang/glslang/MachineIndependent/SymbolTable.cpp",
		"third_party/glslang/glslang/MachineIndependent/Versions.cpp",
		"third_party/glslang/glslang/MachineIndependent/intermOut.cpp",
		"third_party/glslang/glslang/MachineIndependent/limits.cpp",
		"third_party/glslang/glslang/MachineIndependent/linkValidate.cpp",
		"third_party/glslang/glslang/MachineIndependent/parseConst.cpp",
		"third_party/glslang/glslang/MachineIndependent/reflection.cpp",
		"third_party/glslang/glslang/MachineIndependent/preprocessor/Pp.cpp",
		"third_party/glslang/glslang/MachineIndependent/preprocessor/PpAtom.cpp",
		"third_party/glslang/glslang/MachineIndependent/preprocessor/PpContext.cpp",
		"third_party/glslang/glslang/MachineIndependent/preprocessor/PpScanner.cpp",
		"third_party/glslang/glslang/MachineIndependent/preprocessor/PpTokens.cpp",
		"third_party/glslang/glslang/MachineIndependent/propagateNoContraction.cpp",
		"third_party/glslang/glslang/HLSL/hlslAttributes.cpp",
		"third_party/glslang/glslang/HLSL/hlslParseHelper.cpp",
		"third_party/glslang/glslang/HLSL/hlslScanContext.cpp",
		"third_party/glslang/glslang/HLSL/hlslOpMap.cpp",
		"third_party/glslang/glslang/HLSL/hlslTokenStream.cpp",
		"third_party/glslang/glslang/HLSL/hlslGrammar.cpp",
		"third_party/glslang/glslang/HLSL/hlslParseables.cpp"
	}

	includedirs
	{
		"third_party/glslang"
	}
	defines
	{
		"ENABLE_HLSL",
		"ENABLE_OPT=1"
	}
	
	filter { "system:linux"}
		defines
		{
			"GLSLANG_OSINCLUDE_UNIX"
		}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"WIN32",
			"_WINDOWS",
			"_HAS_EXCEPTIONS=0",
			"GLSLANG_OSINCLUDE_WIN32"
		}

	filter "action:gmake*"
		buildoptions { "-fdiagnostics-color=always -fPIC -fno-exceptions -fno-rtti -pthread" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "NDEBUG"

project "OSDependent"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"third_party/re2/re2/prefilter.cc"
	}

	includedirs
	{
		"third_party/re2"
	}

	filter "system:windows"
		systemversion "latest"
		files
		{
			"third_party/glslang/glslang/OSDependent/Windows/ossource.cpp"
		}
	filter "system:linux"
		files
		{
			"third_party/glslang/glslang/OSDependent/Unix/ossource.cpp"
		}
		
	filter "action:gmake*"
		buildoptions { "-fdiagnostics-color=always" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "NDEBUG"

project "GenericCodeGen"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"third_party/glslang/StandAlone/ResourceLimits.cpp",
		"third_party/glslang/glslang/GenericCodeGen/Link.cpp",
		"third_party/re2/re2/prefilter_tree.cc",
		"third_party/re2/re2/prog.cc",
		"third_party/re2/re2/re2.cc",
		"third_party/glslang/StandAlone/resource_limits_c.cpp",
		"third_party/glslang/glslang/GenericCodeGen/CodeGen.cpp"
	}

	includedirs
	{
		"third_party/re2"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"WIN32",
			"_WINDOWS",
			"_HAS_EXCEPTIONS=0",
			"ENABLE_HLSL",
			"GLSLANG_OSINCLUDE_WIN32",
			"ENABLE_OPT=1"
		}

	filter "action:gmake*"
		buildoptions { "-fdiagnostics-color=always" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "NDEBUG"

project "OGLCompiler"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"third_party/glslang/OGLCompilersDLL/InitializeDll.cpp",
		"third_party/re2/re2/parse.cc",
		"third_party/re2/re2/perl_groups.cc"
	}

	includedirs
	{
		"third_party/glslang",
		"third_party/re2"
	}

	filter "system:windows"
		systemversion "latest"

	filter "action:gmake*"
		buildoptions { "-fdiagnostics-color=always" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "NDEBUG"

project "SPIRV"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"third_party/glslang/SPIRV/GlslangToSpv.cpp",
		"third_party/glslang/SPIRV/InReadableOrder.cpp",
		"third_party/glslang/SPIRV/Logger.cpp",
		"third_party/glslang/SPIRV/SpvBuilder.cpp",
		"third_party/glslang/SPIRV/SpvPostProcess.cpp",
		"third_party/glslang/SPIRV/doc.cpp",
		"third_party/glslang/SPIRV/SpvTools.cpp",
		"third_party/glslang/SPIRV/disassemble.cpp",
		"third_party/glslang/SPIRV/CInterface/spirv_c_interface.cpp"
	}

	includedirs
	{
		"third_party/glslang"
	}

	filter "system:windows"
		systemversion "latest"

	filter "action:gmake*"
		buildoptions { "-fdiagnostics-color=always" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "NDEBUG"
