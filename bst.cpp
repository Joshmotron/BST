#ifndef BST_H
#define BST_H

//  enumerated traversal types
enum TraverseType {INFIX, PREFIX, POSTFIX};

#include "treenode.cpp"

template <class KeyType, class DataType>
class BST
{
public:
    BST();
    ~BST();
    bool  insert (KeyType key, DataType data);
    bool  retrieve(KeyType key, DataType& outData);
    bool  remove (KeyType key);
    void  traverse (TraverseType traverseType, void (*visit) (DataType));

    static void printNode (DataType data) {
        std::cout << "Phone Book Record: " << data << std::endl;
    }

private:
    bool _purge   (TreeNode<KeyType, DataType>** node);
    bool _insert  (KeyType key, TreeNode<KeyType, DataType>* newPtr, TreeNode<KeyType, DataType>*& _root);
    void _traversePrefix (TreeNode<KeyType, DataType>* _root, void (*visit)(DataType));
    void _traverseInfix  (TreeNode<KeyType, DataType>* _root, void (*visit)(DataType));
    void _traversePostfix(TreeNode<KeyType, DataType>* _root, void (*visit)(DataType));
    TreeNode<KeyType, DataType>*  _root;
    TreeNode<KeyType, DataType>*  _remove  (KeyType key, TreeNode<KeyType, DataType>*& _root);
    TreeNode<KeyType, DataType>*  _findMaxPtr(TreeNode<KeyType, DataType>* _root);
};

template <class KeyType, class DataType>
BST<KeyType, DataType>::BST() : _root(NULL)
{

}

template <class KeyType, class DataType>
bool BST<KeyType, DataType>::_purge(TreeNode<KeyType, DataType>** Node)
{
    TreeNode<KeyType, DataType> *tmp = *Node;

    if (tmp->get_left_child() != NULL) {
        _purge (&tmp->get_left_child());
    }

    if (tmp->get_right_child() != NULL) {
        _purge (&tmp->get_right_child());
    }

    std::cout << "Deleting: " << tmp->get_key() << std::endl;
    delete tmp;
    *Node = NULL;

    return false;
}

template <class KeyType, class DataType>
BST<KeyType, DataType>::~BST()
{
    std::cout << "Deleting Tree!" << std::endl;
    //delete _root;
    if (_root) {
        _purge(&_root);
    }
    std::cout << "DONE!" << std::endl;
}

template <class KeyType, class DataType>
bool  BST<KeyType, DataType>::insert (KeyType key, DataType data)
{
    TreeNode<KeyType, DataType>* newPtr = new TreeNode<KeyType, DataType>(key, data);

    if (!newPtr) {
        return false;
    }

    return (_insert (key, newPtr, _root));
}

template <class KeyType, class DataType>
bool  BST<KeyType, DataType>::_insert (KeyType key,
                                       TreeNode<KeyType, DataType>* newPtr,
                                       TreeNode<KeyType, DataType>* & root)
{
    std::cout << std::endl << "Inserting node: " << key << std::endl;

    if (root == NULL) {
        std::cout << "Inserted _root. Key: " << key << std::endl;
        root = newPtr;

        return true;
    }

    TreeNode<KeyType, DataType>* tmp = _root;
    while (tmp != NULL) {
        if (key < tmp->get_key()) {
            std::cout << "less than.\tParent: " << tmp->get_key() << std::endl;

            if (tmp->get_left_child() == NULL) {
                tmp->set_left_child(newPtr);

                std::cout << "Inserted left of parent: " << tmp->get_key() << std::endl;

                return true;
            } else {
                tmp = tmp->get_left_child();
            }
        } else if (key > tmp->get_key()) {
            std::cout << "GREATER THAN.\tParent: " << tmp->get_key() << std::endl;

            if (tmp->get_right_child() == NULL) {
                tmp->set_right_child(newPtr);

                std::cout << "Inserted right of parent: " << tmp->get_key() << std::endl;

                return true;
            } else {
                tmp = tmp->get_right_child();
            }
        } else {
            // Instead of retrieving, so this so it doesn't go through
            // the tree twice.
            std::cout << "No duplicates! *ANGRY FACE*\tKey: " << key << std::endl << std::endl;
            return false;
        }
    }

    return false;
}

