#pragma once
#include <type_traits>
#include <cmath>
#include "lazyops.h"
namespace Lazy {
	template<typename T>
	concept NotInit = !std::is_same_v<T, std::initializer_list<typename T::value_type>>;
	template <typename T>
	using if_scalar = std::is_scalar<typename std::remove_reference<T>::type>;

	template <typename T>
	inline auto index_wrapper(const T& val, unsigned int i) {
		if constexpr(if_scalar<T>::value)
			return val;
		else return val[i];
	}

	template <typename T>
	inline unsigned int size_wrapper(const T& val) {
		if constexpr(if_scalar<T>::value)
			return -1;
		else return val.size();
	}

	template <class T1, class Op>
	struct UnExpr {
		const T1 fst;
		const Op op;

		UnExpr(T1&& fst, Op&& op = Op()) : fst(std::forward<T1>(fst)), op(std::forward<Op>(op)) {}
		inline unsigned int size() const {
			return size_wrapper(fst);
		}
		template <NotInit Tres>
		inline operator Tres() const {
			unsigned int sz = size() == -1 ? 1 : size();
			auto res = Tres(sz);
			for(unsigned int i = 0; i < sz; i++) {
				res[i] = operator[](i);
			}
			return res;
		}
		inline auto operator[](unsigned int i)const {
			return op(index_wrapper(fst, i));
		}
	};

	template <class T1, class T2, class Op>
	struct BinExpr {
		const T1 fst;
		const T2 snd;
		const Op op;

		BinExpr(T1&& fst, T2&& snd, Op&& op = Op()) : fst(std::forward<T1>(fst)), snd(std::forward<T2>(snd)), op(std::forward<Op>(op)) {}
		inline unsigned int size() const {
			return std::min(size_wrapper(fst), size_wrapper(snd));
		}
		template <NotInit Tres>
		inline operator Tres() const {
			unsigned int sz = size() == -1 ? 1 : size();
			auto res = Tres(sz);
			for(unsigned int i = 0; i < sz; i++) {
				res[i] = operator[](i);
			}
			return res;
		}
		inline auto operator[](unsigned int i)const {
			return op(index_wrapper(fst, i), index_wrapper(snd, i));
		}
	};
	// Ternary is all you ever need (implemented manually rather than using tuples... might revisit someday)
	template <class T1, class T2, class T3, class Op>
	struct TerExpr {
		const T1 fst;
		const T2 snd;
		const T3 thd;
		const Op op;
		TerExpr(T1&& fst, T2&& snd, T3&& thd, Op&& op = Op()) : fst(std::forward<T1>(fst)), snd(std::forward<T2>(snd)), thd(std::forward<T3>(thd)), op(std::forward<Op>(op)) {}
		inline unsigned int size() const {
			return std::min(std::min(size_wrapper(fst), size_wrapper(snd)), size_wrapper(thd));
		}
		template <class Tres>
		inline operator Tres() const {
			unsigned int sz = size() == -1 ? 1 : size();
			auto res = Tres(sz);
			for(unsigned int i = 0; i < sz; i++) {
				res[i] = operator[](i);
			}
			return res;
		}
		inline auto operator[](unsigned int i)const {
			return op(index_wrapper(fst, i), index_wrapper(snd, i), index_wrapper(thd, i));
		}
	};

}