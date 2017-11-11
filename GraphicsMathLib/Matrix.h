#pragma once

#include <vector>
#include <algorithm>
#include <iterator>

#include "Vector.h"

namespace GraphicsMath
{

#pragma region Matrix Class Definition

	/* -------------------------------------------------------------------------------------------------
		Copyright 2017 Shealyn Tate Hindenlang

		Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
		and associated documentation files (the "Software"), to deal in the Software without restriction, 
		including without limitation the rights to use, copy, modify, merge, publish, distribute, 
		sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
		furnished to do so, subject to the following conditions:

		The above copyright notice and this permission notice shall be included in all copies or 
		substantial portions of the Software.

		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
		BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
		NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
		DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

		-------------------------------------------------------------------------------------------------

		Matrix<row, col> is a templated matrix class designed for 2 and 3 dimensional vector graphics.
		Specialized static methods make constructing and inverting affine transformation matrices faster
		and more efficient.

		Constructors:
			Matrix<row, col>()
			Matrix<row, col>(initializer_list<Vector<row>>)
			static Matrix::Scale(Vector)
			static Matrix::Translation(Vector)
			static Matrix::Rotation(Vector)

		Notes:
			- Matrices are stored in column-major order
			- The default constructor initializes an identity matrix
			- Currently, matrices are restricted to square dimensions in the range [2, 4]. This is
			  sufficient for graphics operations, but more generalized functionality may be added
			  at a future date.
			- The static Scale, Translation, Rotation, and Projection methods provide a streamlined way
			  to construct those matrices. 
			- The corresponding static inverse() methods can be used on the matrices for greater 
			  efficiency, provided the program does not arbitrarily alter the matrix. (e.g. If you've 
			  constructed a Scale matrix, altering any value outside of the diagonal and then calling 
			  ::ScaleInverse() will return an incorrectly inverted matrix.
			- Currently this library just handles 3d transformations using 4x4 matrices with the
			  homogeneous coordinate in the w spot.
		TODO:
			- Provide support for 2 dimensional affine transformations using 3x3 matrices
			- Add quaternion implementation for rotations
			- Implement iterator interface
	*/

	template<int row, int col>
	class Matrix
	{
		static_assert(1 < row && row < 5, "Row dimension must be in range [2, 4]");
		static_assert(1 < col && col < 5, "Column dimension must be in range [2, 4]");

	private:
		std::vector<Vector<row>> m_cols;
		
		std::string toString() const;
		void checkValidMatrix() const;

	public:
		static Matrix Scale(Vector<row - 1>);
		static Matrix Translation(Vector<row - 1>);
		static Matrix Rotation(Vector<row-1>, float);
		static Matrix OrthographicProjection(float, float, float, float, float, float);
		static Matrix PerspectiveProjection(float, float, float, float);

		static Matrix ScaleInverse(Matrix);
		static Matrix TranslationInverse(Matrix);
		static Matrix RotationInverse(Matrix);

		Matrix();
		Matrix(std::initializer_list<Vector<row>>);

		Vector<col>& operator [](const int);
		const Vector<col>& operator [](const int) const;

		bool operator ==(const Matrix&) const;

		Matrix operator +(const Matrix&) const;
		Matrix operator -(const Matrix&) const;
		Matrix operator *(const Matrix&) const;

		void operator +=(const Matrix&);
		void operator -=(const Matrix&);
		void operator *=(const Matrix&);

		Matrix operator *(float) const;
		void operator *=(float);

		Vector<row> operator *(const Vector<col>&) const;

		float determinant() const;
		Matrix inverse() const;
		void invert();

		Matrix transposition() const;
		void transpose();

		std::string to_string() const;

		friend std::ostream& operator <<(std::ostream& os, const Matrix& m)
		{
			os << m.toString() << std::endl;
			return os;
		}
	};

#pragma endregion

#pragma region Transformation Matrix Constructors

	Matrix<4, 4> Matrix<4, 4>::Scale(Vector<3> v)
	{
		Matrix<4, 4> result;

		for (int i = 0; i < 3; ++i)
			result[i][i] = v[i];

		return result;
	}

