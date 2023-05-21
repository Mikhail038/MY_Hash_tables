//==================================================================================================================================================================
//17.04.2023
//==================================================================================================================================================================

// #include "Tracy.hpp"
#include "colors.h"
#define ZoneScoped

#include <cstdlib>
#include <cstring>
#include <stdio.h>

#include "stackT.h"
#include "simpleListT.h"

#include "hash.h"

#include <chrono>


//==================================================================================================================================================================

int main ()
{
    ZoneScoped;

    char* Data = read_data_from_file ("DATA/words.txt");

    CHashTable<int> HashTable (4999, h_ror);

    load_in_HT_data_by_words (&HashTable, Data);

//     char* Name = (char*) calloc (20, sizeof (char));
//
//     Name = strcpy(Name, "man");

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    int buf = 0;
    for (int i = 0; i < 100000000; ++i)
    {
        buf = HashTable.get_by_key("man");
        //printf ("{%d}\n", HashTable.get_by_key("man"));
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    printf ( Kbright KYLW "Time spend: %d microseconds\n" KNRM ,std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());


    // free(Name);

    //HashTable.print_collision_lengths ();

    FILE* OutputFile = fopen ("DATA/HashTestData.csv","w");

    HashTable.print_data_csv (OutputFile);

    fclose (OutputFile);

    //HashTable.print_table ();

    free (Data);

    // FrameMark;

    return 0;
}

//==================================================================================================================================================================

