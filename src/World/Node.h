#ifndef _NODE_H_
#define _NODE_H_

#include <string>
#include <vector>
#include <memory>

class Node
{
public:
	Node() = default;
	Node(const std::string&, Node*);
	
	void SetParent(Node*);

protected:
	std::string m_Name;
	Node const *m_Parent;
	std::vector<Node const*> m_Children;
};

#endif