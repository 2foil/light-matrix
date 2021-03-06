/**
 * @file test_linear_ewise.cpp
 *
 * @brief Test Linear element-wise accesses
 *
 * @author Dahua Lin
 */


#include "../test_base.h"

#define DEFAULT_M_VALUE 13
#define DEFAULT_N_VALUE 9

#include "../multimat_supp.h"

#include <light_mat/matrix/matrix_classes.h>
#include <light_mat/math/basic_functors.h>
#include <light_mat/mateval/ewise_eval.h>


using namespace lmat;
using namespace lmat::test;

// core functions


template<typename U, int M, int N>
void test_linear_ewise_cont_cont()
{
	const index_t m = M == 0 ? DM : M;
	const index_t n = N == 0 ? DN : N;

	typedef typename mat_host<cont, double, M, N>::cmat_t smat_t;
	typedef typename mat_host<cont, double, M, N>::mat_t dmat_t;

	mat_host<cont, double, M, N> src(m, n);
	src.fill_lin();
	mat_host<cont, double, M, N> dst(m, n);

	dense_matrix<double, M, N> rmat(m, n);

	smat_t smat = src.get_cmat();
	dmat_t dmat = dst.get_mat();

	copy_kernel<double> cpy_kernel;
	accum_kernel<double> upd_kernel;

	ewise(cpy_kernel).eval(macc_<linear_, U>(), smat.shape(), in_(smat), out_(dmat));

	ASSERT_MAT_EQ(m, n, smat, dmat);

	for (index_t i = 0; i < m * n; ++i) rmat[i] = smat[i] + dmat[i];

	ewise(upd_kernel).eval(macc_<linear_, U>(), smat.shape(), in_out_(dmat), in_(smat));

	ASSERT_MAT_EQ(m, n, dmat, rmat);
}

template<typename U, typename STag, typename DTag, int M>
void test_linear_ewise_col()
{
	const index_t m = M == 0 ? DM : M;

	typedef typename mat_host<STag, double, M, 1>::cmat_t smat_t;
	typedef typename mat_host<DTag, double, M, 1>::mat_t dmat_t;

	mat_host<STag, double, M, 1> src(m, 1);
	src.fill_lin();
	mat_host<DTag, double, M, 1> dst(m, 1);

	dense_matrix<double, M, 1> rmat(m, 1);

	smat_t smat = src.get_cmat();
	dmat_t dmat = dst.get_mat();

	copy_kernel<double> cpy_kernel;
	accum_kernel<double> upd_kernel;

	matrix_shape<M, 1> shape(m, 1);
	ewise(cpy_kernel).eval(macc_<linear_, U>(), shape, in_(smat), out_(dmat));

	ASSERT_MAT_EQ(m, 1, smat, dmat);

	for (index_t i = 0; i < m; ++i) rmat[i] = smat[i] + dmat[i];

	ewise(upd_kernel).eval(macc_<linear_, U>(), shape, in_out_(dmat), in_(smat));
	ASSERT_MAT_EQ(m, 1, dmat, rmat);
}

template<typename U, typename STag, typename DTag, int N>
void test_linear_ewise_row()
{
	const index_t n = N == 0 ? DN : N;

	typedef typename mat_host<STag, double, 1, N>::cmat_t smat_t;
	typedef typename mat_host<DTag, double, 1, N>::mat_t dmat_t;

	mat_host<STag, double, 1, N> src(1, n);
	src.fill_lin();
	mat_host<DTag, double, 1, N> dst(1, n);

	dense_matrix<double, 1, N> rmat(1, n);

	smat_t smat = src.get_cmat();
	dmat_t dmat = dst.get_mat();

	copy_kernel<double> cpy_kernel;
	accum_kernel<double> upd_kernel;

	matrix_shape<1, N> shape(1, n);
	ewise(cpy_kernel).eval(macc_<linear_, U>(), shape, in_(smat), out_(dmat));
	ASSERT_MAT_EQ(1, n, smat, dmat);

	for (index_t i = 0; i < n; ++i) rmat[i] = smat[i] + dmat[i];

	ewise(upd_kernel).eval(macc_<linear_, U>(), shape, in_out_(dmat), in_(smat));
	ASSERT_MAT_EQ(1, n, dmat, rmat);
}


template<typename U, int M, int N>
void test_linear_ewise_single_cont()
{
	const index_t m = M == 0 ? DM : M;
	const index_t n = N == 0 ? DN : N;

	typedef typename mat_host<cont, double, M, N>::mat_t dmat_t;

	double v = 2.56;
	mat_host<cont, double, M, N> dst(m, n);

	dmat_t dmat = dst.get_mat();

	dense_matrix<double, M, N> rmat(m, n);
	fill(rmat, v);

	matrix_shape<M, N> shape(m, n);

	ewise(copy_kernel<double>()).eval(macc_<linear_, U>(), shape, const_(v), out_(dmat));

	ASSERT_MAT_EQ(m, n, dmat, rmat);
}