	Matrix<4, 4> Matrix<4, 4>::Translation(Vector<3> v)
	{
		Matrix<4, 4> result;

		for (int i = 0; i < 3; ++i)
			result[3][i] = v[i];

		return result;
	}

	Matrix<4, 4> Matrix<4, 4>::Rotation(Vector<3> axis, float theta)
	{
		Matrix<4, 4> result;
		
		float c = cosf(theta);
		float s = sinf(theta);
		float oMc = 1.0f - c;
		float x = axis[0];
		float y = axis[1];
		float z = axis[2];

		result[0][0] = c + oMc*x*x;   result[1][0] = oMc*x*y - z*s; result[2][0] = oMc*x*z + y*s;
		result[0][1] = oMc*x*y + z*s; result[1][1] = c + oMc*y*y;   result[2][1] = oMc*y*z - x*s;
		result[0][2] = oMc*x*z - y*s; result[1][2] = oMc*y*z + x*s; result[2][2] = c + oMc*z*z;

		return result;
	}

#pragma endregion

#pragma region Transformation Matrix Inversion

	Matrix<4, 4> Matrix<4, 4>::ScaleInverse(Matrix<4, 4> m)
	{
		auto result{ m };

		for (int i = 0; i < 3; ++i)
			result[i][i] = 1.0f / result[i][i];
		
		return result;
	}

	Matrix<4, 4> Matrix<4, 4>::TranslationInverse(Matrix<4, 4> m)
	{
		auto result{ m };

		for (int i = 0; i < 3; ++i)
			result[3][i] *= -1;

		return result;
	}

	Matrix<4, 4> Matrix<4, 4>::RotationInverse(Matrix<4, 4> m)
	{
		return m.transposition();
	}

	Matrix<4, 4> Matrix<4, 4>::OrthographicProjection(float l, float r, float t, float b, float zN, float zF)
	{
		Matrix<4, 4> result;

		float width = r - l;
		float height = t - b;
		float depth = zF - zN;

		result[0][0] = 2.0f / width;
		result[1][1] = 2.0f / height;
		result[2][2] = -2.0f / depth;

		result[3][0] = -(r + l) / width;
		result[3][1] = -(t + b) / height;
		result[3][2] = -(zF + zN) / depth;

		return result;
	}

	Matrix<4, 4> Matrix<4, 4>::PerspectiveProjection(float fovy, float aspect, float zNear, float zFar)
	{
		Matrix<4, 4> result;

		float top = zNear * tanf(fovy * PI / 360.0f);
		float bottom = -top;
		float right = top * aspect;
		float left = -right;

		float zNear2 = 2.0f * zNear;
		float width = right - left;
		float height = top - bottom;
		float depth = zFar - zNear;

		result[0][0] = zNear2 / width;
		result[1][1] = zNear2 / height;
		result[2][0] = (right + left) / width;
		result[2][1] = (top + bottom) / height;
		result[2][2] = (-zFar - zNear) / depth;
		result[2][3] = -1.0f;
		result[3][2] = (-zNear2 * zFar) / depth;
		result[3][3] = 0.0f;

		return result;
	}

#pragma endregion

#pragma region Private Methods

	template<int row, int col>
	void Matrix<row, col>::checkValidMatrix() const
	{
		if (row != col)
			throw std::runtime_error("Matrices must be square dimensions");
	}

	template<int row, int col>
	std::string Matrix<row, col>::toString() const
	{
		std::string result;

		for (int i = 0; i < row; ++i)
		{
			result += "[ ";
			for (int j = 0; j < col; ++j)
			{
				result += std::to_string(m_cols[j][i]);
				result += (j < col - 1) ? ", " : " ";
			}
			result += "]\n";
		}

		return result;
	}

#pragma endregion

#pragma region Constructors

	template<int row, int col>
	Matrix<row, col>::Matrix()
		: m_cols{ col, {} }
	{
		checkValidMatrix();

		for (int i = 0; i < row; ++i)
			m_cols[i][i] = 1;
	}

	template<int row, int col>
	Matrix<row, col>::Matrix(std::initializer_list<Vector<row>> args)
	{
		if (args.size() != col)
			throw std::runtime_error("Matrices must be square dimensions");

		for (auto r : args)
			m_cols.push_back(Vector<row>{r});
	}

#pragma endregion

#pragma region Subscript Operators

