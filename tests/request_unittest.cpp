#include "../request.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <mockcpp/mockcpp.hpp>

TEST(Request_TEST, test_has_key) {
    Twf::Request r;

    r["ok"] = "ok";
    EXPECT_FALSE(r.hasKey("ok"));

    r.assign("bad", "bad");
    EXPECT_TRUE(r.hasKey("bad"));
}

int add(int x, int y) {
    return 0;
}

TEST(Request_TEST, test_mockcpp) {
    MOCKER(add).expects(once()).will(returnValue(100));
    EXPECT_EQ(100, add(1,2));
}
