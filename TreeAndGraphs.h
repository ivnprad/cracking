#include <memory>
#include <unordered_set>
#include <iostream>
#include <vector>

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