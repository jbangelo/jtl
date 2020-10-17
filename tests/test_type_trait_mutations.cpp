#include <gtest/gtest.h>

#include <jtl/type_traits.hpp>

namespace {

struct Foo {
    int i;
    int get_i() const { return i; }
};
struct Bar {};
class Baz {};

TEST(TypeTraitMutations, TypeIdentity) {
    EXPECT_TRUE((std::is_same_v<int, jtl::type_identity_t<int>>));
    EXPECT_FALSE((std::is_same_v<unsigned, jtl::type_identity_t<int>>));
    EXPECT_FALSE((std::is_same_v<float, jtl::type_identity_t<int>>));
    EXPECT_FALSE((std::is_same_v<Foo, jtl::type_identity_t<int>>));
    EXPECT_FALSE((std::is_same_v<Bar, jtl::type_identity_t<int>>));
    EXPECT_FALSE((std::is_same_v<Baz, jtl::type_identity_t<int>>));

    EXPECT_TRUE((std::is_same_v<unsigned, jtl::type_identity_t<unsigned>>));
    EXPECT_FALSE((std::is_same_v<int, jtl::type_identity_t<unsigned>>));
    EXPECT_FALSE((std::is_same_v<float, jtl::type_identity_t<unsigned>>));
    EXPECT_FALSE((std::is_same_v<Foo, jtl::type_identity_t<unsigned>>));
    EXPECT_FALSE((std::is_same_v<Bar, jtl::type_identity_t<unsigned>>));
    EXPECT_FALSE((std::is_same_v<Baz, jtl::type_identity_t<unsigned>>));

    EXPECT_TRUE((std::is_same_v<float, jtl::type_identity_t<float>>));
    EXPECT_FALSE((std::is_same_v<int, jtl::type_identity_t<float>>));
    EXPECT_FALSE((std::is_same_v<unsigned, jtl::type_identity_t<float>>));
    EXPECT_FALSE((std::is_same_v<Foo, jtl::type_identity_t<float>>));
    EXPECT_FALSE((std::is_same_v<Bar, jtl::type_identity_t<float>>));
    EXPECT_FALSE((std::is_same_v<Baz, jtl::type_identity_t<float>>));

    EXPECT_TRUE((std::is_same_v<Foo, jtl::type_identity_t<Foo>>));
    EXPECT_FALSE((std::is_same_v<int, jtl::type_identity_t<Foo>>));
    EXPECT_FALSE((std::is_same_v<unsigned, jtl::type_identity_t<Foo>>));
    EXPECT_FALSE((std::is_same_v<float, jtl::type_identity_t<Foo>>));
    EXPECT_FALSE((std::is_same_v<Bar, jtl::type_identity_t<Foo>>));
    EXPECT_FALSE((std::is_same_v<Baz, jtl::type_identity_t<Foo>>));

    EXPECT_TRUE((std::is_same_v<Bar, jtl::type_identity_t<Bar>>));
    EXPECT_FALSE((std::is_same_v<int, jtl::type_identity_t<Bar>>));
    EXPECT_FALSE((std::is_same_v<unsigned, jtl::type_identity_t<Bar>>));
    EXPECT_FALSE((std::is_same_v<float, jtl::type_identity_t<Bar>>));
    EXPECT_FALSE((std::is_same_v<Foo, jtl::type_identity_t<Bar>>));
    EXPECT_FALSE((std::is_same_v<Baz, jtl::type_identity_t<Bar>>));

    EXPECT_TRUE((std::is_same_v<Baz, jtl::type_identity_t<Baz>>));
    EXPECT_FALSE((std::is_same_v<int, jtl::type_identity_t<Baz>>));
    EXPECT_FALSE((std::is_same_v<unsigned, jtl::type_identity_t<Baz>>));
    EXPECT_FALSE((std::is_same_v<float, jtl::type_identity_t<Baz>>));
    EXPECT_FALSE((std::is_same_v<Foo, jtl::type_identity_t<Baz>>));
    EXPECT_FALSE((std::is_same_v<Bar, jtl::type_identity_t<Baz>>));
}

TEST(TypeTraitMutations, RemoveConst) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_const_t<int>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_const_t<int const>>));
    EXPECT_TRUE((std::is_same_v<int volatile, jtl::remove_const_t<int volatile>>));
    EXPECT_TRUE((std::is_same_v<int volatile, jtl::remove_const_t<int volatile const>>));
    EXPECT_TRUE((std::is_same_v<int volatile, jtl::remove_const_t<int const volatile>>));

    // Pointers
    EXPECT_TRUE((std::is_same_v<int const volatile *, jtl::remove_const_t<int const volatile *>>));
    EXPECT_TRUE((std::is_same_v<int const volatile *, jtl::remove_const_t<int const volatile * const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile * volatile, jtl::remove_const_t<int const volatile * volatile>>));
    EXPECT_TRUE((std::is_same_v<int const volatile * volatile, jtl::remove_const_t<int const volatile * volatile const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile * volatile, jtl::remove_const_t<int const volatile * const volatile>>));

    // Pointer to member variable
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::*, jtl::remove_const_t<int const volatile Foo::*>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::*, jtl::remove_const_t<int const volatile Foo::* const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::* volatile, jtl::remove_const_t<int const volatile Foo::* volatile>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::* volatile, jtl::remove_const_t<int const volatile Foo::* volatile const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::* volatile, jtl::remove_const_t<int const volatile Foo::* const volatile>>));

    // Pointer to member function
    EXPECT_TRUE((std::is_same_v<int (Foo::*)() const volatile, jtl::remove_const_t<int (Foo::*)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::*)() const volatile, jtl::remove_const_t<int (Foo::* const)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile)() const volatile, jtl::remove_const_t<int (Foo::* volatile)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile)() const volatile, jtl::remove_const_t<int (Foo::* volatile const)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile)() const volatile, jtl::remove_const_t<int (Foo::* const volatile)() const volatile>>));
}

