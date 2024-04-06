#pragma once
#include "lazyexpr.h"
namespace Lazy {
	//Ternary operands
	template<class U1, class U2, class U3>
	inline auto cond(U1&& a, U2&& b, U3&& c) {
		return TerExpr<U1, U2, U3, OpCond>(std::forward<U1>(a), std::forward<U2>(b), std::forward<U3>(c));
	}
	template<class U1, class U2, class U3>
	inline auto limit(U1&& a, U2&& b, U3&& c) {
		return TerExpr<U1, U2, U3, OpLim>(std::forward<U1>(a), std::forward<U2>(b), std::forward<U3>(c));
	}
	template<class U1, class U2, class U3, class TeOp>
	inline auto map(U1&& a, U2&& b, U3&& c, TeOp&& op = TeOp()) {
		return TerExpr<U1, U2, U3, TeOp>(std::forward<U1>(a), std::forward<U2>(b), std::forward<U3>(c), std::forward<TeOp>(op));
	}
	//Binary operands
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
	inline auto operator==(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpEq>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto operator!=(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpNeq>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto operator>=(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpGte>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto operator<=(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpLte>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto operator<(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpLt>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto operator>(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpGt>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto min(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpMin>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto max(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpMax>(std::forward<U1>(a), std::forward<U2>(b));
	}
	template<class U1, class U2>
	inline auto pow(U1&& a, U2&& b) {
		return BinExpr<U1, U2, OpPow>(std::forward<U1>(a), std::forward<U2>(b));
	}

	// Unary operands
	template<class U1, class UnOp>
	inline auto map(U1&& a, UnOp&& op = UnOp()) {
		return UnExpr<U1, UnOp>(std::forward<U1>(a), std::forward<UnOp>(op));
	}
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
}