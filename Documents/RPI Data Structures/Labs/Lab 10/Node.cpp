#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


class Node{
public:
	Node() : left{NULL}, right{NULL}, value{0} {}
	Node(int val) : left{NULL}, right{NULL}, value{val} {}
	Node* left;
	Node* right;
	int value;
};

void printfu(std::ostream& out, Node* head, int depth) {
	if(!head){
		return;
	}

	printfu(out,head->right,depth+1);
	out << std::string(depth,' ');
	out << " [" << head->value << "]" << std::endl;
	printfu(out,head->left,depth+1);
}
void print(std::ostream& out, Node* root) {
	printfu(out,root,0);
}

bool shape_match(Node* a, Node* b){
	if (!a && !b){return true;}
	if (!a && b){return false;}
	if(a && !b){ return false;}
	return (shape_match(a->left, b->left),
			shape_match(a->right, b->right));
}

Node* find_subtree_match(Node* a, Node* b){
	if (!b){return a;}
	if (a == NULL){ return NULL;}
	if (shape_match(a,b)){
		return a;
	}
	return(find_subtree_match(a->left,b),
			find_subtree_match(a->right,b));
}

int main(){
	Node* ah = new Node;
	ah->left = new Node;
	ah->right = new Node;
	ah->value = 5;
	ah->right->value = 13;
	ah->left->value = 7;
	ah->left->left = new Node;
	ah->left->right = new Node;
	ah->left->left->value = 6;
	ah->left->right->value = 11;
	ah->right->right = new Node;
	ah->right->right->value = 21;

	Node* h = new Node;
	h->left = new Node;
	h->right = new Node;
	h->value = 17;
	h->right->value = 22;
	h->left->value = 9;
	h->left->left = new Node;
	h->left->right = new Node;
	h->left->left->value = 10;
	h->left->right->value = 1;
	h->right->right = new Node;
	h->right->right->value = 8;

	Node *T = new Node(26);
	T->right         = new Node(3);
	T->right->right = new Node(3);
	T->left      = new Node(10);
	T->left->left    = new Node(4);
	T->left->left->right = new Node(30);
	T->left->right   = new Node(6);

	Node *S = new Node(10);
	S->right = new Node(6);
	S->left = new Node(4);
	S->left->right = new Node(30);


	cout<<"TREE 1:"<<endl;
	print(std::cout, ah);
	cout<<endl<<endl<<"TREE 2:"<<endl;
	print(std::cout, h);

	cout<<"SHAPES MATCH: "<<boolalpha<<shape_match(ah,h)<<", SHOULD BE TRUE"<<endl;
	cout<<"SUBTREE MATCH: "<<endl;
	Node* temp = find_subtree_match(ah, h);
	print(std::cout, temp);

	cout<<"TREE 1:"<<endl;
	print(std::cout,S);
	cout<<endl<<endl<<"TREE 2:"<<endl;
	print(std::cout, T);

	cout<<"SHAPES MATCH: "<<boolalpha<<shape_match(T,S)<<", SHOULD BE FALSE"<<endl;
	cout<<"SUBTREE MATCH: "<<endl;
	temp = find_subtree_match(T, S);
	print(std::cout, temp);


}