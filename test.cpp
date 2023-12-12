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
        //make the currrent child internal node
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
                    //substring fully equal till minIndex but still did not rach its end so result maybe in children of currentChild
                    currentChild=currentChild->key.children->getHead();
                }
            }
            else
            {
                currentChild = currentChild->next;
            }
        }
        //no children starts withe the char in substring in index currentIndex
        cout<<"Not Found\n";
    }
};

int main()
{
    //             0123456789012
    SuffixTree t1("bananabanaba$");

    t1.search("ana"); // Prints: 1 3 7
    t1.search("naba"); // Prints: 4 8
    t1.search("bananabanaba"); // Prints: 0
    t1.search("anx"); // Prints: Not Found

    cout << "=========================\n";
    //             01234567
    SuffixTree t2("AAAAAAA$");
    t2.search("A"); // Prints: 0 1 2 3 4 5 6
    t2.search("AA"); // Prints: 0 1 2 3 4 5
    t2.search("AAX"); // Prints: Not Found

    cout << "=========================\n";
    //             012345678901
    SuffixTree t3("MISSISSIPPI$");
    t3.search("SS"); // Prints: 2 5
    t3.search("S"); // Prints: 2 3 5 6
    t3.search("MISSISSIPPI"); // Prints: 0
    t3.search("SSISS"); // Prints: 2

    cout << "=========================\n";
    //             012345678901
    SuffixTree t4("ABRACADABRA$");
    t4.search("ABRA"); // Prints: 0 7
    t4.search("CADABRA"); // Prints: 4
    t4.search("DABRA"); // Prints: 6
    t4.search("DABRAX"); // Prints: Not Found
    t4.search("A"); // Prints: 0 3 5 7 10

    cout << "=========================\n";
    //             01234567
    SuffixTree t5("RATATAT$");
    t5.search("RAT"); // Prints: 0
    t5.search("AT"); // Prints: 1 3 5
    t5.search("TAT"); // Prints: 2 4
    t5.search("X"); // Prints: Not Found

    cout << "=========================\n";
    //             012345
    SuffixTree t6("ABCDE$");
    t6.search("A"); // Prints: 0
    t6.search("B"); // Prints: 1
    t6.search("E"); // Prints: 4
    t6.search("ABCDE"); // Prints: 0
    t6.search("R"); // Prints: Not Found

    cout << "=========================\n";
    //             012345678
    SuffixTree t7("GATAGACA$");
    t7.search("GA"); // Prints: 0 4
    t7.search("GAC"); // Prints: 4
    t7.search("GAT"); // Prints: 0
    t7.search("A"); // Prints: 1 3 5 7

    cout << "=========================\n";
    //             0123456
    SuffixTree t8("AABBCC$");
    t8.search("A"); // Prints: 0 1
    t8.search("B"); // Prints: 2 3
    t8.search("C"); // Prints: 4 5
    t8.search("ABBC"); // Prints: 1

    cout << "=========================\n";
    //             0123456
    SuffixTree t9("BANANA$");
    t9.search("BAN"); // Prints: 0
    t9.search("AN");  // Prints: 1 3
    t9.search("ANA"); // Prints: 1 3
    t9.search("ANAAA"); // Prints: Not Found
    t9.search("ANANA"); // Prints: 1

    cout << "=========================\n";
    //              012345678901
    SuffixTree t10("AABCCRTARRG$");
    t10.search("A"); // Prints: 0 1 7
    t10.search("AAB"); // Prints: 0
    t10.search("AAR"); // Prints: Not Found
    t10.search("G"); // Prints: 10
    t10.search("R"); // Prints: 5 8 9
    t10.search("RR"); // Prints: 8
    t10.search("RT"); // Prints: 5

    return 0;

}