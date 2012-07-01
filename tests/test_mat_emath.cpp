/**
 * @file test_mat_emath.cpp
 *
 * Unit test of elementary functions on matrices
 *
 * @author Dahua Lin
 */

#include "test_base.h"

#include <light_mat/matrix/matrix_classes.h>
#include <light_mat/matrix/matrix_emath.h>

#include <cstdlib>

using namespace lmat;
using namespace lmat::test;

const int default_m = 8;
const int default_n = 6;
const index_t LDim = 12;

template<int M, int N>
void fill_ran(dense_matrix<double, M, N>& X, double a, double b)
{
	for (index_t i = 0; i < X.nelems(); ++i)
	{
		X[i] = a + (double(std::rand()) / RAND_MAX) * (b - a);
	}
}


MN_CASE( mat_emath, max )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	mat_t A(m, n); fill_ran(A, 0.0, 10.0);
	mat_t B(m, n); fill_ran(B, 0.0, 10.0);
	double c = 5.0;

	mat_t AB_r(m, n);
	for (index_t i = 0; i < m * n; ++i) AB_r[i] = A[i] > B[i] ? A[i] : B[i];

	mat_t AC_r(m, n);
	for (index_t i = 0; i < m * n; ++i) AC_r[i] = A[i] > c ? A[i] : c;

	mat_t CB_r(m, n);
	for (index_t i = 0; i < m * n; ++i) CB_r[i] = c > B[i] ? c : B[i];

	mat_t AB = (max)(A, B);
	ASSERT_TRUE( is_equal(AB, AB_r) );

	mat_t AC = (max)(A, c);
	ASSERT_TRUE( is_equal(AC, AC_r) );

	mat_t CB = (max)(c, B);
	ASSERT_TRUE( is_equal(CB, CB_r) );
}

MN_CASE( mat_emath, min )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	mat_t A(m, n); fill_ran(A, 0.0, 10.0);
	mat_t B(m, n); fill_ran(B, 0.0, 10.0);
	double c = 5.0;

	mat_t AB_r(m, n);
	for (index_t i = 0; i < m * n; ++i) AB_r[i] = A[i] < B[i] ? A[i] : B[i];

	mat_t AC_r(m, n);
	for (index_t i = 0; i < m * n; ++i) AC_r[i] = A[i] < c ? A[i] : c;

	mat_t CB_r(m, n);
	for (index_t i = 0; i < m * n; ++i) CB_r[i] = c < B[i] ? c : B[i];

	mat_t AB = (min)(A, B);
	ASSERT_TRUE( is_equal(AB, AB_r) );

	mat_t AC = (min)(A, c);
	ASSERT_TRUE( is_equal(AC, AC_r) );

	mat_t CB = (min)(c, B);
	ASSERT_TRUE( is_equal(CB, CB_r) );
}

MN_CASE( mat_emath, pow )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	mat_t A(m, n); fill_ran(A, 0.0, 5.0);
	mat_t B(m, n); fill_ran(B, 0.0, 2.0);
	double c = 1.5;
	double tol = 1.0e-12;

	mat_t AB_r(m, n);
	for (index_t i = 0; i < m * n; ++i) AB_r[i] = std::pow(A[i], B[i]);

	mat_t AC_r(m, n);
	for (index_t i = 0; i < m * n; ++i) AC_r[i] = std::pow(A[i], c);

	mat_t AB = pow(A, B);
	ASSERT_TRUE( is_approx(AB, AB_r, tol) );

	mat_t AC = pow(A, c);
	ASSERT_TRUE( is_approx(AC, AC_r, tol) );
}


