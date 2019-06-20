#include "pch.h"
#include "simple_node.h"

Node::Node(int value)
{
	this->value = value;
	next_node = NULL;
}