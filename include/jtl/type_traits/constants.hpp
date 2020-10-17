#ifndef JTL_TYPE_TRAITS_CONSTANTS_
#define JTL_TYPE_TRAITS_CONSTANTS_

namespace jtl {

template<typename T, T v>
struct integral_constant {
  using value_type = T;
  using type = integral_constant<T, v>;

  static constexpr T value = v;

  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

template<bool B>
using bool_constant = integral_constant<bool, B>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

}

#endif /* JTL_TYPE_TRAITS_CONSTANTS_ */
