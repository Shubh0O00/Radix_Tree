# Radix_Tree
This project contains a C++ implementation of radix tree or prefix tree for English Alphabets  

Used c++ struct for the node creation  
```
struct Node{
  string data;
  Node *child[26];
  bool isEndOfString;
};
```

data stores the string for a node of the radix Tree.  
child[0,1,2 .... 26] points the child Node of the Node with 0 representing 'A' to 26 representing 'Z'.  
isEndOfString stores true if the Node is the end of the string and false if the Node is not the end of the string.  
