#pragma once
#include <random>

namespace Hazel {

	class Random
	{
	public:
		/*
		* Returns a Random Real between min and max
		*/
		template<typename T>
		static inline T Real(T min, T max)
		{
			HZ_CORE_ASSERT(min < max, "min is > max");
			std::uniform_real_distribution<T> dist(min, max);
			auto& mt = GetEngine();
			return dist(mt);
		}

		/*
		* Returns a Random Integer between min and max
		*/
		template<typename T>
		static inline T Int(T min, T max)
		{
			HZ_CORE_ASSERT(min < max, "min is > max");
			std::uniform_int_distribution<T> dist(min, max);
			auto& mt = GetEngine();
			return dist(mt);
		}

		/*
		* Returns a Random bool value, either 'true' or 'false'
		*/
		static inline bool Bool()
		{
			//fifty fifty chance
			std::bernoulli_distribution dist(0.5);
			auto& mt = GetEngine();
			return dist(mt);
		}

	private:
		static inline std::mt19937& Random::GetEngine()
		{
			static std::random_device seed_gen;
			static std::mt19937 engine(seed_gen());
			return engine;
		}
	};

}
