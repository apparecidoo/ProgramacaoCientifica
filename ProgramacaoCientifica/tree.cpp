#include "pch.h"
#include "tree.h"

template<class T>
int Tree<T>::new_id()
{
	return this->id++;
}

template <class T>
Tree<T>::Tree(int max_children_nodes)
{
	this->max_children_nodes = max_children_nodes;
	this->visited_nodes = 0;
	this->number_nodes = 0;
	this->root = NULL;
	this->id = 1;
}

template<class T>
Tree<T>::~Tree()
{
	Node<T>* node = root;
	Node<T>* aux = NULL;

	while (node != NULL)
	{
		// get the next node to be explored
		if (node->children_nodes != NULL) {
			for (int i = 0; i < max_children_nodes; i++)
			{
				if (node->children_nodes[i] != NULL) {
					node = node->children_nodes[i];
					break;
				}
			}
		}
		else {
			// if there isn't any children, so delete the node
			aux = node;
			node = node->parent;

			if (aux != NULL)
				delete aux;
		}
	}
}

template<class T>
void Tree<T>::add(T value)
{

}

template<class T>
void Tree<T>::add_children(Node<T> current_node, T value)
{
	if (current_node == NULL)
		throw CustomException("current_node is null");

	for (int i = 0; i < max_children_nodes; i++)
	{
		if (current_node->children_nodes[i] == NULL) {
			current_node->children_nodes[i] = new Node<T>(value, current_node, max_children_nodes, new_id());
			this->number_nodes++;
			break;
		}
	}
}

template<class T>
T Tree<T>::remove_cascate(T content)
{
	Node<T>* node = search_dfs(content);
	Node<T>* aux = NULL;

	while (node != NULL)
	{
		if (compare(node->content, content))
			return node;

		// get the next node to be explored
		if (node->has_children()) {
			aux = node->get_next_to_explore();
			if (aux != NULL) {
				node = aux;
			}
			else {
				node = node->parent;
			}
		}
		else {
			// if there isn't any children, so delete the node
			aux = node;
			node = node->parent;

			if (aux != NULL)
				delete aux;
		}
	}
}

template<class T>
Node<T>* Tree<T>::search_bfs(T content)
{
	Node<T>* node = root;

	while (node != NULL)
	{
		if (compare(node->content, content))
			return node;

		// get the next node to be explored
		if (node->children_nodes != NULL) {
			for (int i = 0; i < max_children_nodes; i++)
			{
				if (node->children_nodes[i] != NULL) {
					node = node->children_nodes[i];
					break;
				}
			}
		}
		else {
			node = node->parent;
		}
	}
}

template<class T>
Node<T>* Tree<T>::search_dfs(T content)
{
	Node<T>* node = root;

	while (node != NULL)
	{
		if (compare(node->content, content))
			return node;

		// get the next node to be explored
		if (node->has_child_to_explore()) {
			node = node->get_next_to_explore();
			node->explored = true;
		}
		else {
			node = node->parent;
		}
	}

	return NULL;
}

template<class T>
bool Tree<T>::compare(T first, T second)
{
	return first == second;
}