TEST(TypeTraitMutations, RemoveVolatile) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_volatile_t<int>>));
    EXPECT_TRUE((std::is_same_v<int const, jtl::remove_volatile_t<int const>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_volatile_t<int volatile>>));
    EXPECT_TRUE((std::is_same_v<int const, jtl::remove_volatile_t<int volatile const>>));
    EXPECT_TRUE((std::is_same_v<int const, jtl::remove_volatile_t<int const volatile>>));

    // Pointers
    EXPECT_TRUE((std::is_same_v<int const volatile *, jtl::remove_volatile_t<int const volatile *>>));
    EXPECT_TRUE((std::is_same_v<int const volatile *, jtl::remove_volatile_t<int const volatile * volatile>>));
    EXPECT_TRUE((std::is_same_v<int const volatile * const, jtl::remove_volatile_t<int const volatile * const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile * const, jtl::remove_volatile_t<int const volatile * volatile const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile * const, jtl::remove_volatile_t<int const volatile * const volatile>>));

    // Pointer to member variable
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::*, jtl::remove_volatile_t<int const volatile Foo::*>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::* const, jtl::remove_volatile_t<int const volatile Foo::* const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::*, jtl::remove_volatile_t<int const volatile Foo::* volatile>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::* const, jtl::remove_volatile_t<int const volatile Foo::* volatile const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::* const, jtl::remove_volatile_t<int const volatile Foo::* const volatile>>));

    // Pointer to member function
    EXPECT_TRUE((std::is_same_v<int (Foo::*)() const volatile, jtl::remove_volatile_t<int (Foo::*)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* const)() const volatile, jtl::remove_volatile_t<int (Foo::* const)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::*)() const volatile, jtl::remove_volatile_t<int (Foo::* volatile)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* const)() const volatile, jtl::remove_volatile_t<int (Foo::* volatile const)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* const)() const volatile, jtl::remove_volatile_t<int (Foo::* const volatile)() const volatile>>));
}

