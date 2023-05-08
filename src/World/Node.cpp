#include "Node.h"

Node::Node(const std::string &nodeName, Node *parent)
{
	SetParent(parent);
}

void Node::SetParent(Node *parent)
{
	m_Parent = parent;
}
