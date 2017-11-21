#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <string>
#include <iostream>

namespace GraphicsMath
{
	static const float PI = 3.14159f;

#pragma region Vector Class Definition

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

		Vector<size> is a templated vector class designed for 2 and 3 dimensional vector graphics.
	
		Constructors:
			Vector<size>()
			Vector<size>(initializer_list<float>)
	
		Notes:
			- If fewer arguments are given to the constructor than the dimension, the rest of the values
				are set to zero.
			- Currently, vectors are restricted to the range [2, 4]. This is sufficient for graphics 
				operations, but more generalized functionality may be added at a future date.
			- operator * overloaded to be the Cartesian Product of two vectors
			- The cross product between two vectors is only meaningful in 3 dimensions, and therefore 
				only define for Vector<3>.
		TODO:
			- Make move assignment
			- Define rest of comparisons in terms of == and < 
	*/

	template<int size>
	class Vector
	{
		static_assert(size > 1 && size < 5, "Vector dimension must be in range [2, 4]");
		
	private:
		std::vector<float> m_data;

		void copyElements(const std::vector<float>&);
		std::string toString() const;

	public:
		Vector();
		Vector(std::initializer_list<float>);

		Vector(const Vector&);
		Vector& operator=(const Vector&);

		float& operator[](const int);
		const float& operator[](const int) const;

		std::vector<float>::iterator begin();
		std::vector<float>::const_iterator begin() const;
		std::vector<float>::iterator end();
		std::vector<float>::const_iterator end() const;

		Vector operator +(const Vector&) const;
		Vector operator +(const float) const;
		Vector operator -(const Vector&) const;
		Vector operator -(const float) const;
		Vector operator *(const Vector&) const;
		Vector operator *(const float) const;
		Vector operator /(float) const;
		void operator +=(const Vector&);
		void operator +=(const float);
		void operator -=(const Vector&);
		void operator -=(const float);
		void operator *=(const Vector&);
		void operator *=(const float);
		void operator /=(const float);
		
		bool operator ==(const Vector&) const;
		bool operator !=(const Vector&) const;
		bool operator >(const Vector&) const;
		bool operator <(const Vector&) const;
		bool operator >=(const Vector&) const;
		bool operator <=(const Vector&) const;

		float squareMagnitude() const;
		float magnitude() const;
		float dotProduct(const Vector&) const;
		Vector crossProduct(const Vector&) const;
		Vector normal() const;
		void normalize();
		Vector homogenous() const;
		void homogenize();

		std::string to_string() const;

		friend std::ostream& operator <<(std::ostream& os, const Vector& v)
		{
			os << v.toString() << std::endl;
			return os;
		}
	};

#pragma endregion

#pragma region Private Methods

	template<int size>
	void Vector<size>::copyElements(const std::vector<float>& v)
	{
		std::copy(std::begin(v), std::end(v), std::begin(m_data));
	}

	template<int size>
	std::string Vector<size>::toString() const
	{
		std::string output = "Vector<" + std::to_string(size) + "> (";

		for (int i = 0; i < size; i++)
		{
			output += std::to_string(m_data[i]);
			if (i != size - 1)
				output += ", ";
		}

		output += ")";

		return output;
	}


#pragma endregion

#pragma region Constructors

	template<int size>
	Vector<size>::Vector()
		: m_data(size, 0)
	{
		// TODO: Remove this and see if m_data fills with zero value on default
	}

	template<int size>
	Vector<size>::Vector(std::initializer_list<float> args)
	{
		if (args.size() > size)
			throw std::out_of_range("ERROR: Cannot add more elements to a vector than it can hold.");

		// Insert all given values and fill remaining space with zeros
		m_data.insert(m_data.begin(), args);
		m_data.insert(m_data.end(), size - args.size(), 0);
	}

#pragma endregion

#pragma region Copy Constructor & Assignment
	
	template<int size>
	Vector<size>::Vector(const Vector<size>& v)
	{
		m_data = v.m_data;
	}