TEST(TypeTraitMutations, RemoveConstVolatile) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cv_t<int>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cv_t<int const>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cv_t<int volatile>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cv_t<int volatile const>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cv_t<int const volatile>>));

    // Pointers
    EXPECT_TRUE((std::is_same_v<int const volatile *, jtl::remove_cv_t<int const volatile *>>));
    EXPECT_TRUE((std::is_same_v<int const volatile *, jtl::remove_cv_t<int const volatile * volatile>>));
    EXPECT_TRUE((std::is_same_v<int const volatile *, jtl::remove_cv_t<int const volatile * const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile *, jtl::remove_cv_t<int const volatile * volatile const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile *, jtl::remove_cv_t<int const volatile * const volatile>>));

    // Pointer to member variable
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::*, jtl::remove_cv_t<int const volatile Foo::*>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::*, jtl::remove_cv_t<int const volatile Foo::* const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::*, jtl::remove_cv_t<int const volatile Foo::* volatile>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::*, jtl::remove_cv_t<int const volatile Foo::* volatile const>>));
    EXPECT_TRUE((std::is_same_v<int const volatile Foo::*, jtl::remove_cv_t<int const volatile Foo::* const volatile>>));

    // Pointer to member function
    EXPECT_TRUE((std::is_same_v<int (Foo::*)() const volatile, jtl::remove_cv_t<int (Foo::*)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::*)() const volatile, jtl::remove_cv_t<int (Foo::* const)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::*)() const volatile, jtl::remove_cv_t<int (Foo::* volatile)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::*)() const volatile, jtl::remove_cv_t<int (Foo::* volatile const)() const volatile>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::*)() const volatile, jtl::remove_cv_t<int (Foo::* const volatile)() const volatile>>));
}

TEST(TypeTraitMutations, AddConst) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int const, jtl::add_const_t<int>>));
    EXPECT_TRUE((std::is_same_v<int const, jtl::add_const_t<int const>>));
    EXPECT_TRUE((std::is_same_v<int volatile const, jtl::add_const_t<int volatile>>));
    EXPECT_TRUE((std::is_same_v<int volatile const, jtl::add_const_t<int volatile const>>));

    // Pointers
    EXPECT_TRUE((std::is_same_v<int volatile const * const, jtl::add_const_t<int volatile const *>>));
    EXPECT_TRUE((std::is_same_v<int volatile const * const, jtl::add_const_t<int volatile const * const>>));
    EXPECT_TRUE((std::is_same_v<int volatile const * volatile const, jtl::add_const_t<int volatile const * volatile>>));
    EXPECT_TRUE((std::is_same_v<int volatile const * volatile const, jtl::add_const_t<int volatile const * volatile const>>));

    // Pointer to member variable
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* const, jtl::add_const_t<int volatile const Foo::*>>));
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* const, jtl::add_const_t<int volatile const Foo::* const>>));
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* volatile const, jtl::add_const_t<int volatile const Foo::* volatile>>));
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* volatile const, jtl::add_const_t<int volatile const Foo::* volatile const>>));

    // Pointer to member function
    EXPECT_TRUE((std::is_same_v<int (Foo::* const)() volatile const, jtl::add_const_t<int (Foo::*)() volatile const>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* const)() volatile const, jtl::add_const_t<int (Foo::* const)() volatile const>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile const)() volatile const, jtl::add_const_t<int (Foo::* volatile)() volatile const>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile const)() volatile const, jtl::add_const_t<int (Foo::* volatile const)() volatile const>>));
}

