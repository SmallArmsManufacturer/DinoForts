#include "maths.hpp"

using namespace boost::numeric::ublas;

namespace Maths
{
    Matrix perspectiveProjection(float fov, float aspect, float near, float far)
    {
        float D2R = M_PI / 180.0;
        float yScale = 1.0 / tan(D2R * fov / 2);
        float xScale = yScale / aspect;
        float depth = near - far;
        
        Matrix result = ZeroMatrix(4, 4);
        result(0, 0) = xScale;
        result(1, 1) = yScale;
        result(2, 2) = (far + near) / depth;
        result(2, 3) = -1;
        result(3, 2) = 2 * far * near / depth;
        return result;
    }

    Matrix rotationMatrix(float angle, float x, float y, float z)
    {
        Matrix result = IdentityMatrix(4);
        Vector v(3);
        v(0) = x;
        v(1) = y;
        v(2) = z;
        v /= norm_2(v);

        float b = angle;

        float c = cosf(b);
        float ac = 1.00f - c;
        float s = sinf(b);

        result(0, 0) = v(0) * v(0) * ac + c;
        result(1, 0) = v(0) * v(1) * ac + v(2) * s;
        result(2, 0) = v(0) * v(2) * ac - v(1) * s;

        result(0, 1) = v(1) * v(0) * ac - v(2) * s;
        result(1, 1) = v(1) * v(1) * ac + c;
        result(2, 1) = v(1) * v(2) * ac + v(0) * s;
        
        result(0, 2) = v(2) * v(0) * ac + v(1) * s;
        result(1, 2) = v(2) * v(1) * ac - v(0) * s;
        result(2, 2) = v(2) * v(2) * ac + c;

        return result;
    }
}
