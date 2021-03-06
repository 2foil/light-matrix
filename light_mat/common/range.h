/**
 * @file range.h
 *
 * The classes to represent ranges
 *
 * @author Dahua Lin
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef LIGHTMAT_RANGE_H_
#define LIGHTMAT_RANGE_H_

#include <light_mat/common/prim_types.h>

namespace lmat
{
	template<class Derived>
	class IRange
	{
	public:
		LMAT_CRTP_REF

		LMAT_ENSURE_INLINE index_t get_num(index_t dim) const
		{
			return derived().get_num(dim);
		}

		LMAT_ENSURE_INLINE index_t get_offset(index_t dim, index_t i) const
		{
			return derived().get_offset(dim, i);
		}
	};


	class whole : public IRange<whole>
	{
	public:
		LMAT_ENSURE_INLINE index_t get_num(index_t dim) const
		{
			return dim;
		}

		LMAT_ENSURE_INLINE index_t get_offset(index_t, index_t i) const
		{
			return i;
		}
	};

	class range : public IRange<range>
	{
	public:
		LMAT_ENSURE_INLINE
		range(const index_t i, const index_t n)
		: m_begin(i), m_num(n)
		{
		}

		LMAT_ENSURE_INLINE index_t begin_index() const
		{
			return m_begin;
		}

		LMAT_ENSURE_INLINE index_t end_index() const
		{
			return m_begin + m_num;
		}

		LMAT_ENSURE_INLINE index_t num() const
		{
			return m_num;
		}

		LMAT_ENSURE_INLINE index_t get_num(index_t ) const
		{
			return m_num;
		}

		LMAT_ENSURE_INLINE index_t get_offset(index_t, index_t i) const
		{
			return m_begin + i;
		}

	private:
		const index_t m_begin;
		const index_t m_num;
	};


	class step_range : public IRange<step_range>
	{
	public:
		LMAT_ENSURE_INLINE
		step_range(const index_t i, const index_t n, const index_t s)
		: m_begin(i), m_num(n), m_step(s)
		{
		}

		LMAT_ENSURE_INLINE index_t begin_index() const
		{
			return m_begin;
		}

		LMAT_ENSURE_INLINE index_t end_index() const
		{
			return m_begin + m_num * m_step;
		}

		LMAT_ENSURE_INLINE index_t num() const
		{
			return m_num;
		}

		LMAT_ENSURE_INLINE index_t step() const
		{
			return m_step;
		}

		LMAT_ENSURE_INLINE index_t get_num(index_t ) const
		{
			return m_num;
		}

		LMAT_ENSURE_INLINE index_t get_offset(index_t, index_t i) const
		{
			return m_begin + i * m_step;
		}

	private:
		const index_t m_begin;
		const index_t m_num;
		const index_t m_step;
	};


	/********************************************
	 *
	 *  MATLAB-like colon expression
	 *
	 *  colon(a, b) --> [a, b-1]
	 *
	 *  e.g. colon(0, n) --> the whole range
	 *
	 *  colon(a, s, b) --> [a, a+s, ..., b)
	 *
	 *  Here, b is not included
	 *
	 ********************************************/

	LMAT_ENSURE_INLINE
	inline range colon(index_t a, index_t b)
	{
		return range(a, b-a);
	}

	LMAT_ENSURE_INLINE
	inline step_range colon(index_t a, index_t s, index_t b)
	{
		index_t n = a <= b ?
				(s > 0 ? (b - a) / s : 0) :
				(s < 0 ? (a - b) / (-s) : 0);

		return step_range(a, n, s);
	}
}

#endif
