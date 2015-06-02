#pragma once

namespace fareloz
{
	namespace type
	{
		namespace traits
		{
			struct UIntType;
			struct IntType;
			struct RealType;
			struct VoidType;

			template<typename T>
			struct numeric_type
			{
				typedef VoidType type;
			};

            template<> struct numeric_type<unsigned char>      { typedef UIntType type; };
			template<> struct numeric_type<unsigned short>      { typedef UIntType type; };
			template<> struct numeric_type<unsigned int>        { typedef UIntType type; };
			template<> struct numeric_type<unsigned long>       { typedef UIntType type; };
			template<> struct numeric_type<unsigned long long>  { typedef UIntType type; };

            template<> struct numeric_type<char>      { typedef IntType type; };
			template<> struct numeric_type<short>      { typedef IntType type; };
			template<> struct numeric_type<int>        { typedef IntType type; };
			template<> struct numeric_type<long>       { typedef IntType type; };
			template<> struct numeric_type<long long>  { typedef IntType type; };

			template<> struct numeric_type<float>       { typedef RealType type; };
			template<> struct numeric_type<double>      { typedef RealType type; };
			template<> struct numeric_type<long double> { typedef RealType type; };
		}
	}
}