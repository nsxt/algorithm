#pragma once

template<class T> class BinaryTree
{
public:
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node() { left = right = nullptr; }
	};

public:
	BinaryTree()
	{
		node_head_ = new Node;
		node_tail_ = new Node;

		node_head_->left = node_tail_;
		node_head_->right = node_tail_;

		node_tail_->left = node_tail_;
		node_tail_->right = node_tail_;
	}

	~BinaryTree()
	{
		clear();
		delete node_head_;
		delete node_tail_;
	}

public:
	/**
		Modifiers
	**/
	void remove_subtree(Node* node)
	{
		// Post Order Traverse
		if (node != node_tail_) {
			remove_subtree(node->left);
			remove_subtree(node->right);
			delete node;
		}
	}

	virtual void clear()
	{		
		remove_subtree(node_head_->left);
		node_head_->left = node_tail_;
	}

protected:
	Node* node_head_;
	Node* node_tail_;
};
