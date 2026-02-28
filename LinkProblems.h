#include <memory>
#include <unordered_set>
#include <iostream>
#include <vector>

class Node
{
public:

	std::unique_ptr<Node> nextNode{ };
	int data{ 0 };

	explicit Node(int value) : data(value) {}

	void AppendToTail(int value)
	{
		Node* currentNode = this;
		while (currentNode->nextNode != nullptr)
		{
			currentNode = currentNode->nextNode.get();
		}
		currentNode->nextNode = std::make_unique<Node>(value);
	}
};

void DeleteNode(std::unique_ptr<Node>& head, int d)
{
	// Deleting the head
	if (head && head->data == d)
	{
		head = std::move(head->nextNode);
		return;
	}

	Node* current = head->nextNode.get();
	Node* prev = head.get();
	while (current)
	{
		if (current->data == d)
		{
			prev->nextNode = std::move(current->nextNode);
			return;
		}
		prev = current;
		current = current->nextNode.get();
	}
}

void DeleteDuplicateNodes(std::unique_ptr<Node>& head, int d)
{
	if (!head) return;

	bool seen = false;

	if (head->data == d) seen = true;

	Node* cur = head.get();
	while (cur && cur->nextNode)
	{
		if (cur->nextNode->data == d)
		{
			if (seen)
			{
				cur->nextNode = std::move(cur->nextNode->nextNode); // delete duplicate
			}
			else
			{
				seen = true;                // keep first d
				cur = cur->nextNode.get();  // advance
			}
		}
		else
		{
			cur = cur->nextNode.get();
		}
	}


}

void RemoveDuplicates(std::unique_ptr<Node>& head)
{
	std::unordered_set<int> seen;

	Node* cur = head.get();
	while (cur && cur->nextNode)
	{
		seen.insert(cur->data);

		if (seen.count(cur->nextNode->data))
		{
			cur->nextNode = std::move(cur->nextNode->nextNode);
		}
		else
		{
			cur = cur->nextNode.get();
		}
	}
}

// you have two numers represented by a linked list, where each node contains a single digit. 
// The digits are stored in reverse order, such that the 1's digit is at the head of the list. 
// Write a function that adds the two numbers and returns the sum as a linked list.
// (You are not allowed to "cheat" and just convert the linked list to an integer)
std::unique_ptr<Node> AddTwoNumbers(
	const std::unique_ptr<Node>& l1,
	const std::unique_ptr<Node>& l2)
{
	Node* p1 = l1.get();
	Node* p2 = l2.get();

	std::unique_ptr<Node> head;
	Node* tail = nullptr;
	int carry = 0;

	while (p1 || p2 || carry)
	{
		int sum = (p1 ? p1->data : 0) +
			(p2 ? p2->data : 0) +
			carry;

		carry = sum / 10;
		auto node = std::make_unique<Node>(sum % 10);

		if (!head)
		{
			head = std::move(node);
			tail = head.get();
		}
		else
		{
			tail->nextNode = std::move(node);
			tail = tail->nextNode.get();
		}

		if (p1) p1 = p1->nextNode.get();
		if (p2) p2 = p2->nextNode.get();
	}

	return head;
}


// Write code to partition a linked list around a value x, such that all node less than x 
// come before all nodes greater or equal than x. If x is contained within the list, the values
// of x only need to be after the elements less than x( see below). The partition x can appear anywhere
// in the "righ partition"; it does not need to appeart between left and right partitions
//void Partition(std::unique_ptr<Node>& head, int partition)
//{
	//if (!head) return;

	//Node* fast = head;
	//Node* slow = head;
	//while (fast && fast->nextNode)
	//{
	//	if (fast->nextNode->data >= partition)
	//		fast = fast->nextNode.get();
	//	else
	//	{
	//		std::unique_ptr<Node> tmp = std::make_unique<Node>(fast->nextNode->data);
	//		fast->nextNode = std::move(fast->nextNode->nextNode);
	//		tmp->nextNode = std::move(slow->nextNode);
	//		slow->nextNode = std::move(tmp);
	//	}
	//}
//}

void Partition(std::unique_ptr<Node>& head, int x)
{
	std::unique_ptr<Node> less;
	std::unique_ptr<Node> ge;

	Node* lessTail = nullptr; // non-owning
	Node* geTail = nullptr; // non-owning

	while (head) {
		// Detach front node from input list
		std::unique_ptr<Node> node = std::move(head);
		head = std::move(node->nextNode);
		node->nextNode = nullptr;

		// Append to the appropriate list
		if (node->data < x) {
			if (!less) {
				lessTail = node.get();
				less = std::move(node);
			}
			else {
				lessTail->nextNode = std::move(node);
				lessTail = lessTail->nextNode.get();
			}
		}
		else {
			if (!ge) {
				geTail = node.get();
				ge = std::move(node);
			}
			else {
				geTail->nextNode = std::move(node);
				geTail = geTail->nextNode.get();
			}
		}
	}

	// Stitch lists: less + ge
	if (!less) {
		head = std::move(ge);
	}
	else {
		lessTail->nextNode = std::move(ge);
		head = std::move(less);
	}
}

void PrintList(const Node* head)
{
	const Node* current = head;
	while (current)
	{
		std::cout << current->data << " -> ";
		current = current->nextNode.get();
	}
	std::cout << "nullptr" << std::endl;
}

//This implementation iterates through the list twice.
// A more efficient approach uses two pointers.
// One pointer is advanced k nodes from the head.
// Then, both pointers are moved forward together.
// When the first pointer reaches the end of the list, the second pointer will be at the desired element.
Node* FindKthElementToLast(Node* head, int k)
{
	if (!head || k <= 0) return nullptr;

	Node* fast = head;
	for (int i = 0; i < k; ++i)
	{
		fast = fast->nextNode.get();
		if (!fast) return nullptr;
	}

	Node* slow = head;
	while (fast)
	{
		fast = fast->nextNode.get();
		slow = slow->nextNode.get();
	}
	return slow;
}


void DeleteNodeButNotLastAndFirst(Node* head, int d)
{
	if (!head) return;

	Node* cur = head;
	while (cur && cur->nextNode)
	{
		if (cur->nextNode->data == d && cur->nextNode->nextNode)
		{
			cur->nextNode = std::move(cur->nextNode->nextNode);
			return;
		}
		else
		{
			cur = cur->nextNode.get();
		}
	}
}

// Implement a function to check if a linked list is a palindrome.
bool CheckPalindrome(Node* head)
{
	if (!head) return true;

	Node* current = head;
	std::unique_ptr<Node> reverse = nullptr;

	// Build reversed copy
	while (current)
	{
		auto newNode = std::make_unique<Node>(current->data);
		newNode->nextNode = std::move(reverse);
		reverse = std::move(newNode);

		current = current->nextNode.get();
	}

	// Compare
	Node* forward = head;
	Node* backward = reverse.get();

	while (forward && backward)
	{
		if (forward->data != backward->data)
			return false;

		forward = forward->nextNode.get();
		backward = backward->nextNode.get();
	}

	return true;
}

bool IsPalindrome(const Node* head)
{
	if (!head) return true;
	std::vector<int> values;
	const Node* current = head;
	while (current)
	{
		values.push_back(current->data);
		current = current->nextNode.get();
	}
	int left = 0;
	int right = static_cast<int>(values.size()) - 1;
	while (left < right)
	{
		if (values[left] != values[right])
			return false;
		++left;
		--right;
	}
	return true;
}