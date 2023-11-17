#include <gtest/gtest.h>
#include <cmath>
#include "../src/Vector2.h"

TEST(Vector2, Length){
    //Length of (0, 0) == 0
    {
        Helpers::Vector2 v{0.0f, 0.0f};
        float l = Helpers::Vector2::Length(v);

        ASSERT_FLOAT_EQ(l, 0.0f);
    }

    //Length of a known vector
    {
        Helpers::Vector2 v{8.0f, -3.0f};
        float l = Helpers::Vector2::Length(v);

        ASSERT_NEAR(l, 8.544f, 0.01f);
    }
}

TEST(Vector2, DotProduct){
    //The dot product of Perpendicular vectors is 0.
    {
        Helpers::Vector2 a{0.0f, 1.0f};
        Helpers::Vector2 b{1.0f, 0.0f};

        ASSERT_FLOAT_EQ(Helpers::Vector2::Dot(a, b), 0.0f);
    }

    //The dot product of itself is equal to |v|^2
    {
        Helpers::Vector2 v{10.5f, -43.3f};
        float length = Helpers::Vector2::Length(v);

        ASSERT_FLOAT_EQ(Helpers::Vector2::Dot(v, v), length * length);
    }

    //Dot product of two known normalized vectors
    {
        Helpers::Vector2 a{0.5f, 0.5f};
        Helpers::Vector2 b{1.0f, 0.0f};

        ASSERT_FLOAT_EQ(Helpers::Vector2::Dot(a, b), 0.5f);
    }
 
     //Dot product of two known vectors
    {
        Helpers::Vector2 a{113.63f, -212.51f};
        Helpers::Vector2 b{-85.0f, 4.09f};

        ASSERT_NEAR(Helpers::Vector2::Dot(a, b), -10527.7159f, 0.01f);
    }

} 


TEST(Vector2, Normalize){
    //Normalize known vector
    {
        Helpers::Vector2 v{100.0f, 200.0f};
        Helpers::Vector2 n = Helpers::Vector2::Normalize(v); 

        ASSERT_FLOAT_EQ(n.x, 1.0f / sqrtf(5.0f));
        ASSERT_FLOAT_EQ(n.y, 2.0f / sqrt(5.0f));
    }

    //Normalize zeroed out vector 
    {
        Helpers::Vector2 v{0.0f, 0.0f};
        Helpers::Vector2 n = Helpers::Vector2::Normalize(v);
        ASSERT_TRUE(std::isnan(n.x));
        ASSERT_TRUE(std::isnan(n.y));
    }

    //Normalize already normalized vector
    {
        Helpers::Vector2 v{1.0f, 0.0f};
        Helpers::Vector2 n = Helpers::Vector2::Normalize(v); 

        ASSERT_FLOAT_EQ(n.x, 1.0f);
        ASSERT_FLOAT_EQ(n.y, 0.0f);

    }
}



int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
