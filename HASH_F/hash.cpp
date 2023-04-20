//==================================================================================================================================================================
//20.04.2023
//==================================================================================================================================================================

#include "hash.h"

//==================================================================================================================================================================

int count_symbols_in_file (FILE* stream)
{
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

template <typename TValue>
void load_in_HT_data_by_words (CHashTable<TValue>* HashTable, char* Data)
{

    return;
}

//==================================================================================================================================================================
