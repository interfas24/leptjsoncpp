#include "leptjsonpp.h"

namespace lept
{

LeptValue::LeptValue(const char* j, LeptType t)
    :json(j), type(t)
{
}

ParseResult LeptParser::Parse(const LeptValue& v)
{
    ParseValue(v);
}

ParseResult LeptParser::ParseValue(const LeptValue& v)
{
    switch(*v.GetJson())
    {
        case 'n': return ParseNULL(v);
        case '\0': return ParseResult::PARSE_EXPECT_VALUE;
        default: return ParseResult::PARSE_INVALID_VALUE;
    }
}

ParseResult LeptParser::ParseNULL(const LeptValue& v)
{

}

void LeptParser::ParseWhitespace(const char* nj)
{
    
}

}