#pragma once

#include "Hazel/Scene/Components.h"

#include "box2d/b2_body.h"

namespace Hazel {

	namespace Utils {

		inline b2BodyType Rigidbody2DTypeToBox2DBody(Rigidbody2DComponent::BodyType bodyType)
		{
			switch (bodyType)
			{
				case Rigidbody2DComponent::BodyType::Static:    return b2_staticBody;
				case Rigidbody2DComponent::BodyType::Dynamic:   return b2_dynamicBody;
				case Rigidbody2DComponent::BodyType::Kinematic: return b2_kinematicBody;
			}

			HZ_CORE_ASSERT(false, "Unknown body type");
			return b2_staticBody;
		}

		inline Rigidbody2DComponent::BodyType Rigidbody2DTypeFromBox2DBody(b2BodyType bodyType)
		{
			switch (bodyType)
			{
				case b2_staticBody:    return Rigidbody2DComponent::BodyType::Static;   
				case b2_dynamicBody:   return Rigidbody2DComponent::BodyType::Dynamic;  
				case b2_kinematicBody: return Rigidbody2DComponent::BodyType::Kinematic;
			}

			HZ_CORE_ASSERT(false, "Unknown body type");
			return Rigidbody2DComponent::BodyType::Static;
		}

	}

}
