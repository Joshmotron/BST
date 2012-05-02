#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <cstdlib>

template <class KeyType, class DataType>
class TreeNode
{
public:
    TreeNode();
    //~TreeNode();
    TreeNode(const KeyType key_in, const DataType data_in,
             TreeNode<KeyType, DataType> *left = NULL,
             TreeNode<KeyType, DataType> *right = NULL);

    //	Member functions to set the data and link fields
    void set_data(const DataType& the_data);
    void set_key (const KeyType&  the_key);
    void set_left_child(TreeNode<KeyType, DataType> *new_child); // cannot be const pointer
    void set_right_child(TreeNode<KeyType, DataType> *new_child); // cannot be const pointer

    //	get the data from the TreeNode
    DataType get_data() const;
    KeyType get_key() const;
    //	get the children pointers from the TreeNode
    // 	These are references; cannot be const;
    TreeNode<KeyType, DataType>*& get_left_child();
    TreeNode<KeyType, DataType>*& get_right_child();

public:
    KeyType    key;
    DataType   data;
    TreeNode<KeyType, DataType>   *left;
    TreeNode<KeyType, DataType>   *right;

    //  should be able to set up a BST as a friend class;
    //	difficult with templates
    //template<class KeyType, class DataType>friend class BST;
};

template <class KeyType, class DataType>
TreeNode<KeyType, DataType>::TreeNode()
{
    left = NULL;
    right = NULL;
}

//template <class KeyType, class DataType>
//TreeNode<KeyType, DataType>::~TreeNode()
//{
//	if (left != NULL) {
//		std::cout << "Node:   " << key << "\tLeft:   " << left->key << std::endl;
//	}
//	delete left; // Automatically recurses here if left not null.
//
//	if (right != NULL) {
//		std::cout << "Node:   " << key << "\tRight:   " << right->key << std::endl;
//	}
//	delete right; // Recurses if right not null.
//
//	std::cout << "Deleting node: " << key << "." << std::endl;
//}

template <class KeyType, class DataType>
TreeNode<KeyType, DataType>::TreeNode(const KeyType key_in,
                                      const DataType data_in,
                                      TreeNode<KeyType, DataType> *left_in,
                                      TreeNode<KeyType, DataType> *right_in)
{
    key  = key_in;
    data = data_in;
    left = left_in;
    right = right_in;
}

//	Member functions to set the data, key, and child fields
template <class KeyType, class DataType>
void TreeNode<KeyType, DataType>::set_data(const DataType& new_data)
{
    data = new_data;
}

template <class KeyType, class DataType>
void TreeNode<KeyType, DataType>::set_key(const KeyType& new_key)
{
    key = new_key;
}

template <class KeyType, class DataType>
void TreeNode<KeyType, DataType>::set_left_child(TreeNode<KeyType, DataType> *new_link)
{
    left = new_link;
}

template <class KeyType, class DataType>
void TreeNode<KeyType, DataType>::set_right_child(TreeNode<KeyType, DataType> *new_link)
{
    right = new_link;
}

//	get the data from the TreeNode
template <class KeyType, class DataType>
DataType TreeNode<KeyType, DataType>::get_data() const
{
    return data;
}

template <class KeyType, class DataType>
KeyType  TreeNode<KeyType, DataType>::get_key() const
{
    return key;
}

//	get the children pointers from the TreeNode
template <class KeyType, class DataType>
TreeNode<KeyType, DataType> *& TreeNode<KeyType, DataType>::get_left_child()
{
    return left;
}

template <class KeyType, class DataType>
TreeNode<KeyType, DataType>*& TreeNode<KeyType, DataType>::get_right_child()
{
    TreeNode<KeyType, DataType>*& result = right;
    return result;
}
#endif
