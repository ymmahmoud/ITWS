//"Hop lists"
#include <iostream>

using namespace std;
//IMPORTANT: THIS IS NOT TEMPLATED
class Node{
public:
	Node(int v) : val(v), next_(NULL), prev_odd_(NULL) {}
	Node(int v, Node* next) : val(v), next_(next), prev_odd_(NULL) {}
	int val;
	Node* next_;
	Node* prev_odd_;
};

//Forward declarations
void DeleteList(Node*& head);
void PrintListForward(Node* head);
void PrintHopListBackwards(Node* tail);
void TestList(int size);

//TODO: Fill this function in. You may write your own helper functions if you want
//You should NOT assume tail is initialized
void AddPrevOddPointers(Node* head, Node*& tail) {
	Node* temp = head;
	if (temp == NULL) {
		tail = NULL;
	}
	else {
		if (temp->next_ != NULL) {
			temp = temp->next_->next_;
			if (temp !=NULL) {
				temp->prev_odd_ = head;
				tail = temp;
				AddPrevOddPointers(temp, tail);
			} else if (head->prev_odd_ == NULL) {
				tail = NULL;
			}
		} else if (head->prev_odd_ != NULL) {
			tail = NULL;
		}
	}
}


//
//	Node* temp;
//	if (tail->next_ != NULL){
//		temp = tail;
//		if (temp->next_ != NULL && temp->next_->next_ != NULL){
//			tail = temp->next_->next_;
//			tail->prev_odd_ = temp;
//			AddPrevOddPointers(head, tail);
//		}
//	}
//}

//TODO: Fill this function in. You may write your own helper functions if you want
//You should NOT assume tail is initialized
void AddPrevOddPointersIterative(Node* head, Node*& tail){
	Node* temp = head;
	Node* middleT = temp->next_;
	while(temp != NULL && middleT != NULL){
		if (middleT->next_ != NULL){
			tail = middleT->next_;
			tail->prev_odd_ = temp;
			temp = tail;
			middleT = temp->next_;
		}
		else{
			break;
		}
	}
}

int main(){
	std::cout << "Testing size 10" << std::endl;
	TestList(10);
	std::cout << "Testing size 11" << std::endl;
	TestList(11);
	std::cout << "Testing size 1" << std::endl;
	TestList(1);
	std::cout << "Testing size 2" << std::endl;
	TestList(2);
	std::cout << "Testing size 3" << std::endl;
	TestList(3);
	std::cout << "Testing empty list" << std::endl;
	Node* head = NULL;
	Node* tail;
	AddPrevOddPointers(head, tail);
	PrintHopListBackwards(tail);
	return 0;
}

//Simple destructor
void DeleteList(Node*& head){
	if(!head){
		return;
	}
	while(head){
		DeleteList(head->next_);
		delete head;
		head = NULL;
	}
}

//Starts at the given node and loops forward printing every value
void PrintListForward(Node* head){
	std::cout << "Printing forward list:";
	while(head){
		std::cout << " " << head->val;
		head = head->next_;
	}
	std::cout << std::endl;
}

//Starts at the given node and loops backwards printing every tail value
//This should be the same as every other value. Also handles NULL tail.
void PrintHopListBackwards(Node* tail){
	if(!tail){
		std::cout << "List has less than 3 nodes." << std::endl;
		return;
	}
	std::cout << "Printing backwards every-other list:";
	while(tail){
		std::cout << " " << tail->val;
		tail = tail->prev_odd_;
	}
	std::cout << std::endl;
}

//Do not change this function.
void TestList(int size){
	//Do the recursive version
	Node* head = new Node(1);
	Node* tmp = head;
	for(int i=2; i<=size; i++){
		tmp->next_ = new Node(i);
		tmp = tmp->next_;
	}

	PrintListForward(head);
	Node* tail;
	AddPrevOddPointers(head,tail);
	PrintHopListBackwards(tail);
	std::cout << std::endl;
	DeleteList(head);

	//Now do the iterative version
	head = new Node(1);
	tmp = head;
	for(int i=2; i<=size; i++){
		tmp->next_ = new Node(i);
		tmp = tmp->next_;
	}

	PrintListForward(head);
	Node* tail2;
	AddPrevOddPointersIterative(head,tail2);
	PrintHopListBackwards(tail2);
	std::cout << std::endl;

	DeleteList(head);
}