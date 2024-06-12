#pragma once
#include <cmath>
namespace Lazy{
	// Ternary ops
	struct OpCond {
		template <typename T1, typename T2, typename T3>
		inline auto operator()(const T1& e1, const T2& e2, const T3& e3) const {
			return e1 ? e2 : e3;
		}
	};
	struct OpLim {
		template <typename T1, typename T2, typename T3>
		inline auto operator()(const T1& e1, const T2& e2, const T3& e3) const {
			return std::min(std::max(e1, T1(e2)), T1(e3));
		}
	};
	// Binary ops
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
	struct OpEq {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return e1 == e2;
		}
	};
	struct OpNeq {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return e1 != e2;
		}
	};
	struct OpGt {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return e1 > e2;
		}
	};
	struct OpLt {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return e1 < e2;
		}
	};
	struct OpGte {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return e1 >= e2;
		}
	};
	struct OpLte {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return e1 <= e2;
		}
	};
	struct OpMin {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return std::min(e1, T1(e2));
		}
	};
	struct OpMax {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return std::max(e1, T1(e2));
		}
	};
	struct OpPow {
		template <typename T1, typename T2>
		inline auto operator()(const T1& e1, const T2& e2) const {
			return std::pow(e1, e2);
		}
	};


	// Unary ops
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
}