	template<int size>
	Vector<size>& Vector<size>::operator=(const Vector<size>& v)
	{
		Vector<size> c(v);
		m_data = c.m_data;

		return *this;
	}

#pragma endregion

#pragma region Subscript Operators

	template<int size>
	float& Vector<size>::operator[](const int index)
	{
		if (index < 0 || index >= size)
			throw std::out_of_range("ERROR: Attempted to access value out of Vector range.");

		return m_data[index];
	}

	template<int size>
	const float& Vector<size>::operator[](const int index) const
	{
		if (index < 0 || index >= size)
			throw std::out_of_range("ERROR: Attempted to access value out of Vector range.");

		return m_data[index];
	}

#pragma endregion

#pragma region Iterators

	template<int size>
	std::vector<float>::iterator Vector<size>::begin()
	{ 
		return m_data.begin(); 
	}

	template<int size>
	std::vector<float>::const_iterator Vector<size>::begin() const
	{ 
		return m_data.begin(); 
	}

	template<int size>
	std::vector<float>::iterator Vector<size>::end()
	{ 
		return m_data.end(); 
	}

	template<int size>
	std::vector<float>::const_iterator Vector<size>::end() const
	{ 
		return m_data.end(); 
	}

#pragma endregion

#pragma region Addition, Subtraction, & Multiplication

	template<int size>
	Vector<size> Vector<size>::operator +(const Vector<size>& v) const
	{
		Vector<size> r;
		for (int i = 0; i < size; ++i)
			r[i] = m_data[i] + v[i];

		return r;
	}

	template<int size>
	Vector<size> Vector<size>::operator +(const float s) const
	{
		Vector<size> r;
		for (int i = 0; i < size; ++i)
			r[i] = m_data[i] + s;

		return r;
	}

	template<int size>
	Vector<size> Vector<size>::operator -(const Vector<size>& v) const
	{
		Vector<size> r;
		for (int i = 0; i < size; ++i)
			r[i] = m_data[i] - v[i];

		return r;
	}

	template<int size> 
	Vector<size> Vector<size>::operator -(const float s) const
	{
		Vector<size> r;
		for (int i = 0; i < size; ++i)
			r[i] = m_data[i] - s;

		return r;
	}

	template<int size>
	Vector<size> Vector<size>::operator *(const Vector<size>& v) const
	{
		Vector<size> r;
		for (int i = 0; i < size; ++i)
			r[i] = m_data[i] * v[i];

		return r;
	}

	template<int size>
	Vector<size> Vector<size>::operator *(const float s) const
	{
		Vector<size> r;
		for (int i = 0; i < size; ++i)
			r[i] = m_data[i] * s;

		return r;
	}

	template<int size>
	Vector<size> Vector<size>::operator /(const float s) const
	{
		if (s == 0)
			throw std::runtime_error("Cannot divide vector by zero scalar.");

		Vector<size> r;
		for (int i = 0; i < size; ++i)
			r[i] = m_data[i] / s;

		return r;
	}

	template<int size>
	void Vector<size>::operator +=(const Vector<size>& v)
	{
		for (int i = 0; i < size; ++i)
			m_data[i] += v[i];
	}

	template<int size>
	void Vector<size>::operator +=(float s)
	{
		for (int i = 0; i < size; ++i)
			m_data[i] += s;
	}

	template<int size>
	void Vector<size>::operator -=(const Vector<size>& v)
	{
		for (int i = 0; i < size; ++i)
			m_data[i] -= v[i];
	}

	template<int size>
	void Vector<size>::operator -=(const float s)
	{
		for (int i = 0; i < size; ++i)
			m_data[i] -= s;
	}

	template<int size>
	void Vector<size>::operator *=(const Vector<size>& v)
	{
		for (int i = 0; i < size; ++i)
			m_data[i] *= v[i];
	}

	template<int size>
	void Vector<size>::operator *=(const float s)
	{
		for (int i = 0; i < size; ++i)
			m_data[i] *= s;
	}

