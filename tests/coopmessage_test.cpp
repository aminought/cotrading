#include <gtest/gtest.h>
#include "coop/coopmessage.h"

using ct::coop::CoopMessage;
using ct::chart::HorizontalLine;

TEST(TO_JSON, COOPSERVERMESSAGE) {
    CoopMessage message;
    auto l1 = std::make_shared<HorizontalLine>(10);
    auto l2 = std::make_shared<HorizontalLine>(20);
    auto l3 = std::make_shared<HorizontalLine>(30);
    message.set_lines({l1, l2, l3});
    auto json = message.to_json();

    EXPECT_EQ("[{\"line\":{\"y\":10}},{\"line\":{\"y\":20}},{\"line\":{\"y\":30}}]", json.dump());
}