template <class KeyType, class DataType>
bool BST<KeyType, DataType>::retrieve(KeyType key, DataType& data)
{
    if (!_root) {
        return false;
    }

    TreeNode<KeyType, DataType>* tmp = new TreeNode<KeyType, DataType>();
    tmp = NULL;
    if (key == _root->get_key()) {
        data = _root->get_data();
        return true;
    }

    tmp = _root;
    while (tmp != NULL) {
        if (key < tmp->get_key()) {
            tmp = tmp->get_left_child();
        } else if (key > tmp->get_key()) {
            tmp = tmp->get_right_child();
        } else if (key == tmp->get_key()) {
            data = tmp->get_data();
            return true;
        }
    }

    data = "";
    return false;
}

template <class KeyType, class DataType>
bool  BST<KeyType, DataType>::remove (KeyType key)
{
    if (!_root)
        return false;

    TreeNode<KeyType, DataType>* tmpPtr = _remove (key, _root);

    if (tmpPtr) {
        delete tmpPtr;
        return true;
    } else {
        return false;
    }
}

template <class KeyType, class DataType>
TreeNode<KeyType, DataType>*
BST<KeyType, DataType>::_remove(KeyType removeKey,
                                TreeNode<KeyType, DataType>*& _root)
{
    DataType max, tmpData;
    TreeNode<KeyType, DataType> *foundPtr, *maxPtr;
    KeyType  tmpKey;

    if (!_root)
        return NULL; // data not found

    if (removeKey < _root->get_key()) {
        TreeNode<KeyType, DataType>* result;
        result = _remove(removeKey, _root->left);
        return result;
    }

    if (removeKey > _root->get_key()) {
        return _remove (removeKey, _root->get_right_child());
    }

    if (removeKey == _root->get_key()) {
        foundPtr = _root;
        if (_root->get_left_child() == NULL && _root->get_right_child() == NULL) {
            // deleted TreeNode<KeyType, DataType> has no children
            _root = NULL;
            return foundPtr;
        } else if (_root->get_left_child() == NULL) {
            // no left child, has right child
            _root = _root->get_right_child();
            return foundPtr;
        } else if (_root->get_right_child() == NULL) {
            // no right child, has left child
            _root = _root->get_left_child();
            return foundPtr;
        } else {
            // TreeNode<KeyType, DataType> has left and right children
            maxPtr = _findMaxPtr(_root->get_left_child());
            // swap TreeNode<KeyType, DataType> data with max of left subtree data
            tmpData = maxPtr->get_data();    //  data that is being moved to _root
            maxPtr->set_data(foundPtr->get_data());  // data to be returned;
            foundPtr->set_data(tmpData);
            //  swap keys
            tmpKey = maxPtr->get_key();
            maxPtr->set_key(foundPtr->get_key());
            foundPtr->set_key(tmpKey);

            return _remove(removeKey, _root->get_left_child());
        }
    }
    return NULL;
}

template <class KeyType, class DataType>
TreeNode<KeyType, DataType>* BST<KeyType, DataType>::_findMaxPtr(TreeNode<KeyType, DataType>* _root)
{
    TreeNode<KeyType, DataType>*  maxPtr;

    if (!_root)
        return NULL;
    maxPtr = _root;
    while (maxPtr->get_right_child())
        maxPtr = maxPtr->get_right_child();
    return maxPtr;
}

template <class KeyType, class DataType>
void BST<KeyType, DataType>::traverse(TraverseType traverseType, void (*visit)(DataType))
{
    switch (traverseType) {
    case INFIX:
        _traverseInfix(_root, visit);
        break;
    case PREFIX:
        _traversePrefix(_root, visit);
        break;
    case POSTFIX:
        _traversePostfix(_root, visit);
        break;
    }
}

template <class KeyType, class DataType>
void  BST<KeyType, DataType>::_traversePrefix(TreeNode<KeyType, DataType>* _root, void (*visit)(DataType))
{
    if (!_root) {
        return;
    }

    visit(_root->get_data());
    _traversePrefix(_root->get_left_child(), visit);
    _traversePrefix(_root->get_right_child(), visit);
}

template <class KeyType, class DataType>
void  BST<KeyType, DataType>::_traverseInfix(TreeNode<KeyType, DataType>* _root, void (*visit)(DataType))
{
    if (!_root) {
        return;
    }

    _traverseInfix(_root->get_left_child(), visit);
    visit(_root->get_data());
    _traverseInfix(_root->get_right_child(), visit);
}

template <class KeyType, class DataType>
void  BST<KeyType, DataType>::_traversePostfix(TreeNode<KeyType, DataType>* _root, void (*visit)(DataType))
{
    if (!_root) {
        return;
    }

    _traverseInfix(_root->get_left_child(), visit);
    _traverseInfix(_root->get_right_child(), visit);
    visit(_root->get_data());
}

#endif
