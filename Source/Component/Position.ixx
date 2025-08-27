export module Position;

float InvSqrt( float folatValue );

export struct Sight
{
    std::unordered_set< class WorldObject* > _viewList;
};

export struct FVector
{
    float x{};
    float y{};
    float z{};

    void Normalize()
    {
        *this = GetNormalize();
    }

    FVector GetNormalize() const
    {
        float squareSum = SizeSquared();
        if ( squareSum == 1.f )
            return *this;

        if ( squareSum == 0.f )
            return {};

        float invLength = InvSqrt( squareSum );
        return FVector{ x * invLength, y * invLength, z * invLength };
    }

    float Magnitude() const
    {
        return std::sqrtf( SqrMagnitude() );
    }

    float Size() const
    {
        return std::sqrtf( SqrMagnitude() );
    }

    float SqrMagnitude() const
    {
        return ( x * x ) + ( y * y ) + ( z * z );
    }

    float SizeSquared() const
    {
        return ( x * x ) + ( y * y ) + ( z * z );
    }

    FVector operator+=( const FVector& rhs )
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
    }

    FVector operator-=( const FVector& rhs )
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;

        return *this;
    }

    FVector operator-( const FVector& rhs )
    {
        return { x - rhs.x, y - rhs.y, z - rhs.z };
    }

    FVector operator+( const FVector& rhs )
    {
        return { x + rhs.x, y + rhs.y, z + rhs.z };
    }

    FVector operator*( i32 multiple )
    {
        return { x + multiple, y + multiple, z + multiple };
    }

    FVector operator/( i32 divider )
    {
        return { x / divider, y / divider, z / divider };
    }

    FVector operator*=( i32 multiple )
    {
        x *= multiple;
        y *= multiple;
        z *= multiple;

        return *this;
    }

    void operator/=( i32 d )
    {
        x /= d;
        y /= d;
        z /= d;
    }

};

export struct FVector2
{
    float x;
    float y;
};

export struct PrevPosition : public FVector
{
    PrevPosition( FVector vec )
    : FVector{ vec }
    {
    }
};

export struct Position : public FVector
{
    Position( FVector vec )
    : FVector{ vec }
    {
    }
};

export struct Direction : public FVector2
{
};

export struct DestPosition : public FVector
{
    DestPosition( FVector vec )
    : FVector{ vec }
    {
    }
};

export struct Velocity : public FVector2
{
    float x;
    float y;
};


#include <immintrin.h>
// 언리얼 엔진 코드에서 가져옴. 고속 역제곱근 공식
float InvSqrt( float folatValue )
{
    // Performs two passes of Newton-Raphson iteration on the hardware estimate
    //    v^-0.5 = x
    // => x^2 = v^-1
    // => 1/(x^2) = v
    // => F(x) = x^-2 - v
    //    F'(x) = -2x^-3

    //    x1 = x0 - F(x0)/F'(x0)
    // => x1 = x0 + 0.5 * (x0^-2 - Vec) * x0^3
    // => x1 = x0 + 0.5 * (x0 - Vec * x0^3)
    // => x1 = x0 + x0 * (0.5 - 0.5 * Vec * x0^2)
    //
    // This final form has one more operation than the legacy factorization (X1 = 0.5*X0*(3-(Y*X0)*X0)
    // but retains better accuracy (namely InvSqrt(1) = 1 exactly).

    const __m128 fOneHalf = _mm_set_ss( 0.5f );
    __m128 Y0, X0, X1, X2, FOver2;
    float temp;

    Y0 = _mm_set_ss( folatValue );
    X0 = _mm_rsqrt_ss( Y0 );	// 1/sqrt estimate (12 bits)
    FOver2 = _mm_mul_ss( Y0, fOneHalf );

    // 1st Newton-Raphson iteration
    X1 = _mm_mul_ss( X0, X0 );
    X1 = _mm_sub_ss( fOneHalf, _mm_mul_ss( FOver2, X1 ) );
    X1 = _mm_add_ss( X0, _mm_mul_ss( X0, X1 ) );

    // 2nd Newton-Raphson iteration
    X2 = _mm_mul_ss( X1, X1 );
    X2 = _mm_sub_ss( fOneHalf, _mm_mul_ss( FOver2, X2 ) );
    X2 = _mm_add_ss( X1, _mm_mul_ss( X1, X2 ) );

    _mm_store_ss( &temp, X2 );
    return temp;
}