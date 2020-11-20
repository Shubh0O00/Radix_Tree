/**
 * @file radixTree.cpp
 * @version 1.0
*/

//headers
#include<iostream>
#include<string.h>

using namespace std;

//node structure
struct Node
{
    string data;            //to store the data in the node
    Node *child[26];        //to store the address to the child corresponding to the alphabet
    bool isEndOfString;     //to store whether or not the node is end of an string
};

/**
 * a fucntion to create a new node and assign a string to the data attribute of the node
 * @param s a string to store the input that is needed to be assigned to the node.data
 * @return newnode a pointer to the node that is created
*/
Node* createNewNode(string s)
{
    Node *newnode = new Node;
    newnode->data = s;
    newnode->isEndOfString = true;
    for(int i = 0; i<26; i++)
    {
        newnode->child[i] = NULL;
    }
    return newnode;
}

int countNodeChild(Node *node)
{
    int count=0;
    for(int i = 0; i < 26; i++)
    {
        if(node->child[i] != NULL)
        {
            count++;
        }
    }

    return count;
}

int returnFirstChild(Node *node)
{
    for(int i = 0; i < 26; i++)
    {
        if(node->child[i] != NULL)
        {
            return i;
        }
    }
}

int prefixSearch(string s1, string s2)
{
    int lenS1 = s1.length();
    int lenS2 = s2.length();
    int minLen;
    if(lenS1 > lenS2)
    {
        minLen = lenS2;
    }
    else
    {
        minLen = lenS1;
    }
    for(int i = 0 ; i < minLen ; i++)
    {
        if (s1.at(i) == s2.at(i))
        {
            continue;
        }
        else
        {
            return i;
        }
    }
}

void splitString(string *s1, string *s2, int index, string s)
{
    (*s1).append(s.begin(), s.begin()+index);
    (*s2).append(s.begin() + index, s.end());
}

Node* traversalForInsert(string *s, Node *node, int *index)
{
    (*index) = prefixSearch(node->data, *s);
    string s1, s2;
    splitString(&s1, &s2, *index, *s);
    *s = s2;
    if((*s).empty())
    {
        return node;
    }
    else if (node->data.length() > *index)
    {
        return node;
    }
    
    else if(node->child[(*s).at(0)-65] != NULL)
    {
        node = node->child[(*s).at(0)-65];
        node = traversalForInsert(s, node, index);
        return node;
    }
    else
    {
        return node;
    }
    
}

void split(Node **node, int index)
{
    string s1, s2;
    splitString(&s1, &s2, index, (*node)->data);
    (*node)->data = s1;
    Node *temp;
    temp = createNewNode(s2);
    temp->isEndOfString = (*node)->isEndOfString;
    (*node)->isEndOfString = false;
    for(int i = 0; i < 26; i++)
    {
        temp->child[i] = (*node)->child[i];
    }
    for(int i = 0; i < 26; i++)
    {
        (*node)->child[i] = NULL;
    }

    (*node)->child[s2.at(0) - 65] = temp;
}

void insertNode(Node **root, string inputString)
{
    if(*root == NULL)
    {
        *root = createNewNode(inputString);
    }
    else
    {
        Node *node;
        int index;
        node = traversalForInsert(&inputString, *root, &index);
        if(inputString.empty())
        {
            if((node->data).length() == index)
            {
                node->isEndOfString = true;
            }
            else
            {
                split(&node, index);
                node->isEndOfString = true;
            }
        }
        else
        {
            Node *temp;
            temp = createNewNode(inputString);
            if((node->data).length() == index)
            {
                node->child[int(inputString.at(0) - 65)] = temp;
            }
            else
            {
                split(&node, index);
                node->child[int(inputString.at(0) - 65)] = temp;
            }
            
        }
        
    }
}

void printTree(Node *temp, string s1)
{
    if(temp->isEndOfString)
    {
        s1.append(temp->data);
        cout<<s1<<endl;
        for (int j = 0; j < temp->data.length() ; j++)
        {
            s1.pop_back();
        }
        
    }
    for(int i = 0; i < 26; i++)
    {
        if(temp->child[i] != NULL)
        {   
            s1.append(temp->data);
            printTree(temp->child[i], s1);  
            for (int j = 0; j < temp->data.length() ; j++)
            {
                s1.pop_back();
            }
                     
        }
    }
}

