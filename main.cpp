#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

class LinkedList;

struct SuffixTreeNode{
    int suffixID;
    int startIndex;
    LinkedList* children;
};

struct LinkedListNode{
    LinkedListNode* next;
    SuffixTreeNode key;
    LinkedListNode(){
        next = nullptr;
    }
};

class LinkedList{
    LinkedListNode* head = new LinkedListNode;
public:
    void insert(LinkedListNode* node){
        LinkedListNode* current = head;
        node->next = nullptr;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = node;
        current = nullptr;
        delete current;
    }
    bool isEmpty(){
        return head->next;
    }
    LinkedListNode* getHead(){
        return head->next;
    }
};

class SuffixTree{
    SuffixTreeNode* root = new SuffixTreeNode;
    char* str;
public:
    SuffixTree(char str[]){
        SuffixTreeNode* node;
        root->startIndex = -1;
        root->suffixID = -1;
        root->children = new LinkedList;
        this->str = str;
        for(int i = 0; i < strlen(str); i++){
            node = new SuffixTreeNode();
            node->startIndex = i;
            insert(node, root);
        }
    }
    void insert(SuffixTreeNode* node, SuffixTreeNode* startNode){
        LinkedListNode* current = startNode->children->getHead();

        while(current->next != nullptr){
            int index = current->key.startIndex;
            if(isEqual(node->startIndex,index)){
                current=current->next;
                if(current->key.children->isEmpty()){

                }else{
                    int min=0;
                    //getting min index
                    while(current->next!=nullptr){
                        if(current->key.startIndex<min){
                            min=current->key.startIndex;
                        }
                    }
                    int newStartIndex=node->startIndex;
                    bool splitted=false;
                    for(int i=index;i<min;i++){
                        if(str[i]!=str[newStartIndex]){
                            //split
                            splitted=true;
                            break;
                        }
                        newStartIndex++;
                    }
                    if(!splitted){
                        // SuffixTreeNode* strt=current->key;
                        // insert(node,strt);
                    }
                    
                }


            }

        }

    }
    bool isEqual(int index1,int index2){
        if(str[index1]==str[index2]){
            return true;
        }else{
            return false;
        }
    }
    void search(char sequence[]){

    }
};

int main() {

}
