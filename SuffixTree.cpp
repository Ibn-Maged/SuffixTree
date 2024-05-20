#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

class LinkedList;

struct SuffixTreeNode
{
    int suffixID;
    int startIndex;
    LinkedList* children;
};

struct LinkedListNode
{
    LinkedListNode* next;
    SuffixTreeNode key;
    LinkedListNode(SuffixTreeNode key)
    {
        next = nullptr;
        this->key=key;
    }
    LinkedListNode()
    {
        next = nullptr;
    }
};

class LinkedList
{
    LinkedListNode* head = new LinkedListNode();
public:
    void insert(LinkedListNode* node)
    {
        LinkedListNode* current = head;
        node->next = nullptr;
        while(current->next != nullptr)
        {
            current = current->next;
        }
        current->next = node;
        current = nullptr;
        delete current;
    }
    bool isEmpty()
    {
        return head->next == nullptr;
    }
    // returns the first element in the linked list
    LinkedListNode* getHead()
    {
        return head->next;
    }
    // returns the minimum start index in the linked list
    int getMinIndex()
    {
        if(isEmpty())
        {
            return -1;
        }
        else
        {
            LinkedListNode* current = head->next;
            int min=INT_MAX;
            while(current!= nullptr)
            {
                if(current->key.startIndex<min)
                {
                    min=current->key.startIndex;
                }
                current = current->next;
            }
            return min;
        }
    }
};

class SuffixTree
{
    char* str;
public:
    SuffixTreeNode* root = new SuffixTreeNode;
    SuffixTree(char str[])
    {
        // creating the root node
        SuffixTreeNode* node;
        root->startIndex = -1;
        root->suffixID = -1;
        root->children = new LinkedList;
        this->str = str;
        // insert all the suffixes in the tree starting from suffix 0 to suffix n - 1
        for(int i = 0; i < strlen(str); i++)
        {
            // create a node for each suffix
            node = new SuffixTreeNode();
            node->startIndex = i;
            node->suffixID=i;
            node->children=new LinkedList;
            insert(root,node);
        }
    }
    // recursive function to insert each suffix in the tree
    // currentNode is the node we are currently checking to insert in
    // newSuffix is the node to be inserted
    void insert(SuffixTreeNode* currentNode, SuffixTreeNode* newSuffix)
    {
        // if the currentNode does not have any child we just insert the newSuffix
        if(currentNode->children->isEmpty())
        {
            currentNode->children->insert(new LinkedListNode(*newSuffix));
        }
        else
        {
            LinkedListNode* currentChild = currentNode->children->getHead();
            // iterating over all the children in the currentNode
            while(currentChild != nullptr)
            {
                // check if the first character in the currentChild equals the first in the newSuffix
                if(isEqual(currentChild->key.startIndex, newSuffix->startIndex))
                {
                    // get the minimum index in currentChild's Linked list to get the substring on this node
                    int minIndex=currentChild->key.children->getMinIndex();
                    // if minIndex equals -1 then this substring goes until the end of the original string
                    if(minIndex==-1)
                    {
                        minIndex= strlen(str) ;
                    }
                    int i = currentChild->key.startIndex;
                    int j = newSuffix->startIndex;
                    // iterate over the substring to check
                    // if the currentChild is fully equal till minIndex to the newSuffix or partially equal
                    while(i < minIndex)
                    {
                        // if not fully equal we call function split
                        if(!isEqual(i,j))
                        {
                            newSuffix->startIndex=j;
                            split(currentChild,new LinkedListNode(*newSuffix),i);
                            return;
                        }
                        else
                        {
                            // increment the start index of the newSuffix if the current characters are equal
                            newSuffix->startIndex++;
                        }
                        i++;
                        j++;
                    }
                    // currentChild is fully equal newSuffix till minIndex
                    // call insert recursively on the currentChild to check his children
                    insert(&currentChild->key,newSuffix);
                    return;
                }
                else
                {
                    currentChild = currentChild->next;
                }
            }
            // the new suffix starts with a new distinct character
            // insert it as a child to the currentNode
            currentNode->children->insert(new LinkedListNode(*newSuffix));
        }
    }
    void split(LinkedListNode* current, LinkedListNode* newNode ,int subNodeStartIndex)
    {
        // create a new node to contain the rest of the string
        SuffixTreeNode currentSub = SuffixTreeNode();
        // move the children of the parent node to the subNode
        currentSub.children = current->key.children;
        // currentSub's start index is the index where we called split
        currentSub.startIndex = subNodeStartIndex;
        // check if currentSub is internal node or not
        if(currentSub.children->isEmpty())
        {
            currentSub.suffixID=current->key.suffixID;
        }
        else
        {
            currentSub.suffixID = -1;
        }
        //make the current child internal node
        current->key.suffixID=-1;
        //put the two node currentSub and new suffix in children of current child
        current->key.children= new LinkedList();
        current->key.children->insert(newNode);
        current->key.children->insert(new LinkedListNode(currentSub));

    }
    bool isEqual(int index1,int index2)
    {
        return str[index1] == str[index2];
    }

    void dfs(SuffixTreeNode* node)
    {
        if(node->suffixID > -1)
        {
            cout<< node->suffixID <<" ";
        }
        if(node->children->isEmpty())
        {
            return;
        }
        else
        {
            LinkedListNode* current= node->children->getHead();
            while(current != nullptr)
            {
                dfs(&current->key);
                current=current->next;
            }
        }
    }
    void search(char subString[])
    {
        LinkedListNode* currentChild = root->children->getHead();
        //currentIndex visited indices in substring
        int currentIndex=0;
        //iterate over children starting from root
        while(currentChild!= nullptr)
        {
            //check first char of current child with last visited index in substring
            if(str[currentChild->key.startIndex] == subString[currentIndex])
            {
                // get the minimum index in currentChild's Linked list to get the substring on this node
                int minIndex = currentChild->key.children->getMinIndex();
                // if minIndex equals -1 then this substring goes until the end of the original string
                if(minIndex==-1)
                {
                    minIndex= strlen(str) ;
                }
                // iterate over the substring to check
                // if the currentChild is fully equal till minIndex to the newSuffix or partially equal
                for(int i = currentChild->key.startIndex; i < minIndex;i++)
                {
                    // if reached end of substring break
                    if(currentIndex == strlen(subString)) break;
                    // if not fully equal till minIndex then not found
                    if(str[i]!= subString[currentIndex])
                    {
                        cout<<"Not Found"<<endl;
                        return;
                    }
                    currentIndex++;
                }
                //if reached end of substring the result will be the subtree of current node
                if(currentIndex == strlen(subString))
                {
                    dfs(&currentChild->key);
                    cout << '\n';
                    return;
                }
                else
                {
                    //substring fully equal till minIndex but still did not reach its end so result maybe in children of currentChild
                    currentChild=currentChild->key.children->getHead();
                }
            }
            else
            {
                currentChild = currentChild->next;
            }
        }
        //no children start with the char in substring in index currentIndex
        cout<<"Not Found\n";
    }
};
