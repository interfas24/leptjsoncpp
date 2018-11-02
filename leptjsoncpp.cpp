#include "leptjsoncpp.h"

using namespace std;

namespace lept
{

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
        case 'n': return ParseNULL(v, j);
        case '\0': return PARSE_EXPECT_VALUE;
        default: return PARSE_INVALID_VALUE;
    }
}

ParseResult LeptParser::ParseNULL(LeptValue& v, LeptContext& j)
{
    if(j.GetOneToken(4) != string("null")) {
        return PARSE_INVALID_VALUE;
    }
    j += 4;
    v.SetType(LeptValue::LEPT_NULL);
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