	template<int row, int col>
	Vector<col>& Matrix<row, col>::operator [](const int index)
	{
		if (index < 0 || index >= col)
			throw std::out_of_range("ERROR: Attempted to access value out of Matrix range.");

		return m_cols[index];
	}

	template<int row, int col>
	const Vector<col>& Matrix<row, col>::operator [](const int index) const
	{
		if (index < 0 || index >= col)
			throw std::out_of_range("ERROR: Attempted to access value out of Matrix range.");

		return m_cols[index];
	}

#pragma endregion

#pragma region Comparison Operators

	template<int row, int col>
	bool Matrix<row, col>::operator ==(const Matrix& m) const
	{
		for (int i = 0; i < row; ++i)
		{
			if (m_cols[i] != m[i])
				return false;
		}

		return true;
	}

#pragma endregion

#pragma region Matrix Addtion, Subtraction, & Multiplication

	template<int row, int col>
	Matrix<row, col> Matrix<row, col>::operator +(const Matrix<row, col>& m) const
	{
		Matrix<row, col> result;
	
		for (int i = 0; i < row; i++)
			result[i] = m_cols[i] + m[i];
		
		return result;
	}

	template<int row, int col>
	Matrix<row, col> Matrix<row, col>::operator -(const Matrix<row, col>& m) const
	{
		Matrix<row, col> result;

		for (int i = 0; i < row; i++)
			result[i] = m_cols[i] - m[i];

		return result;
	}

	template<int row, int col>
	Matrix<row, col> Matrix<row, col>::operator *(const Matrix<row, col>& m) const
	{
		Matrix<row, col> result;

		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				float sum = 0;

				for (int k = 0; k < col; ++k)
					sum += m_cols[k][j] * m[i][k];

				result[i][j] = sum;
			}
		}

		return result;
	}

	template<int row, int col>
	void Matrix<row, col>::operator +=(const Matrix<row, col>& m)
	{
		for (int i = 0; i < row; i++)
			m_cols[i] += m[i];
	}

	template<int row, int col>
	void Matrix<row, col>::operator -=(const Matrix<row, col>& m)
	{
		for (int i = 0; i < row; i++)
			m_cols[i] -= m[i];
	}

	template<int row, int col>
	void Matrix<row, col>::operator *=(const Matrix<row, col>& m)
	{
		*this = *this * m;
	}

	template<int row, int col>
	Vector<row> Matrix<row, col>::operator *(const Vector<col>& v) const
	{
		Vector<col> result;

		for (int i = 0; i < col; ++i)
		{
			for (int j = 0; j < row; ++j)
				result[i] += v[j] * m_cols[j][i];
		}

		return result;
	}

	template<int row, int col>
	Matrix<row, col> Matrix<row, col>::operator *(float s) const
	{
		auto result{ *this };

		for (int i = 0; i < row; ++i)
			result[i] *= s;
		
		return result;
	}

	template<int row, int col>
	void Matrix<row, col>::operator *=(float s)
	{
		for (int i = 0; i < row; ++i)
			m_cols[i] *= s;
	}

#pragma endregion

