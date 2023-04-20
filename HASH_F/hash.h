//==================================================================================================================================================================
//17.04.2023
//==================================================================================================================================================================

#include <simpleListT.h>

#include "MYassert.h"

#include <inttypes.h>


//==================================================================================================================================================================

#define VOID (void) 0

//==================================================================================================================================================================

template <typename TValue>
struct SBucket
{
    TValue  value;
    char*   key;
};

template <typename TValue>
class CHashTable
{
    public:
        size_t  size;
        CList <SBucket <TValue>>**   Table;

        CHashTable (int Size)
        {
            size = Size;

            Table = new CList <SBucket <TValue>>* [size];

            for (size_t cnt = 0; cnt < size; cnt++)
            {
                Table[cnt] = nullptr;
            }

            return;
        }

        ~CHashTable ()
        {
            for (size_t cnt = 0; cnt < size; ++cnt)
            {
                if (Table[cnt] != nullptr)
                {
                    delete Table[cnt];
                }
            }

            delete[] Table;

            return;
        }

        int key_to_index (char* Key)
        {
            MCA (Key != nullptr, 0);

            int hash = first_ASCII (Key);

            return hash % size;
        }

        void add_to_table (char* Key, TValue Value)
        {
            MCA (Table != nullptr, VOID);

//             SBucket<TValue>* bucket = new SBucket<TValue>;
//
//             bucket->key      = Key;
//             bucket->value    = Value;


            int index = key_to_index (Key);

            if (Table[index] == nullptr)
            {
                Table[index] = new CList<SBucket<TValue>>;
            }

            Table[index]->insert_tail ({Value, Key});

            return;
        }

        void print_table ()
        {
            for (size_t cnt = 0; cnt < size; ++cnt)
            {
                if (Table[cnt] != nullptr)
                {
                    printf ("=%d=\n", cnt);
                    Table[cnt]->print_list ();
                }
            }

            return;
        }

//==================================================================================================================================================================

        uint64_t constant (char* Key)
        {
            MCA (Key != nullptr, 0);

            return 1ul;
        }

        uint64_t first_ASCII (char* Key)
        {
            MCA (Key != nullptr, 0);

            return (uint64_t) Key[0];
        }
};

//==================================================================================================================================================================

int count_symbols_in_file (FILE* stream);

char* read_data_from_file (const char* Filename);

template <typename TValue>
void load_in_HT_data_by_words (CHashTable<TValue>* HashTable, char* Data);

//==================================================================================================================================================================
