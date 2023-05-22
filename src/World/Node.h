#ifndef _NODE_H_
#define _NODE_H_

#include <string>
#include <vector>
#include <memory>

class Node
{
public:
	Node() = default;
	Node(const std::string&, const Node&);
	
	void SetParent(const Node&);
	void AddChild(const Node&);

protected:
	std::string m_Name;
	std::shared_ptr<Node> m_Parent;
	std::vector< std::shared_ptr<Node> > m_Children;
};

#endif