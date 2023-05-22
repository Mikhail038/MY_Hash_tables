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

size_t rol (size_t a, size_t n);

size_t ror (size_t a, size_t n);

//==================================================================================================================================================================

size_t h_constant (char* Key);

size_t h_first_ascii (char* Key);

size_t h_length (char* Key);

size_t h_sum_ascii (char* Key);

size_t h_rol (char* Key);

size_t h_ror (char* Key);

//==================================================================================================================================================================

inline const bool my_simd_cmp (const __m256i* FirstVector, const __m256i* SecondVector)
{
    return (_mm256_movemask_epi8(_mm256_cmpeq_epi64(*FirstVector, *SecondVector)) == (int) 0xFFFFFFFF);
}

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

        TValue new_get_by_key (char* Key)
        {
            size_t index = key_to_index (Key);

            char Key_packed[SIMD_SIZE] __attribute__ ((aligned (32))) {0};

            for (int cnt = 0; (Key[cnt] != '\0') && (cnt != SIMD_SIZE - 1); ++cnt)
            {
                Key_packed[cnt] = Key[cnt];
            }

            const __m256i Key_vector = _mm256_load_si256((const __m256i*) Key_packed);

            SNode<CBucket<TValue>>* Node = Table[index]->head;
            while (my_simd_cmp (&Key_vector, &Node->data.key) != 0)
            {
                MLA(Node->next != nullptr);

                Node = Node->next;
            }
            return Node->data.value;
        }

//         TValue get_by_key (char* Key)
//         {
//             ZoneScoped;
//
//             size_t index = key_to_index (Key);
//
//             SNode<CBucket<TValue>>* Node = Table[index]->head;
//
//             while (strcmp (Key, Node->data.key) != 0)
//             {
//                 MLA(Node->next != nullptr);
//
//                 Node = Node->next;
//             }
//
//             return Node->data.value;
//         }

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
