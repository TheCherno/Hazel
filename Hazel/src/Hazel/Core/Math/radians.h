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

        constexpr Radians( const Radians& other ) noexcept : accumulated_( other.accumulated_ ) {}
        explicit Radians( const Degrees& degs ) noexcept;
        Radians( Radians&& other ) noexcept { std::swap( this->accumulated_, other.accumulated_ ); }
        explicit constexpr Radians( float angle ) noexcept : accumulated_( angle ) {}
        explicit constexpr Radians( double angle ) noexcept : accumulated_( static_cast<float>( angle ) ) {}
        explicit constexpr Radians( long double angle ) noexcept : accumulated_( static_cast<float>( angle ) ) {}



        constexpr Radians& operator=( const Radians& other ) noexcept
        {
            accumulated_ = other.accumulated_;
            return *this;
        }



        constexpr Radians& operator=( Radians&& other ) noexcept
        {
            if( *this != other )
            {
                std::swap( this->accumulated_, other.accumulated_ );
            }
            return *this;
        }


        // Boolean
        //  Radians
        [[nodiscard]] friend constexpr bool operator==( Radians lhs, const Radians& rhs ) noexcept { return lhs.accumulated_ == rhs.accumulated_; }
        [[nodiscard]] friend constexpr bool operator!=( Radians lhs, const Radians& rhs ) noexcept { return !( lhs == rhs ); }
        [[nodiscard]] friend constexpr bool operator<( Radians lhs, const Radians& rhs ) noexcept { return lhs.accumulated_ < rhs.accumulated_; }
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
        [[nodiscard]] friend constexpr Radians operator+( const Radians& lhs, const Radians rhs ) noexcept { return Radians( lhs.accumulated_ + rhs.accumulated_ ); }
        [[nodiscard]] friend constexpr Radians operator-( const Radians& lhs, const Radians rhs ) noexcept { return Radians( lhs.accumulated_ - rhs.accumulated_ ); }
        [[nodiscard]] friend constexpr Radians operator*( const Radians& lhs, const float rhs ) noexcept { return Radians( lhs.accumulated_ * rhs ); }
        [[nodiscard]] friend constexpr Radians operator/( const Radians& lhs, const float rhs ) noexcept { return Radians( lhs.accumulated_ / rhs ); }

        // Arithmetic Assignment
        friend constexpr Radians& operator+=( Radians& lhs, const Radians& rhs ) noexcept { lhs.accumulated_ += rhs.accumulated_; return lhs; }
        friend constexpr Radians& operator-=( Radians& lhs, const Radians& rhs ) noexcept { lhs.accumulated_ -= rhs.accumulated_; return lhs; }
        friend constexpr Radians& operator+=( Radians& lhs, const float& rhs ) noexcept { return lhs += Radians( rhs ); }
        friend constexpr Radians& operator-=( Radians& lhs, const float& rhs ) noexcept { return lhs -= Radians( rhs ); }
        constexpr Radians& operator*=( const float& rhs ) noexcept { accumulated_ *= rhs; return *this; }
        constexpr Radians& operator/=( const float& rhs ) noexcept { accumulated_ /= rhs; return *this; }

        // Explicit conversions.
        //  I don't really see any great use cases for converstions to integral types,
        // but those can be trivially added or done by casting to fp-type then int-type.
        [[nodiscard]] explicit constexpr operator float( void ) const noexcept { return accumulated_; }
        [[nodiscard]] explicit constexpr operator double( void ) const noexcept { return static_cast<double>( accumulated_ ); }
        [[nodiscard]] explicit constexpr operator long double( void ) const noexcept { return static_cast<long double>( accumulated_ ); }
        [[nodiscard]] explicit constexpr operator Degrees( void ) const noexcept;

        [[nodiscard]] constexpr Radians reduced( void ) const noexcept;
        constexpr void reduce( void ) noexcept { *this = reduced(); }

        static constexpr const float ONE_FULL_ROTATION{ 2 * PI };
        static constexpr const float MAX_ANGLE{ PI };
        static constexpr const float MIN_ANGLE{ -PI };

    private:
        [[nodiscard]] constexpr float rad_to_deg( float rad ) const noexcept;
        [[nodiscard]] constexpr float deg_to_rad( float deg ) const noexcept;

    private:
        float accumulated_{ 0.0f };
    };

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
