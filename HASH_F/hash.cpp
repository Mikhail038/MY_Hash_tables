//==================================================================================================================================================================
//20.04.2023
//==================================================================================================================================================================

// #include "Tracy.hpp"

#include <immintrin.h>
#define ZoneScoped

#include "hash.h"

//==================================================================================================================================================================



//==================================================================================================================================================================

int count_symbols_in_file (FILE* stream)
{
    ZoneScoped;

    MCA (stream != NULL,  -1);

//     int counter = 0;
//     char symbol = '\0';
//
//     for (; symbol != EOF; counter++)
//     {
//         symbol = getc (stream);
//     }
//     // do
//     // {
//     //     symbol = getc (stream);
//     //     counter++;
//     // } while (symbol != EOF);
//     counter--;
//
//     return counter;

    fseek (stream, 0, SEEK_END);

    int AmntSymbols = ftell (stream);

    fseek (stream, 0, SEEK_SET);

    return AmntSymbols;
}

char* read_data_from_file (const char* Filename)
{
    ZoneScoped;

    FILE* DataFile = fopen (Filename, "r");
    MCA (DataFile != NULL, nullptr);

    int BufferSize = 1 + count_symbols_in_file (DataFile);
    MCA (BufferSize >= 0, nullptr);

    char* Buf = (char*) calloc (BufferSize, sizeof (char));
    MCA (Buf != NULL, nullptr);

    fread (Buf, sizeof (char), BufferSize, DataFile);
    Buf[BufferSize - 1] = '\0';

    return Buf;
}

//==================================================================================================================================================================

size_t h_constant (char* Key)
{
    ZoneScoped;

    MCA (Key != nullptr, 0);

    return (size_t) 1;
}

size_t h_first_ascii (char* Key)
{
    ZoneScoped;

    MCA (Key != nullptr, 0);

    return (size_t) Key[0];
}

size_t h_length (char* Key)
{
    ZoneScoped;

    MCA (Key != nullptr, 0);

    return strlen (Key);
}

size_t h_sum_ascii (char* Key)
{
    ZoneScoped;

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

size_t h_rol (char* Key)
{
    ZoneScoped;

    size_t ret_val = 0;

    size_t cnt = 0;
    while (Key[cnt] != '\0')
    {
        ret_val = ((ret_val << 1) | (ret_val >> 31)) ^ (unsigned int) Key[cnt];

        cnt++;
    }

    return ret_val;
}

size_t h_ror (char* Key)
{
    ZoneScoped;

    size_t ret_val = 0;

    size_t cnt = 0;
    while (Key[cnt] != '\0')
    {
        ret_val = ((ret_val >> 1) | (ret_val << 31)) ^ (unsigned int) Key[cnt];

        cnt++;
    }

    return ret_val;
}

//==================================================================================================================================================================

size_t rol (size_t a, size_t n)
{
    ZoneScoped;

    size_t t1, t2;

    n = n % (sizeof(a)*8);

    t1 = a << n;

    t2 = a >> (sizeof(a)*8 - n);


    return t1 | t2;
}

size_t ror (size_t a, size_t n)
{
    ZoneScoped;

    size_t t1, t2;

    n = n % (sizeof(a)*8);

    t1 = a >> n;

    t2 = a << (sizeof(a)*8 - n);

    return t1 | t2;
}

//==================================================================================================================================================================



// __m256i* pack_line_256 (char* Line)
// {
//
//     char packed_Line[SIMD_SIZE]{0};
//
//     for (int cnt = 0; (Line[cnt] != '\0') && (cnt != SIMD_SIZE - 1); ++cnt)
//     {
//         packed_Line[cnt] = Line[cnt];
//     }
//
//     return (__m256i*) &packed_Line;
// }

//==================================================================================================================================================================

template <typename TListData>
void CList<TListData>::print_elem (SNode<TListData>* Node)
{
    ZoneScoped;

    printf ("[%d]", Node->data);

    if (Node->next != nullptr)
    {
        printf ("->");
        print_elem (Node->next);
    }

    return;
}

template <>
void CList<CBucket<int>>::print_elem (SNode<CBucket<int>>* Node)
{
    ZoneScoped;

    printf ("[%s]", Node->data.key);

    if (Node->next != nullptr)
    {
        printf ("->");
        print_elem (Node->next);
    }

    return;
}

//==================================================================================================================================================================
