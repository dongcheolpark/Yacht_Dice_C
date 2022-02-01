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
    std::vector<int> res = {1,2,3,4,5,0,0,
                            15,0,0,15,30,0};
    EXPECT_EQ(v,res);
}