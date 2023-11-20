#include <gtest/gtest.h>
#include <cmath>
#include "../src/Vector2.h"
#include "../src/Solver.h"

//UTILS
TEST(Helpers, DegToRad) {
     //Known Radians
    {
        float x0 = Helpers::DegToRad(0.0f); //0 degrees
        float x1 = Helpers::DegToRad(30.0f); //30 degrees
        float x2 = Helpers::DegToRad(240.0f); //240 degrees
        float x3 = Helpers::DegToRad(180.0f); //180 degrees

        ASSERT_FLOAT_EQ(x0, 0.0f);
        ASSERT_FLOAT_EQ(x1, Helpers::PI / 6.0);
        ASSERT_FLOAT_EQ(x2, (Helpers::PI * 4) / 3.0);
        ASSERT_FLOAT_EQ(x3, Helpers::PI);
    }

}

TEST(Helpers, RadToDeg) {
    //Known Degrees
    {
        float x0 = Helpers::RadToDeg(0.0f); //0 degrees
        float x1 = Helpers::RadToDeg(Helpers::PI / 6.0); //30 degrees
        float x2 = Helpers::RadToDeg((Helpers::PI * 4)/3.0); //240 degrees
        float x3 = Helpers::RadToDeg(Helpers::PI); //180 degrees

        ASSERT_FLOAT_EQ(x0, 0.0f);
        ASSERT_FLOAT_EQ(x1, 30.0f);
        ASSERT_FLOAT_EQ(x2, 240.0f);
        ASSERT_FLOAT_EQ(x3, 180.0f);
    }
}

//VECTOR 2
TEST(Vector2, Rotation) {
    //Rotate by +90 degrees
    {
        Helpers::Vector2 v{0.0f, 1.0f};
        Helpers::Vector2 r = Helpers::Vector2::Rotate(v, (90.0f));
        Helpers::Vector2 r2 = Helpers::Vector2::Rotate(r, (-90.0f));

        float l = Helpers::Vector2::Length(r); 
        float x = Helpers::Vector2::ToDegrees(v); 
        float inv = Helpers::Vector2::ToDegrees(r);   //Convert from heading angle to normal angles. 
        float inv2 = Helpers::Vector2::ToDegrees(r2);   //Convert from heading angle to normal angles. 

        ASSERT_NEAR(r.x, 1.0f, 0.001f);
        ASSERT_NEAR(r.y, 0.0f, 0.001f);
        ASSERT_FLOAT_EQ(inv, 90.0f);
    }

    //Rotate by -90 degrees
    {
        Helpers::Vector2 v{0.0f, 1.0f};
        Helpers::Vector2 r = Helpers::Vector2::Rotate(v, (-90.0f));

        ASSERT_NEAR(r.x, -1.0f, 0.001f);
        ASSERT_NEAR(r.y, 0.0f, 0.001f);

    }
}

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

        float l = Helpers::Vector2::Length(n);

        ASSERT_FLOAT_EQ(n.x, 1.0f / sqrtf(5.0f));
        ASSERT_FLOAT_EQ(n.y, 2.0f / sqrt(5.0f));
        ASSERT_FLOAT_EQ(l, 1.0f);
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

        float l = Helpers::Vector2::Length(n);

        ASSERT_FLOAT_EQ(n.x, 1.0f);
        ASSERT_FLOAT_EQ(n.y, 0.0f);
        ASSERT_FLOAT_EQ(l, 1.0f);
        
    }
}

TEST(Intersection, Visibility) {
    //Run the test case from the example given. 
    std::vector<Helpers::Entity> world;
    ASSERT_NO_THROW(world = Helpers::LoadEntityData("../Data/TestData.csv"));
    if (world.size() > 0) {
        Helpers::Entity* pStart = &*world.begin();
        Helpers::Entity* pEnd = &*world.begin() + world.size();
        float FoV = 45.0f;
        float distance = 20.0f;
        Helpers::Entity& viewer = world[0];
        {
            std::vector<uint32_t> visible = VisibleEntities(viewer, pStart, pEnd, FoV, distance);
            ASSERT_EQ(visible.size(), 1);
            ASSERT_EQ(visible[0], 2);
        }


    }
    else {
        FAIL();
    }
}

int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