TEST(TypeTraitMutations, AddVolatile) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int volatile, jtl::add_volatile_t<int>>));
    EXPECT_TRUE((std::is_same_v<int volatile const, jtl::add_volatile_t<int const>>));
    EXPECT_TRUE((std::is_same_v<int volatile, jtl::add_volatile_t<int volatile>>));
    EXPECT_TRUE((std::is_same_v<int volatile const, jtl::add_volatile_t<int volatile const>>));

    // Pointers
    EXPECT_TRUE((std::is_same_v<int volatile const * volatile, jtl::add_volatile_t<int volatile const *>>));
    EXPECT_TRUE((std::is_same_v<int volatile const * volatile const, jtl::add_volatile_t<int volatile const * const>>));
    EXPECT_TRUE((std::is_same_v<int volatile const * volatile, jtl::add_volatile_t<int volatile const * volatile>>));
    EXPECT_TRUE((std::is_same_v<int volatile const * volatile const, jtl::add_volatile_t<int volatile const * volatile const>>));

    // Pointer to member variable
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* volatile, jtl::add_volatile_t<int volatile const Foo::*>>));
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* volatile const, jtl::add_volatile_t<int volatile const Foo::* const>>));
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* volatile, jtl::add_volatile_t<int volatile const Foo::* volatile>>));
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* volatile const, jtl::add_volatile_t<int volatile const Foo::* volatile const>>));

    // Pointer to member function
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile)() volatile const, jtl::add_volatile_t<int (Foo::*)() volatile const>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile const)() volatile const, jtl::add_volatile_t<int (Foo::* const)() volatile const>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile)() volatile const, jtl::add_volatile_t<int (Foo::* volatile)() volatile const>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile const)() volatile const, jtl::add_volatile_t<int (Foo::* volatile const)() volatile const>>));
}

TEST(TypeTraitMutations, AddConstVolatile) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int volatile const, jtl::add_cv_t<int>>));
    EXPECT_TRUE((std::is_same_v<int volatile const, jtl::add_cv_t<int const>>));
    EXPECT_TRUE((std::is_same_v<int volatile const, jtl::add_cv_t<int volatile>>));
    EXPECT_TRUE((std::is_same_v<int volatile const, jtl::add_cv_t<int volatile const>>));

    // Pointers
    EXPECT_TRUE((std::is_same_v<int volatile const * volatile const, jtl::add_cv_t<int volatile const *>>));
    EXPECT_TRUE((std::is_same_v<int volatile const * volatile const, jtl::add_cv_t<int volatile const * const>>));
    EXPECT_TRUE((std::is_same_v<int volatile const * volatile const, jtl::add_cv_t<int volatile const * volatile>>));
    EXPECT_TRUE((std::is_same_v<int volatile const * volatile const, jtl::add_cv_t<int volatile const * volatile const>>));

    // Pointer to member variable
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* volatile const, jtl::add_cv_t<int volatile const Foo::*>>));
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* volatile const, jtl::add_cv_t<int volatile const Foo::* const>>));
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* volatile const, jtl::add_cv_t<int volatile const Foo::* volatile>>));
    EXPECT_TRUE((std::is_same_v<int volatile const Foo::* volatile const, jtl::add_cv_t<int volatile const Foo::* volatile const>>));

    // Pointer to member function
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile const)() volatile const, jtl::add_cv_t<int (Foo::*)() volatile const>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile const)() volatile const, jtl::add_cv_t<int (Foo::* const)() volatile const>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile const)() volatile const, jtl::add_cv_t<int (Foo::* volatile)() volatile const>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile const)() volatile const, jtl::add_cv_t<int (Foo::* volatile const)() volatile const>>));
}

