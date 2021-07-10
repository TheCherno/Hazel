#pragma once

#include "Entity.h"

namespace Hazel {

	class NativeScript
	{
	public:
		NativeScript(Entity entity) : m_Entity(entity) {}
		virtual ~NativeScript() {}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

	protected:
		virtual void OnUpdate(Timestep ts) {}

	private:
		Entity m_Entity;
		friend class Scene;
	};

}
