#pragma once



#include<cmath>
#include<type_traits>
#include "Hazel/Core/Base.h"



// Extensive use of explicit conversions helps reduce the chances of unintentionally copying
//values between radians and degrees without performing a conversion calculation.



namespace Hazel
{
    class Degrees;



    class Radians
    {
    public:
        constexpr Radians( void ) noexcept = default;
        ~Radians( void ) noexcept = default;

        constexpr Radians( const Radians& other ) noexcept : m_Angle( other.m_Angle ) {}
        explicit Radians( const Degrees& degrees ) noexcept;
        Radians( Radians&& other ) noexcept { std::swap( this->m_Angle, other.m_Angle ); }
        explicit constexpr Radians( float angle ) noexcept : m_Angle( angle ) {}
        explicit constexpr Radians( double angle ) noexcept : m_Angle( static_cast<float>( angle ) ) {}
        explicit constexpr Radians( long double angle ) noexcept : m_Angle( static_cast<float>( angle ) ) {}



        constexpr Radians& operator=( const Radians& other ) noexcept
        {
            m_Angle = other.m_Angle;
            return *this;
        }



        constexpr Radians& operator=( Radians&& other ) noexcept
        {
            if( *this != other )
            {
                std::swap( this->m_Angle, other.m_Angle );
            }
            return *this;
        }


        // Boolean
        //  Radians
        [[nodiscard]] friend constexpr bool operator==( Radians lhs, const Radians& rhs ) noexcept { return lhs.m_Angle == rhs.m_Angle; }
        [[nodiscard]] friend constexpr bool operator!=( Radians lhs, const Radians& rhs ) noexcept { return !( lhs == rhs ); }
        [[nodiscard]] friend constexpr bool operator<( Radians lhs, const Radians& rhs ) noexcept { return lhs.m_Angle < rhs.m_Angle; }
        [[nodiscard]] friend constexpr bool operator>( Radians lhs, const Radians& rhs ) noexcept { return ( lhs >= rhs ) && ( lhs != rhs ); }
        [[nodiscard]] friend constexpr bool operator<=( Radians lhs, const Radians& rhs ) noexcept { return !( lhs > rhs ); }
        [[nodiscard]] friend constexpr bool operator>=( Radians lhs, const Radians& rhs ) noexcept { return !( lhs < rhs ); }
        //  Degrees
        friend constexpr bool operator==( Radians lhs, const Degrees& rhs ) noexcept;
        friend constexpr bool operator!=( Radians lhs, const Degrees& rhs ) noexcept;
        friend constexpr bool operator<( Radians lhs, const Degrees& rhs ) noexcept;
        friend constexpr bool operator>( Radians lhs, const Degrees& rhs ) noexcept;
        friend constexpr bool operator<=( Radians lhs, const Degrees& rhs ) noexcept;
        friend constexpr bool operator>=( Radians lhs, const Degrees& rhs ) noexcept;

        // Arithmetic
        [[nodiscard]] friend constexpr Radians operator+( const Radians& lhs, const Radians rhs ) noexcept { return Radians( lhs.m_Angle + rhs.m_Angle ); }
        [[nodiscard]] friend constexpr Radians operator-( const Radians& lhs, const Radians rhs ) noexcept { return Radians( lhs.m_Angle - rhs.m_Angle ); }
        [[nodiscard]] friend constexpr Radians operator*( const Radians& lhs, const float rhs ) noexcept { return Radians( lhs.m_Angle * rhs ); }
        [[nodiscard]] friend constexpr Radians operator/( const Radians& lhs, const float rhs ) noexcept { return Radians( lhs.m_Angle / rhs ); }

        // Arithmetic Assignment
        friend constexpr Radians& operator+=( Radians& lhs, const Radians& rhs ) noexcept { lhs.m_Angle += rhs.m_Angle; return lhs; }
        friend constexpr Radians& operator-=( Radians& lhs, const Radians& rhs ) noexcept { lhs.m_Angle -= rhs.m_Angle; return lhs; }
        friend constexpr Radians& operator+=( Radians& lhs, const float& rhs ) noexcept { return lhs += Radians( rhs ); }
        friend constexpr Radians& operator-=( Radians& lhs, const float& rhs ) noexcept { return lhs -= Radians( rhs ); }
        constexpr Radians& operator*=( const float& rhs ) noexcept { m_Angle *= rhs; return *this; }
        constexpr Radians& operator/=( const float& rhs ) noexcept { m_Angle /= rhs; return *this; }

        // Explicit conversions.
        //  I don't really see any great use cases for converstions to integral types,
        // but those can be trivially added or done by casting to fp-type then int-type.
        [[nodiscard]] explicit constexpr operator float( void ) const noexcept { return m_Angle; }
        [[nodiscard]] explicit constexpr operator double( void ) const noexcept { return static_cast<double>( m_Angle ); }
        [[nodiscard]] explicit constexpr operator long double( void ) const noexcept { return static_cast<long double>( m_Angle ); }
        [[nodiscard]] explicit constexpr operator Degrees( void ) const noexcept;

        [[nodiscard]] constexpr Radians reduced( void ) const noexcept;
        constexpr void reduce( void ) noexcept { *this = reduced(); }

        static constexpr const float ONE_FULL_ROTATION{ 2 * PI };
        static constexpr const float MAX_ANGLE{ PI };
        static constexpr const float MIN_ANGLE{ -PI };

    private:
        [[nodiscard]] constexpr float radiansToDegrees( float radians ) const noexcept;
        [[nodiscard]] constexpr float degreesToRadians( float degrees ) const noexcept;

    private:
        float m_Angle{ 0.0f };
    };



    // These use the same parameter name(s) as the standard library versions.
    float sin( const Hazel::Radians& theta );
    float cos( const Hazel::Radians& theta );
    float tan( const Hazel::Radians& theta );
    // Our versions of inverse trig functions will only provide Radians.
    //It is up to the client to cast to Degrees if needed.
    Radians asin( float arg );
    Radians acos( float arg );
    Radians atan( float arg );
    Radians atan2( float y, float x );
}
