#include "stdafx.h"
#include "CppUnitTest.h"

#include <iostream>
#include "..\GraphicsMathLib\Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GraphicsMath;

namespace GraphicsMathUnitTests
{
	TEST_CLASS(MatrixTests1)
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

	public:

		// TODO: Copy and move constructor and assignment tests

		TEST_METHOD(Matrix_Constructors_And_Accessors_1)
		{
			Matrix<2, 2> m2a;
			Matrix<3, 3> m3a;
			Matrix<4, 4> m4a;
			
			Assert::AreEqual(m2a[0][0], one);
			Assert::AreEqual(m2a[0][1], zero);
			Assert::AreEqual(m2a[1][0], zero);
			Assert::AreEqual(m2a[1][1], one);

			Assert::AreEqual(m3a[0][0], one);
			Assert::AreEqual(m3a[0][1], zero);
			Assert::AreEqual(m3a[0][2], zero);
			Assert::AreEqual(m3a[1][0], zero);
			Assert::AreEqual(m3a[1][1], one);
			Assert::AreEqual(m3a[1][2], zero);
			Assert::AreEqual(m3a[2][0], zero);
			Assert::AreEqual(m3a[2][1], zero);
			Assert::AreEqual(m3a[2][2], one);

			Assert::AreEqual(m4a[0][0], one);
			Assert::AreEqual(m4a[0][1], zero);
			Assert::AreEqual(m4a[0][2], zero);
			Assert::AreEqual(m4a[0][3], zero);
			Assert::AreEqual(m4a[1][0], zero);
			Assert::AreEqual(m4a[1][1], one);
			Assert::AreEqual(m4a[1][2], zero);
			Assert::AreEqual(m4a[1][3], zero);
			Assert::AreEqual(m4a[2][0], zero);
			Assert::AreEqual(m4a[2][1], zero);
			Assert::AreEqual(m4a[2][2], one);
			Assert::AreEqual(m4a[2][3], zero);
			Assert::AreEqual(m4a[3][0], zero);
			Assert::AreEqual(m4a[3][1], zero);
			Assert::AreEqual(m4a[3][2], zero);
			Assert::AreEqual(m4a[3][3], one);
		}

		TEST_METHOD(Matrix_Constructors_And_Accessors_2)
		{
			Matrix<2, 2> m2{ Vector<2>{1, 2}, Vector<2>{3, 4} };
			Matrix<3, 3> m3{ Vector<3>{1, 2, 3}, Vector<3>{4, 5, 6}, Vector<3>{7, 8, 9} };
			Matrix<4, 4> m4{ Vector<4>{1, 2, 3, 4}, Vector<4>{5, 6, 7, 8}, Vector<4>{9, 10, 11, 12}, Vector<4>{13, 14, 15, 16} };

			Assert::AreEqual(m2[0][0], one);
			Assert::AreEqual(m2[0][1], two);
			Assert::AreEqual(m2[1][0], three);
			Assert::AreEqual(m2[1][1], four);

			Assert::AreEqual(m3[0][0], one);
			Assert::AreEqual(m3[0][1], two);
			Assert::AreEqual(m3[0][2], three);
			Assert::AreEqual(m3[1][0], four);
			Assert::AreEqual(m3[1][1], five);
			Assert::AreEqual(m3[1][2], six);
			Assert::AreEqual(m3[2][0], seven);
			Assert::AreEqual(m3[2][1], eight);
			Assert::AreEqual(m3[2][2], nine);

			Assert::AreEqual(m4[0][0], one);
			Assert::AreEqual(m4[0][1], two);
			Assert::AreEqual(m4[0][2], three);
			Assert::AreEqual(m4[0][3], four);
			Assert::AreEqual(m4[1][0], five);
			Assert::AreEqual(m4[1][1], six);
			Assert::AreEqual(m4[1][2], seven);
			Assert::AreEqual(m4[1][3], eight);
			Assert::AreEqual(m4[2][0], nine);
			Assert::AreEqual(m4[2][1], (float)10);
			Assert::AreEqual(m4[2][2], (float)11);
			Assert::AreEqual(m4[2][3], (float)12);
			Assert::AreEqual(m4[3][0], (float)13);
			Assert::AreEqual(m4[3][1], (float)14);
			Assert::AreEqual(m4[3][2], (float)15);
			Assert::AreEqual(m4[3][3], (float)16);
		}

