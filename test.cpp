#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "leptjsoncpp.h"

using namespace lept;

TEST_CASE("TestParse") {
    REQUIRE(1 == 1);

    SECTION("parse null") {
        LeptValue v(LeptValue::LEPT_FALSE);
        LeptContext json("null");
        REQUIRE(PARSE_OK == LeptParser::Parse(v, json));
        REQUIRE(LeptValue::LEPT_NULL == v.GetType());
    }

    SECTION("parse expect value") {
        LeptValue v(LeptValue::LEPT_FALSE);
        LeptContext json("");
        REQUIRE(PARSE_EXPECT_VALUE == LeptParser::Parse(v, json));
        REQUIRE(LeptValue::LEPT_NULL == v.GetType());

        v.SetType(LeptValue::LEPT_FALSE);
        json = " ";
        REQUIRE(PARSE_EXPECT_VALUE == LeptParser::Parse(v, json));
        REQUIRE(LeptValue::LEPT_NULL == v.GetType());
    }

    SECTION("parse invalid value") {
        LeptValue v(LeptValue::LEPT_FALSE);
        LeptContext json("nul");
        REQUIRE(PARSE_INVALID_VALUE == LeptParser::Parse(v, json));
        REQUIRE(LeptValue::LEPT_NULL == v.GetType());

        v.SetType(LeptValue::LEPT_FALSE);
        json = "?";
        REQUIRE(PARSE_INVALID_VALUE == LeptParser::Parse(v, json));
        REQUIRE(LeptValue::LEPT_NULL == v.GetType());
    }

    SECTION("parse root not singular") {
        LeptValue v(LeptValue::LEPT_FALSE);
        LeptContext json("null x");
        REQUIRE(PARSE_ROOT_NOT_SINGULAR == LeptParser::Parse(v, json));
        REQUIRE(LeptValue::LEPT_NULL == v.GetType());
    }
}