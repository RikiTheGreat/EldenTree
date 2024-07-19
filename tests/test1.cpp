//
// Created by mahdi on 7/17/24.
//

#include <gtest/gtest.h>
#include "et/eldentree.hpp"

using namespace et;

class EldenTreeTest : public ::testing::Test {
    protected:
    et::EldenTree tree_;
};

TEST_F(EldenTreeTest, AddGodNoDuplicate) {
    god::God god1{"God1", 23};
    god::God god2{"God2", 3};
    auto mockAction = [](const god::GodEvent&) {};

    tree_.addGod(god1, mockAction);
    EXPECT_NO_THROW(tree_.addGod(god2, mockAction));
}

TEST_F(EldenTreeTest, AddGodDuplicate) {
    god::God god{"God1", 1};
    auto mockAction = [](const god::GodEvent&) {};

    tree_.addGod(god, mockAction);

    EXPECT_THROW(tree_.addGod(god, mockAction), std::runtime_error);
}

TEST_F(EldenTreeTest, AddEventGodEvent) {
    god::God god{"God1", 2};
    god::GodEvent event{"Event1"};
    auto mockAction = [](const god::GodEvent&) {};

    tree_.addGod(god, mockAction);
    EXPECT_NO_THROW(tree_.addEvent(god, event));
}

TEST_F(EldenTreeTest, AddEventString) {
    god::God god{"God1", 3};
    std::string event = "Event1";
    auto mockAction = [](const god::GodEvent&) {};

    tree_.addGod(god, mockAction);
    EXPECT_NO_THROW(tree_.addEvent(god, event));
}

TEST_F(EldenTreeTest, NoID) {
    god::God god{"God1"};
    std::string event = "Event1";
    auto mockAction = [](const god::GodEvent&) {};
    EXPECT_NO_THROW(tree_.addGod(god, mockAction));

}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}