		TEST_METHOD(Matrix_Addition_1)
		{
			Matrix<2, 2> m1;
			m1[0][0] = 1;
			m1[1][1] = 2;

			Matrix<2, 2> m2;
			m2[0][1] = 3;
			m2[1][0] = 4;

			Assert::AreEqual(m1[0][0], one);
			Assert::AreEqual(m1[0][1], zero);
			Assert::AreEqual(m1[1][0], zero);
			Assert::AreEqual(m1[1][1], two);

			Assert::AreEqual(m2[0][1], three);
			Assert::AreEqual(m2[0][0], one);
			Assert::AreEqual(m2[1][1], one);
			Assert::AreEqual(m2[1][0], four);

			auto m3 = m1 + m2;

			Assert::AreEqual(m3[0][0], two);
			Assert::AreEqual(m3[1][1], three);
			Assert::AreEqual(m3[0][1], three);
			Assert::AreEqual(m3[1][0], four);
		}

		TEST_METHOD(Matrix_Addition_2)
		{
			Matrix<3, 3> m1;
			m1[0][0] = 1;
			m1[1][1] = 2;
			m1[2][2] = 3;

			Matrix<3, 3> m2;
			m2[0][1] = 4;
			m2[0][2] = 5;
			m2[1][0] = 6;
			m2[1][2] = 7;
			m2[2][0] = 8;
			m2[2][1] = 9;

			auto m3 = m1 + m2;

			Assert::AreEqual(m3[0][0], two);
			Assert::AreEqual(m3[0][1], four);
			Assert::AreEqual(m3[0][2], five);

			Assert::AreEqual(m3[1][0], six);
			Assert::AreEqual(m3[1][1], three);
			Assert::AreEqual(m3[1][2], seven);
			
			Assert::AreEqual(m3[2][0], eight);
			Assert::AreEqual(m3[2][1], nine);
			Assert::AreEqual(m3[2][2], four);
		}

		TEST_METHOD(Matrix_Matrix_Multiplication_1)
		{
			Matrix<2, 2> m1;
			m1[0][0] = 1;
			m1[1][1] = 2;

			Matrix<2, 2> m2;
			m2[0][0] = 3;
			m2[1][1] = 4;

			auto m3 = m1 * m2;

			Assert::AreEqual(m3[0][0], three);
			Assert::AreEqual(m3[1][1], eight);
		}

		TEST_METHOD(Matrix_Matrix_Multiplication_2)
		{
			Matrix<3, 3> m1;
			m1[0][0] = 1;
			m1[1][1] = 2;
			m1[2][2] = 0;
			m1[0][1] = 3;
			m1[2][0] = 2;

			Matrix<3, 3> m2;
			m2[0][0] = 3;
			m2[1][1] = 4;
			m2[2][2] = 0;
			m2[0][1] = 2;
			m2[2][0] = 2;

			m1 *= m2;

			Assert::AreEqual(m1[0][0], three);
			Assert::AreEqual(m1[2][0], two);
			Assert::AreEqual(m1[0][1], (float)13);
			Assert::AreEqual(m1[1][1], eight);
			Assert::AreEqual(m1[2][0], two);
			Assert::AreEqual(m1[2][1], six);
		}

		TEST_METHOD(Matrix_Vector_Multiplication_1)
		{
			Matrix<2, 2> m1;
			m1[0][0] = 1;
			m1[1][1] = 2;

			Vector<2> v1{ 3, 4 };

			auto v2 = m1 * v1;

			Assert::AreEqual(v2[0], (float)3);
			Assert::AreEqual(v2[1], (float)8);
		}

		TEST_METHOD(Matrix_Vector_Multiplication_2)
		{
			Matrix<3, 3> m1;

		}

		TEST_METHOD(Matrix_Scale_Matrix)
		{
			auto m1 = Matrix<4, 4>::Scale(Vector<3>{2, 4, 8});

			Assert::AreEqual(m1[0][0], two);
			Assert::AreEqual(m1[1][1], four);
			Assert::AreEqual(m1[2][2], eight);
			Assert::AreEqual(m1[0][1], zero);
			Assert::AreEqual(m1[0][2], zero);

			auto m2 = Matrix<4, 4>::ScaleInverse(m1);

			Assert::AreEqual(m2[0][0], 0.5f);
			Assert::AreEqual(m2[1][1], 0.25f);
			Assert::AreEqual(m2[2][2], 0.125f);
			Assert::AreEqual(m2[0][1], zero);
			Assert::AreEqual(m2[0][2], zero);
		}

		TEST_METHOD(Matrix_To_String)
		{
			Matrix<4, 4> m1;
			
			std::cout << m1 << std::endl;
		}
	};
}