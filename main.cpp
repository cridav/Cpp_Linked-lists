#include <iostream>
#include <assert.h>
using namespace std;

//Abstract class
template <typename Key,typename info>
class sequence
{
private:
    struct Node
    {
        Key _key;
        info _info;
        Node *link;
    };
    int n;//Counter of added elements
public:
    Node *head=NULL, *tail, *p, *q, *newNode, *current, *ptrSE1, *ptrSE2;//current for print
    sequence();//constructor
    void insertFirst(const info& newItem, const Key& newKey);//Insert in the first position of the list
    void insertLast(const info& newItem, const Key& newKey);//Insert after the last element
    void insertPos(const info& newItem, const Key& newKey, int pos);//Insert in specific position
    bool removeNode(const Key& key);//Remove the first node with the given key
    bool removeNode(const Key& key, int numit);//Remove the 'n' node with the key
    bool iskey(const Key& key);//True if there is the specified key
    info headItem();
    info tailItem();
    int getposKey(const Key& key);//Get position of the key in the list, first position = 0, if non-existent retrieves n (out of the list)
    void copyList(const sequence<Key,info>& original);
    //void swapItem(const Key& key1, const Key& key2)
    int length();//Length of the list
    void print();//Display list's elements
    void destroyList();
    Node* createNode()
    {
        Node newNode = new Node;
        return newNode;
    }
};

// -------------------- Shuffle function for creating new vector according to specifications --------------------
template <typename Key, typename info>
sequence <Key, info> shuffle(const sequence<Key,info>& S1, int start1, int length1, const sequence<Key,info>& S2, int start2, int length2, int times);

int main()
{
    sequence <char,int> S1;//

    S1.insertLast(1,'a');//Insert elements to the new created list
    S1.insertLast(3,'b');
    S1.insertLast(5,'c');
    S1.insertLast(7,'d');
    S1.insertLast(9,'e');
    S1.insertLast(5,'z');
    S1.insertLast(7,'d');
    S1.insertLast(9,'e');
    S1.insertLast(5,'c');

    sequence <char,int> S2;
    S2.insertLast(2,'f');
    S2.insertLast(4,'g');
    S2.insertLast(6,'h');
    S2.insertLast(8,'i');
    S2.insertLast(1,'j');
    S2.insertLast(6,'h');
    S2.insertLast(8,'i');
    S2.insertLast(7,'j');
    S2.insertPos(5,'r',7);
    S2.insertPos(3,'r',2);

    cout<<"\nList S1: ";
    S1.print();
    cout<<""<<S1.length()<<" elements"<<endl;

    cout<<"Position of Key 'z' in S1: "<<S1.getposKey('z')<<endl;

    cout<<"\nList S2: ";
    S2.print();
    cout<<""<<S2.length()<<" elements"<<endl;

    sequence <char,int> S3;
    cout<<"\nHead of S3: "<<S3.headItem();
    cout<<"\n";
    S3 = shuffle(S1,0,2,S2,0,2,1);
    cout<<"\nList S3: ";
    S3.print();
    cout<<""<<S3.length()<<" elements"<<endl;

    cout<<"\nRemoving the node 'c' from S1 with removeNode function"<<endl;
    S1.removeNode('c');
    S1.print();

    cout<<"\nS3 list:"<<endl;
    S3.print();
    cout<<"\nRemoving the second node 'j' from S3 with removeNode function"<<endl;
    S3.removeNode('j',2);//Remove the second node with key = 'j'
    cout<<"\nNew S3:\n";
    S3.print();

    cout<<"\nHead of S3: "<<S3.headItem();
    cout<<"\nTail of S3: "<<S3.tailItem();
    cout<<"\n\nS1:"<<endl;
    S1.print();

    cout<<"\nDoes 'a' exists in S1?: "<<S1.iskey('a');
    cout<<"\nDoes '1' exists in S1?: "<<S1.iskey('1');

    //Copy S3 intro S4
    sequence <char,int> S4;
    S4.copyList(S3);
    cout<<"\n\nS4.copyList(S3)"<<endl;
    S4.print();
    cout<<"\nDestroy S4"<<endl;

    S4.destroyList();
    cout<<"\nS4: ";
    S4.print();
    cout<<"\nLength of S4: "<<S4.length()<<endl;

    cout<<"\n";
    cout<<"\nS1: ";
    S1.print();
    cout<<"\nS3: ";
    S3.print();
    S4 = shuffle(S1,3,2,S3,0,1,6);
    cout<<"\nList S4: ";
    S4.print();
    cout<<""<<S4.length()<<" elements"<<endl;

    return 0;
}

//Defined class

