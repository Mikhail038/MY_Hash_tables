#pragma once

//==================================================================================================================================================================

// #include "Tracy.hpp"
#define ZoneScoped

#include <string.h>
#include <ctype.h>
#include <inttypes.h>

#include <cstring>

//==================================================================================================================================================================

template <typename TValue>
class CBucket
{
    public:
        TValue  value;
        char*   key;

        CBucket ()
        {
            ZoneScoped;

            key = nullptr;
            value = 0;
        }

        CBucket (TValue Value, char* Key)
        {
            ZoneScoped;

            key = Key;
            value = Value;
        }

        CBucket (const CBucket& other)
        {
            ZoneScoped;

            value   = other.value;
            key     = new char[std::strlen(other.key) + 1];
            std::strcpy (key, other.key);
        }

        CBucket (const CBucket&& other)
        {
            ZoneScoped;

            value   = other.value;

            key     = other.key;
            other.key = nullptr;
        }

        CBucket& operator= (const CBucket& other)
        {
            ZoneScoped;

            if (this == &other)
            {
                return *this;
            }

            char* tmp_key = new char[std::strlen (other.key) + 1];

            std::strcpy (tmp_key, other.key);

            delete[] key;

            key = tmp_key;

            return *this;
        }

        ~CBucket()
        {
            ZoneScoped;

            delete [] key;
        }
};
