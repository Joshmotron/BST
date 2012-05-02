#include "bst.cpp"

int main() {
    TreeNode<int, std::string> *node = new TreeNode<int, std::string>();
    node->set_data("Foo");
    node->set_key(213);
    node->set_left_child(NULL);
    node->set_right_child(NULL);

    std::cout << "key: " << node->get_key() << std::endl;
    std::cout << "data: " << node->get_data() << std::endl;

    TreeNode<int, std::string> *lnode = new TreeNode<int, std::string>();
    TreeNode<int, std::string> *rnode = new TreeNode<int, std::string>();

    node->set_left_child(lnode);
    node->set_right_child(rnode);

    node->get_left_child()->set_key(999);
    node->get_left_child()->set_data("Josh");

    node->get_right_child()->set_key(1000);
    node->get_right_child()->set_data("FOO");

    std::cout << "key: " << node->get_left_child()->get_key() << std::endl;
    std::cout << "data: " << node->get_left_child()->get_data() << std::endl;
    std::cout << "key: " << node->get_right_child()->get_key() << std::endl;
    std::cout << "data: " << node->get_right_child()->get_data() << std::endl;

    BST<int, std::string> *bst = new BST<int, std::string>();
    bst->insert(node->get_key(), node->get_data());
    bst->insert(rnode->get_key(), rnode->get_data());
    bst->insert(lnode->get_key(), lnode->get_data());

    void (*pf)(std::string) = BST<int, std::string>::printNode;
    bst->traverse(INFIX, pf);

    std::string data;
    bst->retrieve(rnode->get_key(), data);
    std::cout << "Retrieved: " << rnode->get_key() << std::endl;

    delete bst;
    return 0;
}
