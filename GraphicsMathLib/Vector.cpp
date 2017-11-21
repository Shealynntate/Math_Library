
#include "Vector.h"

namespace GraphicsMath
{

#pragma region Vector Conversion Methods

	Vector<3> lowerDimension(const Vector<4>& v)
	{
		return Vector<3>{ v[0], v[1], v[2] };
	}

	Vector<2> lowerDimension(const Vector<3>& v)
	{
		return Vector<2>{ v[0], v[1] };
	}

	Vector<4> higherDimension(const Vector<3>& v, float w)
	{
		return Vector<4>{ v[0], v[1], v[2], w };
	}

	Vector<3> higherDimension(const Vector<2>& v, float z)
	{
		return Vector<3>{ v[0], v[1], z };
	}

#pragma endregion

}