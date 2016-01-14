#ifndef DECAF_MATH_VECTOR_HH_
#define DECAF_MATH_VECTOR_HH_

#include <algorithm>
#include <array>
#include <string>
#include <cmath>

namespace decaf
{

	/// <summary>A templated class representing an n-dimensional geometric vector.</summary>
	template <typename T, size_t S>
	class VectorN
	{

	public:

		VectorN() 
		{ 
			std::fill(m_data.begin(), m_data.end(), T(0));
		}

		VectorN(const VectorN<T, S>& other)
		{
			Assign(other);
		}

		VectorN(T fill)
		{
			Assign(fill);
		}

		inline VectorN<T, S>& operator = (const VectorN<T, S>& other)
		{
			Assign(other);
			return *this;
		}

		inline VectorN<T, S>& operator = (T fill)
		{
			Assign(fill);
			return *this;
		}

		inline T& operator [] (size_t i)
		{
			return m_data[i];
		}

		inline const T& operator [] (size_t i) const
		{
			return m_data[i];
		}

		/// <summary>Calculates the squared length of the <c>VectorN</c>.</summary>
		/// <returns>The squared length of the <c>VectorN</c>.</summary>
		inline T LengthSquared() const
		{
			T result = 0;

			for (auto elem : m_data)
				result += (elem * elem);

			return result;
		}

		/// <summary>Calculates the length of the <c>VectorN</c>.</summary>
		/// <returns>The length of the <c>VectorN</c>.</summary>
		inline T Length() const
		{
			return static_cast<T>(sqrt(LengthSquared()));
		}

		/// <summary>Normalizes the <c>VectorN</c>.</summary>
		/// <returns>A reference to the normalized <c>VectorN</c>.</summary>
		inline VectorN<T, S>& Normalize()
		{
			T len = Length();

			for (auto& elem : m_data)
				elem /= len;

			return *this;
		}

	protected:

		std::array<T, S> m_data;

	private:

		inline void Assign(const VectorN<T, S>& other)
		{
			std::copy(other.m_data.begin(), other.m_data.end(), m_data.begin());
		}

		inline void Assign(T fill)
		{
			std::fill(m_data.begin(), m_data.end(), fill);
		}

	};

	/// <summary>A templated class representing a 2-dimensional geometric vector.</summary>
	template <typename T>
	class Vector2 : public VectorN<T, 2>
	{

	public:

		Vector2() : VectorN<T, 2>() { }

		Vector2(const VectorN<T, 2>& other) : VectorN<T, 2>(other) { }

		Vector2(T fill) : VectorN<T, 2>(fill) { }

		Vector2(T x, T y)
		{
			m_data[0] = x;
			m_data[1] = y;
		}

		inline T& X() { return m_data[0]; }

		inline const T& X() const { return m_data[0]; }

		inline T& Y() { return m_data[1]; }

		inline const T& Y() const { return m_data[1]; }

	};

	using Vector2u = Vector2<unsigned int>;
	using Vector2i = Vector2<signed int>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;

	/// <summary>A templated class representing a 3-dimensional geometric vector.</summary>
	template <typename T>
	class Vector3 : public VectorN<T, 3>
	{

	public:

		Vector3() : VectorN<T, 3>() { }

		Vector3(const VectorN<T, 3>& other) : VectorN<T, 3>(other) { }

		Vector3(T fill) : VectorN<T, 3>(fill) { }

		Vector3(T x, T y, T z)
		{
			m_data[0] = x;
			m_data[1] = y;
			m_data[2] = z;
		}

		Vector3(const VectorN<T, 2>& vector, T z)
			: Vector3(vector[0], vector[1], z) { }

		inline T& X() { return m_data[0]; }

		inline const T& X() const { return m_data[0]; }

		inline T& Y() { return m_data[1]; }

		inline const T& Y() const { return m_data[1]; }

		inline T& Z() { return m_data[2]; }

		inline const T& Z() const { return m_data[2]; }

	};

	using Vector3u = Vector3<unsigned int>;
	using Vector3i = Vector3<signed int>;
	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;

	/// <summary>A templated class representing a 4-dimensional geometric vector.</summary>
	template <typename T>
	class Vector4 : public VectorN<T, 4>
	{

