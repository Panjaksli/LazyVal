#pragma once
#include <type_traits>
#include <cmath>
namespace Lazy {
	struct OpMul {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return e1 * e2;
		}
	};
	struct OpSub {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return e1 - e2;
		}
	};
	struct OpDiv {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return e1 / e2;
		}
	};
	struct OpAdd {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return e1 + e2;
		}
	};
	struct OpPow {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return std::pow(e1, e2);
		}
	};
	struct OpNeg {
		template <typename T1>
		inline auto operator()(const T1& e1) const {
			return -e1;
		}
	};
	struct OpSqrt {
		template <typename T1>
		inline auto operator()(const T1& e1) const {
			return std::sqrt(e1);
		}
	};
	struct OpExp {
		template <typename T1>
		inline auto operator()(const T1& e1) const {
			return std::exp(e1);
		}
	};
	struct OpLog2 {
		template <typename T1>
		inline auto operator()(const T1& e1) const {
			return std::log2(e1);
		}
	};
	struct OpLog {
		template <typename T1>
		inline auto operator()(const T1& e1) const {
			return std::log(e1);
		}
	};
	struct OpLog10 {
		template <typename T1>
		inline auto operator()(const T1& e1) const {
			return std::log10(e1);
		}
	};
	struct OpSqr {
		template <typename T1>
		inline auto operator()(const T1& e1) const {
			return e1 * e1;
		}
	};
	struct OpId {
		template <typename T1>
		inline auto operator()(const T1& e1) const {
			return e1;
		}
	};

	template<typename T>
	concept NotInit = !std::is_same_v<T, std::initializer_list<typename T::value_type>>;

	template <class T1, class Op>
	struct UnExpr;

	template <class T1, class Op>
	struct UnExpr {
		const T1 fst;
		const Op op;
		static constexpr bool Scal1 = std::is_scalar_v<typename std::remove_reference<T1>::type>;

		UnExpr(T1&& fst, Op&& op = Op()) : fst(std::forward<T1>(fst)), op(std::forward<Op>(op)) {}
		inline unsigned int size() const {
			if constexpr(Scal1) {
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
		inline auto operator[](unsigned int i)const {
			if constexpr(Scal1) {
				return op(fst);
			}
			else return op(fst[i]);
		}
	};

	template <class T1, class T2, class Op>
	struct BinExpr {
		const T1 fst;
		const T2 snd;
		const Op op;
		static constexpr bool Scal1 = std::is_scalar_v<typename std::remove_reference<T1>::type>;
		static constexpr bool Scal2 = std::is_scalar_v<typename std::remove_reference<T2>::type>;

		BinExpr(T1&& fst, T2&& snd, Op&& op = Op()) : fst(std::forward<T1>(fst)), snd(std::forward<T2>(snd)), op(std::forward<Op>(op)) {}
		inline unsigned int size() const {
			if constexpr(Scal1 && Scal2) {
				return -1;
			}
			else if constexpr(Scal1) {
				return snd.size();
			}
			else if constexpr(Scal2) {
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

		inline auto operator[](unsigned int i)const {
			if constexpr(Scal1 && Scal2) {
				return op(fst, snd);
			}
			else if constexpr(Scal1) {
				return op(fst, snd[i]);
			}
			else if constexpr(Scal2) {
				return op(fst[i], snd);
			}
			else return op(fst[i], snd[i]);
		}
		static unsigned int min(unsigned int x, unsigned int y) {
			return x < y ? x : y;
		}
	};

	template<class U1>
	inline auto operator-(U1&& a) {
		return UnExpr<U1, OpNeg>(std::forward<U1>(a));
	}
	template<class U1, class UnOp>
	inline auto map(U1&& a, UnOp && op = UnOp()) {
		return UnExpr<U1, UnOp>(std::forward<U1>(a), std::forward<UnOp>(op));
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
	template<class U1, class U2, class BiOp>
	inline auto map(U1&& a, U2&& b, BiOp&& op = BiOp()) {
		return BinExpr<U1, U2, BiOp>(std::forward<U1>(a), std::forward<U2>(b), std::forward<BiOp>(op));
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