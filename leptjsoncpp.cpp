#include "leptjsoncpp.h"
#include <cassert>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

namespace lept
{

double LeptValue::GetNumber() const 
{
    assert(type == LEPT_NUMBER);
    return number;
}

ParseResult LeptParser::Parse(LeptValue& v, LeptContext& j)
{
    ParseResult ret;
    v.SetType(LeptValue::LEPT_NULL);
    ParseWhitespace(j);
    if((ret = ParseValue(v, j)) == PARSE_OK) {
        ParseWhitespace(j);
        if(j.CurrentChar() != '\0')
            return PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
}

ParseResult LeptParser::ParseValue(LeptValue& v, LeptContext& j)
{
    switch(j.CurrentChar())
    {
        case 'n': return ParseLiteral(v, j, "null", LeptValue::LEPT_NULL);
        case 't': return ParseLiteral(v, j, "true", LeptValue::LEPT_TRUE);
        case 'f': return ParseLiteral(v, j, "false", LeptValue::LEPT_FALSE);
        default: return ParseNumber(v, j);
        case '\0': return PARSE_EXPECT_VALUE;
    }
}

ParseResult LeptParser::ParseNumber(LeptValue &v, LeptContext &j)
{
    //TODO: modify Context
    const char *p = j.CurrentJson();
    char *end;

    errno = 0;
    //use strtod not stod
    double d = strtod(p, &end);
    if(errno == ERANGE && (d == HUGE_VAL || d == -HUGE_VAL))
        return PARSE_NUMBER_TOO_BIG;

    j += (end - p);
    v.SetNumber(d);
    v.SetType(LeptValue::LEPT_NUMBER);
    return PARSE_OK;
}

ParseResult LeptParser::ParseLiteral(LeptValue &v, LeptContext &j,
                                     const string &literal, LeptValue::LeptType type)
{
    size_t len = literal.size();
    if(j.GetOneToken(len) != literal) {
        return PARSE_INVALID_VALUE;
    }
    j += len;
    v.SetType(type);
    return PARSE_OK;
}

void LeptParser::ParseWhitespace(LeptContext& j)
{
    while(j.CurrentChar() == ' ' ||
          j.CurrentChar() == '\t' ||
          j.CurrentChar() == '\n')
    {
        j += 1;
    }
}

}