#pragma region Determinant

	float Matrix<2, 2>::determinant() const
	{
		return m_cols[0][0] * m_cols[1][1] - m_cols[0][1] * m_cols[1][0];
	}

	float Matrix<3, 3>::determinant() const
	{
		return m_cols[0][0] * m_cols[1][1] * m_cols[2][2] + m_cols[0][1] * m_cols[1][2] * m_cols[2][0] +
			   m_cols[0][2] * m_cols[1][0] * m_cols[2][1] - m_cols[0][0] * m_cols[1][2] * m_cols[2][1] -
			   m_cols[0][2] * m_cols[1][1] * m_cols[2][0] - m_cols[0][1] * m_cols[1][0] * m_cols[2][2];
	}

	float Matrix<4, 4>::determinant() const
	{
		return
			m_cols[0][0] * m_cols[1][1] * m_cols[2][2] * m_cols[3][3] + m_cols[0][0] * m_cols[2][1] * m_cols[3][2] * m_cols[1][3] +
			m_cols[0][0] * m_cols[3][1] * m_cols[1][2] * m_cols[2][3] + m_cols[1][0] * m_cols[0][1] * m_cols[3][2] * m_cols[2][3] +
			m_cols[1][0] * m_cols[2][1] * m_cols[0][2] * m_cols[3][3] + m_cols[1][0] * m_cols[3][1] * m_cols[2][2] * m_cols[0][3] +
			m_cols[2][0] * m_cols[0][1] * m_cols[1][2] * m_cols[3][3] + m_cols[2][0] * m_cols[1][1] * m_cols[3][2] * m_cols[0][3] +
			m_cols[2][0] * m_cols[3][1] * m_cols[0][2] * m_cols[1][3] + m_cols[3][0] * m_cols[0][1] * m_cols[2][2] * m_cols[1][3] +
			m_cols[3][0] * m_cols[1][1] * m_cols[0][2] * m_cols[2][3] + m_cols[3][0] * m_cols[2][1] * m_cols[1][2] * m_cols[0][3] -
			m_cols[0][0] * m_cols[1][1] * m_cols[3][2] * m_cols[2][3] - m_cols[0][0] * m_cols[2][1] * m_cols[1][2] * m_cols[3][3] -
			m_cols[0][0] * m_cols[3][1] * m_cols[2][2] * m_cols[1][3] - m_cols[1][0] * m_cols[0][1] * m_cols[2][2] * m_cols[3][3] -
			m_cols[1][0] * m_cols[2][1] * m_cols[3][2] * m_cols[0][3] - m_cols[1][0] * m_cols[3][1] * m_cols[0][2] * m_cols[2][3] -
			m_cols[2][0] * m_cols[0][1] * m_cols[3][2] * m_cols[1][3] - m_cols[2][0] * m_cols[1][1] * m_cols[0][2] * m_cols[3][3] -
			m_cols[2][0] * m_cols[3][1] * m_cols[1][2] * m_cols[0][3] - m_cols[3][0] * m_cols[0][1] * m_cols[1][2] * m_cols[2][3] -
			m_cols[3][0] * m_cols[1][1] * m_cols[2][2] * m_cols[0][3] - m_cols[3][0] * m_cols[2][1] * m_cols[0][2] * m_cols[1][3];
	}

#pragma endregion

