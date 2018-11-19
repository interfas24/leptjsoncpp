#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "leptjsoncpp.h"

using namespace lept;

#define TEST_NUMBER(expect, json) \
    do {\
        LeptValue v;\
        LeptContext j(json);\
        REQUIRE(PARSE_OK == LeptParser::Parse(v, j));\
        REQUIRE(LeptValue::LEPT_NUMBER == v.GetType());\
        REQUIRE(expect == v.GetNumber());\
    }while(0)

TEST_CASE("TestParse") {

    SECTION("parse literal") {
        LeptValue v(LeptValue::LEPT_FALSE);
        LeptContext json("null");
	REQUIRE(PARSE_OK == LeptParser::Parse(v, json));
	REQUIRE(LeptValue::LEPT_NULL == v.GetType());
	
	json = "true";
	REQUIRE(PARSE_OK == LeptParser::Parse(v, json));
	REQUIRE(LeptValue::LEPT_TRUE == v.GetType());

	json = "false";
	REQUIRE(PARSE_OK == LeptParser::Parse(v, json));
	REQUIRE(LeptValue::LEPT_FALSE == v.GetType());
    }

    #if 0
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
    #endif

    SECTION("parse root not singular") {
        LeptValue v(LeptValue::LEPT_FALSE);
        LeptContext json("null x");
        REQUIRE(PARSE_ROOT_NOT_SINGULAR == LeptParser::Parse(v, json));
        REQUIRE(LeptValue::LEPT_NULL == v.GetType());
    }
}

TEST_CASE("TestNumber") {
    SECTION("simple number"){
        TEST_NUMBER(0.0, "0");
        TEST_NUMBER(0.0, "-0");
        TEST_NUMBER(0.0, "-0.0");
        TEST_NUMBER(1.0, "1");
        TEST_NUMBER(-1.0, "-1");
        TEST_NUMBER(1.5, "1.5");
        TEST_NUMBER(-1.5, "-1.5");
        TEST_NUMBER(3.1416, "3.1416");
        TEST_NUMBER(1E10, "1E10");
        TEST_NUMBER(1e10, "1e10");
        TEST_NUMBER(1E+10, "1E+10");
        TEST_NUMBER(1E-10, "1E-10");
        TEST_NUMBER(-1E10, "-1E10");
        TEST_NUMBER(-1e10, "-1e10");
        TEST_NUMBER(-1E+10, "-1E+10");
        TEST_NUMBER(-1E-10, "-1E-10");
        TEST_NUMBER(1.234E+10, "1.234E+10");
        TEST_NUMBER(1.234E-10, "1.234E-10");
        //TEST_NUMBER(0.0, "1e-10000"); /* must underflow */
    }

}
