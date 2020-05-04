#pragma once

namespace Hazel {

	class Timestep
	{
	public:
		explicit Timestep(float time = 0.0f)
			: m_Time(time)
		{
		}

		operator float() const { return m_Time; }

		[[nodiscard]] float GetSeconds() const { return m_Time; }
        [[nodiscard]] float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};

}