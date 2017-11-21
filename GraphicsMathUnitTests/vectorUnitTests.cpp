#include "stdafx.h"
#include "CppUnitTest.h"

#include <iostream>
#include "..\GraphicsMathLib\Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GraphicsMath;

namespace GraphicsMathUnitTests
{
	const float zero = 0;
	const float one = 1;
	const float two = 2;
	const float three = 3;
	const float four = 4;
	const float five = 5;
	const float six = 6;
	const float seven = 7;
	const float eight = 8;
	const float nine = 9;

	TEST_CLASS(VectorTests1)
	{
	public:

		TEST_METHOD(Vector_Constructors_And_Accessors_1)
		{
			Vector<2> v2;
			Vector<3> v3;
			Vector<4> v4;

			Assert::AreEqual(v2[0] + v2[1], zero);
			Assert::AreEqual(v3[0] + v3[1] + v3[2], zero);
			Assert::AreEqual(v4[0] + v4[1] + v4[2] + v4[3], zero);
		}

		TEST_METHOD(Vector_Constructors_And_Accessors_2)
		{
			Vector<2> v2{ 1, 2 };
			Vector<3> v3{ 3, 4, 5 };
			Vector<4> v4{ 6, 7, 8, 9 };

			Assert::AreEqual(v2[0] + v2[1], (float)3);
			Assert::AreEqual(v3[0] + v3[1] + v3[2], (float)12);
			Assert::AreEqual(v4[0] + v4[1] + v4[2] + v4[3], (float)30);
		}

		// TODO: Copy and move constructor and assignment tests

		TEST_METHOD(Vector_Addition_1)
		{
			Vector<2> v2a{ 1, 2 };
			Vector<2> v2b{ 3, 4 };
			Vector<2> v2c;

			Vector<2> v2d = v2a + v2b;
			Vector<2> v2e = v2a + v2b + v2c;

			Assert::AreEqual(v2d[0], (float)4);
			Assert::AreEqual(v2d[1], (float)6);

			Assert::AreEqual(v2e[0], (float)4);
			Assert::AreEqual(v2e[1], (float)6);
		}

		TEST_METHOD(Vector_Addition_2)
		{
			Vector<3> v3a{ 2.5, -3, 6 };
			Vector<3> v3b{ 1, -4, 2 };
			Vector<3> v3c{ -1, 2, -5 };

			Vector<3> v3d = v3a + v3b;
			Vector<3> v3e = v3a + v3b + v3c;

			Assert::AreEqual(v3d[0], (float)3.5);
			Assert::AreEqual(v3d[1], (float)-7);
			Assert::AreEqual(v3d[2], (float)8);

			Assert::AreEqual(v3e[0], (float)2.5);
			Assert::AreEqual(v3e[1], (float)-5);
			Assert::AreEqual(v3e[2], (float)3);
		}

		TEST_METHOD(Vector_Addition_3)
		{
			Vector<4> v4a{ 2.5, -3, 6 };
			Vector<4> v4b{ 1, -4, 2, -1 };
			Vector<4> v4c{ -1, 2, -5, 10 };

			Vector<4> v4d = v4a + v4b;
			Vector<4> v4e = v4a + v4b + v4c;

			Assert::AreEqual(v4d[0], (float)3.5);
			Assert::AreEqual(v4d[1], (float)-7);
			Assert::AreEqual(v4d[2], (float)8);
			Assert::AreEqual(v4d[3], (float)-1);

			Assert::AreEqual(v4e[0], (float)2.5);
			Assert::AreEqual(v4e[1], (float)-5);
			Assert::AreEqual(v4e[2], (float)3);
			Assert::AreEqual(v4e[3], (float)9);
		}

		TEST_METHOD(Vector_Mutating_Addition_1)
		{
			Vector<2> v2a{ 1, 2 };
			Vector<2> v2b{ 3, 4 };

			v2a += v2b;

			Assert::AreEqual(v2a[0], (float)4);
			Assert::AreEqual(v2a[1], (float)6);

			Assert::AreEqual(v2b[0], (float)3);
			Assert::AreEqual(v2b[1], (float)4);
		}

		TEST_METHOD(Vector_Mutating_Addition_2)
		{
			Vector<3> v3a{ 1, 2, 3 };
			Vector<3> v3b{ 4, 5 };
			Vector<3> v3c{ -1, -3, -5 };

			v3a += v3b;

			Assert::AreEqual(v3a[0], (float)5);
			Assert::AreEqual(v3a[1], (float)7);
			Assert::AreEqual(v3a[2], (float)3);

			Assert::AreEqual(v3b[0], (float)4);
			Assert::AreEqual(v3b[1], (float)5);
			Assert::AreEqual(v3b[2], zero);

			v3a += v3c;

			Assert::AreEqual(v3a[0], (float)4);
			Assert::AreEqual(v3a[1], (float)4);
			Assert::AreEqual(v3a[2], (float)-2);
		}

		TEST_METHOD(Vector_Subtraction_1)
		{
			Vector<4> v4a{ 1, 2, 3 };
			Vector<4> v4b{ 4, 5, 6, 1 };
			Vector<4> v4c{ 7, 8, 9, 10 };

			Vector<4> v4d = v4a - v4b;
			Vector<4> v4e = v4a - v4b - v4c;

			Assert::AreEqual(v4d[0], (float)-3);
			Assert::AreEqual(v4d[1], (float)-3);
			Assert::AreEqual(v4d[2], (float)-3);
			Assert::AreEqual(v4d[3], (float)-1);

			Assert::AreEqual(v4e[0], (float)-10);
			Assert::AreEqual(v4e[1], (float)-11);
			Assert::AreEqual(v4e[2], (float)-12);
			Assert::AreEqual(v4e[3], (float)-11);
		}

		TEST_METHOD(Vector_Mutating_Subtraction_1)
		{
			Vector<3> v3a{ 1, 2, 3 };
			Vector<3> v3b{ 4, 5 };
			Vector<3> v3c{ -1, -3, -5 };

			v3a -= v3b;

			Assert::AreEqual(v3a[0], (float)-3);
			Assert::AreEqual(v3a[1], (float)-3);
			Assert::AreEqual(v3a[2], (float)3);

			Assert::AreEqual(v3b[0], (float)4);
			Assert::AreEqual(v3b[1], (float)5);
			Assert::AreEqual(v3b[2], zero);

			v3a -= v3c;

			Assert::AreEqual(v3a[0], (float)-2);
			Assert::AreEqual(v3a[1], zero);
			Assert::AreEqual(v3a[2], (float)8);
		}

		TEST_METHOD(Vector_Scalar_Multiplication_1)
		{
			Vector<4> v4a{ 1, 2, 3, 4 };
			Vector<4> v4b = v4a * 2;
			Vector<4> v4c{ v4a };
			v4c *= 3;

			Assert::AreEqual(v4b[0], (float)2);
			Assert::AreEqual(v4b[1], (float)4);
			Assert::AreEqual(v4b[2], (float)6);
			Assert::AreEqual(v4b[3], (float)8);

			Assert::AreEqual(v4c[0], (float)3);
			Assert::AreEqual(v4c[1], (float)6);
			Assert::AreEqual(v4c[2], (float)9);
			Assert::AreEqual(v4c[3], (float)12);
		}

		TEST_METHOD(Vector_Vector_Multiplication_1)
		{
			Vector<3> v3a{ 1, 2, 3 };
			Vector<3> v3b{ 4, 5, 6 };
			Vector<3> v3c{ v3a };

			Vector<3> v3d = v3a * v3b;
			v3c *= v3b;

			Assert::AreEqual(v3d[0], (float)4);
			Assert::AreEqual(v3d[1], (float)10);
			Assert::AreEqual(v3d[2], (float)18);

			Assert::AreEqual(v3c[0], (float)4);
			Assert::AreEqual(v3c[1], (float)10);
			Assert::AreEqual(v3c[2], (float)18);
		}

		TEST_METHOD(Vector_Scalar_Division_1)
		{
			Vector<3> v3a{ 2, 4, 6 };
			float s = 2;

			auto v3b = v3a / s;

			Assert::AreEqual(v3b[0], one);
			Assert::AreEqual(v3b[1], two);
			Assert::AreEqual(v3b[2], three);
		}


		TEST_METHOD(Vector_Equality)
		{
			Vector<4> v4a{ 1, 2, 3, 4 };
			Vector<4> v4b{ v4a };

			Assert::IsTrue(v4a == v4b);

			v4b[2] = 0;
			
			Assert::IsTrue(v4a != v4b);
		}

		TEST_METHOD(Vector_GreaterLessThan)
		{
			Vector<4> v4a{ 1, 2, 3, 4 };
			Vector<4> v4b{ 0, 1, 2, 3 };
			Vector<4> v4c{ 0, 1, 2, 4 };
			Vector<4> v4d{ 0, 2, 3, 3 };

			Assert::IsTrue(v4a > v4b);
			Assert::IsFalse(v4b > v4c);
			Assert::IsTrue(v4c <= v4a);

			Assert::IsTrue(v4a >= v4d);
			Assert::IsTrue(v4d <= v4a);
			Assert::IsFalse(v4d < v4a);
		}

		TEST_METHOD(Vector_Magnitude)
		{
			Vector<3> v3a{ 1, 2, 3 };
			Vector<3> v3b{ -1, -2, -3 };
			Vector<3> v3c{ 3, 4, 5 };

			Assert::AreEqual(v3a.squareMagnitude(), (float)14);
			Assert::AreEqual(v3b.squareMagnitude(), (float)14);
			
			Assert::AreEqual((int)v3c.magnitude(), (int)sqrt(50));
		}

		TEST_METHOD(Vector_DotAndCrossProduct)
		{
			Vector<3> v3a{ 1, 2, 3 };
			Vector<3> v3b{ 4, 5, 6 };

			Assert::AreEqual(v3a.dotProduct(v3b), (float)32);

			Vector<3> v3c{ 0, 1, 0 };
			Vector<3> v3d{ 0, 0, 1 };
			Vector<3> v3e{ 1, 0, 0 };
			Vector<3> v3f = v3c.crossProduct(v3d);
			
			Assert::AreEqual(v3e[0], v3f[0]);
			Assert::AreEqual(v3e[1], v3f[1]);
			Assert::AreEqual(v3e[2], v3f[2]);
		}

		TEST_METHOD(Vector_Normal_1)
		{
			Vector<3> v3a{ 0, 0, 1 };

			auto v3b = v3a.normal();
			v3a.normalize();

			Assert::AreEqual(v3b[0], zero);
			Assert::AreEqual(v3b[1], zero);
			Assert::AreEqual(v3b[2], one);

			Assert::AreEqual(v3a[0], zero);
			Assert::AreEqual(v3a[1], zero);
			Assert::AreEqual(v3a[2], one);
		}

		TEST_METHOD(Vector_Normalize)
		{
			Vector<3> v3a{1, 2, 3};
			std::string s = v3a.to_string();
			std::cout << s << std::endl;
			std::cout << "Test string";
			std::cout << v3a;

			Assert::AreEqual(v3a[0], (float)1);
		}

		TEST_METHOD(Vector_Dimension_Change_1)
		{
			Vector<2> v2{ 1, 2 };
			auto v3 = higherDimension(v2, 3);

			Assert::AreEqual(v3[0], one);
			Assert::AreEqual(v3[1], two);
			Assert::AreEqual(v3[2], three);
		}

		TEST_METHOD(Vector_Dimension_Change_2)
		{
			Vector<3> v3{ 1, 2, 3 };
			auto v4 = higherDimension(v3, 4);

			Assert::AreEqual(v4[0], one);
			Assert::AreEqual(v4[1], two);
			Assert::AreEqual(v4[2], three);
			Assert::AreEqual(v4[3], four);
		}

		TEST_METHOD(Vector_Dimension_Change_3)
		{
			Vector<3> v3{ 1, 2, 3 };
			auto v2 = lowerDimension(v3);

			Assert::AreEqual(v2[0], one);
			Assert::AreEqual(v2[1], two);
		}

		TEST_METHOD(Vector_Dimension_Change_4)
		{
			Vector<4> v4{ 1, 2, 3, 4 };
			auto v3 = lowerDimension(v4);

			Assert::AreEqual(v3[0], one);
			Assert::AreEqual(v3[1], two);
			Assert::AreEqual(v3[2], three);
		}
	};
}