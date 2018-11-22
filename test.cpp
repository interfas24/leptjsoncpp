#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "leptjsoncpp.h"

using namespace lept;

#define TEST_NUMBER(expect, json)   \
    do {\
        LeptValue v;\
        LeptContext j(json);\
        REQUIRE(PARSE_OK == LeptParser::Parse(v, j));\
        REQUIRE(LeptValue::LEPT_NUMBER == v.GetType());\
        REQUIRE(expect == v.GetNumber());\
    }while(0)

#define TEST_ERROR(error, json) \
    do {\
        LeptValue v;\
        LeptContext j(json);\
        REQUIRE(error == LeptParser::Parse(v, j));\
        REQUIRE(LeptValue::LEPT_NULL == v.GetType());\
    }while(0)

#define TEST_INVALID(json)	\
	TEST_ERROR(PARSE_INVALID_VALUE, json)

#define TEST_EXPECT(json)	\
	TEST_ERROR(PARSE_EXPECT_VALUE, json)

#define TEST_NOT_SINGULAR(json)	\
	TEST_ERROR(PARSE_ROOT_NOT_SINGULAR, json)

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
        TEST_EXPECT("");
        TEST_EXPECT("");
    }

    SECTION("parse invalid value") {
        TEST_INVALID("nul");
        TEST_INVALID("?");
    }

    SECTION("parse root not singular") {
        TEST_NOT_SINGULAR("null x");
    }
    #endif
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
        TEST_NUMBER(0.0, "1e-10000"); /* must underflow */
    	TEST_NUMBER(1.0000000000000002, "1.0000000000000002"); /* the smallest number > 1 */
    	TEST_NUMBER( 4.9406564584124654e-324, "4.9406564584124654e-324"); /* minimum denormal */
    	TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
    	TEST_NUMBER( 2.2250738585072009e-308, "2.2250738585072009e-308");  /* Max subnormal double */
    	TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
    	TEST_NUMBER( 2.2250738585072014e-308, "2.2250738585072014e-308");  /* Min normal positive double */
    	TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
    	TEST_NUMBER( 1.7976931348623157e+308, "1.7976931348623157e+308");  /* Max double */
        TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");
    }

}
