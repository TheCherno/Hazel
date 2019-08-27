/* Copyright 2019 Yan Chernikov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http ://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

// For use by Hazel applications

#include "Hazel/Application.h"
#include "Hazel/Layer.h"
#include "Hazel/Log.h"

#include "Hazel/Core/Timestep.h"

#include "Hazel/Input.h"
#include "Hazel/KeyCodes.h"
#include "Hazel/MouseButtonCodes.h"

#include "Hazel/ImGui/ImGuiLayer.h"

// ---Renderer------------------------
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/RenderCommand.h"

#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Texture.h"
#include "Hazel/Renderer/VertexArray.h"

#include "Hazel/Renderer/OrthographicCamera.h"
// -----------------------------------

// ---Entry Point---------------------
#include "Hazel/EntryPoint.h"
// -----------------------------------