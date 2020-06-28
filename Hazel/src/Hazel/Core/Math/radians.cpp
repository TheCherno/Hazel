#include "hzpch.h"



#include "Hazel/Core/Base.h"
#include "Hazel/Core/Math/radians.h"
#include "Hazel/Core/Math/degrees.h"



namespace Hazel
{
	Radians::Radians( const Degrees& degrees ) noexcept
		:
		m_Angle( degreesToRadians( static_cast<float>( degrees ) ) )
	{}



	[[nodiscard]]
	constexpr Radians::operator Degrees( void ) const noexcept
	{
		return Degrees( radiansToDegrees( m_Angle ) );
	}



	[[nodiscard]]
	constexpr Radians Radians::reduced( void ) const noexcept
	{
		auto angle = m_Angle;
		while( angle > MAX_ANGLE )
		{
			angle -= ONE_FULL_ROTATION;
		}
		while( angle < MIN_ANGLE )
		{
			angle += ONE_FULL_ROTATION;
		}
		return Radians( angle );
	}



	[[nodiscard]]
	constexpr float Radians::radiansToDegrees( float radians ) const noexcept
	{
		constexpr float CONVERSION{ 180.0f / PI };
		return radians * CONVERSION;
	}



	[[nodiscard]]
	constexpr float Radians::degreesToRadians( float degrees ) const noexcept
	{
		constexpr float CONVERSION{ PI / 180.0f };
		return degrees * CONVERSION;
	}



	[[nodiscard]]
	constexpr bool operator==( Radians lhs, const Degrees& rhs ) noexcept
	{
		return lhs == static_cast<Radians>( rhs );
	}



	[[nodiscard]]
	constexpr bool operator!=( Radians lhs, const Degrees& rhs ) noexcept
	{
		return lhs != static_cast<Radians>( rhs );
	}



	[[nodiscard]]
	constexpr bool operator<( Radians lhs, const Degrees& rhs ) noexcept
	{
		return lhs < static_cast<Radians>( rhs );
	}



	[[nodiscard]]
	constexpr bool operator>( Radians lhs, const Degrees& rhs ) noexcept
	{
		return lhs > static_cast<Radians>( rhs );
	}



	[[nodiscard]]
	constexpr bool operator<=( Radians lhs, const Degrees& rhs ) noexcept
	{
		return lhs <= static_cast<Radians>( rhs );
	}



	[[nodiscard]]
	constexpr bool operator>=( Radians lhs, const Degrees& rhs ) noexcept
	{
		return lhs >= static_cast<Radians>( rhs );
	}



	[[nodiscard]]
	float sin( const Radians& theta )
	{
		return std::sin( static_cast<float>( theta ) );
	}

	[[nodiscard]]
	float cos( const Radians& theta )
	{
		return std::cos( static_cast<float>( theta ) );
	}

	[[nodiscard]]
	float tan( const Radians& theta )
	{
		return std::tan( static_cast<float>( theta ) );
	}



	[[nodiscard]]
	Radians asin( float arg )
	{
		return Radians( std::asin( arg ) );
	}

	[[nodiscard]]
	Radians acos( float arg )
	{
		return Radians( std::acos( arg ) );
	}

	[[nodiscard]]
	Radians atan( float arg )
	{
		return Radians( std::atan( arg ) );
	}

	[[nodiscard]]
	Radians atan2( float y, float x )
	{
		return Radians( std::atan2( y, x ) );
	}
}
