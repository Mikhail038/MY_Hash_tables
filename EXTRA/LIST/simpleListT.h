#pragma once

//===================================================================================================================================================================
//18.04.2023
//===================================================================================================================================================================

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
            head = nullptr;
            tail = nullptr;

            size = 0;

            return;
        }

        ~CList()
        {
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
            tail = tail->prev;

            delete tail->next;

            tail->next = nullptr;

            size--;
        }

        void print_elem (SNode<TListData>* Node)
        {
            printf ("[%d]", Node->data);

            if (Node->next != nullptr)
            {
                printf ("->");
                print_elem (Node->next);
            }

            return;
        }

        void print_list ()
        {
            printf ("size %d\n", size);
            print_elem (head);
            printf ("\n");

            return;
        }
};

template <>
class CList<CBucket<int>>
{
    public:
        int                 size;
        SNode<CBucket<int>>*   head;
        SNode<CBucket<int>>*   tail;

        CList()
        {
            head = nullptr;
            tail = nullptr;

            size = 0;

            return;
        }

        ~CList()
        {
            while (tail != nullptr)
            {
                SNode<CBucket<int>>*  old_tail_prev = tail->prev;

                delete tail;

                tail = old_tail_prev;
            }

            return;
        }

        void insert_tail (CBucket<int> Value)
        {
            if (tail == nullptr)
            {
                head = new SNode <CBucket<int>>;
                head->data = Value;

                head->next = nullptr;
                head->prev = nullptr;

                tail = head;

                size++;

                return;
            }

            tail->next = new SNode<CBucket<int>>;
            tail->next->data = Value;

            tail->next->prev = tail;
            tail->next->next = nullptr;

            tail = tail->next;
            size++;

            return;
        }

        void delete_tail ()
        {
            tail = tail->prev;

            delete tail->next;

            tail->next = nullptr;

            size--;
        }

        void print_elem (SNode<CBucket<int>>* Node)
        {
            printf ("[%s]", Node->data.key);

            if (Node->next != nullptr)
            {
                printf ("->");
                print_elem (Node->next);
            }

            return;
        }

        void print_list ()
        {
            printf ("size %d\n", size);
            print_elem (head);
            printf ("\n");

            return;
        }
};

//===================================================================================================================================================================
