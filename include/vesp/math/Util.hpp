#pragma once

namespace vesp { namespace math {

	template <typename T>
	T Clamp(T const in, T const min, T const max)
	{
		if (in > max)
			return max;
		else if (in < min)
			return min;

		return in;
	}

	template <typename T>
	typename std::enable_if<std::is_unsigned<T>::value, T>::type
	PackFloat(float value, float min = 0.0f, float max = 1.0f)
	{
		value -= min;
		value /= (max - min);

		return static_cast<T>(value * std::numeric_limits<T>::max());
	}

	template <typename T>
	typename std::enable_if<std::is_unsigned<T>::value, float>::type
	UnpackFloat(T value, float min = 0.0f, float max = 1.0f)
	{
		float ret = static_cast<float>(value) / static_cast<float>(std::numeric_limits<T>::max());
		ret *= (max - min);
		ret += min;

		return ret;
	}

	inline U16 LowWord(U32 v)
	{
		return static_cast<U16>(v);
	}

	inline U16 HighWord(U32 v)
	{
		return static_cast<U16>((v >> 16) & 0xffff);
	}
	
	inline U32 LowDword(U64 v)
	{
		return static_cast<U32>(v);
	}

	inline U32 HighDword(U64 v)
	{
		return static_cast<U32>((v >> 32) & 0xffffffff);
	}
} }