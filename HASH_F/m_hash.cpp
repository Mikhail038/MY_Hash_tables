//==================================================================================================================================================================
//17.04.2023
//==================================================================================================================================================================

#include "Tracy.hpp"

#include <stdio.h>

#include "stackT.h"
#include "simpleListT.h"

#include "hash.h"

#include <chrono>

//==================================================================================================================================================================

int main ()
{
    char* Data = read_data_from_file ("DATA/words.txt");

    CHashTable<int> HashTable (5000, h_ror);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    load_in_HT_data_by_words (&HashTable, Data);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printf ("Time spend: %d microseconds\n",std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());

    //HashTable.print_collision_lengths ();

    FILE* OutputFile = fopen ("DATA/HashTestData.csv","w");

    HashTable.print_data_csv (OutputFile);

    fclose (OutputFile);

    //HashTable.print_table ();

    free (Data);

    return 0;
}

//==================================================================================================================================================================

