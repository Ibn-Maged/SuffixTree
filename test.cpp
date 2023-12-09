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
    LinkedListNode(SuffixTreeNode key){
        next = nullptr;
        this->key=key;
    }
    LinkedListNode(){
        next = nullptr;
    }
};

class LinkedList{
    LinkedListNode* head = new LinkedListNode();
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
        return head->next == nullptr;
    }
    LinkedListNode* getHead(){
        return head->next;
    }

    int getMinIndex(){
        if(isEmpty()){
            return -1;
        } else {
            LinkedListNode* current=head->next;
            int min=INT_MAX;
            while(current!= nullptr){
                if(current->key.startIndex<min){
                    min=current->key.startIndex;
                }
                current = current->next;
            }
            return min;
        }
    }
};

class SuffixTree{
    char* str;
public:
    SuffixTreeNode* root = new SuffixTreeNode;
    SuffixTree(char str[]){
        SuffixTreeNode* node;
        root->startIndex = -1;
        root->suffixID = -1;
        root->children = new LinkedList;
        this->str = str;
        for(int i = 0; i < strlen(str); i++){
            node = new SuffixTreeNode();
            node->startIndex = i;
            node->suffixID=i;
            node->children=new LinkedList;
            insert(root,node);
        }
    }
    void insert(SuffixTreeNode* currentNode,SuffixTreeNode* newSuffix){
        if(currentNode->children->isEmpty()){
            currentNode->children->insert(new LinkedListNode(*newSuffix));
        }else {
            LinkedListNode* currentChild = currentNode->children->getHead();
            while(currentChild!= nullptr){
                if(isEqual(currentChild->key.startIndex, newSuffix->startIndex)){
                    int minIndex=currentChild->key.children->getMinIndex();
                    if(minIndex==-1){
                        minIndex= ::strlen(str) ;
                    }
                    for(int i = currentChild->key.startIndex,j=newSuffix->startIndex; i < minIndex;i++,j++){
                        if(!isEqual(i,j)){
                            newSuffix->startIndex=j;
                            split(currentChild,new LinkedListNode(*newSuffix),i);
                            return;
                        } else{
                            newSuffix->startIndex++;
                        }
                    }
                    insert(&currentChild->key,newSuffix);
                    return;
                } else {
                    currentChild = currentChild->next;
                }
            }
            currentNode->children->insert(new LinkedListNode(*newSuffix));
        }
    }
    void split(LinkedListNode* current,LinkedListNode* newNode,int subNodeStartIndex){
        SuffixTreeNode currentSub=SuffixTreeNode();
        currentSub.children=current->key.children;
        currentSub.startIndex=subNodeStartIndex;
        if(currentSub.children->isEmpty()){
            currentSub.suffixID=current->key.suffixID;
        }else{
            currentSub.suffixID=-1;
        }
        current->key.suffixID=-1;
        current->key.children= new LinkedList();
        current->key.children->insert(newNode);
        current->key.children->insert(new LinkedListNode(currentSub));

    }
    bool isEqual(int index1,int index2) {
        return str[index1] == str[index2];
    }

    void dfs(SuffixTreeNode* node){
        if(node->children->isEmpty()){
            print(node->startIndex,strlen(str));
            return;
        }
        else{
            LinkedListNode* current= node->children->getHead();
            print(node->startIndex,node->children->getMinIndex());
            while(current!=nullptr){
                dfs(&current->key);
                current=current->next;
            }
        }
    }
    void print(int start,int end){
        for(int i=start;i<end;i++){
            cout<<str[i];
        }
        cout<<endl;
    }
};

int main(){
    char s[] = "bananabanaba$";
    SuffixTree t = SuffixTree(s);
    t.dfs(t.root);
}