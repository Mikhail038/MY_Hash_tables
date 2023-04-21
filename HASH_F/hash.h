#pragma once

//==================================================================================================================================================================
//17.04.2023
//==================================================================================================================================================================

#include "simpleListT.h"
#include "bucket.h"

#include "MYassert.h"

#include <string.h>
#include <ctype.h>
#include <inttypes.h>

#include <cstring>

//==================================================================================================================================================================

#define PLUG 0

#define VOID (void) 0

#define MAX_WORD_LENGTH 20

//==================================================================================================================================================================

template <typename TValue>
class CHashTable
{
    public:
        size_t  size;
        CList <CBucket <TValue>>**   Table;

        CHashTable (size_t Size)
        {
            size = Size;

            Table = new CList <CBucket <TValue>>* [size];

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

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

        void add_to_table (char* Key, TValue Value)
        {
            MCA (Table != nullptr, VOID);

            size_t index = key_to_index (Key);

            if (Table[index] == nullptr)
            {
                Table[index] = new CList<CBucket<TValue>>;
            }

            CBucket<TValue>* bucket = new CBucket<TValue>(Value, Key);

            Table[index]->insert_tail (*bucket);

            delete bucket;

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

        void print_collision_lengths ()
        {
            for (size_t cnt = 0; cnt < size; ++cnt)
            {
                if (Table[cnt] != nullptr)
                {
                    printf ("|%3d| SIZE: %d\n", cnt, Table[cnt]->size);

                }
            }

            return;
        }

        size_t key_to_index (char* Key)
        {
            MCA (Key != nullptr, 0);

            size_t hash = h_first_ascii (Key);

            return hash % size;
        }

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

        size_t h_constant (char* Key)
        {
            MCA (Key != nullptr, 0);

            return (size_t) 1;
        }

        size_t h_first_ascii (char* Key)
        {
            MCA (Key != nullptr, 0);

            return (size_t) Key[0];
        }

        size_t h_length (char* Key)
        {
            MCA (Key != nullptr, 0);

            return strlen (Key);
        }

        size_t h_sum_ascii (char* Key)
        {
            MCA (Key != nullptr, 0);

            size_t sum = 0;

            size_t cnt = 0;
            while (Key[cnt] != '\0')
            {
                sum += (size_t) Key[cnt];

                cnt++;
            }

            return sum;
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
            char* Word = (char*) new char [MAX_WORD_LENGTH];

            size_t i = 0;
            while ((isalpha (Data[cnt]) != 0) || (Data[cnt] == '\''))
            {
                //printf ("%c", Data[cnt]);

                Word[i] = Data[cnt];

                i++;
                cnt++;
            }

            //printf ("\n");

            Word[i] = '\0';
            HashTable->add_to_table (Word, PLUG);
        }
    }

    return;
}

//==================================================================================================================================================================
