#pragma once

//===================================================================================================================================================================
//18.04.2023
//===================================================================================================================================================================

// #include "Tracy.hpp"

#include <stdlib.h>
#include "MYassert.h"

#include "bucket.h"

//===================================================================================================================================================================

template <typename TListData>
struct SNode
{
    TListData   data;
    SNode*      next;
    SNode*      prev;

    SNode ()
    {
        ZoneScoped;

        next = nullptr;
        prev = nullptr;
    }
};

template <typename TListData>
class CList
{
    public:
        int                 size;
        SNode<TListData>*   head;
        SNode<TListData>*   tail;

        CList()
        {
            ZoneScoped;

            head = nullptr;
            tail = nullptr;

            size = 0;

            return;
        }

        ~CList()
        {
            ZoneScoped;

            while (tail != nullptr)
            {
                SNode<TListData>*  old_tail_prev = tail->prev;

                delete tail;

                tail = old_tail_prev;
            }

            return;
        }

        void insert_tail (TListData value)
        {
            ZoneScoped;

            if (tail == nullptr)
            {
                head = new SNode<TListData>;
                head->data = value;

                head->next = nullptr;
                head->prev = nullptr;

                tail = head;

                size++;

                return;
            }

            tail->next = new SNode<TListData>;
            tail->next->data = value;

            tail->next->prev = tail;
            tail->next->next = nullptr;

            tail = tail->next;
            size++;

            return;
        }

        void delete_tail ()
        {
            ZoneScoped;

            tail = tail->prev;

            delete tail->next;

            tail->next = nullptr;

            size--;
        }

        void print_elem (SNode<TListData>* Node);

        void print_list ()
        {
            ZoneScoped;

            printf ("size %d\n", size);
            print_elem (head);
            printf ("\n");

            return;
        }
};

//===================================================================================================================================================================
