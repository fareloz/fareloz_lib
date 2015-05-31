#pragma once

#include <type_traits>
#include <random>

#include "..\type\traits.hpp"

namespace fareloz
{
	namespace math
	{
		namespace
		{
			static std::default_random_engine& default_engine()
			{
				static std::default_random_engine e{};
				return e;
			}
		}

		namespace random
		{
			template<typename T, typename PT = type::traits::numeric_type<T>::type>
			struct random
			{
				static T generate(T min, T max);
			};

			template<typename T>
			struct random<T, type::traits::IntType>
			{
				static T generate(T min, T max)
				{
					std::uniform_int_distribution<T> d{ min, max };
					return d(default_engine());
				}
			};

			template<typename T>
			struct random<T, type::traits::RealType>
			{
				static T generate(T min, T max)
				{
					std::uniform_real_distribution<T> d{ min, max };
					return d(default_engine());
				}
			};
		}
	}
}