#include "serialize.h"

////////////////////////////////////////////////////
// define normal template function
////////////////////////////////////////////////////

template<typename SerializableType>
std::string serialize(SerializableType& a)
{
    return a.serialize();
}

template<typename SerializableType>
int deserialize(std::string &str, SerializableType& a)
{
    return a.deserialize(str);
}

DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(char)
DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(unsigned char)
DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(short int)
DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(unsigned short int)
DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(unsigned int)
DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(int)
DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(long int)
DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(unsigned long int)
DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(float)
DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(long long int)
DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(unsigned long long int)
DEF_BASIC_TYPE_SERIALIZE_AND_DESERIALIZE(double)

// for c++ type std::string
//template<>
std::string serialize(std::string& s)
{
    int len = s.size();
    std::string ret;
    ret.append(::serialize(len));
    ret.append(s.data(), len);
    return ret;
}

//template<>
int deserialize(std::string &str, std::string& s)
{
    int len;
    ::deserialize(str, len);
    s = str.substr(sizeof(len), len);
    return sizeof(int) + len;
}



