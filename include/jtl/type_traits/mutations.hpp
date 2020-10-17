#ifndef JTL_TYPE_TRAITS_MUTATIONS_
#define JTL_TYPE_TRAITS_MUTATIONS_

#include <cstddef>

namespace jtl {

template<typename T>
struct type_identity {
    using type = T;
};
template<typename T>
using type_identity_t = typename type_identity<T>::type;

template<typename T>
struct remove_const : type_identity<T> {};
template<typename T>
struct remove_const<T const> : type_identity<T> {};
template<typename T>
using remove_const_t = typename remove_const<T>::type;

template<typename T>
struct remove_volatile : type_identity<T> {};
template<typename T>
struct remove_volatile<T volatile> : type_identity<T> {};
template<typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template<typename T>
using remove_cv = remove_volatile<remove_const_t<T>>;
template<typename T>
using remove_cv_t = typename remove_cv<T>::type;

template<typename T>
struct add_const : type_identity<T const> {};
template<typename T>
using add_const_t = typename add_const<T>::type;

template<typename T>
struct add_volatile : type_identity<T volatile> {};
template<typename T>
using add_volatile_t = typename add_volatile<T>::type;

template<typename T>
using add_cv = add_volatile<add_const_t<T>>;
template<typename T>
using add_cv_t = typename add_cv<T>::type;

template<typename T>
struct remove_reference : type_identity<T> {};
template<typename T>
struct remove_reference<T&> : type_identity<T> {};
template<typename T>
struct remove_reference<T&&> : type_identity<T> {};
template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

template<typename T>
struct add_lvalue_reference : type_identity<T&> {};
template<>
struct add_lvalue_reference<void> : type_identity<void> {};
template<>
struct add_lvalue_reference<const void> : type_identity<const void> {};
template<>
struct add_lvalue_reference<volatile void> : type_identity<volatile void> {};
template<>
struct add_lvalue_reference<volatile const void> : type_identity<volatile const void> {};
template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template<typename T>
struct add_rvalue_reference : type_identity<T&&> {};
template<>
struct add_rvalue_reference<void> : type_identity<void> {};
template<>
struct add_rvalue_reference<const void> : type_identity<const void> {};
template<>
struct add_rvalue_reference<volatile void> : type_identity<volatile void> {};
template<>
struct add_rvalue_reference<volatile const void> : type_identity<volatile const void> {};
template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template<typename T>
struct remove_pointer : type_identity<T> {};
template<typename T>
struct remove_pointer<T *> : type_identity<T> {};
template<typename T>
struct remove_pointer<T * const> : type_identity<T> {};
template<typename T>
struct remove_pointer<T * volatile> : type_identity<T> {};
template<typename T>
struct remove_pointer<T * const volatile> : type_identity<T> {};
template<typename T>
using remove_pointer_t = typename remove_pointer<T>::type;

template<typename T>
struct add_pointer : type_identity<T *> {};
template<typename T>
using add_pointer_t = typename add_pointer<T>::type;

template<typename T>
struct remove_extent : type_identity<T> {};
template<typename T, size_t N>
struct remove_extent<T[N]> : type_identity<T> {};
template<typename T>
struct remove_extent<T[]> : type_identity<T> {};
template<typename T>
using remove_extent_t = typename remove_extent<T>::type;

template<typename T>
struct remove_all_extents : type_identity<T> {};
template<typename T, size_t N>
struct remove_all_extents<T[N]> : remove_all_extents<T> {};
template<typename T>
struct remove_all_extents<T[]> : remove_all_extents<T> {};
template<typename T>
using remove_all_extents_t = typename remove_all_extents<T>::type;

template<typename T>
using remove_cvref = remove_cv<remove_reference_t<T>>;
template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

template<typename...>
using void_t = void;

}

#endif /* JTL_TYPE_TRAITS_MUTATIONS_ */
