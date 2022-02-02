#include "gtest/gtest.h"
#include "../common/scoreboard.hpp"

TEST(scoreboardTest, displayTest1) { //1 야추
    scoreboard * a = new scoreboard();
    dice_game _dice({1,1,1,1,1});
    auto v = a->display(_dice);
    std::vector<int> res = {5,0,0,0,0,0,0,
                            5,5,0,0,0,50};
    EXPECT_EQ(v,res);
}
TEST(scoreboardTest, displayTest2) { //2 야추
    scoreboard * a = new scoreboard();
    dice_game _dice({2,2,2,2,2});
    auto v = a->display(_dice);
    std::vector<int> res = {0,10,0,0,0,0,0,
                            10,10,0,0,0,50};
    EXPECT_EQ(v,res);
}

TEST(scoreboardTest, displayTest3) { //라지 스트레이트
    scoreboard * a = new scoreboard();
    dice_game _dice({1,2,3,4,5});
    auto v = a->display(_dice);
    std::vector<int> res = {1,2,3,4,5,0,0,
                            15,0,0,15,30,0};
    EXPECT_EQ(v,res);
}
TEST(scoreboardTest, displayTest4) { //풀하우스
    scoreboard * a = new scoreboard();
    dice_game _dice({5,5,5,6,6});
    auto v = a->display(_dice);
    std::vector<int> res = {0,0,0,0,15,12,0,
                            27,0,27,0,0,0};
    EXPECT_EQ(v,res);
}

TEST(scoreboardTest, displayTest5) { //스몰 스트레이트
    scoreboard * a = new scoreboard();
    dice_game _dice({1,2,3,4,6});
    auto v = a->display(_dice);
    std::vector<int> res = {1,2,3,4,0,6,0,
                            16,0,0,15,0,0};
    EXPECT_EQ(v,res);
}

TEST(scoreboardTest, displayTest6) { //4 of kind
    scoreboard * a = new scoreboard();
    dice_game _dice({4,2,4,4,4});
    auto v = a->display(_dice);
    std::vector<int> res = {0,2,0,16,0,0,0,
                            18,18,0,0,0,0};
    EXPECT_EQ(v,res);
}

TEST(scoreboardTest, displayTest7) { //3 야추
    scoreboard * a = new scoreboard();
    dice_game _dice({3,3,3,3,3});
    auto v = a->display(_dice);
    std::vector<int> res = {0,0,15,0,0,0,0,
                            15,15,0,0,0,50};
    EXPECT_EQ(v,res);
}
TEST(scoreboardTest, displayTest8) { //4 야추
    scoreboard * a = new scoreboard();
    dice_game _dice({4,4,4,4,4});
    auto v = a->display(_dice);
    std::vector<int> res = {0,0,0,20,0,0,0,
                            20,20,0,0,0,50};
    EXPECT_EQ(v,res);
}
TEST(scoreboardTest, displayTest9) { //5 야추
    scoreboard * a = new scoreboard();
    dice_game _dice({5,5,5,5,5});
    auto v = a->display(_dice);
    std::vector<int> res = {0,0,0,0,25,0,0,
                            25,25,0,0,0,50};
    EXPECT_EQ(v,res);
}

TEST(scoreboardTest, displayTest10) { //6 야추
    scoreboard * a = new scoreboard();
    dice_game _dice({6,6,6,6,6});
    auto v = a->display(_dice);
    std::vector<int> res = {0,0,0,0,0,30,0,
                            30,30,0,0,0,50};
    EXPECT_EQ(v,res);
}

TEST(scoreboardTest, displayTest11) { // 1 6 6 6 5
    scoreboard * a = new scoreboard();
    dice_game _dice({1,6,6,6,5});
    auto v = a->display(_dice);
    std::vector<int> res = {1,0,0,0,5,18,0,
                            24,0,0,0,0,0};
    EXPECT_EQ(v,res);
}

TEST(scoreboardTest, displayTest12) { //4 of kind
    scoreboard * a = new scoreboard();
    dice_game _dice({5,6,6,6,6});
    auto v = a->display(_dice);
    std::vector<int> res = {0,0,0,0,5,24,0,
                            29,29,0,0,0,0};
    EXPECT_EQ(v,res);
}

TEST(scoreboardTest, displayTest13) { //풀하우스
    scoreboard * a = new scoreboard();
    dice_game _dice({2,2,4,4,4});
    auto v = a->display(_dice);
    std::vector<int> res = {0,4,0,12,0,0,0,
                            16,0,16,0,0,0};
    EXPECT_EQ(v,res);
}

TEST(scoreboardTest, displayTest14) { //스몰 스트레이트
    scoreboard * a = new scoreboard();
    dice_game _dice({2,2,3,4,5});
    auto v = a->display(_dice);
    std::vector<int> res = {0,4,3,4,5,0,0,
                            16,0,0,15,0,0};
    EXPECT_EQ(v,res);
}