//-------------------- sequence --------------------
template <typename Key, typename info>
//Constructor
sequence<Key,info>::sequence()
{
    head=NULL;
    tail=NULL;
    n=0;//Reset counter of elements
}
//-------------------- insertFirst --------------------
template <typename Key, typename info>
void sequence<Key,info>::insertFirst(const info& newItem, const Key& newKey)
{
    //Insert elements in the first position of the list
    Node *newNode = new Node;//Create new node
    newNode->_info = newItem;//Set new value
    newNode->_key = newKey; //Set new Key
    newNode->link = head;//set new address
    head = newNode;//Update the address of the head of the list
    n++;
    if (tail==NULL) //If the list was empty, the new node is also the last one
    {
        tail=newNode;//The new node is also the tail (the last one)
    }
}

//-------------------- insertLast --------------------
template <typename Key, typename info>
void sequence<Key,info>::insertLast(const info& newItem, const Key& newKey)
{
    //Insert the next element to the last position (after the last entered element)
    Node *newNode = new Node;//Pointer and create new node
    newNode->_info = newItem;//Assign first value to the node
    newNode->_key = newKey; //Set new Key
    newNode->link = NULL;//Set the link as NULL

    if (head==NULL) //IF the list is empty, the new node is the first and only
    {
        head = newNode;
        tail = newNode;
        n++;
        //cout<<newItem<<" correctly added in "<<&newItem<<"\n";
    }
    else  //If there are already elements, insert new node after the last one
    {
        tail->link = newNode; //Insert new node after last
        tail = newNode; //Point to the actual and last element in the list
        n++;
        //cout<<newItem<<" correctly added in "<<&newItem<<"\n";
    }
}

// -------------------- insertPos ---------------
template <typename Key, typename info>
void sequence<Key,info>::insertPos(const info& newItem, const Key& newKey, int pos) //insert node in position "pos"
{
//Neither head nor tail are modified because they conserve the same address, new pointer is used
    if (pos <0 || pos>=(n)) //Validate input data
    {
        cout<<"\nInvalid position for the item: "<<newItem<<", key: "<<newKey<<"\nPosition must be between 0 and "<<this->length()-1<<endl;

    }
    else{
    if (pos == 0)
    {
        insertFirst(newItem,newKey);

    }
    else if ((pos == (n-1)))
    {
        insertLast(newItem,newKey);
    }
    else //Neither head nor tail are modified because they conserve the same address, new pointer is used
    {
        Node *newNode = new Node;//Create new node
        current = head;//Copy the beginning of the list, does not modify head's address
        for (int i=0; i<pos; i++)
        {
            p = current;//Previous = current (for keeping information about the node for giving its new link)
            current = current->link; //Jump to the next node
        }
        newNode->_info=newItem;//Assign data to the new node
        newNode->_key = newKey; //Set new Key
        p->link=newNode;//Assign new link address of the new node
        newNode->link=current;//Assign link to the current node in the for cycle
        n++;//count new item
    }
    }

}

//-------------------- removeNode --------------------
template <typename Key, typename info>
bool sequence<Key,info>::removeNode(const Key& key)
{
    Node *curr;//Pointer to the current node
    Node *last;//Pointer to the last node
    bool found;
    if (head == NULL) //List is empty, cannot delete any node
    {
        cout<<"\non-existent node\n";
        return false;
    }
    else
    {
        if (head->_info == key) //In case the node to remove is the first one (head)
        {
            curr=head;
            head = head->link;
            n--;//decrease number of elements in the list
            if(head==NULL) //In case the list has one node only
            {
                tail=NULL;
            }
            delete curr;
        }
        else //Look for the node with the given Key
        {
            found=false;
            last = head;//Maintain information about the previous node
            curr=head->link;//Jump to the next node
            while (curr != NULL && !found) //Loop until found or end of the list
            {
                if (curr->_key != key) //If not fund, jump to the next node
                {
                    last=curr;
                    curr=curr->link;
                }
                else
                {
                    found=true;
                }
            }//end While loop
            if (found) //When found, delete it
            {
                last->link=curr->link;//Set address of the next node to the previous one, skipping the current node
                n--;//Decrease counter of nodes in the list
                if (tail==curr) //Node to delete is the tail of the list
                {
                    tail=last;//Update the new value for the tail of the list
                }
                delete curr;
            }
            else
            {
                cout<<"\nKey does not match to an existent element in the list"<<endl;
            }
        }
    }
    return true;
}