template<typename U>
void test_linear_ewise_varysize()
{
	const index_t max_len = 64;

	dense_col<double> s(max_len);
	dense_col<double> d(max_len, zero());
	dense_col<double> r(max_len, zero());

	for (index_t i = 0; i < max_len; ++i)
	{
		s[i] = double(2 * i + 3);
	}

	map_kernel<sqr_fun<double> > kernel = sqr_fun<double>();

	for (index_t len = 0; len <= 64; ++len)
	{
		zero(d);
		zero(r);

		for (index_t i = 0; i < len; ++i)
			r[i] = math::sqr(s[i]);

		ewise(kernel).eval(macc_<linear_, U>(), len, 1, out_(d), in_(s));
		ASSERT_VEC_EQ( len, d, r );
	}
}

// Specific test cases


MN_CASE( linear_ewise_scalar_cont_cont  )
{
	test_linear_ewise_cont_cont<scalar_, M, N>();
}

N_CASE( linear_ewise_scalar_cont_stepcol  )
{
	test_linear_ewise_col<scalar_, cont, grid, N>();
}

N_CASE( linear_ewise_scalar_stepcol_cont  )
{
	test_linear_ewise_col<scalar_, grid, cont, N>();
}

N_CASE( linear_ewise_scalar_stepcol_stepcol  )
{
	test_linear_ewise_col<scalar_, grid, grid, N>();
}

N_CASE( linear_ewise_scalar_cont_steprow  )
{
	test_linear_ewise_row<scalar_, cont, bloc, N>();
}

N_CASE( linear_ewise_scalar_steprow_cont  )
{
	test_linear_ewise_row<scalar_, bloc, cont, N>();
}

N_CASE( linear_ewise_scalar_steprow_steprow  )
{
	test_linear_ewise_row<scalar_, bloc, bloc, N>();
}


MN_CASE( linear_ewise_sse_cont_cont  )
{
	test_linear_ewise_cont_cont<simd_<sse_t>, M, N>();
}

#ifdef LMAT_HAS_AVX

MN_CASE( linear_ewise_avx_cont_cont  )
{
	test_linear_ewise_cont_cont<simd_<avx_t>, M, N>();
}

#endif


MN_CASE( linear_ewise_scalar_single_cont )
{
	test_linear_ewise_single_cont<scalar_, M, N>();
}

MN_CASE( linear_ewise_sse_single_cont )
{
	test_linear_ewise_single_cont<simd_<sse_t>, M, N>();
}

#ifdef LMAT_HAS_AVX

MN_CASE( linear_ewise_avx_single_cont )
{
	test_linear_ewise_single_cont<simd_<avx_t>, M, N>();
}

#endif


SIMPLE_CASE( linear_ewise_varysize_scalar )
{
	test_linear_ewise_varysize<scalar_>();
}

SIMPLE_CASE( linear_ewise_varysize_sse )
{
	test_linear_ewise_varysize<simd_<sse_t> >();
}

#ifdef LMAT_HAS_AVX
SIMPLE_CASE( linear_ewise_varysize_avx )
{
	test_linear_ewise_varysize<simd_<avx_t> >();
}
#endif


// Test packs


AUTO_TPACK( linear_ewise_scalar_cont_cont )
{
	ADD_MN_CASE_3X3( linear_ewise_scalar_cont_cont, DM, DN )
}

AUTO_TPACK( linear_ewise_scalar_cont_stepcol )
{
	ADD_N_CASE_3( linear_ewise_scalar_cont_stepcol, DM )
}

AUTO_TPACK( linear_ewise_scalar_stepcol_cont )
{
	ADD_N_CASE_3( linear_ewise_scalar_stepcol_cont, DM )
}

AUTO_TPACK( linear_ewise_scalar_stepcol_stepcol )
{
	ADD_N_CASE_3( linear_ewise_scalar_stepcol_stepcol, DM )
}

AUTO_TPACK( linear_ewise_scalar_cont_steprow )
{
	ADD_N_CASE_3( linear_ewise_scalar_cont_steprow, DN )
}

AUTO_TPACK( linear_ewise_scalar_steprow_cont )
{
	ADD_N_CASE_3( linear_ewise_scalar_steprow_cont, DN )
}

AUTO_TPACK( linear_ewise_scalar_steprow_steprow )
{
	ADD_N_CASE_3( linear_ewise_scalar_steprow_steprow, DN )
}


AUTO_TPACK( linear_ewise_sse_cont_cont )
{
	ADD_MN_CASE_3X3( linear_ewise_sse_cont_cont, DM, DN )
}

#ifdef LMAT_HAS_AVX

AUTO_TPACK( linear_ewise_avx_cont_cont )
{
	ADD_MN_CASE_3X3( linear_ewise_avx_cont_cont, DM, DN )
}

#endif

AUTO_TPACK( linear_ewise_scalar_single_cont )
{
	ADD_MN_CASE_3X3( linear_ewise_scalar_single_cont, DM, DN )
}

AUTO_TPACK( linear_ewise_sse_single_cont )
{
	ADD_MN_CASE_3X3( linear_ewise_sse_single_cont, DM, DN )
}

#ifdef LMAT_HAS_AVX

AUTO_TPACK( linear_ewise_avx_single_cont )
{
	ADD_MN_CASE_3X3( linear_ewise_avx_single_cont, DM, DN )
}

#endif



AUTO_TPACK( linear_ewise_varysize )
{
	ADD_SIMPLE_CASE( linear_ewise_varysize_scalar )
	ADD_SIMPLE_CASE( linear_ewise_varysize_sse )
#ifdef LMAT_HAS_AVX
	ADD_SIMPLE_CASE( linear_ewise_varysize_avx )
#endif
}



