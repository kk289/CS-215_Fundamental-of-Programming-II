// File: Homework Problem 9
// Date Assigned: March 19, 2018
// Date Completed: March 26, 2018
// Name: Kevil khadka

#include "list.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include <stdexcept>

using namespace std;

struct Node                    
{                              
   T data;          // the data
   Node* rlink;     // pointer to next (forward, right) node
   Node* llink;     // pointer to previous (backward, left) node
   // Constructor
   Node (const T & item = T())
     :data(item), llink(nullptr), rlink(nullptr) {}
};

int main()
{  
  return 0; 
}

// is_ascending function: 
// This function will return true if list is in ascending order,
// otherwise it return false
bool is_ascending(struct Node* head)
{
  Node *ptr = head;
  while(ptr->rlink != NULL)
  {
    if(ptr->data > ptr->rlink->data)
    {
      return false; //list is not in ascending order
    }
    ptr = ptr->rlink;
  }
  return true;
}

// remove_duplicates function :
// This function will remove the duplicate item (if any) from the list.
void remove_duplicates(struct Node *head)
{
  struct Node *base, *compared; 
  base = head;
  while(base->rlink != NULL) 
  {
    compared = base->rlink;
    
    // Check the rest of the nodes
    while(compared->rlink != NULL)
    {
      if(base->data == compared->data)
      {
	// remove node
	if(compared->rlink == NULL)
	{
	  compared->llink->rlink == NULL;
	  free(compared);
	}
	else
	{
	  compared->llink->rlink = compared->rlink;
	  free(compared);
	}	
      }
      compared = compared->rlink; 
    }
    base = base->rlink;
  } 
}

// split_list function: 
//   This function will divide list in two new list such that one new
//   list will contain the value lesser than the passed value and second
//   new list will contain greater or equal value of passed value.
//   The source list will not be modified.

void split_list(struct Node *head,
		int target_val,
		struct Node *head1,
		struct Node *head2)
{
  struct Node *ptr, *ptr1, *ptr2;
  
  ptr = head; // pointer of source list initializing
              // with the head of source list.
  
  ptr1 = head1; // pointer of first newly list initializing
                // with the head of first list.
  
  ptr2 = head2; // pointer of second newly list initializing
                // with the head of second list.
  while(ptr != NULL)
  {  
    /*
      If source list value is lesser than the passed value, 
      it will be added in the first newly list
    */
    if(ptr->data < target_val)
    {  
      /*
	If node is the first node of this new list
      */
      if(ptr1 == NULL)
      {	
	ptr1 = ptr;
	ptr1->rlink = NULL;
	ptr1->llink = head1;
	/*
	  Otherwise all other node will be added as the last nodeof this list
	*/
      }
      else
      {
	while(ptr1 != NULL)
	{  
	  ptr1 = ptr1->rlink; 
	}
	ptr1 = ptr;
	ptr1->rlink = NULL;
      }
      /*If source list value is greater than the passed value, 
        it will be added in the second newly list
      */
    }
    else
    {  
      /*If node is the first node of this new list*/
       if(ptr2 == NULL)
       {
	 ptr2 = ptr;
	 ptr2->rlink = NULL;
         ptr2->llink = head2;
	 /*
	   Otherwise all other node will be added as 
	   the last nodeof this list */
       }
       else
       {
	 while(ptr2 != NULL)
	 {
	   ptr2 = ptr2->rlink; 
         }
	 ptr2 = ptr;
	 ptr2->rlink = NULL;
       }
    }
    ptr = ptr->rlink; 
  }  
}
