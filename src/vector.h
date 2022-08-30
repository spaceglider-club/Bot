#ifndef SPACEGLIDER_SRC_VECTOR_H_
#define SPACEGLIDER_SRC_VECTOR_H_

#pragma once

namespace Vector
{
	template <class T>
	struct Vector1
	{
		T x;
	};

	template <class T>
	struct Vector2
	{
		T x;
		T y;
	};

	template <class T>
	struct Vector3
	{
		T x;
		T y;
		T z;
	};

	template <class T>
	struct Vector4
	{
		T x;
		T y;
		T z;
		T w;
	};

}

#endif