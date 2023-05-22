#pragma once

//==================================================================================================================================================================

// #include "Tracy.hpp"
#include <cstdio>
#include <memory>
#define ZoneScoped

#include <immintrin.h>

#include <string.h>
#include <ctype.h>
#include <inttypes.h>

#include <cstring>

//==================================================================================================================================================================

#define SIMD_SIZE 32

//==================================================================================================================================================================

// template <typename TValue>
// class CBucket
// {
//     public:
//         TValue  value;
//         char*   key;
//
//         CBucket ()
//         {
//             ZoneScoped;
//
//             key = nullptr;
//             value = 0;
//         }
//
//         CBucket (TValue Value, char* Key)
//         {
//             ZoneScoped;
//
//             key = Key;
//             value = Value;
//         }
//
//         CBucket (const CBucket& other)
//         {
//             ZoneScoped;
//
//             value   = other.value;
//             key     = new char[std::strlen(other.key) + 1];
//             std::strcpy (key, other.key);
//         }
//
//         CBucket (const CBucket&& other)
//         {
//             ZoneScoped;
//
//             value   = other.value;
//
//             key     = other.key;
//             other.key = nullptr;
//         }
//
//         CBucket& operator= (const CBucket& other)
//         {
//             ZoneScoped;
//
//             if (this == &other)
//             {
//                 return *this;
//             }
//
//             char* tmp_key = new char[std::strlen (other.key) + 1];
//
//             std::strcpy (tmp_key, other.key);
//
//             delete[] key;
//
//             key = tmp_key;
//
//             return *this;
//         }
//
//         ~CBucket()
//         {
//             ZoneScoped;
//
//             delete [] key;
//         }
// };

//==================================================================================================================================================================

template <typename TValue>
class CBucket
{
    public:
        TValue  value = 0;
        __m256i   key = {0};

        CBucket () = default;

        CBucket (TValue Value, char* Key)
        {
            // MLA (strlen (Key) >= SIMD_SIZE);

            ZoneScoped;

            char Key_packed[SIMD_SIZE] __attribute__ ((aligned (32))) {0};


            for (int cnt = 0; (Key[cnt] != '\0') && (cnt != SIMD_SIZE - 1); ++cnt)
            {
                Key_packed[cnt] = Key[cnt];
            }

            // printf("param  %p ""\n""packed %p ""\n""class  %p""\n", Key, Key_packed, key);
            key = _mm256_load_si256((const __m256i*) Key_packed);

            // free (Key_packed);

            value = Value;

            delete [] Key;
        }

//         CBucket (const CBucket& other)
//         {
//             ZoneScoped;
//
//             value   = other.value;
//             key     = other.key;
//         }
//
//         CBucket (const CBucket&& other)
//         {
//             ZoneScoped;
//
//             value   = other.value;
//
//             key     = other.key;
//             other.key = nullptr;
//         }
//
//         CBucket& operator= (const CBucket& other)
//         {
//             ZoneScoped;
//
//             if (this == &other)
//             {
//                 return *this;
//             }
//
//             key = other.key;
//
//             return *this;
//         }
//
//         ~CBucket()
//         {
//             ZoneScoped;
//         }
};
