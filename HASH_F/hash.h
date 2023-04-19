//==================================================================================================================================================================
//17.04.2023
//==================================================================================================================================================================

#include <simpleListT.h>

#include "MYassert.h"

#include <inttypes.h>


//==================================================================================================================================================================

#define VOID (void) 0

//==================================================================================================================================================================

template <typename TKey, typename TValue>
struct SBucket
{
    TKey    key;
    TValue  value;
};

template <typename TKey, typename TValue>
class CHashTable
{
    public:
        size_t  size;
        CList <SBucket <TKey, TValue>>*   Table;

        CHashTable (int Size)
        {
            size = Size;

            Table = new CList <SBucket <TKey, TValue>> [size];

            return;
        }

        ~CHashTable ()
        {
            delete[] Table;

            return;
        }

        void add_to_table (TKey Key, TValue Value)
        {
            MCA (Table != nullptr, VOID);

            Table[Key % size].insert_tail ({Key, Value});

            return;
        }

        uint64_t constant (char* line)
        {
            MLA (line != nullptr);

            return 1ul;
        }

        uint64_t first_ASCII (char* line)
        {
            MLA (line != nullptr);

            return (uint64_t) line[0];
        }
};

//==================================================================================================================================================================
