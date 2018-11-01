#pragma once

namespace lept
{
    typedef enum {
        LEPT_NULL,
        LEPT_FALSE,
        LEPT_TRUE,
        LEPT_NUMBER,
        LEPT_STRING,
        LEPT_ARRAY,
        LEPT_OBJECT
    }LeptType;

    typedef enum {
        PARSE_OK = 0,
        PARSE_EXPECT_VALUE,
        PARSE_INVALID_VALUE,
        PARSE_ROOT_NOT_SINGULAR
    }ParseResult;

    class LeptValue 
    {
    public:
        LeptValue(const char* j, LeptType t);

        LeptType GetType() const {
            return type;
        }

        const char* GetJson() const {
            return json;
        }

        void SetJson(const char* nj) {
            json = nj;
        }

    private:    
        const char* json;
        LeptType type;
    };

    class LeptParser
    {
    public:
        static ParseResult Parse(const LeptValue &v);

    private:
        static ParseResult ParseValue(const LeptValue& v);
        static ParseResult ParseNULL(const LeptValue& v);
        //static ParseResult ParseNULL(const LeptValue& v);
        static void ParseWhitespace(const char* j);

    };


    
}