TEST(TypeTraitMutations, RemoveReference) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_reference_t<int>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_reference_t<int &>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_reference_t<int &&>>));

    // Pointers
    EXPECT_TRUE((std::is_same_v<int *, jtl::remove_reference_t<int *>>));
    EXPECT_TRUE((std::is_same_v<int *, jtl::remove_reference_t<int * &>>));
    EXPECT_TRUE((std::is_same_v<int *, jtl::remove_reference_t<int * &&>>));

    // Pointer to member variable
    EXPECT_TRUE((std::is_same_v<int Foo::*, jtl::remove_reference_t<int Foo::*>>));
    EXPECT_TRUE((std::is_same_v<int Foo::*, jtl::remove_reference_t<int Foo::* &>>));
    EXPECT_TRUE((std::is_same_v<int Foo::*, jtl::remove_reference_t<int Foo::* &&>>));

    // Pointer to member function
    EXPECT_TRUE((std::is_same_v<int (Foo::*)(), jtl::remove_reference_t<int (Foo::*)()>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::*)(), jtl::remove_reference_t<int (Foo::* &)()>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::*)(), jtl::remove_reference_t<int (Foo::* &&)()>>));
}

TEST(TypeTraitMutations, AddLValueReference) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int &, jtl::add_lvalue_reference_t<int>>));
    EXPECT_TRUE((std::is_same_v<int &, jtl::add_lvalue_reference_t<int &>>));
    EXPECT_TRUE((std::is_same_v<int &, jtl::add_lvalue_reference_t<int &&>>));

    // Pointers
    EXPECT_TRUE((std::is_same_v<int * &, jtl::add_lvalue_reference_t<int *>>));
    EXPECT_TRUE((std::is_same_v<int * &, jtl::add_lvalue_reference_t<int * &>>));
    EXPECT_TRUE((std::is_same_v<int * &, jtl::add_lvalue_reference_t<int * &&>>));

    // Pointer to member variable
    EXPECT_TRUE((std::is_same_v<int Foo::* &, jtl::add_lvalue_reference_t<int Foo::*>>));
    EXPECT_TRUE((std::is_same_v<int Foo::* &, jtl::add_lvalue_reference_t<int Foo::* &>>));
    EXPECT_TRUE((std::is_same_v<int Foo::* &, jtl::add_lvalue_reference_t<int Foo::* &&>>));

    // Pointer to member function
    EXPECT_TRUE((std::is_same_v<int (Foo::* &)(), jtl::add_lvalue_reference_t<int (Foo::*)()>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* &)(), jtl::add_lvalue_reference_t<int (Foo::* &)()>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* &)(), jtl::add_lvalue_reference_t<int (Foo::* &&)()>>));

    // void
    EXPECT_TRUE((std::is_same_v<void, jtl::add_lvalue_reference_t<void>>));
    EXPECT_TRUE((std::is_same_v<volatile void, jtl::add_lvalue_reference_t<volatile void>>));
    EXPECT_TRUE((std::is_same_v<const void, jtl::add_lvalue_reference_t<const void>>));
    EXPECT_TRUE((std::is_same_v<volatile const void, jtl::add_lvalue_reference_t<volatile const void>>));
}

TEST(TypeTraitMutations, AddRValueReference) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int &&, jtl::add_rvalue_reference_t<int>>));
    EXPECT_TRUE((std::is_same_v<int &, jtl::add_rvalue_reference_t<int &>>));
    EXPECT_TRUE((std::is_same_v<int &&, jtl::add_rvalue_reference_t<int &&>>));

    // Pointers
    EXPECT_TRUE((std::is_same_v<int * &&, jtl::add_rvalue_reference_t<int *>>));
    EXPECT_TRUE((std::is_same_v<int * &, jtl::add_rvalue_reference_t<int * &>>));
    EXPECT_TRUE((std::is_same_v<int * &&, jtl::add_rvalue_reference_t<int * &&>>));

    // Pointer to member variable
    EXPECT_TRUE((std::is_same_v<int Foo::* &&, jtl::add_rvalue_reference_t<int Foo::*>>));
    EXPECT_TRUE((std::is_same_v<int Foo::* &, jtl::add_rvalue_reference_t<int Foo::* &>>));
    EXPECT_TRUE((std::is_same_v<int Foo::* &&, jtl::add_rvalue_reference_t<int Foo::* &&>>));

    // Pointer to member function
    EXPECT_TRUE((std::is_same_v<int (Foo::* &&)(), jtl::add_rvalue_reference_t<int (Foo::*)()>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* &)(), jtl::add_rvalue_reference_t<int (Foo::* &)()>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* &&)(), jtl::add_rvalue_reference_t<int (Foo::* &&)()>>));

    // void
    EXPECT_TRUE((std::is_same_v<void, jtl::add_rvalue_reference_t<void>>));
    EXPECT_TRUE((std::is_same_v<volatile void, jtl::add_rvalue_reference_t<volatile void>>));
    EXPECT_TRUE((std::is_same_v<const void, jtl::add_rvalue_reference_t<const void>>));
    EXPECT_TRUE((std::is_same_v<volatile const void, jtl::add_rvalue_reference_t<volatile const void>>));
}