void capitalise(string *str)
{
	
	for(int i=0; (*str)[i]!='\0';i++)
	{
		if ((*str)[i] >= 'a' && (*str)[i] <= 'z')
        {
			(*str)[i] = (*str)[i] - 32;
        }
	}
}

void spaceRemover(string *s)
{
    for(int i=0; i<(*s).length(); i++)
    {
        if((*s).at(i) == ' ')
        {
            (*s).erase((*s).begin()+i);
        }
    }
}

void modifyString(string *s)
{
    spaceRemover(s);
    capitalise(s);
}

bool search(Node *node, string stringToBeFind)
{
    Node * currNode;
    int index;
    currNode = traversalForInsert(&stringToBeFind, node, &index);
    if(stringToBeFind.empty() && index == currNode->data.length() && currNode->isEndOfString == true)
    {

        return true;
    }
    else
    {
        return false;
    }
    
}

void mergeNode(Node *node)
{
    string s="";
    int childIndex = returnFirstChild(node);
    s.append(node->data);
    s.append(node->child[childIndex]->data);
    node->data = s;
    Node *temp = node->child[childIndex];
    node->isEndOfString = temp->isEndOfString;
    node->child[childIndex] = NULL;
    for(int i=0; i<26; i++)
    {
        node->child[i] = temp->child[i];
    }
    delete temp;
}

bool deleteNode(Node* node, string stringToBeDeleted)
{
    Node * currNode, *prevNode;
    int index1, index2;
    int count;
    string modifiedString = stringToBeDeleted;
    currNode = traversalForInsert(&stringToBeDeleted, node, &index1);
    if(stringToBeDeleted.empty() && index1 == currNode->data.length() && currNode->isEndOfString == true)
    {
        for(int i=0; i<currNode->data.length(); i++)
        {
            modifiedString.pop_back();
        }
        prevNode = traversalForInsert(&modifiedString, node, &index2);
        count = countNodeChild(currNode);
        currNode->isEndOfString = false;
        if(count == 0)
        {
            prevNode->child[currNode->data.at(0) - 65] = NULL;
            delete currNode;
            int count1 = countNodeChild(prevNode);
            if(count1 == 1 && prevNode->isEndOfString == false)
            {
                mergeNode(prevNode);
            }
        }
        else if (count == 1)
        {
            mergeNode(currNode);
        }
        return true;
    }
    else
    {
       cout<<"\nString Not Found!!!\n";
       return false;
    }
}

int main()
{
    Node *root;
    root = NULL;
    string s;
    int choice;
    char ch = 'y';
    while (ch == 'y')
    {
        cout<<"\nMenu:   \n"
            <<"------------\n"
            <<"1. Insert String\n"
            <<"2. Delete String\n"
            <<"3. Search String\n"
            <<"4. Print Tree\n"
            <<"5. Exit\n\n"
            <<"--------------\n\n";
        cin>>choice;
        switch (choice)
        {
            case 1: cout<<"Enter the string to be inserted: ";
                    getline(cin >>ws , s);
                    modifyString(&s);
                    insertNode(&root, s);
                    break;
            
            case 2: cout<<"Enter the string to be deleted: ";
                    getline(cin >>ws , s);
                    modifyString(&s);
                    bool isDeleted;
                    isDeleted = deleteNode(root, s);
                    if(isDeleted)
                    {
                        cout<<"The tree after deleting "<<s<<endl;
                        s="";
                        printTree(root,s);
                    }
                    break;

            case 3: bool isFound;
                    cout<<"Enter the string to be searched: ";
                    getline(cin >>ws , s);
                    modifyString(&s);
                    isFound = search(root,s);
                    if(isFound)
                    {
                        cout<<"\nFound\n";
                    }
                    else
                    {
                        cout<<"\nNot Found\n";
                    }
                    break;
            
            case 4: cout<<"\n\nPrintint the strings in alphabetical order\n\n";
                    s = "";
                    printTree(root, s);
                    cout<<"\n";
                    break;
            
            case 5: cout<<"\nExiting!!!!\n";
                    ch = 'n';
        }
    }
    return 0;

}

/**
* Executed successfully using mingwX86 compiler
* used c++11
* So compile accordingly
*/