//-------------------- removeNode --------------------
template <typename Key, typename info>
bool sequence<Key,info>::removeNode(const Key& key, int numit)
{
    Node *curr;//Pointer to the current node
    Node *last;//Pointer to the last node
    bool found;
    int control=1;//Control for the position of the node to delete
    if (head == NULL) //List is empty, cannot delete any node
    {
        cout<<"\non-existent node\n";
        return false;
    }
    else
    {
        if (head->_info == key) //In case the node to remove is the first one (head)
        {
            if (numit==1) //if it is desired to delete the first node and it is in the head
            {
                curr=head;
                head = head->link;
                n--;//decrease number of elements in the list
                if(head==NULL) //In case the list has one node only
                {
                    tail=NULL;
                }
                delete curr;
            }
            else
            {
                control++;//increase for the next node with the same key
            }
        }
        else //Look for the node with the given Key
        {
            found=false;
            last = head;//Maintain information about the previous node
            curr=head->link;//Jump to the next node
            while (curr != NULL && !found) //Loop until found or end of the list
            {
                if (curr->_key != key) //If not found, jump to the next node
                {
                    //cout<<"Key: "<<curr->_key<<endl;
                    last=curr;
                    curr=curr->link;
                }
                else
                {
                    //cout<<"Control: "<<control<<" numit: "<<numit<<endl;
                    if (control == numit)
                    {
                        found=true;
                    }
                    else
                    {
                        control++;//increase until fulfil condition
                        last=curr;
                        curr=curr->link;
                    }

                }
            }//end While loop
            if (found) //When found, delete it
            {
                last->link=curr->link;//Set address of the next node to the previous one, skipping the current node
                n--;//Decrease counter of nodes in the list
                if (tail==curr) //Node to delete is the tail of the list
                {
                    tail=last;//Update the new value for the tail of the list
                }
                delete curr;
            }
            else
            {
                cout<<"\nKey does not match to an existent element in the list"<<endl;
            }
        }
    }
    return true;
}

//-------------------- isKey --------------------
template <typename Key, typename info>
bool sequence<Key,info>::iskey(const Key& key) //True if there is the specified key
{
    Node *curr;//Pointer
    bool found=false;
    curr = head;//current point is equal to the head of the list
    while(curr != NULL && !found) //Loop, look for key
    {
        if (curr->_key == key)
            found = true;
        else
            curr = curr->link;//If not found, jump to the next node
    }
    return found;
}

//-------------------- headItem --------------------
template <typename Key, typename info>
info sequence<Key,info>::headItem()
{

    if (head != NULL)
    {
        return head->_info;//return value of head
    }
    else
    {
        return NULL;
    }
}

//-------------------- tailItem --------------------
template <typename Key, typename info>
info sequence<Key,info>::tailItem()
{
    if (tail != NULL)
    {
        return tail->_info;//Return value of tail
    }
    else
    {
        return NULL;
    }
}

//-------------------- getposKey --------------------
template <typename Key, typename info>
int sequence<Key,info>::getposKey(const Key& key) //Get position of the key in the list, first position = 0
{
    Node *curr;//Pointer
    bool found=false;
    curr = head;//current point is equal to the head of the list
    int i=0;//set counter to the first node
    while(curr != NULL && !found) //Loop, look for key
    {
        if (curr->_key == key)
            found = true;
        else
        {
            curr = curr->link;//If not found, jump to the next node
            i++;//increment position to the next node
        }
    }
    if (found == true)
    {
        return i;
    }
    else
    {
        return n;//if not, retrieves an integer out of the boundaries of the list (non-existent)
    }
}

//-------------------- print --------------------
template <typename Key, typename info>
void sequence<Key,info>::print() //Print the list
{
    current = head;//Set current to the first node (list copied, so that list won't be lost)
    cout << "\n";

    while(current != NULL) //will print until the end of the list (current==NULL)
    {
        cout << current->_info << "  ";//Display information of the list
        current=current->link;//Go to the next position
    }
    current = head;//Set current to the first node (list copied, so that list won't be lost)
    cout << "\n";
    while(current != NULL) //will print until the end of the list (current==NULL)
    {
        cout << current->_key<< "  ";//Display information of the list
        current=current->link;//Go to the next position
    }
    cout <<"\n";
}
// -------------------- length ------------------
template <typename Key, typename info>
int sequence<Key,info>::length()
{
    return n;//Length of the list
}
// -------------------- destroyList ------------------
template <typename Key, typename info>
void sequence<Key,info>::destroyList()
{
    Node *temp; //Temporal pointer for deallocating memory
    while (head != NULL)
    {
        temp = head; //Load temp with head's value
        head = head->link; //Go to the next node
        delete temp; //delete memory used by temp
        n=0;//Set length of list equal to 0
    }
}
/*sequence(sequence&)
operator=
s1.copyList(s1);*/ //CHEACK THIS, FOR THE COPY LIST FUNCTION
template <typename Key, typename info>
void sequence<Key,info>::copyList(const sequence<Key,info>& original) //Copies the original list into a second list
{
    Node *newNode;//Pointer for a new node
    Node *curr;//Actual element of the list to copy

    if (head != NULL)
    {
        //Clear the list if it's not clear
        destroyList();
    }
    if(original.head == NULL) //If the original list is empty, set the second list as empty
    {
        head = NULL;
        tail = NULL;
        n=0;
    }
    else
    {
        curr = original.head; //Copy value of the head
        n = original.n; //Copy the length

        //Copy the nodes
        head = new Node;
        head->_info = curr->_info;
        head->_key = curr->_key;
        head->link = NULL;
        tail = head; //Make last point to the first node
        curr = curr->link;//jump to the next node

        while (curr != NULL)
        {
            newNode = new Node;//create node
            newNode->_info = curr->_info;//Copy info
            newNode->_key = curr->_key;
            newNode->link = NULL;
            tail->link=newNode;//link newnode after tail
            tail = newNode; //update tail of list
            curr = curr->link;//Go to next node
        }
    }
}

