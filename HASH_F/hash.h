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
        CList <SBucket <TKey, TValue>>**   Table;

        CHashTable (int Size)
        {
            size = Size;

            Table = new CList <SBucket <TKey, TValue>>* [size];

            return;
        }

        ~CHashTable ()
        {
            delete[] Table;

            return;
        }

        int key_to_index (TKey Key)
        {
            return first_ASCII (Key) % size;
        }

        void add_to_table (TKey Key, TValue Value)
        {
            MCA (Table != nullptr, VOID);

            int index = key_to_index (Key);

            Table[index]->insert_tail ({Key, Value});

            return;
        }

        void print_table ()
        {
            for (int cnt = 0; cnt < size; ++cnt)
            {
                if (Table[cnt] != nullptr)
                {
                    Table[cnt]->print_list ();
                }
            }

            return;
        }

        uint64_t constant (TKey Key)
        {
            return 1ul;
        }

        uint64_t first_ASCII (TKey Key)
        {
            MCA ((char*) Key != nullptr, 0);

            return (uint64_t) ((char*) Key)[0];
        }
};

//==================================================================================================================================================================
