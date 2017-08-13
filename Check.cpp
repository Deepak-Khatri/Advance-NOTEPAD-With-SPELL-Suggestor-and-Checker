#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string>
using namespace std;

int found=0;
struct node{
	char info;
	string Word;
	struct node*ptrs[256];
};


void insertword(string word,int pos, node * root){
    if(word.length()==pos){
        root->Word=word;
        return;
    }
    if( root-> ptrs[word[pos]]==NULL ){
        node *newnode;
        newnode= new node;
        newnode->info=word[pos];
        root->ptrs[word[pos]]=newnode;
        insertword(word,pos+1,root->ptrs[word[pos]]);
    }
    else
        insertword(word,pos+1,root->ptrs[word[pos]]);
}

void find(string key,int pos,  node * root){
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL))
        find(key,pos+1,root->ptrs[key[pos]]);
    else if(key==root->Word){
        //cout<<"The spelling of the word is correct"<<endl;
        found=1;
    }
}







//ofstream myfile ("example1.txt");

void printall(node * root){
    for(int i=0;i<256;i++)
        if(root->ptrs[i]!=NULL){
            printall(root->ptrs[i]);
        }
    if(root->Word != "")
       {
//myfile << "->  "<<root->Word<<endl;
 cout<<root->Word<<endl;
}
}

void suggest(string key,int pos,  node * root){
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL)){
            suggest(key,pos+1,root->ptrs[key[pos]]);
    }
    else{
            printall(root);
    }
   
}

int main(){
    ifstream in("/home/god/workspace/notepadd/word.txt");
    string word,current="",key;
    struct node *root;
    root = new node;
for(int i=0;i<256;i++){
                root->ptrs[i]=NULL;
            }
            root->info='\0';
            root->Word="";
    while(in){
        in>>word;
        insertword(word,0,root);
    }
    in.close();
     cin>>key;

    find(key,0,root);
    if(!found){
    //cout<<"possible suggetion are:"<<endl;
        suggest(key,0,root);
    }
//myfile.close();
    getchar();
    return 0;
}
