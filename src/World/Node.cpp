#include "Node.h"

Node::Node(const std::string &name, const Node &parent)
	: m_Name{name}
{
	SetParent(parent);
}

void Node::SetParent(const Node &parent)
{
	m_Parent = std::make_shared<Node>(parent);
}

void Node::AddChild(const Node &node)
{
	m_Children.push_back(std::make_shared<Node>(node));
}
