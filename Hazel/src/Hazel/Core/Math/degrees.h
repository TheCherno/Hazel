#pragma once



#include<type_traits>
#include "Hazel/Core/Base.h"



// Extensive use of explicit for all converstion reduces the chances of unintentionally copying
//values between radians and degrees without performing a conversion calculation.
// implicit conversions are the devil's playground.



namespace Hazel
{
	class Radians;

	class Degrees
	{
	public:
		constexpr Degrees( void ) noexcept = default;
		~Degrees( void ) noexcept = default;

		constexpr Degrees( const Degrees& other ) noexcept : m_Angle( other.m_Angle ) {}
		explicit Degrees( const Radians& radians ) noexcept;
		Degrees( Degrees&& other ) noexcept { std::swap( this->m_Angle, other.m_Angle ); }
		explicit constexpr Degrees( float angle ) noexcept : m_Angle( angle ) {}
		explicit constexpr Degrees( double angle ) noexcept : m_Angle( static_cast<float>( angle ) ) {}
		explicit constexpr Degrees( long double angle ) noexcept : m_Angle( static_cast<float>( angle ) ) {}



		constexpr Degrees& operator=( const Degrees& other ) noexcept
		{
			m_Angle = other.m_Angle;
			return *this;
		}



		constexpr Degrees& operator=( Degrees&& other ) noexcept
		{
			if( *this != other )
			{
				std::swap( this->m_Angle, other.m_Angle );
			}
			return *this;
		}



		// Boolean
		//   Degrees
		[[nodiscard]] constexpr bool operator==( const Degrees& rhs ) const noexcept { return m_Angle == rhs.m_Angle; }
		[[nodiscard]] constexpr bool operator!=( const Degrees& rhs ) const noexcept { return !( *this == rhs ); }
		[[nodiscard]] constexpr bool operator<( const Degrees& rhs ) const noexcept { return m_Angle < rhs.m_Angle; }
		[[nodiscard]] constexpr bool operator>( const Degrees& rhs ) const noexcept { return ( *this >= rhs ) && ( *this != rhs ); }
		[[nodiscard]] constexpr bool operator<=( const Degrees& rhs ) const noexcept { return !( *this > rhs ); }
		[[nodiscard]] constexpr bool operator>=( const Degrees& rhs ) const noexcept { return !( *this < rhs ); }

		// Arithmetic
		[[nodiscard]] friend constexpr Degrees operator+( const Degrees& lhs, const Degrees rhs ) noexcept { return Degrees( lhs.m_Angle + rhs.m_Angle ); }
		[[nodiscard]] friend constexpr Degrees operator-( const Degrees& lhs, const Degrees rhs ) noexcept { return Degrees( lhs.m_Angle - rhs.m_Angle ); }
		[[nodiscard]] friend constexpr Degrees operator*( const Degrees& lhs, const float rhs ) noexcept { return Degrees( lhs.m_Angle * rhs ); }
		[[nodiscard]] friend constexpr Degrees operator/( const Degrees& lhs, const float rhs ) noexcept { return Degrees( lhs.m_Angle / rhs ); }

		// Arithmetic Assignment
		friend constexpr Degrees& operator+=( Degrees& lhs, const Degrees& rhs ) noexcept { lhs.m_Angle += rhs.m_Angle; return lhs; }
		friend constexpr Degrees& operator-=( Degrees& lhs, const Degrees& rhs ) noexcept { lhs.m_Angle -= rhs.m_Angle; return lhs; }
		friend constexpr Degrees& operator+=( Degrees& lhs, const float& rhs ) noexcept { return lhs += Degrees( rhs ); }
		friend constexpr Degrees& operator-=( Degrees& lhs, const float& rhs ) noexcept { return lhs -= Degrees( rhs ); }
		constexpr Degrees& operator*=( const float& rhs ) noexcept { m_Angle *= rhs; return *this; }
		constexpr Degrees& operator/=( const float& rhs ) noexcept { m_Angle /= rhs; return *this; }

		// Explicit conversions.
		//  I don't really see any great use cases for converstions to integral types,
		// but those can be trivially added or done by casting to fp-type then int-type.
		[[nodiscard]] explicit constexpr operator float( void ) const noexcept { return m_Angle; }
		[[nodiscard]] explicit constexpr operator double( void ) const noexcept { return static_cast<double>( m_Angle ); }
		[[nodiscard]] explicit constexpr operator long double( void ) const noexcept { return static_cast<long double>( m_Angle ); }
		[[nodiscard]] explicit constexpr operator Radians( void ) const noexcept;

		[[nodiscard]] constexpr Degrees reduced( void ) const noexcept;
		constexpr void reduce( void ) noexcept { *this = reduced(); }

		static constexpr const float ONE_FULL_ROTATION{ 360.0f };
		static constexpr const float MAX_ANGLE{ 180.0f };
		static constexpr const float MIN_ANGLE{ -180.0f };


	private:
		constexpr float degreesToRadians( float degrees ) const noexcept;
		constexpr float radiansToDegrees( float radians ) const noexcept;

	private:
		float m_Angle{ 0.0f };
	};



	float sin( const Degrees& theta );
	float cos( const Degrees& theta );
	float tan( const Degrees& theta );
}


