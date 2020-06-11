#pragma once
#include <string>
#include <vector>
#include <utility>

template <class T>
class BSTree
{
private:
	struct node
	{
		node* parent = nullptr;
		node* left = nullptr;
		node* right = nullptr;
		T data = T();
		int key = 0;
	};
	node* root = nullptr;
	int size = 0;

private:

	void delete_tree(node* node_ptr)
	{
		if (node_ptr == nullptr) return;

		if (node_ptr->left != nullptr)
		{
			delete_tree(node_ptr->left);
			delete node_ptr->left;
		}
		if (node_ptr->right != nullptr)
		{
			delete_tree(node_ptr->right);
			delete node_ptr->right;
		}
	}

	node* search_(const int key, node* node_ptr)
	{

		while (node_ptr != nullptr)
		{
			if (key < node_ptr->key)
			{
				node_ptr = node_ptr->left;
			}
			else if (key > node_ptr->key)
			{
				node_ptr = node_ptr->right;
			}
			else return node_ptr;
		}
		return nullptr;
	}


	node* next(node* node_ptr)
	{
		if (node_ptr == nullptr) return nullptr;

		if (node_ptr->right != nullptr)
		{
			node_ptr = node_ptr->right;

			while (node_ptr->left != nullptr)
			{
				node_ptr = node_ptr->left;
			}

			return node_ptr;
		}
		else if (node_ptr->parent->left == node_ptr)
		{
			return node_ptr->parent;
		}
		else return nullptr;
	}

	void remove_(node* del_node_)
	{
		node* del_node = del_node_;

		if (del_node == nullptr) return;

		if (del_node->right == nullptr && del_node->left == nullptr)
		{
			if (del_node == this->root)
			{
				delete del_node;
				this->root = nullptr;
			}
			else
			{
				if (del_node->parent->right == del_node) del_node->parent->right = nullptr;
				else del_node->parent->left = nullptr;

				delete del_node;
			}
		}
		else if (del_node->right != nullptr && del_node->left == nullptr)
		{
			if (del_node == this->root)
			{
				del_node->right->parent = nullptr;
				this->root = del_node->right;

			}
			else
			{
				if (del_node->parent->left == del_node) del_node->parent->left = del_node->right;
				else del_node->parent->right = del_node->right;

				del_node->right->parent = del_node->parent;

			}

			delete del_node;
		}
		else if (del_node->right == nullptr && del_node->left != nullptr)
		{
			if (del_node == this->root)
			{
				del_node->left->parent = nullptr;
				this->root = del_node->left;
			}
			else
			{
				if (del_node->parent->left == del_node) del_node->parent->left = del_node->left;
				else del_node->parent->right = del_node->left;

				del_node->left->parent = del_node->parent;

			}

			delete del_node;
		}

		else if (del_node->right != nullptr && del_node->left != nullptr)
		{
			node* swap_node = next(del_node);

			T tmp_value = del_node->data;
			del_node->data = swap_node->data;
			swap_node->data = tmp_value;

			int tmp_key = del_node->key;
			del_node->key = swap_node->key;
			swap_node->key = tmp_key;

			this->remove_(swap_node);
		}
	}

	BSTree<T>* where_(bool (*func)(T), node* node_ptr)
	{
		if (!node_ptr) {
			return	nullptr;
		}

		static BSTree<T>* result = new BSTree<T>();

		if (func(node_ptr->data))
		{
			result->add(node_ptr->key,node_ptr->data);
		}

		if (node_ptr->left != nullptr)
		{
			where_(func, node_ptr->left);
		}

		if (node_ptr->right != nullptr)
		{
			where_(func, node_ptr->right);
		}

		return result;
	}

	void Map_(T(*func)(T), node* node_ptr) 
	{
		if (!node_ptr) {
			return;
		}

		node_ptr->data = func(node_ptr->data);

		if (node_ptr->left != nullptr) 
		{
			Map_(func, node_ptr->left);
		} 

		if (node_ptr->right != nullptr)
		{
			Map_(func, node_ptr->right);
		}
	}

	T Reduce_(T(*func)(T, T), const T& start, node* node_ptr) {
		if (node_ptr == nullptr)
		{
			return T();
		}

		std::vector<T> tree_vector;
		to_string_(node_ptr, tree_vector);

		T result;
		for (int i = 0; i < tree_vector.size(); i++) {
			if (i == 0) {
				result = func(tree_vector[i], start);
			}
			else {
				result = func(tree_vector[i], result);
			}
		}

		return result;
	}

	void to_string_(node* node_ptr, std::vector<T>& result, std::string order = "NLR")
	{
		for (int i = 0; i < order.size(); ++i) {
			switch (order[i])
			{
			case 'N' :
				result.push_back(node_ptr->data);
				break;
			case 'L' :
				if (node_ptr->left != NULL)
				{
					to_string_(node_ptr->left, result, order);
				}
				break;
			case 'R' :
				if (node_ptr->right != NULL)
				{
					to_string_(node_ptr->right, result, order); 
				}
				break;
			}
		}	
		return;
	}

public:

	BSTree() = default;

	BSTree(const int key, const T data)
	{
		this->root = new node;
		this->root->data = data;
		this->root->key = key;
		size = 1;
	}

	int get_size()
	{
		return this->size;
	}

	void add(const int key, const T data)
	{
		node* node_ptr = this->root;

		++this->size;

		if (this->root == nullptr)
		{
			this->root = new node;
			this->root->data = data;
			this->root->key = key;
			return;
		}

		while (node_ptr != nullptr)
		{
			if (key < node_ptr->key)
			{
				if (node_ptr->left != nullptr)
				{
					node_ptr = node_ptr->left;
				}
				else
				{
					node_ptr->left = new node;
					node_ptr->left->data = data;
					node_ptr->left->parent = node_ptr;
					node_ptr->left->key = key;
					break;
				}
			}
			else
			{
				if (node_ptr->right != nullptr)
				{
					node_ptr = node_ptr->right;
				}
				else
				{
					node_ptr->right = new node;
					node_ptr->right->data = data;
					node_ptr->right->parent = node_ptr;
					node_ptr->right->key = key;
					break;
				}
			}
		}
	}

	void remove(int key)
	{
		node* del_node = search_(key, this->root);
		if (del_node == nullptr) return;

		remove_(del_node);
		--this->size;
	}

	T search(int key)
	{
		if (search_(key,this->root) != nullptr)
		{
			return search_(key, this->root)->data;
		}
		else return T();
	}

	void map(T(*func) (T))
	{
		Map_(func, this->root);
	}

	BSTree<T>* where(bool (*func) (T))
	{
		return where_(func, this->root);
	}

	T reduce(T(*func) (T, T), const T& start) {
		return Reduce_(func, start, this->root);
	}

	void to_string(std::vector<T>& result, std::string order = "NLR")
	{
		to_string_(this->root,result, order);
	}

	~BSTree()
	{
		delete_tree(this->root);

		size = 0;
		delete this->root;
	}

};

