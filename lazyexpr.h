#pragma once
#include <type_traits>
#include <cmath>
#include "lazyops.h"
namespace Lazy {

	template<typename T>
	using NotInit = std::negation<std::is_same<T, std::initializer_list<typename T::value_type>>>;
	template <typename T>
	using IfScalar = std::is_scalar<typename std::remove_reference<T>::type>;

	template <typename T>
	inline auto index_wrapper(const T& val, size_t i) {
		if constexpr(IfScalar<T>::value)
			return val;
		else return val[i];
	}

	template <typename T>
	inline size_t size_wrapper(const T& val) {
		if constexpr(IfScalar<T>::value)
			return size_t(-1);
		else return val.size();
	}

	template <typename T1, typename Op>
	struct UnExpr {
		const T1 fst;
		const Op op;

		UnExpr(T1&& fst, Op&& op = Op()) : fst(std::forward<T1>(fst)), op(std::forward<Op>(op)) {}

		inline size_t size() const { return size_wrapper(fst); }

		template <typename Tres, typename = std::enable_if_t<NotInit<Tres>::value>>
		inline operator Tres() const { return eval<Tres>();}

		template <typename Tres>
		inline Tres eval() const {
			size_t sz = size() == size_t(-1) ? 1 : size();
			auto res = Tres(sz);
			for(size_t i = 0; i < sz; i++) res[i] = operator[](i);
			return res;
		}

		inline auto operator[](size_t i)const { return op(index_wrapper(fst, i)); }
	};

	template <typename T1, typename T2, typename Op>
	struct BinExpr {
		const T1 fst;
		const T2 snd;
		const Op op;

		BinExpr(T1&& fst, T2&& snd, Op&& op = Op()) : fst(std::forward<T1>(fst)), snd(std::forward<T2>(snd)), op(std::forward<Op>(op)) {}

		inline size_t size() const { return std::min(size_wrapper(fst), size_wrapper(snd)); }

		template <typename Tres, typename = std::enable_if_t<NotInit<Tres>::value>>
		inline operator Tres() const { return eval<Tres>(); }

		template <typename Tres>
		inline Tres eval() const {
			size_t sz = size() == size_t(-1) ? 1 : size();
			auto res = Tres(sz);
			for(size_t i = 0; i < sz; i++) res[i] = operator[](i);
			return res;
		}

		inline auto operator[](size_t i)const { return op(index_wrapper(fst, i), index_wrapper(snd, i)); }

	};
	// Ternary is all you ever need (implemented manually rather than using tuples... might revisit someday)
	template <typename T1, typename T2, typename T3, typename Op>
	struct TerExpr {
		const T1 fst;
		const T2 snd;
		const T3 thd;
		const Op op;

		TerExpr(T1&& fst, T2&& snd, T3&& thd, Op&& op = Op()) : fst(std::forward<T1>(fst)), snd(std::forward<T2>(snd)), thd(std::forward<T3>(thd)), op(std::forward<Op>(op)) {}

		inline size_t size() const { return std::min(std::min(size_wrapper(fst), size_wrapper(snd)), size_wrapper(thd)); }

		template <typename Tres, typename = std::enable_if_t<NotInit<Tres>::value>>
		inline operator Tres() const { return eval<Tres>(); }

		template <typename Tres>
		inline Tres eval() const {
			size_t sz = size() == size_t(-1) ? 1 : size();
			auto res = Tres(sz);
			for(size_t i = 0; i < sz; i++) res[i] = operator[](i);
			return res;
		}

		inline auto operator[](size_t i)const { return op(index_wrapper(fst, i), index_wrapper(snd, i), index_wrapper(thd, i)); }
	};

}