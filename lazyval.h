#pragma once
#include "lazyexpr.h"
namespace Lazy {
	//Ternary operands
	template<typename U1, typename U2, typename U3>
	inline auto cond(U1&& a, U2&& b, U3&& c) {
		return NaryExpr<OpCond, U1, U2, U3>(OpCond(), std::forward<U1>(a), std::forward<U2>(b), std::forward<U3>(c));
	}
	template<typename U1, typename U2, typename U3>
	inline auto limit(U1&& a, U2&& b, U3&& c) {
		return NaryExpr<OpLim, U1, U2, U3>(OpLim(), std::forward<U1>(a), std::forward<U2>(b), std::forward<U3>(c));
	}
	template<typename U1, typename U2, typename U3, typename TeOp>
	inline auto map(U1&& a, U2&& b, U3&& c, TeOp&& op = TeOp()) {
		return NaryExpr<TeOp, U1, U2, U3>(std::forward<TeOp>(op), std::forward<U1>(a), std::forward<U2>(b), std::forward<U3>(c));
	}
	//Binary operands
	template<typename U1, typename U2, typename BiOp>
	inline auto map(U1&& a, U2&& b, BiOp&& op = BiOp()) {
		return NaryExpr<BiOp, U1, U2>(std::forward<BiOp>(op), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto operator+(U1&& a, U2&& b) {
		return NaryExpr<OpAdd, U1, U2>(OpAdd(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto operator-(U1&& a, U2&& b) {
		return NaryExpr<OpSub, U1, U2>(OpSub(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto operator*(U1&& a, U2&& b) {
		return NaryExpr<OpMul, U1, U2>(OpMul(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto operator/(U1&& a, U2&& b) {
		return NaryExpr<OpDiv, U1, U2>(OpDiv(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto operator==(U1&& a, U2&& b) {
		return NaryExpr<OpEq, U1, U2>(OpEq(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto operator!=(U1&& a, U2&& b) {
		return NaryExpr<OpNeq, U1, U2>(OpNeq(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto operator>=(U1&& a, U2&& b) {
		return NaryExpr<OpGte, U1, U2>(OpGte(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto operator<=(U1&& a, U2&& b) {
		return NaryExpr<OpLte, U1, U2>(OpLte(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto operator<(U1&& a, U2&& b) {
		return NaryExpr<OpLt, U1, U2>(OpLt(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto operator>(U1&& a, U2&& b) {
		return NaryExpr<OpGt, U1, U2>(OpGt(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto min(U1&& a, U2&& b) {
		return NaryExpr<OpMin, U1, U2>(OpMin(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto max(U1&& a, U2&& b) {
		return NaryExpr<OpMax, U1, U2>(OpMax(), std::forward<U1>(a), std::forward<U2>(b));
	}
	template<typename U1, typename U2>
	inline auto pow(U1&& a, U2&& b) {
		return NaryExpr<OpPow, U1, U2>(OpPow(), std::forward<U1>(a), std::forward<U2>(b));
	}

	// Unary operands
	template<typename U1, typename UnOp>
	inline auto map(U1&& a, UnOp&& op = UnOp()) {
		return NaryExpr<UnOp, U1>(std::forward<UnOp>(op), std::forward<U1>(a));
	}
	template<typename U1>
	inline auto operator-(U1&& a) {
		return NaryExpr<OpNeg, U1>(OpNeg(),std::forward<U1>(a));
	}
	template<typename U1>
	inline auto identity(U1&& a) {
		return NaryExpr<OpId, U1>(OpId(), std::forward<U1>(a));
	}
	template<typename U1>
	inline auto sqrt(U1&& a) {
		return NaryExpr<OpSqrt, U1>(OpSqrt(), std::forward<U1>(a));
	}
	template<typename U1>
	inline auto sqr(U1&& a) {
		return NaryExpr<OpSqr, U1>(OpSqr(), std::forward<U1>(a));
	}
	template<typename U1>
	inline auto exp(U1&& a) {
		return NaryExpr<OpExp, U1>(OpExp(), std::forward<U1>(a));
	}
	template<typename U1>
	inline auto log(U1&& a) {
		return NaryExpr<OpLog, U1>(OpLog(), std::forward<U1>(a));
	}
	template<typename U1>
	inline auto log2(U1&& a) {
		return NaryExpr<OpLog2, U1>(OpLog2(), std::forward<U1>(a));
	}
	template<typename U1>
	inline auto log10(U1&& a) {
		return NaryExpr<OpLog10, U1>(OpLog10(), std::forward<U1>(a));
	}
}