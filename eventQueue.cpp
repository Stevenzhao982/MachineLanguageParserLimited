#include <iostream>
#include "eventQueue.h"
using namespace std;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Node
{
  const Event* eventPointer;
  Node* next;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// we want to remove from the front and can only put to the end of the list 
struct Node* head = NULL; // pointer to a Node struct to hold where our beginning of the linked list is
struct Node* tail = NULL;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int nodesAdded = 0; // counter for our number of nodes added;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Enqueue event e
// Return true if sucessful and false otherwise
// add based on order of  time (head should have the event that has the lowest time and tail should have the event that has the highest time)
bool enqueue(const Event* e)
{

    Node* currentNode = new Node; // create our new node
  


    currentNode->eventPointer = e;  // essentially assign data to our current node
    currentNode->next = NULL;       // will keep track of our current node
    Node* previousNode = NULL;      // will keep track of our previous node 

 
    if ((currentNode->eventPointer)->time < 0) // error if we have a negative time
    {
      cerr << "Error : incorrect time." << endl;
      return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  	////////////////////////////////////////////////// If inserting first node //////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (head == NULL)
    {
        currentNode->next = head; 
        head = tail = currentNode; // head and tail, which are node pointers, now point to currentNode, so their * value is that of the actual node Current node (so that *head.next and *tail.next would be equal 
       
        nodesAdded++;
        return true;
    }
	  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////// If not inserting the very first node /////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	  else 
    {

      
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (nodesAdded == 1)
      {
        if ((currentNode->eventPointer)->time < (head->eventPointer)->time)
        {
          currentNode->next = head;
          head = currentNode;
          nodesAdded++;
          return true;
        }

        else 
        {
          head->next = currentNode;
          tail = currentNode;
          currentNode->next = NULL;
          nodesAdded++;
          return true;
        }
      }
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


      
      ////////////////////////////////////////////////////////// If our current nodes time is less than the heads time  ///////////////////////////////////////////////////////////////////////////=

      else if ((currentNode->eventPointer)->time < (head->eventPointer)->time) // if whats inputted has a time less than our head -> our shit is added as the new head and head is shifted down
      {
          
          currentNode->next = head; // Since our currentNode is first, we want to have *currentNode.next point to head, which is equal to the address of our preivously assigned node struct
          head = currentNode; // now we want our head to be equivalent to the address of our current node structure (also known as currentNode).
                              // This means head now points to our new node which should indeed be the head, and our new heads.next points to the address of the node that was previously the head.
          nodesAdded++;
          return true;
      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



      /////////////////////////////////////////////////////// If our current nodes time is greater than the heads time ///////////////////////////////////////////////////////////////////

      else
      {
        Node* tempNodePointer = (head->next); // since we know our current pointers time is now by this else statement greater than the heads time, we set the temp pointer equal to the node that comes after the head
                                              // and as we go through the while loop we make the temp pointer point to the next node then the next then the next while doing comparison operations, until we reach tail
                                              // Thanks to our previous if statement, our head->next will no longer be pointing to NULL but instead some other node.
        previousNode = head; // previous node is intially at NULL, so to start our while loop, we must start 
        
        while (((currentNode->eventPointer)->time >= (tempNodePointer->eventPointer)->time) && tempNodePointer != tail)
                                                                                      // this while loops operates to move our tempNodePointer along to the next node so long as our current nodes time is greater than
                                                                                      // that nodes time.
                                                                                      // When we reach the tail we want to exit the while loop too
        {
          previousNode = tempNodePointer; // have our previousnode move along in such a way that when we have to exit, the previousnode is one node behind our tempnodepointer
          tempNodePointer = tempNodePointer->next;
        }


       
        if (tempNodePointer == tail) // if we exited at the tail now we have to evaluate currentNode vs the tail
        {
          
          if ((currentNode->eventPointer)->time < (tail->eventPointer)->time) // if we must insert our current node before the tail
          {
            
            currentNode->next = tail;
            
            previousNode->next = currentNode;
            
            nodesAdded++;
            
            return true;
          }

          else if ((currentNode->eventPointer)->time >= (tail->eventPointer)->time) // if we must insert our currente node after the tail
          {
            
            previousNode->next = tail;
            tail->next = currentNode;
            currentNode->next = NULL;
            tail = currentNode;
            nodesAdded++;
            return true;
          }
        }

        else // If we didn't exit on the tail, but some other node that has an evenet that in turn has a time greater than our nodes events time, we must add our current node right before tempnodepointer's node
        {
          
          currentNode->next =  previousNode->next;
          previousNode->next = currentNode;
          nodesAdded++;
          return true;
        }



      }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
    
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






// Dequeue
// Return the next event on the queue (which is what's being dequeued), ordered by time
// Return 0 if queue is empty
const Event* dequeue()
{
  Event* dequeuedEvent = new Event;
  Node* tempNodePointer = head;
  if (head == NULL)
  { 
    return NULL;
  }
  else
  {
    dequeuedEvent-> time =  head-> eventPointer->time;
    dequeuedEvent-> type =  head-> eventPointer->type;
    head = tempNodePointer->next; // now move down our head to the node that comes after what was originally head / unlink the current head and return it by dequeueEvent
    return dequeuedEvent;
  }

}