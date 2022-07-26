#ifndef __tree_h__
#define __tree_h__

#include <entropy\cfg.h>

namespace entropy
{

template<typename T>
class Tree
{
public:
	//node
	struct Node
	{
		Node(String id) : ID(id),parent(0),left(0),right(0),children(0) {}
		~Node() { std::cout << "Removing node: " << ID << std::endl; }
		String ID; //temp
		Node *parent;		//nodes parent
		Node *left,*right;	//nodes siblings
		Node *children;		//nodes children
		T data;				//data held by this node
	};
	//constructor
	Tree();
	//destructor
	~Tree();
	//methods
	void erase(Node *from);
private:
	//
protected:
	//variables
	Node *root;
	Node *currentPtr;
};

template<typename T>
Tree<T>::Tree()
{
	root = 0;
	currentPtr = root;

	root = new Node("0");
	/*Node *a = new Node("1");
	Node *b = new Node("2");
	a->parent = root;
	a->right = b;
	b->left = a;
	b->parent = root;
	root->children = a;*/
}

template<typename T>
Tree<T>::~Tree()
{
	erase(root);
}

template<typename T>
void Tree<T>::erase(Node *from)
{
	if(from == 0)
	{
		return;
	}
	erase(from->children);
	delete from;
}

}

#endif
