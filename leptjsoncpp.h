#pragma once

#include <string>

namespace lept
{

typedef enum {
    PARSE_OK = 0,
    PARSE_EXPECT_VALUE,
    PARSE_INVALID_VALUE,
    PARSE_ROOT_NOT_SINGULAR
}ParseResult;

class LeptContext
{
public:
    LeptContext(const char* j)
        :json(j), offset(0)
    {
    }

    LeptContext& operator=(const char* nj)
    {
        json = nj;
        offset = 0;
        return *this;
    }

    LeptContext& operator+=(int adv)
    {
        offset += adv;
        return *this;
    }

    std::string GetOneToken(int count) const {
        return std::string(CurrentJson(), count);
    }

    char CurrentChar() const {
        return *CurrentJson();
    }

    const char* CurrentJson() const{
        return json + offset;
    }

    const char* OriginJson() const {
        return json;
    }

private:
    const char* json;
    int offset;
};

class LeptValue 
{
public:
    typedef enum {
        LEPT_NULL,
        LEPT_FALSE,
        LEPT_TRUE,
        LEPT_NUMBER,
        LEPT_STRING,
        LEPT_ARRAY,
        LEPT_OBJECT
    }LeptType;

    LeptValue(LeptType t = LEPT_NULL)
    :type(t)
    {
    }

    LeptType GetType() const {
        return type;
    }

    void SetType(LeptType t) {
        type = t;
    }

private:    
    LeptType type;
};

class LeptParser
{
public:
    static ParseResult Parse(LeptValue &v, LeptContext &j);

private:
    static ParseResult ParseValue(LeptValue& v, LeptContext &j);
    static ParseResult ParseNULL(LeptValue& v, LeptContext &j);
    static void ParseWhitespace(LeptContext &j);
};


    
}