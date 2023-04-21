#pragma once

//==================================================================================================================================================================
//17.04.2023
//==================================================================================================================================================================

#include <simpleListT.h>

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
class CBucket
{
    public:
        TValue  value;
        char*   key;

        CBucket ()
        {
            key = nullptr;
            value = 0;
        }

        CBucket (TValue Value, char* Key)
        {
            key = Key;
            value = Value;
        }

        CBucket (const CBucket& other)
        {
            value   = other.value;
            key     = new char[std::strlen(other.key) + 1];
            std::strcpy (key, other.key);
        }

        CBucket (const CBucket&& other)
        {
            value   = other.value;

            key     = other.key;
            other.key = nullptr;
        }

        CBucket& operator= (const CBucket& other)
        {
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
            delete [] key;
        }
};

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

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
