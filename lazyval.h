#pragma once
#include <type_traits>
#include <cmath>
namespace Lazy {
	struct OpMul {
		template <typename T1, typename T2>
		static auto op(const T1& e1, const T2& e2) {
			return e1 * e2;
		}
	};
	struct OpSub {
		template <typename T1, typename T2>
		static auto op(const T1& e1, const T2& e2) {
			return e1 - e2;
		}
	};
	struct OpDiv {
		template <typename T1, typename T2>
		static auto op(const T1& e1, const T2& e2) {
			return e1 / e2;
		}
	};
	struct OpAdd {
		template <typename T1, typename T2>
		static auto op(const T1& e1, const T2& e2) {
			return e1 + e2;
		}
	};
	struct OpPow {
		template <typename T1, typename T2>
		static auto op(const T1& e1, const T2& e2) {
			return std::pow(e1, e2);
		}
	};
	struct OpNeg {
		template <typename T1>
		static auto op(const T1& e1) {
			return -e1;
		}
	};
	struct OpSqrt {
		template <typename T1>
		static auto op(const T1& e1) {
			return std::sqrt(e1);
		}
	};
	struct OpExp {
		template <typename T1>
		static auto op(const T1& e1) {
			return std::exp(e1);
		}
	};
	struct OpLog2 {
		template <typename T1>
		static auto op(const T1& e1) {
			return std::log2(e1);
		}
	};
	struct OpLog {
		template <typename T1>
		static auto op(const T1& e1) {
			return std::log(e1);
		}
	};
	struct OpLog10 {
		template <typename T1>
		static auto op(const T1& e1) {
			return std::log10(e1);
		}
	};
	struct OpSqr {
		template <typename T1>
		static auto op(const T1& e1) {
			return e1 * e1;
		}
	};
	struct OpId {
		template <typename T1>
		static auto op(const T1& e1) {
			return e1;
		}
	};

	template<typename T>
	concept NotInit = !std::is_same_v<T, std::initializer_list<typename T::value_type>>;

	template <class T1, class Op>
	struct UnExpr {
		const T1 fst;
		UnExpr(T1&& fst) : fst(std::forward<T1>(fst)) {}
		unsigned int size() const {
			if constexpr(std::is_scalar<T1>::value) {
				return -1;
			}
			else return fst.size();
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
		auto operator[](unsigned int i)const {
			if constexpr(std::is_scalar<T1>::value) {
				return Op::op(fst);
			}
			else return Op::op(fst[i]);
		}
	};

	template <class T1, class T2, class Op>
	struct BinExpr {
		const T1 fst;
		const T2 snd;
		BinExpr(T1&& fst, T2&& snd) : fst(std::forward<T1>(fst)), snd(std::forward<T2>(snd)) {}
		unsigned int size() const {
			if constexpr(std::is_scalar<T1>::value && std::is_scalar<T2>::value) {
				return -1;
			}
			else if constexpr(std::is_scalar<T1>::value) {
				return snd.size();
			}
			else if constexpr(std::is_scalar<T2>::value) {
				return fst.size();
			}
			else return min(fst.size(), snd.size());
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

		auto operator[](unsigned int i)const {
			if constexpr(std::is_scalar<T1>::value && std::is_scalar<T2>::value) {
				return Op::op(fst, snd);
			}
			else if constexpr(std::is_scalar<T1>::value) {
				return Op::op(fst, snd[i]);
			}
			else if constexpr(std::is_scalar<T2>::value) {
				return Op::op(fst[i], snd);
			}
			else return Op::op(fst[i], snd[i]);
		}
		static unsigned int min(unsigned int x, unsigned int y) {
			return x < y ? x : y;
		}
	};

	template<class U1>
	inline auto operator-(U1&& a) {
		return UnExpr<U1, OpNeg>(std::forward<U1>(a));
	}
	template<class U1>
	inline auto sqrt(U1&& a) {
		return UnExpr<U1, OpSqrt>(std::forward<U1>(a));
	}
	template<class U1>
	inline auto sqr(U1&& a) {
		return UnExpr<U1, OpSqr>(std::forward<U1>(a));
	}
	template<class U1>
	inline auto exp(U1&& a) {
		return UnExpr<U1, OpExp>(std::forward<U1>(a));
	}
	template<class U1>
	inline auto log(U1&& a) {
		return UnExpr<U1, OpLog>(std::forward<U1>(a));
	}
	template<class U1>
	inline auto log2(U1&& a) {
		return UnExpr<U1, OpLog2>(std::forward<U1>(a));
	}
	template<class U1>
	inline auto log10(U1&& a) {
		return UnExpr<U1, OpLog10>(std::forward<U1>(a));
	}
	template<class U1, class U2>
	inline auto operator+(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpAdd>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto operator-(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpSub>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto operator*(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpMul>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto operator/(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpDiv>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto pow(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpPow>(std::forward<U1>(a), std::forward<U2>(b));
	}
}
