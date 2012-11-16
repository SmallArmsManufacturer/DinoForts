#include "maths.hpp"

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
}
