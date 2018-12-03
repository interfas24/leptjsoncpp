#pragma once

#include <string>
#include <cstdlib>

namespace lept
{

typedef enum {
    PARSE_OK = 0,
    PARSE_EXPECT_VALUE,
    PARSE_INVALID_VALUE,
    PARSE_ROOT_NOT_SINGULAR,
    PARSE_NUMBER_TOO_BIG
}ParseResult;

#define MAX_STACK_SIZE  (512)

class LeptStack
{
public:
    LeptStack()
        :p_base((char*)(malloc(MAX_STACK_SIZE))),
       	 top(0),
	     capacity(MAX_STACK_SIZE)
    {
    }

    ~LeptStack()
    {
        if((p_base != nullptr) &&
           (top == 0)) {
            std::free(p_base);
        }
    }

    LeptStack(const LeptStack&) = delete;
    LeptStack(LeptStack&&) = delete;
    LeptStack& operator=(const LeptStack&) = delete;
    LeptStack& operator=(LeptStack&&) = delete;

    template<typename T>
    T* Push()
    {
        T* p = new (p_base+top) T(); 
        if(p != nullptr) {
            top += sizeof(T);
        }
        return p;
    }

    template<typename T>
    T* Pop()
    {
        top -= sizeof(T);
        return Top<T>();
    }

    template<typename T>
    T* Top() const
    {
        return reinterpret_cast<T*>(p_base + top);
    }

private:
    char *p_base;
    std::size_t top;
    std::size_t capacity;
};

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

    LeptContext& operator+=(std::size_t adv)
    {
        offset += adv;
        return *this;
    }

    std::string GetOneToken(std::size_t count) const {
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
    std::size_t offset;
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

    double GetNumber() const;

    void SetNumber(double num) {
        number = num;
    }


private:    
    LeptType type;
    double number;

};

class LeptParser
{
public:
    static ParseResult Parse(LeptValue &v, LeptContext &j);

private:
    static ParseResult ParseValue(LeptValue &v, LeptContext &j);
    static ParseResult ParseNumber(LeptValue &v, LeptContext &j);
    static ParseResult ParseLiteral(LeptValue &v, LeptContext &j,
                                    const std::string& literal, LeptValue::LeptType type);
    static void ParseWhitespace(LeptContext &j);
};


    
}
