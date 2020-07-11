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
		static T Real(T min, T max)
		{
			HZ_CORE_ASSERT(min < max, "min is >= max");
			std::uniform_real_distribution<T> dist(min, max);
			auto& mt = GetEngine();
			return dist(mt);
		}

		/*
		* Returns a Random Integer between min and max
		*/
		template<typename T>
		static T Int(T min, T max)
		{
			HZ_CORE_ASSERT(min < max, "min is >= max");
			std::uniform_int_distribution<T> dist(min, max);
			auto& mt = GetEngine();
			return dist(mt);
		}

		/*
		* Returns a Random bool value, either 'true' or 'false'
		*/
		static bool Bool()
		{
			//fifty fifty chance
			std::bernoulli_distribution dist(0.5);
			auto& mt = GetEngine();
			return dist(mt);
		}

	private:
		static std::mt19937& GetEngine()
		{
			static std::random_device seed_gen;
			static std::mt19937 engine(seed_gen());
			return engine;
		}
	};

}
