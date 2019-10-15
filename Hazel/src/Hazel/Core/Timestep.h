#pragma once

namespace Hazel {

	class Timestep
	{
	public:
		Timestep(float_t time = 0.0f)
			: m_Time(time)
		{
		}

		operator float_t() const { return m_Time; }

		float_t GetSeconds() const { return m_Time; }
		float_t GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float_t m_Time;
	};

}