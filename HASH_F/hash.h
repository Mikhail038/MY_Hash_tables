#pragma once

//==================================================================================================================================================================
//17.04.2023
//==================================================================================================================================================================

// #include "Tracy.hpp"
#define ZoneScoped

#include <immintrin.h>

#include "simpleListT.h"
#include "bucket.h"

#include "MYassert.h"

#include <cstddef>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

#include <cstring>

//==================================================================================================================================================================

#define PLUG 0

#define VOID (void) 0

#define MAX_WORD_LENGTH 20

//==================================================================================================================================================================

// void* operator new (std::size_t count)
// {
//     auto ptr = malloc (count);
//
//     TracyAlloc (ptr , count);
//     return ptr;
// }
//
// void operator delete (void* ptr) noexcept
// {
//     TracyFree (ptr);
//
//     free (ptr);
// }

//==================================================================================================================================================================

int my_strcmp (const char* str1, const char* str2);

//==================================================================================================================================================================

size_t rol (size_t a, size_t n);

size_t ror (size_t a, size_t n);

//==================================================================================================================================================================

size_t h_constant (char* Key);

size_t h_first_ascii (char* Key);

size_t h_length (char* Key);

size_t h_sum_ascii (char* Key);

size_t h_rol (char* Key);

size_t h_ror (char* Key);

size_t h_crc32 (char* Key);

//==================================================================================================================================================================

int count_symbols_in_file (FILE* stream);

char* read_data_from_file (const char* Filename);

//==================================================================================================================================================================

template <typename TValue>
class CHashTable
{
    public:
        size_t  size;
        CList <CBucket <TValue>>**   Table;
        size_t (*current_h_function) (char* Key);

        CHashTable (size_t Size, size_t (*user_function) (char*) = h_ror): current_h_function(user_function)
        {
            ZoneScoped;

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
            ZoneScoped;

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
            ZoneScoped;

            MLA (Table != nullptr);
            MLA (Key != nullptr);


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

        TValue get_by_key (char* Key)
        {
            ZoneScoped;

            size_t index = key_to_index (Key);

            SNode<CBucket<TValue>>* Node = Table[index]->head;

            while (my_strcmp (Key, Node->data.key) != 0)
            {
                MLA(Node->next != nullptr);

                Node = Node->next;
            }

            return Node->data.value;
        }

        size_t key_to_index (char* Key)
        {
            ZoneScoped;

            size_t hash = current_h_function (Key);

            return hash % size;
        }

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

        void print_table ()
        {
            ZoneScoped;

            for (size_t cnt = 0; cnt < size; ++cnt)
            {
                if (Table[cnt] != nullptr)
                {
                    printf ("=%d=\n", cnt);
                    Table[cnt]->print_list();
                }
            }

            return;
        }

        void print_collision_lengths ()
        {
            ZoneScoped;

            for (size_t cnt = 0; cnt < size; ++cnt)
            {
                if (Table[cnt] != nullptr)
                {
                    printf ("|%3d| SIZE: %d\n", cnt, Table[cnt]->size);

                }
            }

            return;
        }

        void print_data_csv (FILE* OutputFile)
        {
            ZoneScoped;

            for (size_t cnt = 0; cnt < size; ++cnt)
            {
                if (Table[cnt] == nullptr)
                {
                    fprintf (OutputFile, "%d\n", 0);
                }
                else
                {
                    fprintf (OutputFile, "%d\n", Table[cnt]->size);
                }
            }

            return;
        }
};

//==================================================================================================================================================================

template <typename TValue>
void load_in_HT_data_by_words (CHashTable<TValue>* HashTable, char* Data)
{
    ZoneScoped;

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