#pragma region Inversion

	Matrix<2, 2> Matrix<2, 2>::inverse() const
	{
		float det = determinant();

		if (det == 0)
			throw std::exception("ERROR: Matrix cannot be inverted.");

		auto m = Matrix<2, 2>{ Vector<2>{m_cols[1][1], -m_cols[0][1]}, 
							   Vector<2>{-m_cols[1][0], m_cols[0][0]} };
		m *= 1.0f / det;

		return m;
	}

	Matrix<3, 3> Matrix<3, 3>::inverse() const
	{
		float det = determinant();

		if (det == 0)
			throw std::exception("ERROR: Matrix cannot be inverted.");

		auto m = Matrix<3, 3>{ Vector<3>{m_cols[1][1] * m_cols[2][2] - m_cols[2][1] * m_cols[1][2],
										 m_cols[2][1] * m_cols[0][2] - m_cols[0][1] * m_cols[2][2],
										 m_cols[0][1] * m_cols[1][2] - m_cols[1][1] * m_cols[0][2]},
							   Vector<3>{m_cols[2][0] * m_cols[1][2] - m_cols[1][0] * m_cols[2][2],
										 m_cols[0][0] * m_cols[2][2] - m_cols[2][0] * m_cols[0][2],
										 m_cols[1][0] * m_cols[0][2] - m_cols[0][0] * m_cols[1][2]},
							   Vector<3>{m_cols[1][0] * m_cols[2][1] - m_cols[2][0] * m_cols[1][1],
										 m_cols[2][0] * m_cols[0][1] - m_cols[0][0] * m_cols[2][1],
										 m_cols[0][0] * m_cols[1][1] - m_cols[1][0] * m_cols[0][1]} };
		
		m *= 1.0f / det;

		return m;
	}

	Matrix<4, 4> Matrix<4, 4>::inverse() const
	{
		float det = determinant();

		if (det == 0)
			throw std::exception("ERROR: Matrix cannot be inverted.");

		auto m = Matrix<4, 4>{
					Vector<4>{m_cols[1][1] * m_cols[2][2] * m_cols[3][3] + m_cols[2][1] * m_cols[3][2] * m_cols[1][3] + m_cols[3][1] * m_cols[1][2] * m_cols[2][3] -
							  m_cols[1][1] * m_cols[3][2] * m_cols[2][3] - m_cols[2][1] * m_cols[1][2] * m_cols[3][3] - m_cols[3][1] * m_cols[2][2] * m_cols[1][3],
							  m_cols[0][1] * m_cols[3][2] * m_cols[2][3] + m_cols[2][1] * m_cols[0][2] * m_cols[3][3] + m_cols[3][1] * m_cols[2][2] * m_cols[0][3] -
							  m_cols[0][1] * m_cols[2][2] * m_cols[3][3] - m_cols[2][1] * m_cols[3][2] * m_cols[0][3] - m_cols[3][1] * m_cols[0][2] * m_cols[2][3],
							  m_cols[0][1] * m_cols[1][2] * m_cols[3][3] + m_cols[1][1] * m_cols[3][2] * m_cols[0][3] + m_cols[3][1] * m_cols[0][2] * m_cols[1][3] -
							  m_cols[0][1] * m_cols[3][2] * m_cols[1][3] - m_cols[1][1] * m_cols[0][2] * m_cols[3][3] - m_cols[3][1] * m_cols[1][2] * m_cols[0][3],
							  m_cols[0][1] * m_cols[2][2] * m_cols[1][3] + m_cols[1][1] * m_cols[0][2] * m_cols[2][3] + m_cols[2][1] * m_cols[1][2] * m_cols[0][3] -
							  m_cols[0][1] * m_cols[1][2] * m_cols[2][3] - m_cols[1][1] * m_cols[2][2] * m_cols[0][3] - m_cols[2][1] * m_cols[0][2] * m_cols[1][3]},

					Vector<4>{m_cols[1][0] * m_cols[3][2] * m_cols[2][3] + m_cols[2][0] * m_cols[1][2] * m_cols[3][3] + m_cols[3][0] * m_cols[2][2] * m_cols[1][3] -
							  m_cols[1][0] * m_cols[2][2] * m_cols[3][3] - m_cols[2][0] * m_cols[3][2] * m_cols[1][3] - m_cols[3][0] * m_cols[1][2] * m_cols[2][3],
							  m_cols[0][0] * m_cols[2][2] * m_cols[3][3] + m_cols[2][0] * m_cols[3][2] * m_cols[0][3] + m_cols[3][0] * m_cols[0][2] * m_cols[2][3] -
							  m_cols[0][0] * m_cols[3][2] * m_cols[2][3] - m_cols[2][0] * m_cols[0][2] * m_cols[3][3] - m_cols[3][0] * m_cols[2][2] * m_cols[0][3],
							  m_cols[0][0] * m_cols[3][2] * m_cols[1][3] + m_cols[1][0] * m_cols[0][2] * m_cols[3][3] + m_cols[3][0] * m_cols[1][2] * m_cols[0][3] -
							  m_cols[0][0] * m_cols[1][2] * m_cols[3][3] - m_cols[1][0] * m_cols[3][2] * m_cols[0][3] - m_cols[3][0] * m_cols[0][2] * m_cols[1][3],
							  m_cols[0][0] * m_cols[1][2] * m_cols[2][3] + m_cols[1][0] * m_cols[2][2] * m_cols[0][3] + m_cols[2][0] * m_cols[0][2] * m_cols[1][3] -
							  m_cols[0][0] * m_cols[2][2] * m_cols[1][3] - m_cols[1][0] * m_cols[0][2] * m_cols[2][3] - m_cols[2][0] * m_cols[1][2] * m_cols[0][3]},

					Vector<4>{m_cols[1][0] * m_cols[2][1] * m_cols[3][3] + m_cols[2][0] * m_cols[3][1] * m_cols[1][3] + m_cols[3][0] * m_cols[1][1] * m_cols[2][3] -
							  m_cols[1][0] * m_cols[3][1] * m_cols[2][3] - m_cols[2][0] * m_cols[1][1] * m_cols[3][3] - m_cols[3][0] * m_cols[2][1] * m_cols[1][3],
							  m_cols[0][0] * m_cols[3][1] * m_cols[2][3] + m_cols[2][0] * m_cols[0][1] * m_cols[3][3] + m_cols[3][0] * m_cols[2][1] * m_cols[0][3] -
							  m_cols[0][0] * m_cols[2][1] * m_cols[3][3] - m_cols[2][0] * m_cols[3][1] * m_cols[0][3] - m_cols[3][0] * m_cols[0][1] * m_cols[2][3],
							  m_cols[0][0] * m_cols[1][1] * m_cols[3][3] + m_cols[1][0] * m_cols[3][1] * m_cols[0][3] + m_cols[3][0] * m_cols[0][1] * m_cols[1][3] -
							  m_cols[0][0] * m_cols[3][1] * m_cols[1][3] - m_cols[1][0] * m_cols[0][1] * m_cols[3][3] - m_cols[3][0] * m_cols[1][1] * m_cols[0][3],
							  m_cols[0][0] * m_cols[2][1] * m_cols[1][3] + m_cols[1][0] * m_cols[0][1] * m_cols[2][3] + m_cols[2][0] * m_cols[1][1] * m_cols[0][3] -
							  m_cols[0][0] * m_cols[1][1] * m_cols[2][3] - m_cols[1][0] * m_cols[2][1] * m_cols[0][3] - m_cols[2][0] * m_cols[0][1] * m_cols[1][3]},

					Vector<4>{m_cols[1][0] * m_cols[3][1] * m_cols[2][2] + m_cols[2][0] * m_cols[1][1] * m_cols[3][2] + m_cols[3][0] * m_cols[2][1] * m_cols[1][2] -
							  m_cols[1][0] * m_cols[2][1] * m_cols[3][2] - m_cols[2][0] * m_cols[3][1] * m_cols[1][2] - m_cols[3][0] * m_cols[1][1] * m_cols[2][2],
							  m_cols[0][0] * m_cols[2][1] * m_cols[3][2] + m_cols[2][0] * m_cols[3][1] * m_cols[0][2] + m_cols[3][0] * m_cols[0][1] * m_cols[2][2] -
							  m_cols[0][0] * m_cols[3][1] * m_cols[2][2] - m_cols[2][0] * m_cols[0][1] * m_cols[3][2] - m_cols[3][0] * m_cols[2][1] * m_cols[0][2],
							  m_cols[0][0] * m_cols[3][1] * m_cols[1][2] + m_cols[1][0] * m_cols[0][1] * m_cols[3][2] + m_cols[3][0] * m_cols[1][1] * m_cols[0][2] -
							  m_cols[0][0] * m_cols[1][1] * m_cols[3][2] - m_cols[1][0] * m_cols[3][1] * m_cols[0][2] - m_cols[3][0] * m_cols[0][1] * m_cols[1][2],
							  m_cols[0][0] * m_cols[1][1] * m_cols[2][2] + m_cols[1][0] * m_cols[2][1] * m_cols[0][2] + m_cols[2][0] * m_cols[0][1] * m_cols[1][2] -
							  m_cols[0][0] * m_cols[2][1] * m_cols[1][2] - m_cols[1][0] * m_cols[0][1] * m_cols[2][2] - m_cols[2][0] * m_cols[1][1] * m_cols[0][2]} };

		m *= 1.0f / det;

		return m;
	}

	template<int row, int col>
	void  Matrix<row, col>::invert()
	{
		*this = inverse();
	}

#pragma endregion

#pragma region Transpose

	template<int row, int col>
	Matrix<row, col> Matrix<row, col>::transposition() const
	{
		Matrix<row, col> result;

		for (int i = 0; i < col; ++i)
		{
			for (int j = 0; j < row; ++j)
				result[i][j] = m_cols[j][i];
		}

		return result;
	}

	template<int row, int col>
	void Matrix<row, col>::transpose()
	{
		*this = transposition();
	}

#pragma endregion

#pragma region Standard Methods

	template<int row, int col>
	std::string Matrix<row, col>::to_string() const
	{
		return this->toString();
	}

#pragma endregion

}



