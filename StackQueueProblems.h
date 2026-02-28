#include <array>
#include <vector>
#include <stack>

// implementing a stack
// 
// remove the top item from the stack
// pop () 

// add an item to the top of the stack
// push (item)

// peek at the top item on the stack without removing it
// peek ()

// is the stack empty?
// isEmpty()

template <typename T>
class MyStack
{
	class StackNode
	{
	public:
		T data;
		std::unique_ptr<StackNode> next;
		StackNode(const T& value) : data(value), next(nullptr) {}
	};

	class MinNode
	{
	public:
		T minValue;
		std::unique_ptr<MinNode> next;
		MinNode(const T& value) : minValue(value), next(nullptr) {}
	};

	std::unique_ptr<StackNode> top;
	std::unique_ptr<MinNode> minTop;

private:

	void RemoveMin(T value)
	{
		if (minTop && value == minTop->minValue)
		{
			minTop = std::move(minTop->next);
		}
	}
	void PushMin(T value)
	{
		if (!minTop || value <= minTop->minValue) // <= to handle duplicates (push 3 twice, pop once, min should still be 3)
		{
			std::unique_ptr<MinNode> newMinNode = std::make_unique<MinNode>(value);
			newMinNode->next = std::move(minTop);
			minTop = std::move(newMinNode);
		}
	}

public:
	T pop()
	{
		if (!top)
			throw std::runtime_error("Stack is empty");
		T value{ std::move(top->data) };
		top = std::move(top->next);
		RemoveMin(value);
		return value;
	}

	T min()
	{
		if (!minTop)
			throw std::runtime_error("Stack is empty");
		return minTop->minValue;
	}

	void push(const T& item)
	{
		std::unique_ptr<StackNode> newNode = std::make_unique<StackNode>(item);
		newNode->next = std::move(top);
		top = std::move(newNode);
		PushMin(item);
	}

	T peek() const
	{
		if (!top)
			throw std::runtime_error("Stack is empty");
		return top->data;
	}

	bool isEmpty() const
	{
		return top == nullptr;
	}
};

// implementing a queue
// add(item) - add an item to the end of the queue
// remove() - remove the item at the top of the queue and return it
// peek() - return the item at the top of the queue without removing it
// isEmpty() - return true if the queue is empty, false otherwise


template <typename T>
class MyQueue
{
	class QueueNode
	{
	public:
		T data;
		std::unique_ptr<QueueNode> next;
		QueueNode(const T& value) : data(value), next(nullptr) {}
	};


	std::unique_ptr<QueueNode> head;
	QueueNode* tail = nullptr;

public:
	T remove()
	{
		if (!head)
			throw std::runtime_error("queue is empty");
		auto oldHead = std::move(head);
		head = std::move(oldHead->next);
		if (!head)
			tail = nullptr;
		return std::move(oldHead->data);
	}

	void add(const T& item)
	{
		auto newNode = std::make_unique<QueueNode>(item);
		QueueNode* newTail = newNode.get();

		if (!head)
		{
			head = std::move(newNode);
		}
		else
		{
			tail->next = std::move(newNode);
		}
		tail = newTail;
	}

	T& peek()
	{
		if (!head) throw std::runtime_error("Queue is empty");
		return head->data;
	}

	const T& peek() const
	{
		if (!head) throw std::runtime_error("Queue is empty");
		return head->data;
	}

	bool isEmpty() const
	{
		return head == nullptr;
	}
};

// Describe how could you use a single array to implement three stacks. 
// For example, you could divide the array into three equal parts and use each part for a different stack. 
// However, this approach can lead to inefficient use of space if one stack grows much larger than the others.

class ThreeStacks
{
	constexpr static int numberOfStacks = 3;
	constexpr static int stackSize = 99;
	std::array<int, stackSize> stackData{};
	std::array<int, numberOfStacks> stackSizes{ };
	constexpr static int stackCapacity = stackSize / numberOfStacks;

public:

	bool isEmpty(int stackNum) const
	{
		if (stackNum < 0 || stackNum >= numberOfStacks)
			throw std::out_of_range("Invalid stack number");
		return stackSizes[stackNum] == 0;
	}


	void push(int stackNum, int value)
	{
		if (stackNum < 0 || stackNum >= numberOfStacks)
			throw std::out_of_range("Invalid stack number");
		if (stackSizes[stackNum] >= stackCapacity)
			throw std::overflow_error("Stack is full");
		const int index = stackNum * stackCapacity + stackSizes[stackNum];
		stackData[index] = value;
		stackSizes[stackNum]++;
	}

	int pop(int stackNum)
	{
		if (stackNum < 0 || stackNum >= numberOfStacks)
			throw std::out_of_range("Invalid stack number");
		if (isEmpty(stackNum))
			throw std::underflow_error("Stack is empty");
		const int top = stackNum * stackCapacity + stackSizes[stackNum] - 1;
		const int value = stackData[top];
		stackSizes[stackNum]--;
		return value;
	}
	int peek(int stackNum) const
	{
		if (stackNum < 0 || stackNum >= numberOfStacks)
			throw std::out_of_range("Invalid stack number");
		if (isEmpty(stackNum))
			throw std::underflow_error("Stack is empty");
		const int top = stackNum * stackCapacity + stackSizes[stackNum] - 1;
		return stackData[top];
	}

};

class SetOfStacks
{
	std::vector<std::stack<int>> stacks;
	const size_t stackCapacity;

public:
	SetOfStacks(size_t capacity) : stackCapacity(capacity)
	{
		if (stackCapacity == 0)
			throw std::invalid_argument("Stack capacity must be greater than 0");
	}

	void push(int value)
	{
		if (stacks.empty() || stacks.back().size() >= stackCapacity)
		{
			stacks.push_back(std::stack<int>()); // create a new stack
		}
		stacks.back().push(value);
	}

	// no rollover
	int popAt(size_t stackNum)
	{
		auto& stack = stacks.at(stackNum);
		if (stack.empty())
			throw std::runtime_error("Stack is empty");
		const auto value{ stack.top() };

		stack.pop();
		if (stack.empty())
		{
			stacks.erase(stacks.begin() + stackNum); // remove empty stack
		}
		return value;
	}

	int pop()
	{
		if (isEmpty())
			throw std::runtime_error("Set of stacks is empty");

		const auto value{ stacks.back().top() };
		stacks.back().pop();
		if (stacks.back().empty())
		{
			stacks.pop_back();
		}
		return value;
	}

	int peek() const
	{
		if (isEmpty())
			throw std::runtime_error("Set of stacks is empty");
		return stacks.back().top();
	}

	bool isEmpty() const
	{
		return stacks.empty();
	}
};