// -|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-| END OF THE CLASS "sequence" -|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|

// -------------------- Shuffle function for creating new vector according to specifications --------------------
template <typename Key, typename info>
sequence <Key, info> shuffle(const sequence<Key,info>& S1, int start1, int length1, const sequence<Key,info>& S2, int start2, int length2, int times)
{
    cout<<"\nInserted function: Shuffle(S1, "<<start1<<", "<<length1<<", S2, "<<start2<<", "<<length2<<", "<<times<<")\n";
    sequence <Key,info> SE;//For creating the new list

    //S1.head = nullptr;
    SE.ptrSE1=S1.head;
    //cout << "\nS1 head: "<<S1.head <<endl;
    SE.ptrSE2=S2.head;
    //cout << "\nS2 head: "<<S2.head <<endl;


    for (int i=0; i<start1; i++) //Look for starting point in list SE
    {
        //cout<<"SE link: "<<SE.ptrSE1->_info<<" S1 link: "<<S1.head->_info<<endl;//Control of data and address for SE
        SE.ptrSE1=SE.ptrSE1->link; //Indicate the starting point "start1"
        if (SE.ptrSE1->link==NULL){
            cout<<"\nOut of boundaries of S1";
            SE.ptrSE1=NULL;
            break;
        }
    }
    for (int i=0; i<start2; i++) //Look for starting point in list SE
    {
        //cout<<"SE link: "<<SE.ptrSE2->_info<<" S2 link: "<<S2.head->_info<<endl;//Control of data and address for SE
        SE.ptrSE2=SE.ptrSE2->link; //Indicate the starting point "start1"
        if (SE.ptrSE2->link==NULL){
            cout<<"\nOut of boundaries of S2";
            SE.ptrSE2=NULL;
            break;
        }
    }



    for (int j=0; j<times; j++) //Repeat the process "times" times
    {

        //do //Repeate the cycle with the specified length until the tail of each list
        bool a=true;
        bool b=true;
        //while (a||b)
        {
            //cout<<"head of SE1: "<<SE.ptrSE1->_info<<" head of SE2: "<<SE.ptrSE2->_info<<endl;//Control of heads for SE
            //cout<<"head of SE1: "<<SE.ptrSE1<<" head of S1: "<<S1.head<<endl;//Control of heads for SE
            //cout<<"Tail of SE1: "<<S1.tail->_info<<" Tail of SE2: "<<S2.tail->_info<<endl;//Control of heads for SE
            //Create SE list with the selected length 1 & 2
            for(int i=0; i<length1; i++)
            {
                if (SE.ptrSE1 != NULL) //Validate that the pointer is not NULL, if it is, add items until valid
                {
                    SE.insertLast(SE.ptrSE1->_info, SE.ptrSE1->_key);//Create list with values from S1
                    SE.ptrSE1=SE.ptrSE1->link;//Go to next node
                }
                else
                {
                    i=length1;   //Finish the loop if the list ran out of elements
                    a=false;
                }
            }
            for(int i=0; i<length2; i++)
            {
                if (SE.ptrSE2 != NULL) //validation of data from S2 to SE
                {
                    SE.insertLast(SE.ptrSE2->_info,SE.ptrSE2->_key);//Create list with values from S2
                    SE.ptrSE2=SE.ptrSE2->link;//go to next node
                }
                else
                {
                    i=length2;   //Finish the loop if the list ran out of elements
                    b=false;
                }
            }
            //cout<<"\nptrSE1: "<<SE.ptrSE1<<" ptrSE2: "<<SE.ptrSE2<<endl;
        }//Condition for finishing the cycle: reach the tail of both lists S1 and S2
        //cout<<"\nSE list: ";
        //SE.print();
        //Repeat the list "times" times
        //cout<<"Head of SE is: "<<SE.head<<" and its value is: "<<SE.head->_info<<" and tail is: "<<SE.tail->_info<<endl;//Validate head of SE
    }
    return SE;
}

