#include "bst.cpp"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

std::string createData(const std::string phoneNumber,
        const std::string name,
        const std::string address)
{
    std::stringstream data;

    data.width(10);
    data << std::right << phoneNumber;
    data.width(15);
    data << std::right << name;
    data.width(30);
    data << std::right << address;

    return data.str();
}

long long convertStringToLL (std::string str)
{
    std::stringstream ss(str);
    long long num;
    if (!(ss >> num)) {
        std::cout << "Couldn't convert keyStream string to key long long." << std::endl;
        num = 0;
    }

    return num;
}

bool insertAddress(BST<long long, std::string> *bst,
        const std::vector<std::string> address)
{
    return bst->insert(convertStringToLL(address[0]),
            createData(address[0], address[1], address[2]));
}

bool writeAddress(BST<long long, std::string> *bst,
        const std::string phoneNumber,
        const std::string name,
        const std::string address)
{
    return bst->insert(convertStringToLL(phoneNumber),
            createData(phoneNumber, name, address));
}

int main()
{
    // Phone Number:Person:Address
    std::fstream phoneData ("phone.dat");
    std::string record;
    BST<long long, std::string> *bst = new BST<long long, std::string>();

    if (phoneData.is_open()) {
        while (phoneData.good()) {
            std::getline (phoneData, record);
            insertAddress (bst, split(record, ':'));
        }
    } else {
        std::cout << "Can't open file." << std::endl;
    }

    std::string menuEntry = "e";
    std::string phoneNumber, name, address, data;
    do {
        std::cout << std::endl << std::endl << "This is a menu!" << std::endl;
        std::cout << "(i)\tInsert a new record" << std::endl;
        std::cout << "(d)\tDelete an existing record" << std::endl;
        std::cout << "(f)\tFind a print a record" << std::endl;
        std::cout << "(t)\tTraverse tree" << std::endl;
        std::cout << "(e)\tEnd the program" << std::endl;
        std::getline (std::cin, menuEntry);

        if (menuEntry == "i") {
            std::cout << "Insertion! (hehe)" << std::endl;
            std::cout << "Phone Number (key): ";
            std::getline (std::cin, phoneNumber);

            std::cout << "Name: ";
            std::getline (std::cin, name);

            std::cout << "Address: ";
            std::getline (std::cin, address);

            writeAddress(bst, phoneNumber, name, address);
        }

        if (menuEntry == "f") {
            std::string foundData = "";
            std::cout << "Find phone number (key): ";
            std::getline (std::cin, phoneNumber);

            if (bst->retrieve (convertStringToLL(phoneNumber), foundData)) {
                std::cout << "Retrieved key: " << foundData << std::endl;
            } else {
                std::cout << "Nothing found for key: " << phoneNumber << std::endl;
            }
        }

        if (menuEntry == "d") {
            std::cout << "Delete phone number (key): ";
            std::getline (std::cin, phoneNumber);

            if (bst->remove (convertStringToLL(phoneNumber))) {
                std::cout << "Deleted key: " << phoneNumber;
            } else {
                std::cout << "Key not found in tree." << std::endl;
            }
        }

        if (menuEntry == "t") {
            void (*pf)(std::string) = &BST<int, std::string>::printNode;
            //std::cout << "PREFIX!" << std::endl;
            //bst->traverse(PREFIX, pf);
            //std::cout << std::endl;

            std::cout << "INFIX!" << std::endl;
            bst->traverse(INFIX, pf);
            std::cout << std::endl;

            //std::cout << "POSTFIX!" << std::endl;
            //bst->traverse(POSTFIX, pf);
            //std::cout << std::endl;;
        }

    } while (menuEntry != "e" && menuEntry != "E");

    delete bst;

    return 0;
}