MN_CASE( mat_emath, floor )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	mat_t A(m, n); fill_ran(A, -10.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::floor(A[i]);

	mat_t R = floor(A);
	ASSERT_TRUE( is_equal(R, R_r) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(floor(A), R_s);
	ASSERT_TRUE( is_equal(R_s, R_r) );
}


MN_CASE( mat_emath, ceil )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	mat_t A(m, n); fill_ran(A, -10.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::ceil(A[i]);

	mat_t R = ceil(A);
	ASSERT_TRUE( is_equal(R, R_r) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(ceil(A), R_s);
	ASSERT_TRUE( is_equal(R_s, R_r) );
}


MN_CASE( mat_emath, exp )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -1.0, 3.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::exp(A[i]);

	mat_t R = exp(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(exp(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}


MN_CASE( mat_emath, log )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, 1.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::log(A[i]);

	mat_t R = log(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(log(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}


MN_CASE( mat_emath, log10 )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, 1.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::log10(A[i]);

	mat_t R = log10(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(log10(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}


MN_CASE( mat_emath, sin )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -10.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::sin(A[i]);

	mat_t R = sin(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(sin(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, cos )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -10.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::cos(A[i]);

	mat_t R = cos(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(cos(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, tan )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-10;
	mat_t A(m, n); fill_ran(A, -10.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::tan(A[i]);

	mat_t R = tan(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(tan(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}


MN_CASE( mat_emath, asin )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -1.0, 1.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::asin(A[i]);

	mat_t R = asin(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(asin(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, acos )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -1.0, 1.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::acos(A[i]);

	mat_t R = acos(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(acos(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, atan )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -10.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::atan(A[i]);

	mat_t R = atan(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(atan(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, atan2 )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	mat_t A(m, n); fill_ran(A, 1.0, 10.0);
	mat_t B(m, n); fill_ran(B, 1.0, 10.0);
	double tol = 1.0e-15;

	mat_t AB_r(m, n);
	for (index_t i = 0; i < m * n; ++i) AB_r[i] = std::atan2(A[i], B[i]);

	mat_t AB = atan2(A, B);
	ASSERT_TRUE( is_approx(AB, AB_r, tol) );
}


MN_CASE( mat_emath, sinh )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -3.0, 3.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::sinh(A[i]);

	mat_t R = sinh(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(sinh(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, cosh )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -3.0, 3.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::cosh(A[i]);

	mat_t R = cosh(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(cosh(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, tanh )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -5.0, 5.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::tanh(A[i]);

	mat_t R = tanh(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(tanh(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}


#ifdef LMAT_HAS_CXX11_MATH

MN_CASE( mat_emath, round )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -10.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::round(A[i]);

	mat_t R = round(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(round(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, trunc )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -10.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::trunc(A[i]);

	mat_t R = trunc(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(trunc(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}


MN_CASE( mat_emath, cbrt )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -10.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::cbrt(A[i]);

	mat_t R = cbrt(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(cbrt(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, hypot )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	mat_t A(m, n); fill_ran(A, -5.0, 5.0);
	mat_t B(m, n); fill_ran(B, -5.0, 5.0);
	double tol = 1.0e-15;

	mat_t AB_r(m, n);
	for (index_t i = 0; i < m * n; ++i) AB_r[i] = std::hypot(A[i], B[i]);

	mat_t AB = hypot(A, B);
	ASSERT_TRUE( is_approx(AB, AB_r, tol) );
}


MN_CASE( mat_emath, exp2 )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -1.0, 4.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::exp2(A[i]);

	mat_t R = exp2(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(exp2(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, log2 )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, 1.0, 10.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::log2(A[i]);

	mat_t R = log2(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(log2(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, expm1 )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -1.0, 1.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::expm1(A[i]);

	mat_t R = expm1(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(expm1(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, log1p )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -0.5, 1.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::log1p(A[i]);

	mat_t R = log1p(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(log1p(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, asinh )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -5.0, 5.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::asinh(A[i]);

	mat_t R = asinh(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(asinh(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, acosh )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, 1.0, 3.0);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::acosh(A[i]);

	mat_t R = acosh(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(acosh(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}

MN_CASE( mat_emath, atanh )
{
	typedef dense_matrix<double, M, N> mat_t;

	const index_t m = M == 0 ? default_m : M;
	const index_t n = N == 0 ? default_n : N;

	double tol = 1.0e-12;
	mat_t A(m, n); fill_ran(A, -0.9, 0.9);

	mat_t R_r(m, n);
	for (index_t i = 0; i < m * n; ++i) R_r[i] = std::atanh(A[i]);

	mat_t R = atanh(A);
	ASSERT_TRUE( is_approx(R, R_r, tol) );

	mat_t R_s(m, n, fill_value(0.0));
	evaluate_by_scalars(atanh(A), R_s);
	ASSERT_TRUE( is_approx(R_s, R_r, tol) );
}



#endif


BEGIN_TPACK( mat_max )
	ADD_MN_CASE( mat_emath, max, 0, 0 )
	ADD_MN_CASE( mat_emath, max, 0, 1 )
	ADD_MN_CASE( mat_emath, max, 0, default_n )
	ADD_MN_CASE( mat_emath, max, 1, 0 )
	ADD_MN_CASE( mat_emath, max, 1, 1 )
	ADD_MN_CASE( mat_emath, max, 1, default_n )
	ADD_MN_CASE( mat_emath, max, default_m, 0 )
	ADD_MN_CASE( mat_emath, max, default_m, 1 )
	ADD_MN_CASE( mat_emath, max, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_min )
	ADD_MN_CASE( mat_emath, min, 0, 0 )
	ADD_MN_CASE( mat_emath, min, 0, 1 )
	ADD_MN_CASE( mat_emath, min, 0, default_n )
	ADD_MN_CASE( mat_emath, min, 1, 0 )
	ADD_MN_CASE( mat_emath, min, 1, 1 )
	ADD_MN_CASE( mat_emath, min, 1, default_n )
	ADD_MN_CASE( mat_emath, min, default_m, 0 )
	ADD_MN_CASE( mat_emath, min, default_m, 1 )
	ADD_MN_CASE( mat_emath, min, default_m, default_n )
END_TPACK


BEGIN_TPACK( mat_pow )
	ADD_MN_CASE( mat_emath, pow, 0, 0 )
	ADD_MN_CASE( mat_emath, pow, 0, 1 )
	ADD_MN_CASE( mat_emath, pow, 0, default_n )
	ADD_MN_CASE( mat_emath, pow, 1, 0 )
	ADD_MN_CASE( mat_emath, pow, 1, 1 )
	ADD_MN_CASE( mat_emath, pow, 1, default_n )
	ADD_MN_CASE( mat_emath, pow, default_m, 0 )
	ADD_MN_CASE( mat_emath, pow, default_m, 1 )
	ADD_MN_CASE( mat_emath, pow, default_m, default_n )
END_TPACK


BEGIN_TPACK( mat_floor )
	ADD_MN_CASE( mat_emath, floor, 0, 0 )
	ADD_MN_CASE( mat_emath, floor, 0, 1 )
	ADD_MN_CASE( mat_emath, floor, 0, default_n )
	ADD_MN_CASE( mat_emath, floor, 1, 0 )
	ADD_MN_CASE( mat_emath, floor, 1, 1 )
	ADD_MN_CASE( mat_emath, floor, 1, default_n )
	ADD_MN_CASE( mat_emath, floor, default_m, 0 )
	ADD_MN_CASE( mat_emath, floor, default_m, 1 )
	ADD_MN_CASE( mat_emath, floor, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_ceil )
	ADD_MN_CASE( mat_emath, ceil, 0, 0 )
	ADD_MN_CASE( mat_emath, ceil, 0, 1 )
	ADD_MN_CASE( mat_emath, ceil, 0, default_n )
	ADD_MN_CASE( mat_emath, ceil, 1, 0 )
	ADD_MN_CASE( mat_emath, ceil, 1, 1 )
	ADD_MN_CASE( mat_emath, ceil, 1, default_n )
	ADD_MN_CASE( mat_emath, ceil, default_m, 0 )
	ADD_MN_CASE( mat_emath, ceil, default_m, 1 )
	ADD_MN_CASE( mat_emath, ceil, default_m, default_n )
END_TPACK


BEGIN_TPACK( mat_exp )
	ADD_MN_CASE( mat_emath, exp, 0, 0 )
	ADD_MN_CASE( mat_emath, exp, 0, 1 )
	ADD_MN_CASE( mat_emath, exp, 0, default_n )
	ADD_MN_CASE( mat_emath, exp, 1, 0 )
	ADD_MN_CASE( mat_emath, exp, 1, 1 )
	ADD_MN_CASE( mat_emath, exp, 1, default_n )
	ADD_MN_CASE( mat_emath, exp, default_m, 0 )
	ADD_MN_CASE( mat_emath, exp, default_m, 1 )
	ADD_MN_CASE( mat_emath, exp, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_log )
	ADD_MN_CASE( mat_emath, log, 0, 0 )
	ADD_MN_CASE( mat_emath, log, 0, 1 )
	ADD_MN_CASE( mat_emath, log, 0, default_n )
	ADD_MN_CASE( mat_emath, log, 1, 0 )
	ADD_MN_CASE( mat_emath, log, 1, 1 )
	ADD_MN_CASE( mat_emath, log, 1, default_n )
	ADD_MN_CASE( mat_emath, log, default_m, 0 )
	ADD_MN_CASE( mat_emath, log, default_m, 1 )
	ADD_MN_CASE( mat_emath, log, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_log10 )
	ADD_MN_CASE( mat_emath, log10, 0, 0 )
	ADD_MN_CASE( mat_emath, log10, 0, 1 )
	ADD_MN_CASE( mat_emath, log10, 0, default_n )
	ADD_MN_CASE( mat_emath, log10, 1, 0 )
	ADD_MN_CASE( mat_emath, log10, 1, 1 )
	ADD_MN_CASE( mat_emath, log10, 1, default_n )
	ADD_MN_CASE( mat_emath, log10, default_m, 0 )
	ADD_MN_CASE( mat_emath, log10, default_m, 1 )
	ADD_MN_CASE( mat_emath, log10, default_m, default_n )
END_TPACK


BEGIN_TPACK( mat_sin )
	ADD_MN_CASE( mat_emath, sin, 0, 0 )
	ADD_MN_CASE( mat_emath, sin, 0, 1 )
	ADD_MN_CASE( mat_emath, sin, 0, default_n )
	ADD_MN_CASE( mat_emath, sin, 1, 0 )
	ADD_MN_CASE( mat_emath, sin, 1, 1 )
	ADD_MN_CASE( mat_emath, sin, 1, default_n )
	ADD_MN_CASE( mat_emath, sin, default_m, 0 )
	ADD_MN_CASE( mat_emath, sin, default_m, 1 )
	ADD_MN_CASE( mat_emath, sin, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_cos )
	ADD_MN_CASE( mat_emath, cos, 0, 0 )
	ADD_MN_CASE( mat_emath, cos, 0, 1 )
	ADD_MN_CASE( mat_emath, cos, 0, default_n )
	ADD_MN_CASE( mat_emath, cos, 1, 0 )
	ADD_MN_CASE( mat_emath, cos, 1, 1 )
	ADD_MN_CASE( mat_emath, cos, 1, default_n )
	ADD_MN_CASE( mat_emath, cos, default_m, 0 )
	ADD_MN_CASE( mat_emath, cos, default_m, 1 )
	ADD_MN_CASE( mat_emath, cos, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_tan )
	ADD_MN_CASE( mat_emath, tan, 0, 0 )
	ADD_MN_CASE( mat_emath, tan, 0, 1 )
	ADD_MN_CASE( mat_emath, tan, 0, default_n )
	ADD_MN_CASE( mat_emath, tan, 1, 0 )
	ADD_MN_CASE( mat_emath, tan, 1, 1 )
	ADD_MN_CASE( mat_emath, tan, 1, default_n )
	ADD_MN_CASE( mat_emath, tan, default_m, 0 )
	ADD_MN_CASE( mat_emath, tan, default_m, 1 )
	ADD_MN_CASE( mat_emath, tan, default_m, default_n )
END_TPACK


BEGIN_TPACK( mat_asin )
	ADD_MN_CASE( mat_emath, asin, 0, 0 )
	ADD_MN_CASE( mat_emath, asin, 0, 1 )
	ADD_MN_CASE( mat_emath, asin, 0, default_n )
	ADD_MN_CASE( mat_emath, asin, 1, 0 )
	ADD_MN_CASE( mat_emath, asin, 1, 1 )
	ADD_MN_CASE( mat_emath, asin, 1, default_n )
	ADD_MN_CASE( mat_emath, asin, default_m, 0 )
	ADD_MN_CASE( mat_emath, asin, default_m, 1 )
	ADD_MN_CASE( mat_emath, asin, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_acos )
	ADD_MN_CASE( mat_emath, acos, 0, 0 )
	ADD_MN_CASE( mat_emath, acos, 0, 1 )
	ADD_MN_CASE( mat_emath, acos, 0, default_n )
	ADD_MN_CASE( mat_emath, acos, 1, 0 )
	ADD_MN_CASE( mat_emath, acos, 1, 1 )
	ADD_MN_CASE( mat_emath, acos, 1, default_n )
	ADD_MN_CASE( mat_emath, acos, default_m, 0 )
	ADD_MN_CASE( mat_emath, acos, default_m, 1 )
	ADD_MN_CASE( mat_emath, acos, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_atan )
	ADD_MN_CASE( mat_emath, atan, 0, 0 )
	ADD_MN_CASE( mat_emath, atan, 0, 1 )
	ADD_MN_CASE( mat_emath, atan, 0, default_n )
	ADD_MN_CASE( mat_emath, atan, 1, 0 )
	ADD_MN_CASE( mat_emath, atan, 1, 1 )
	ADD_MN_CASE( mat_emath, atan, 1, default_n )
	ADD_MN_CASE( mat_emath, atan, default_m, 0 )
	ADD_MN_CASE( mat_emath, atan, default_m, 1 )
	ADD_MN_CASE( mat_emath, atan, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_atan2 )
	ADD_MN_CASE( mat_emath, atan2, 0, 0 )
	ADD_MN_CASE( mat_emath, atan2, 0, 1 )
	ADD_MN_CASE( mat_emath, atan2, 0, default_n )
	ADD_MN_CASE( mat_emath, atan2, 1, 0 )
	ADD_MN_CASE( mat_emath, atan2, 1, 1 )
	ADD_MN_CASE( mat_emath, atan2, 1, default_n )
	ADD_MN_CASE( mat_emath, atan2, default_m, 0 )
	ADD_MN_CASE( mat_emath, atan2, default_m, 1 )
	ADD_MN_CASE( mat_emath, atan2, default_m, default_n )
END_TPACK


BEGIN_TPACK( mat_sinh )
	ADD_MN_CASE( mat_emath, sinh, 0, 0 )
	ADD_MN_CASE( mat_emath, sinh, 0, 1 )
	ADD_MN_CASE( mat_emath, sinh, 0, default_n )
	ADD_MN_CASE( mat_emath, sinh, 1, 0 )
	ADD_MN_CASE( mat_emath, sinh, 1, 1 )
	ADD_MN_CASE( mat_emath, sinh, 1, default_n )
	ADD_MN_CASE( mat_emath, sinh, default_m, 0 )
	ADD_MN_CASE( mat_emath, sinh, default_m, 1 )
	ADD_MN_CASE( mat_emath, sinh, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_cosh )
	ADD_MN_CASE( mat_emath, cosh, 0, 0 )
	ADD_MN_CASE( mat_emath, cosh, 0, 1 )
	ADD_MN_CASE( mat_emath, cosh, 0, default_n )
	ADD_MN_CASE( mat_emath, cosh, 1, 0 )
	ADD_MN_CASE( mat_emath, cosh, 1, 1 )
	ADD_MN_CASE( mat_emath, cosh, 1, default_n )
	ADD_MN_CASE( mat_emath, cosh, default_m, 0 )
	ADD_MN_CASE( mat_emath, cosh, default_m, 1 )
	ADD_MN_CASE( mat_emath, cosh, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_tanh )
	ADD_MN_CASE( mat_emath, tanh, 0, 0 )
	ADD_MN_CASE( mat_emath, tanh, 0, 1 )
	ADD_MN_CASE( mat_emath, tanh, 0, default_n )
	ADD_MN_CASE( mat_emath, tanh, 1, 0 )
	ADD_MN_CASE( mat_emath, tanh, 1, 1 )
	ADD_MN_CASE( mat_emath, tanh, 1, default_n )
	ADD_MN_CASE( mat_emath, tanh, default_m, 0 )
	ADD_MN_CASE( mat_emath, tanh, default_m, 1 )
	ADD_MN_CASE( mat_emath, tanh, default_m, default_n )
END_TPACK

#ifdef LMAT_HAS_CXX11_MATH

BEGIN_TPACK( mat_round )
	ADD_MN_CASE( mat_emath, round, 0, 0 )
	ADD_MN_CASE( mat_emath, round, 0, 1 )
	ADD_MN_CASE( mat_emath, round, 0, default_n )
	ADD_MN_CASE( mat_emath, round, 1, 0 )
	ADD_MN_CASE( mat_emath, round, 1, 1 )
	ADD_MN_CASE( mat_emath, round, 1, default_n )
	ADD_MN_CASE( mat_emath, round, default_m, 0 )
	ADD_MN_CASE( mat_emath, round, default_m, 1 )
	ADD_MN_CASE( mat_emath, round, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_trunc )
	ADD_MN_CASE( mat_emath, trunc, 0, 0 )
	ADD_MN_CASE( mat_emath, trunc, 0, 1 )
	ADD_MN_CASE( mat_emath, trunc, 0, default_n )
	ADD_MN_CASE( mat_emath, trunc, 1, 0 )
	ADD_MN_CASE( mat_emath, trunc, 1, 1 )
	ADD_MN_CASE( mat_emath, trunc, 1, default_n )
	ADD_MN_CASE( mat_emath, trunc, default_m, 0 )
	ADD_MN_CASE( mat_emath, trunc, default_m, 1 )
	ADD_MN_CASE( mat_emath, trunc, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_cbrt )
	ADD_MN_CASE( mat_emath, cbrt, 0, 0 )
	ADD_MN_CASE( mat_emath, cbrt, 0, 1 )
	ADD_MN_CASE( mat_emath, cbrt, 0, default_n )
	ADD_MN_CASE( mat_emath, cbrt, 1, 0 )
	ADD_MN_CASE( mat_emath, cbrt, 1, 1 )
	ADD_MN_CASE( mat_emath, cbrt, 1, default_n )
	ADD_MN_CASE( mat_emath, cbrt, default_m, 0 )
	ADD_MN_CASE( mat_emath, cbrt, default_m, 1 )
	ADD_MN_CASE( mat_emath, cbrt, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_hypot )
	ADD_MN_CASE( mat_emath, hypot, 0, 0 )
	ADD_MN_CASE( mat_emath, hypot, 0, 1 )
	ADD_MN_CASE( mat_emath, hypot, 0, default_n )
	ADD_MN_CASE( mat_emath, hypot, 1, 0 )
	ADD_MN_CASE( mat_emath, hypot, 1, 1 )
	ADD_MN_CASE( mat_emath, hypot, 1, default_n )
	ADD_MN_CASE( mat_emath, hypot, default_m, 0 )
	ADD_MN_CASE( mat_emath, hypot, default_m, 1 )
	ADD_MN_CASE( mat_emath, hypot, default_m, default_n )
END_TPACK


BEGIN_TPACK( mat_exp2 )
	ADD_MN_CASE( mat_emath, exp2, 0, 0 )
	ADD_MN_CASE( mat_emath, exp2, 0, 1 )
	ADD_MN_CASE( mat_emath, exp2, 0, default_n )
	ADD_MN_CASE( mat_emath, exp2, 1, 0 )
	ADD_MN_CASE( mat_emath, exp2, 1, 1 )
	ADD_MN_CASE( mat_emath, exp2, 1, default_n )
	ADD_MN_CASE( mat_emath, exp2, default_m, 0 )
	ADD_MN_CASE( mat_emath, exp2, default_m, 1 )
	ADD_MN_CASE( mat_emath, exp2, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_log2 )
	ADD_MN_CASE( mat_emath, log2, 0, 0 )
	ADD_MN_CASE( mat_emath, log2, 0, 1 )
	ADD_MN_CASE( mat_emath, log2, 0, default_n )
	ADD_MN_CASE( mat_emath, log2, 1, 0 )
	ADD_MN_CASE( mat_emath, log2, 1, 1 )
	ADD_MN_CASE( mat_emath, log2, 1, default_n )
	ADD_MN_CASE( mat_emath, log2, default_m, 0 )
	ADD_MN_CASE( mat_emath, log2, default_m, 1 )
	ADD_MN_CASE( mat_emath, log2, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_expm1 )
	ADD_MN_CASE( mat_emath, expm1, 0, 0 )
	ADD_MN_CASE( mat_emath, expm1, 0, 1 )
	ADD_MN_CASE( mat_emath, expm1, 0, default_n )
	ADD_MN_CASE( mat_emath, expm1, 1, 0 )
	ADD_MN_CASE( mat_emath, expm1, 1, 1 )
	ADD_MN_CASE( mat_emath, expm1, 1, default_n )
	ADD_MN_CASE( mat_emath, expm1, default_m, 0 )
	ADD_MN_CASE( mat_emath, expm1, default_m, 1 )
	ADD_MN_CASE( mat_emath, expm1, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_log1p )
	ADD_MN_CASE( mat_emath, log1p, 0, 0 )
	ADD_MN_CASE( mat_emath, log1p, 0, 1 )
	ADD_MN_CASE( mat_emath, log1p, 0, default_n )
	ADD_MN_CASE( mat_emath, log1p, 1, 0 )
	ADD_MN_CASE( mat_emath, log1p, 1, 1 )
	ADD_MN_CASE( mat_emath, log1p, 1, default_n )
	ADD_MN_CASE( mat_emath, log1p, default_m, 0 )
	ADD_MN_CASE( mat_emath, log1p, default_m, 1 )
	ADD_MN_CASE( mat_emath, log1p, default_m, default_n )
END_TPACK


BEGIN_TPACK( mat_asinh )
	ADD_MN_CASE( mat_emath, asinh, 0, 0 )
	ADD_MN_CASE( mat_emath, asinh, 0, 1 )
	ADD_MN_CASE( mat_emath, asinh, 0, default_n )
	ADD_MN_CASE( mat_emath, asinh, 1, 0 )
	ADD_MN_CASE( mat_emath, asinh, 1, 1 )
	ADD_MN_CASE( mat_emath, asinh, 1, default_n )
	ADD_MN_CASE( mat_emath, asinh, default_m, 0 )
	ADD_MN_CASE( mat_emath, asinh, default_m, 1 )
	ADD_MN_CASE( mat_emath, asinh, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_acosh )
	ADD_MN_CASE( mat_emath, acosh, 0, 0 )
	ADD_MN_CASE( mat_emath, acosh, 0, 1 )
	ADD_MN_CASE( mat_emath, acosh, 0, default_n )
	ADD_MN_CASE( mat_emath, acosh, 1, 0 )
	ADD_MN_CASE( mat_emath, acosh, 1, 1 )
	ADD_MN_CASE( mat_emath, acosh, 1, default_n )
	ADD_MN_CASE( mat_emath, acosh, default_m, 0 )
	ADD_MN_CASE( mat_emath, acosh, default_m, 1 )
	ADD_MN_CASE( mat_emath, acosh, default_m, default_n )
END_TPACK

BEGIN_TPACK( mat_atanh )
	ADD_MN_CASE( mat_emath, atanh, 0, 0 )
	ADD_MN_CASE( mat_emath, atanh, 0, 1 )
	ADD_MN_CASE( mat_emath, atanh, 0, default_n )
	ADD_MN_CASE( mat_emath, atanh, 1, 0 )
	ADD_MN_CASE( mat_emath, atanh, 1, 1 )
	ADD_MN_CASE( mat_emath, atanh, 1, default_n )
	ADD_MN_CASE( mat_emath, atanh, default_m, 0 )
	ADD_MN_CASE( mat_emath, atanh, default_m, 1 )
	ADD_MN_CASE( mat_emath, atanh, default_m, default_n )
END_TPACK

#endif


BEGIN_MAIN_SUITE
	ADD_TPACK( mat_max )
	ADD_TPACK( mat_min )

	ADD_TPACK( mat_pow )

	ADD_TPACK( mat_floor )
	ADD_TPACK( mat_ceil )

	ADD_TPACK( mat_exp )
	ADD_TPACK( mat_log )
	ADD_TPACK( mat_log10 )

	ADD_TPACK( mat_sin )
	ADD_TPACK( mat_cos )
	ADD_TPACK( mat_tan )

	ADD_TPACK( mat_asin )
	ADD_TPACK( mat_acos )
	ADD_TPACK( mat_atan )
	ADD_TPACK( mat_atan2 )

	ADD_TPACK( mat_sinh )
	ADD_TPACK( mat_cosh )
	ADD_TPACK( mat_tanh )

#ifdef LMAT_HAS_CXX11_MATH

	ADD_TPACK( mat_round )
	ADD_TPACK( mat_trunc )

	ADD_TPACK( mat_cbrt )
	ADD_TPACK( mat_hypot )

	ADD_TPACK( mat_exp2 )
	ADD_TPACK( mat_log2 )
	ADD_TPACK( mat_expm1 )
	ADD_TPACK( mat_log1p )

	ADD_TPACK( mat_asinh )
	ADD_TPACK( mat_acosh )
	ADD_TPACK( mat_atanh )

#endif

END_MAIN_SUITE




