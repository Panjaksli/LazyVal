#pragma once
#include <type_traits>
#include <cmath>
#include <tuple>
#include "lazyops.h"
namespace Lazy {

	template <typename Op, typename ...Ts>
	struct NaryExpr {

		template<typename T>
		using NotInit = std::negation<std::is_same<T, std::initializer_list<typename T::value_type>>>;
		template <typename T>
		using IfScalar = std::is_scalar<typename std::remove_reference<T>::type>;

		std::tuple<Ts...> args;
		const Op op; // = Op();
		// Uncomment if you want... There is really no need
		//NaryExpr(Ts && ... _args) : args(std::forward<Ts>(_args)...) {}
		NaryExpr(Op&& op, Ts && ... _args) : args(std::forward<Ts>(_args)...), op(std::forward<Op>(op)) {}

		inline size_t size() const {
			const auto call = [](Ts const& ... arg) { return std::min({size_wrapper(arg)...}); };
			return std::apply(call, args);
		}

		template <typename Tres, typename = std::enable_if_t<NotInit<Tres>::value>>
		inline operator Tres() const { return eval<Tres>(); }

		template <typename Tres>
		inline Tres eval() const {
			size_t res_size = size();
			res_size = res_size == size_t(-1) ? 1 : res_size;
			auto res = Tres(res_size);
			for(size_t i = 0; i < res_size; i++)
				res[i] = operator[](i);
			return res;
		}

		inline auto operator[](size_t i)const {
			const auto call = [op = this->op, i](Ts const& ... arg) { return op(index_wrapper(arg, i)...); };
			return std::apply(call, args);
		}

		template <typename T>
		static auto index_wrapper(const T& val, size_t i) {
			if constexpr(IfScalar<T>::value)
				return val;
			else return val[i];
		}

		template <typename T>
		static size_t size_wrapper(const T& val) {
			if constexpr(IfScalar<T>::value)
				return size_t(-1);
			else return val.size();
		}

	};

	template <typename Op, typename T1>
	using UnExpr = NaryExpr<Op, T1>;
	template <typename Op, typename T1, typename T2>
	using BinExpr = NaryExpr<Op, T1, T2>;
	template <typename Op, typename T1, typename T2, typename T3>
	using TerExpr = NaryExpr<Op, T1, T2, T3>;
}
