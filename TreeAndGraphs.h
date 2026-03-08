#include <memory>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <queue>
#include <span>
#include <map>
#include <limits>

class BinaryTree
{
public:

	std::unique_ptr<BinaryTree> m_left{};
    std::unique_ptr<BinaryTree> m_right{};
	int data{ 0 };

	explicit BinaryTree(int value) : data(value) {}

};

// In-order traversal
inline void InOrderTraversal(const BinaryTree* node )
{
    if (node)
    {
        InOrderTraversal(node->m_left.get());
        // visit(node)
        InOrderTraversal(node->m_right.get());
    }
}

// Pre-Order traversal
inline void PreOrderTraversal(const BinaryTree* node)
{
    if (node)
    {
        //visit(node);
        PreOrderTraversal(node->m_left.get());
        PreOrderTraversal(node->m_right.get());
    }
}

// Post-Order Traversal
inline void PostOrderTraversal(const BinaryTree* node)
{
    if (node)
    {
        PostOrderTraversal(node->m_left.get());
        PostOrderTraversal(node->m_right.get());
        // visit (node)
    }
}

struct Node
{
    std::string name;
    std::vector<Node*> m_neighbors;
    bool visited{false};
    bool marked{false};
};

inline void Visit(Node* node)
{
    return; // dummy
}

struct Graph
{
    std::vector<std::unique_ptr<Node>> nodes;
};

void DepthFirstSearch(Node* root)
{
    if (!root) return;
    Visit(root);
    root->visited=true;
    for (auto* node:root->m_neighbors)
    {
        if(!node) continue;
        if (!node->visited)  DepthFirstSearch(node);
    }
}


void BreathFirstSearch(Node* root)
{
    std::queue<Node*> itsQueue;
    root->marked=true;
    itsQueue.push(root); // enqueue

    while (!itsQueue.empty())
    {
        Node* r = itsQueue.front();
        itsQueue.pop();
        Visit(r);
        for (auto* node:r->m_neighbors)
        {
            if (node->marked==false)
            {
                node->marked=true;
                itsQueue.push(node); // enqueue
            }
        }
    }
}

// Given a directed graph and two nodes ( S and E), design an algorithm to find out 
// whether there is a route from S to E.

bool RouteStoE(Node* S, Node* E)
{
    // reset all to false;
    if (S==E) return true;
    if (S==nullptr  ||  E==nullptr) return false;
    std::queue<Node*> itsQueue;
    S->marked=true;
    itsQueue.push(S); // enqueue

    while (!itsQueue.empty())
    {
        Node* r = itsQueue.front();
        itsQueue.pop();

        if (r == E) return true;

        Visit(r);
        for (auto* node:r->m_neighbors)
        {
            if (node->marked==false)
            {
                node->marked=true;
                itsQueue.push(node); // enqueue
            }
        }
    }
    return false;
}

// Given a sorted ( increasing order ) array with unique integer elements, write
// an algorithm to create a binary search tree with minimal height.

template <typename T>
std::unique_ptr<BinaryTree>  MinimalTree(std::span<const T> increasingOrderSorted)
{
    if (increasingOrderSorted.size()==0) nullptr;

    const std::size_t middleIdx = increasingOrderSorted.size() / 2;

    auto root = std::make_unique<BinaryTree>(increasingOrderSorted[middleIdx]);

    auto left  = increasingOrderSorted.subspan(0, middleIdx);
    auto right = increasingOrderSorted.subspan(middleIdx + 1);

    root->m_left = MinimalTree(left);
    root->m_right = MinimalTree(right);
    return root;
}

std::unique_ptr<BinaryTree> buildMinimalTree(
    const std::vector<int>& arr, int lo, int hi)
{
    if (lo > hi) return nullptr;

    int mid = lo + (hi - lo) / 2;
    auto root = std::make_unique<BinaryTree>(arr[mid]);

    root->m_left  = buildMinimalTree(arr, lo, mid - 1);
    root->m_right = buildMinimalTree(arr, mid + 1, hi);

    return root;
}

std::unique_ptr<BinaryTree> MinimalTree(const std::vector<int>& increasingOrderSorted)
{
    if (increasingOrderSorted.empty()) return nullptr;
    return buildMinimalTree(increasingOrderSorted, 0,
                            static_cast<int>(increasingOrderSorted.size()) - 1);
}

// Given a binary tree, design an algorithm which creates a linked list of all the nodes of each depth
// e.g. If you have a tree with depth D, you will have D Linked list

struct BinaryTreeNode
{
    std::string name;
    BinaryTreeNode* m_left;
    BinaryTreeNode* m_right;
};

class LinkedListNode
{
    public:
    BinaryTreeNode* root;
    std::unique_ptr<LinkedListNode> nextNode{ };
    
    explicit LinkedListNode(BinaryTreeNode*init):root(init){}

    void AppendToTail(BinaryTreeNode* tail)
	{
        if (!tail) return;
		LinkedListNode* currentNode = this;
		while (currentNode->nextNode != nullptr)
		{
			currentNode = currentNode->nextNode.get();
		}
		currentNode->nextNode = std::make_unique<LinkedListNode>(tail);
    }
};

std::map<int, std::unique_ptr<LinkedListNode>> linkedLists;

void AddToLevel(BinaryTreeNode* node, int depth)
{
    if (!node) return;

    if (!linkedLists.contains(depth)) {
        linkedLists[depth] = std::make_unique<LinkedListNode>(node);
    } else {
        linkedLists[depth]->AppendToTail(node);
    }

    AddToLevel(node->m_left, depth + 1);
    AddToLevel(node->m_right, depth + 1);
}

void ListOfDepths(BinaryTreeNode* root)
{
    linkedLists.clear();
    AddToLevel(root, 0);
}

// Check balanced. Implement a function to check if a binary tree is balanced. For the purposes of this question, 
// a balanced tree is defined to be a tree such that the heights of the two subtrees of any node never
// differ by more than one

struct BalancedNode
{
    BalancedNode* m_left;
    BalancedNode* m_right;
};

int Height(BalancedNode* n) {
    if (!n) return 0;
    int left = Height(n->m_left);    // go down
    if (left==-1) return -1;
    int right = Height(n->m_right);  // go down
    if (right=-1) return -1;
    if (std::abs(left-right)>1)
    {
       return -1; // unbalanced
    }
    return 1 + std::max(left, right);   // return up
}

// implement a function to check if binary tree is binary search tree

struct BSTNode
{
    int value;
    BSTNode* m_left;
    BSTNode* m_right;
};

bool BSTCheck(BSTNode* node, long long minVal, long long maxVal)
{
    if (!node) return true;

    if (node->value <= minVal || node->value >= maxVal)
        return false;

    return BSTCheck(node->m_left, minVal, node->value) &&
           BSTCheck(node->m_right, node->value, maxVal);
}

bool StartBSTCheck(BSTNode* root)
{
    return BSTCheck(root,
                    std::numeric_limits<long long>::min(),
                    std::numeric_limits<long long>::max());
}