	template<int size>
	void Vector<size>::operator /=(const float s)
	{
		if (s == 0)
			throw std::runtime_error("Cannot divide vector by zero scalar.");

		for (int i = 0; i < size; ++i)
			m_data[i] /= s;
	}

#pragma endregion

#pragma region Comparison Operators

	template<int size>
	bool Vector<size>::operator ==(const Vector<size>& v) const
	{
		for (int i = 0; i < size; ++i)
		{
			if (m_data[i] != v[i])
				return false;
		}

		return true;
	}

	template<int size>
	bool Vector<size>::operator !=(const Vector<size>& v) const
	{
		return !(*this == v);
	}

	template<int size>
	bool Vector<size>::operator >(const Vector<size>& v) const
	{
		for (int i = 0; i < size; ++i)
		{
			if (m_data[i] <= v[i])
				return false;
		}

		return true;
	}

	template<int size>
	bool Vector<size>::operator <(const Vector<size>& v) const
	{
		for (int i = 0; i < size; ++i)
		{
			if (m_data[i] >= v[i])
				return false;
		}

		return true;
	}

	template<int size>
	bool Vector<size>::operator >=(const Vector<size>& v) const
	{
		for (int i = 0; i < size; ++i)
		{
			if (m_data[i] < v[i])
				return false;
		}

		return true;
	}

	template<int size>
	bool Vector<size>::operator <=(const Vector<size>& v) const
	{
		for (int i = 0; i < size; ++i)
		{
			if (m_data[i] > v[i])
				return false;
		}

		return true;
	}

#pragma endregion

#pragma region Vector Specific Operations

	template<int size>
	float Vector<size>::squareMagnitude() const
	{
		float result = 0;

		for (int i = 0; i < size; ++i)
			result += m_data[i] * m_data[i];

		return result;
	}

	template<int size>
	float Vector<size>::magnitude() const
	{
		return sqrt(this->squareMagnitude());
	}

	template<int size>
	float Vector<size>::dotProduct(const Vector<size>& v) const
	{
		float result = 0;

		for (int i = 0; i < size; ++i)
			result += m_data[i] * v[i];

		return result;
	}

	template<int size>
	Vector<size> Vector<size>::crossProduct(const Vector<size>& v) const
	{
		static_assert(size == 3, "Cross product only valid in 3 dimensional space.");

		Vector<size> product;
		product[0] = m_data[1] * v[2] - m_data[2] * v[1];
		product[1] = m_data[2] * v[0] - m_data[0] * v[2];
		product[2] = m_data[0] * v[1] - m_data[1] * v[0];

		return product;
	}

	template<int size>
	Vector<size> Vector<size>::normal() const
	{
		float m = this->magnitude();

		Vector<size> v;
		for (int i = 0; i < size; ++i)
			v[i] = m_data[i] / m;

		return v;
	}

	template<int size>
	void Vector<size>::normalize()
	{
		float m = this->magnitude();

		for (int i = 0; i < size; ++i)
			m_data[i] /= m;
	}

	template<int size>
	Vector<size> Vector<size>::homogenous() const
	{
		Vector result{ *this };
		result.homogenize();

		return result;
	}

	template<int size>
	void Vector<size>::homogenize()
	{
		if (m_data[size - 1] != 0)
		{
			for (int i = 0; i < size - 1; ++i)
				m_data[i] /= m_data[size - 1];
		}
	}

#pragma endregion

#pragma region Standard Methods

	template<int size>
	std::string Vector<size>::to_string() const
	{
		return this->toString();
	}

#pragma endregion

#pragma region Vector Conversion Methods

	Vector<3> lowerDimension(const Vector<4>& v);

	Vector<2> lowerDimension(const Vector<3>& v);

	Vector<4> higherDimension(const Vector<3>& v, float w);

	Vector<3> higherDimension(const Vector<2>& v, float z);

#pragma endregion

}

#endif