TEST(TypeTraitMutations, RemovePointer) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_pointer_t<int>>));
    EXPECT_TRUE((std::is_same_v<volatile int, jtl::remove_pointer_t<volatile int>>));
    EXPECT_TRUE((std::is_same_v<const int, jtl::remove_pointer_t<const int>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_pointer_t<volatile const int>>));

    // Pointers
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_pointer_t<int *>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_pointer_t<int * volatile>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_pointer_t<int * const>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_pointer_t<int * volatile const>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_pointer_t<volatile const int *>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_pointer_t<volatile const int * volatile>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_pointer_t<volatile const int * const>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_pointer_t<volatile const int * volatile const>>));
    EXPECT_TRUE((std::is_same_v<int *, jtl::remove_pointer_t<int **>>));
    EXPECT_TRUE((std::is_same_v<int *, jtl::remove_pointer_t<int ** volatile>>));
    EXPECT_TRUE((std::is_same_v<int *, jtl::remove_pointer_t<int ** const>>));
    EXPECT_TRUE((std::is_same_v<int *, jtl::remove_pointer_t<int ** volatile const>>));
}

TEST(TypeTraitMutations, AddPointer) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int *, jtl::add_pointer_t<int>>));
    EXPECT_TRUE((std::is_same_v<volatile int *, jtl::add_pointer_t<volatile int>>));
    EXPECT_TRUE((std::is_same_v<const int *, jtl::add_pointer_t<const int>>));
    EXPECT_TRUE((std::is_same_v<volatile const int *, jtl::add_pointer_t<volatile const int>>));

    // Pointers
    EXPECT_TRUE((std::is_same_v<int **, jtl::add_pointer_t<int *>>));
    EXPECT_TRUE((std::is_same_v<int * volatile *, jtl::add_pointer_t<int * volatile>>));
    EXPECT_TRUE((std::is_same_v<int * const *, jtl::add_pointer_t<int * const>>));
    EXPECT_TRUE((std::is_same_v<int * volatile const *, jtl::add_pointer_t<int * volatile const>>));

    // Pointer to member variable
    EXPECT_TRUE((std::is_same_v<int Foo::**, jtl::add_pointer_t<int Foo::*>>));
    EXPECT_TRUE((std::is_same_v<int Foo::* volatile *, jtl::add_pointer_t<int Foo::* volatile>>));
    EXPECT_TRUE((std::is_same_v<int Foo::* const *, jtl::add_pointer_t<int Foo::* const>>));
    EXPECT_TRUE((std::is_same_v<int Foo::* volatile const *, jtl::add_pointer_t<int Foo::* volatile const>>));

    // Pointer to member function
    EXPECT_TRUE((std::is_same_v<int (Foo::**)(), jtl::add_pointer_t<int (Foo::*)()>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile *)(), jtl::add_pointer_t<int (Foo::* volatile)()>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* const *)(), jtl::add_pointer_t<int (Foo::* const)()>>));
    EXPECT_TRUE((std::is_same_v<int (Foo::* volatile const *)(), jtl::add_pointer_t<int (Foo::* volatile const)()>>));

    // void
    EXPECT_TRUE((std::is_same_v<void *, jtl::add_pointer_t<void>>));
}

