#include "hzpch.h"



#include "Hazel/Core/Base.h"
#include "Hazel/Core/Math/radians.h"
#include "Hazel/Core/Math/degrees.h"



namespace Hazel
{
    Radians::Radians( const Degrees& degs ) noexcept
        :
        accumulated_( deg_to_rad( static_cast<float>( degs ) ) )
    {}



    [[nodiscard]]
    constexpr Radians::operator Degrees( void ) const noexcept
    {
        return Degrees( rad_to_deg( accumulated_ ) );
    }



    [[nodiscard]]
    constexpr Radians Radians::reduced( void ) const noexcept
    {
        auto angle = accumulated_;
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
    constexpr float Radians::rad_to_deg( float rad ) const noexcept
    {
        constexpr float CONVERSION{ 180.0f / PI };
        return rad * CONVERSION;
    }



    [[nodiscard]]
    constexpr float Radians::deg_to_rad( float deg ) const noexcept
    {
        constexpr float CONVERSION{ PI / 180.0f };
        return deg * CONVERSION;
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
