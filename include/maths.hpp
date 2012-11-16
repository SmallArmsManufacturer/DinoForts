#pragma once

#include <boost/numeric/ublas/matrix.hpp>
#include "gl.hpp"

namespace Maths
{
	typedef boost::numeric::ublas::matrix<GLfloat, boost::numeric::ublas::column_major> Matrix;
	typedef boost::numeric::ublas::identity_matrix<GLfloat, boost::numeric::ublas::column_major> IdentityMatrix;
	typedef boost::numeric::ublas::zero_matrix<GLfloat, boost::numeric::ublas::column_major> ZeroMatrix;

	typedef boost::numeric::ublas::vector<GLfloat> Vector;

	Matrix perspectiveProjection(float fov, float aspect, float near, float far);
	Matrix rotationMatrix(float angle, float x, float y, float z);
}