TEST(TypeTraitMutations, RemoveExtent) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_extent_t<int>>));
    EXPECT_TRUE((std::is_same_v<volatile int, jtl::remove_extent_t<volatile int>>));
    EXPECT_TRUE((std::is_same_v<const int, jtl::remove_extent_t<const int>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_extent_t<volatile const int>>));

    // Unknown array length
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_extent_t<int[]>>));
    EXPECT_TRUE((std::is_same_v<volatile int, jtl::remove_extent_t<volatile int[]>>));
    EXPECT_TRUE((std::is_same_v<const int, jtl::remove_extent_t<const int[]>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_extent_t<volatile const int[]>>));

    // Known array length
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_extent_t<int[10]>>));
    EXPECT_TRUE((std::is_same_v<volatile int, jtl::remove_extent_t<volatile int[10]>>));
    EXPECT_TRUE((std::is_same_v<const int, jtl::remove_extent_t<const int[10]>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_extent_t<volatile const int[10]>>));

    // Multiple dimentional array
    EXPECT_TRUE((std::is_same_v<int[10], jtl::remove_extent_t<int[10][10]>>));
    EXPECT_TRUE((std::is_same_v<volatile int[10], jtl::remove_extent_t<volatile int[10][10]>>));
    EXPECT_TRUE((std::is_same_v<const int[10], jtl::remove_extent_t<const int[10][10]>>));
    EXPECT_TRUE((std::is_same_v<volatile const int[10], jtl::remove_extent_t<volatile const int[10][10]>>));
}

TEST(TypeTraitMutations, RemoveAllExtents) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_all_extents_t<int>>));
    EXPECT_TRUE((std::is_same_v<volatile int, jtl::remove_all_extents_t<volatile int>>));
    EXPECT_TRUE((std::is_same_v<const int, jtl::remove_all_extents_t<const int>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_all_extents_t<volatile const int>>));

    // Unknown array length
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_all_extents_t<int[]>>));
    EXPECT_TRUE((std::is_same_v<volatile int, jtl::remove_all_extents_t<volatile int[]>>));
    EXPECT_TRUE((std::is_same_v<const int, jtl::remove_all_extents_t<const int[]>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_all_extents_t<volatile const int[]>>));

    // Known array length
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_all_extents_t<int[10]>>));
    EXPECT_TRUE((std::is_same_v<volatile int, jtl::remove_all_extents_t<volatile int[10]>>));
    EXPECT_TRUE((std::is_same_v<const int, jtl::remove_all_extents_t<const int[10]>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_all_extents_t<volatile const int[10]>>));

    // Multiple dimentional array
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_all_extents_t<int[10][10]>>));
    EXPECT_TRUE((std::is_same_v<volatile int, jtl::remove_all_extents_t<volatile int[10][10]>>));
    EXPECT_TRUE((std::is_same_v<const int, jtl::remove_all_extents_t<const int[10][10]>>));
    EXPECT_TRUE((std::is_same_v<volatile const int, jtl::remove_all_extents_t<volatile const int[10][10]>>));
}

TEST(TypeTraitMutations, RemoveConstVolatileReference) {
    // Regular variable
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int volatile>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int const>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int volatile const>>));

    // lvalue reference
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int &>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int volatile &>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int const &>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int volatile const &>>));

    // rvalue reference
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int &&>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int volatile &&>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int const &&>>));
    EXPECT_TRUE((std::is_same_v<int, jtl::remove_cvref_t<int volatile const &&>>));
}

TEST(TypeTraitMutations, VoidT) {
    EXPECT_TRUE((std::is_same_v<void, jtl::void_t<int>>));
    EXPECT_TRUE((std::is_same_v<void, jtl::void_t<volatile int>>));
    EXPECT_TRUE((std::is_same_v<void, jtl::void_t<const int>>));
    EXPECT_TRUE((std::is_same_v<void, jtl::void_t<volatile const int>>));
}

}
