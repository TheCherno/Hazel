#include "hzpch.h"



#include "Hazel/Core/Base.h"
#include "Hazel/Core/Math/degrees.h"
#include "Hazel/Core/Math/radians.h"



namespace Hazel
{
    Degrees::Degrees( const Radians& rads ) noexcept
        :
        accumulated_( rad_to_deg( static_cast<float>( rads ) ) )
    {}



    [[nodiscard]]
    constexpr Degrees::operator Radians( void ) const noexcept
    {
        return Radians( deg_to_rad( accumulated_ ) );
    }



    [[nodiscard]]
    constexpr Degrees Degrees::reduced( void ) const noexcept
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
        return Degrees( angle );
    }



    [[nodiscard]] constexpr float Degrees::deg_to_rad( float deg ) const noexcept
    {
        constexpr float CONVERSION{ PI / 180.0f };
        return deg * CONVERSION;
    }

    [[nodiscard]] constexpr float Degrees::rad_to_deg( float rad ) const noexcept
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
