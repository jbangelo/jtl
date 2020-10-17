#include <type_traits>
#include <gtest/gtest.h>
#include <jtl/type_traits.hpp>

namespace {

TEST(TypeTraitConstants, IntegralConstant) {
    {
        jtl::integral_constant<int, 0> i;

        EXPECT_EQ(i, 0);
        EXPECT_NE(i, 1);
        EXPECT_EQ(i(), 0);
        EXPECT_NE(i(), 1);

        EXPECT_TRUE((std::is_same_v<typename decltype(i)::type, decltype(i)>));
        EXPECT_TRUE((std::is_same_v<typename decltype(i)::value_type, int>));
    }

    {
        jtl::integral_constant<unsigned, 0> u;

        EXPECT_EQ(u, 0);
        EXPECT_NE(u, 1);
        EXPECT_EQ(u(), 0);
        EXPECT_NE(u(), 1);

        EXPECT_TRUE((std::is_same_v<typename decltype(u)::type, decltype(u)>));
        EXPECT_TRUE((std::is_same_v<typename decltype(u)::value_type, unsigned>));
    }

    {
        enum class E {
            E1,
            E2,
            E3,
        };
        jtl::integral_constant<E, E::E2> e;

        EXPECT_EQ(e, E::E2);
        EXPECT_NE(e, E::E1);
        EXPECT_NE(e, E::E3);
        EXPECT_EQ(e(), E::E2);
        EXPECT_NE(e(), E::E1);
        EXPECT_NE(e(), E::E3);

        EXPECT_TRUE((std::is_same_v<typename decltype(e)::type, decltype(e)>));
        EXPECT_TRUE((std::is_same_v<typename decltype(e)::value_type, E>));
    }
}

TEST(TypeTraitConstants, BoolConstant) {
    EXPECT_TRUE(jtl::true_type{});
    EXPECT_TRUE(jtl::true_type{}());
    EXPECT_TRUE(jtl::true_type{}.value);
    EXPECT_TRUE((std::is_same_v<jtl::true_type::value_type, bool>));
    EXPECT_TRUE((std::is_same_v<jtl::true_type::type, jtl::integral_constant<bool, true>>));

    EXPECT_FALSE(jtl::false_type{});
    EXPECT_FALSE(jtl::false_type{}());
    EXPECT_FALSE(jtl::false_type{}.value);  
    EXPECT_TRUE((std::is_same_v<jtl::false_type::value_type, bool>));
    EXPECT_TRUE((std::is_same_v<jtl::false_type::type, jtl::integral_constant<bool, false>>));
}

}
