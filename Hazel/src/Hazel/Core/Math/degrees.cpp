#include "hzpch.h"



#include "Hazel/Core/Base.h"
#include "Hazel/Core/Math/degrees.h"
#include "Hazel/Core/Math/radians.h"



namespace Hazel
{
	Degrees::Degrees( const Radians& radians ) noexcept
		:
		m_Angle( radiansToDegrees( static_cast<float>( radians ) ) )
	{}



	[[nodiscard]]
	constexpr Degrees::operator Radians( void ) const noexcept
	{
		return Radians( degreesToRadians( m_Angle ) );
	}



	[[nodiscard]]
	constexpr Degrees Degrees::reduced( void ) const noexcept
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
		return Degrees( angle );
	}



	[[nodiscard]] constexpr float Degrees::degreesToRadians( float degrees ) const noexcept
	{
		constexpr float CONVERSION{ PI / 180.0f };
		return degrees * CONVERSION;
	}

	[[nodiscard]] constexpr float Degrees::radiansToDegrees( float rad ) const noexcept
	{
		constexpr float CONVERSION{ 180.0f / PI };
		return rad * CONVERSION;
	}


	[[nodiscard]] float sin( const Degrees& theta )
	{
		return sin( static_cast<Radians>( theta ) );
	}

	[[nodiscard]] float cos( const Degrees& theta )
	{
		return cos( static_cast<Radians>( theta ) );
	}

	[[nodiscard]] float tan( const Degrees& theta )
	{
		return tan( static_cast<Radians>( theta ) );
	}
}
