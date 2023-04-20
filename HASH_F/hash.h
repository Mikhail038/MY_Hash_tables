#pragma once

//==================================================================================================================================================================
//17.04.2023
//==================================================================================================================================================================

#include <simpleListT.h>

#include "MYassert.h"

#include <string.h>
#include <ctype.h>
#include <inttypes.h>


//==================================================================================================================================================================

#define PLUG 0

#define VOID (void) 0

#define MAX_WORD_LENGTH 20

//==================================================================================================================================================================

template <typename TValue>
struct SBucket
{
    TValue  value;
    char*   key;

    ~SBucket()
    {
        free (key);
    }
};

template <typename TValue>
class CHashTable
{
    public:
        size_t  size;
        CList <SBucket <TValue>>**   Table;

        CHashTable (size_t Size)
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

        size_t key_to_index (char* Key)
        {
            MCA (Key != nullptr, 0);

            size_t hash = first_ASCII (Key);

            return hash % size;
        }

        void add_to_table (char* Key, TValue Value)
        {
            MCA (Table != nullptr, VOID);

            size_t index = key_to_index (Key);

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

        size_t constant (char* Key)
        {
            MCA (Key != nullptr, 0);

            return 1ul;
        }

        size_t first_ASCII (char* Key)
        {
            MCA (Key != nullptr, 0);

            return (size_t) Key[0];
        }
};

//==================================================================================================================================================================

int count_symbols_in_file (FILE* stream);

char* read_data_from_file (const char* Filename);

template <typename TValue>
void load_in_HT_data_by_words (CHashTable<TValue>* HashTable, char* Data)
{
    size_t Length = strlen (Data);

    for (size_t cnt = 0; cnt < Length; ++cnt)
    {
        if (isalpha (Data[cnt]) != 0)
        {
            char* Word = (char*) calloc (MAX_WORD_LENGTH, sizeof (char));

            size_t i = 0;
            while ((isalpha (Data[cnt]) != 0) || (Data[cnt] == '\''))
            {
                printf ("%c", Data[cnt]);

                Word[i] = Data[cnt];

                i++;
                cnt++;
            }

            printf ("\n");

            Word[i] = '\0';
            HashTable->add_to_table (Word, PLUG);
        }
    }

    return;
}

//==================================================================================================================================================================