	public:

		Vector4() : VectorN<T, 4>() { }

		Vector4(const VectorN<T, 4>& other) : VectorN<T, 4>(other) { }

		Vector4(T fill) : VectorN<T, 4>(fill) { }

		Vector4(T x, T y, T z, T w)
		{
			m_data[0] = x;
			m_data[1] = y;
			m_data[2] = z;
			m_data[3] = w;
		}

		Vector4(const VectorN<T, 3>& vector, T w)
			: Vector4(vector[0], vector[1], vector[2], w) { }

		Vector4(const VectorN<T, 2>& vectorA, const VectorN<T, 2>& vectorB)
			: Vector4(vectorA[0], vectorA[1], vectorB[0], vectorB[1]) { }

		inline T& X() { return m_data[0]; }

		inline const T& X() const { return m_data[0]; }

		inline T& Y() { return m_data[1]; }

		inline const T& Y() const { return m_data[1]; }

		inline T& Z() { return m_data[2]; }

		inline const T& Z() const { return m_data[2]; }

		inline T& W() { return m_data[3]; }

		inline const T& W() const { return m_data[3]; }

	};

	using Vector4u = Vector4<unsigned int>;
	using Vector4i = Vector4<signed int>;
	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;

	template <typename T, size_t S>
	inline bool operator == (const VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
	{
		return std::equal(&lhs[0], &lhs[S - 1], &rhs[0], &rhs[S - 1]);
	}

	template <typename T, size_t S>
	inline bool operator != (const VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, size_t S>
	inline VectorN<T, S> operator - (const VectorN<T, S>& that)
	{
		VectorN<T, S> result;

		for (size_t i = 0; i < S; ++i)
			result[i] = -that[i];

		return result;
	}

	template <typename T, size_t S>
	inline VectorN<T, S>& operator += (VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
	{
		for (size_t i = 0; i < S; ++i)
			lhs[i] += rhs[i];

		return lhs;
	}

	template <typename T, size_t S>
	inline VectorN<T, S> operator + (const VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
	{
		VectorN<T, S> result(lhs);
		return (result += rhs);
	}

	template <typename T, size_t S>
	inline VectorN<T, S>& operator -= (VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
	{
		for (size_t i = 0; i < S; ++i)
			lhs[i] -= rhs[i];
		
		return lhs;
	}

	template <typename T, size_t S>
	inline VectorN<T, S> operator - (const VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
	{
		VectorN<T, S> result(lhs);
		return (result -= rhs);
	}

	template <typename T, size_t S>
	inline VectorN<T, S>& operator *= (VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
	{
		for (size_t i = 0; i < S; ++i)
			lhs[i] *= rhs[i];

		return lhs;
	}

	template <typename T, size_t S>
	inline VectorN<T, S> operator * (const VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
	{
		VectorN<T, S> result(lhs);
		return (result *= rhs);
	}

	template <typename T, size_t S>
	inline VectorN<T, S>& operator *= (VectorN<T, S>& lhs, const T rhs)
	{
		for (size_t i = 0; i < S; ++i)
			lhs[i] *= rhs;

		return lhs;
	}

	template <typename T, size_t S>
	inline VectorN<T, S> operator * (const VectorN<T, S>& lhs, const T rhs)
	{
		VectorN<T, S> result(lhs);
		return (result *= rhs);
	}

	template <typename T, size_t S>
	inline VectorN<T, S>& operator /= (VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
	{
		for (size_t i = 0; i < S; ++i)
			lhs[i] /= rhs[i];

		return lhs;
	}

	template <typename T, size_t S>
	inline VectorN<T, S> operator / (const VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
	{
		VectorN<T, S> result(lhs);
		return (result /= rhs);
	}

	template <typename T, size_t S>
	inline VectorN<T, S>& operator /= (VectorN<T, S>& lhs, const T rhs)
	{
		for (size_t i = 0; i < S; ++i)
			lhs[i] /= rhs;
		
		return lhs;
	}

	template <typename T, size_t S>
	inline VectorN<T, S> operator / (const VectorN<T, S>& lhs, const T rhs)
	{
		VectorN<T, S> result(lhs);
		return (result /= rhs);
	}

	namespace Vector
	{
		
		/// <summary>Calculates the dot product of two n-dimensional <c>Vector</c>s.</summary>
		/// <param name='lhs'>The left-hand operand.</param>
		/// <param name='rhs'>The right-hand operand.</param>
		/// <returns>The dot product of two n-dimensional <c>Vector</c>s.</returns>
		template <typename T, size_t S>
		inline T Dot(const VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
		{
			T result = T(0);

			for (size_t i = 0; i < S; ++i)
				result += (lhs[i] * rhs[i]);

			return result;
		}

		/// <summary>Calculates the cross product of two 3-dimensional <c>Vector</c>s.</summary>
		/// <param name='lhs'>The left-hand operand.</param>
		/// <param name='rhs'>The right-hand operand.</param>
		/// <returns>A 3-dimensional <c>Vector</c> representing the cross product of <paramref name='lhs'/> and <paramref name='rhs'/>.</returns>
		template <typename T>
		inline VectorN<T, 3> Cross(const VectorN<T, 3>& lhs, const VectorN<T, 3>& rhs)
		{
			VectorN<T, 3> result;

			result[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
			result[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
			result[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];

			return result;
		}

		/// <summary>Reflects a <c>Vector</c> around a normal.</summary>
		/// <param name='vector'>The <c>Vector</c> to reflect.</param>
		/// <param name='normal'>The normal to reflect the <c>Vector</c> around.</param>
		/// <returns>A <c>Vector</c> representing '<paramref name='vector'/>' reflected around '<paramref name='normal'/>.</returns>
		template <typename T, size_t S>
		inline VectorN<T, S> Reflect(const VectorN<T, S>& vector, const VectorN<T, S>& normal)
		{
			return (vector - (normal * Dot(vector, normal) * T(2)));
		}

		/// <summary>Refracts a <c>Vector</c> around a normal.</summary>
		/// <param name='vector'>The <c>Vector</c> to refract.</param>
		/// <param name='normal'>The normal to refract the <c>Vector</c> around.</param>
		/// <param name='amount'>The amount of refraction to apply.</param>
		/// <returns>A <c>Vector</c> representing '<paramref name='vector'/>' refracted around '<paramref name='normal'/>.</returns>
		template <typename T, size_t S>
		inline VectorN<T, S> Refract(const VectorN<T, S>& vector, const VectorN<T, S>& normal, const T amount)
		{
			float NdotV = Dot(normal, vector);
			float k = T(1) - (amount * amount * (T(1) - NdotV * NdotV));
			if (k < T(0))
				return VectorN<T, S>(T(0));
			else
				return (vector * amount) - (normal * (amount * NdotV + sqrtf(k)));
		}

		/// <summary>Compares two <c>VectorN</c> objects and returns a new <c>VectorN</c> with each member set to the lower value of each corresponding pair of members.</summary>
		/// <param name="lhs">The first of the two <c>VectorN</c> objects to compare.</param>
		/// <param name="rhs">The second of the two <c>VectorN</c> objects to compare.</param>
		/// <returns>A new <c>VectorN</c> with each member set to the lower value of each corresponding pair of members.</returns>
		template <typename T, size_t S>
		inline VectorN<T, S> Min(const VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
		{
			VectorN<T, S> result;

			for (size_t i = 0; i < S; ++i)
				result[i] = std::min(lhs[i], rhs[i]);

			return result;
		}

		/// <summary>Compares two <c>VectorN</c> objects and returns a new <c>VectorN</c> with each member set to the greater value of each corresponding pair of members.</summary>
		/// <param name="lhs">The first of the two <c>VectorN</c> objects to compare.</param>
		/// <param name="rhs">The second of the two <c>VectorN</c> objects to compare.</param>
		/// <returns>A new <c>VectorN</c> with each member set to the greater value of each corresponding pair of members.</returns>
		template <typename T, size_t S>
		inline VectorN<T, S> Max(const VectorN<T, S>& lhs, const VectorN<T, S>& rhs)
		{
			VectorN<T, S> result;

			for (size_t i = 0; i < S; ++i)
				result[i] = std::max(lhs[i], rhs[i]);

			return result;
		}

	};

}

#endif
