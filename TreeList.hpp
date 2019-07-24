#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <set>
#include <stdexcept>
#include <utility>
#include <stack>

template <typename T>
class TreeList {
    private: class Node;    //forward declaration
    public: class iterator; //forward declaration
    private: Node* root;    //head of TreeList

    public: TreeList ()
    {
        root = &Node::NULL_NODE;
    };

    public: TreeList (std::size_t len, const T &val = nullptr)
    {
        root = &Node::NULL_NODE;
        for (std::size_t i = 0; i < len; i++)       push_back(val);
    }

    public: ~TreeList ()
    {
        clear();
    }

    public: bool empty() const
    {
        return (root->size == 0);
    }

    public: std::size_t size() const
    {
        return root->size;
    }

    public: T &operator [] (std::size_t index)
    {
        if (index >= size())    throw std::out_of_range("Index is out of bounds");
        return root->getNodeAt(index)->data;
    }

    public: void push_back (const T &val)
    {
        insert(size(), val);
    }

    public: void pop_back ()
    {
        erase(size()-1);
    }

    public: void insert (std::size_t index, const T &val)
    {
        if (index > size())     throw std::out_of_range("Index is out of bounds");
        if (size() == SIZE_MAX) throw std::length_error("Maximum size for TreeList reached");
        root = root->insertAt(index, val);
    }

    public: void erase (std:: size_t index)
    {
        if (index >= size())    throw std::out_of_range("Index is out of bounds");
        Node* delNode = NULL;
        root = root->removeAt(index, &delNode);
        delete delNode;
    }

    public: void clear ()
    {
        if (root != &Node::NULL_NODE)
        {
            delete root;
            root = &Node::NULL_NODE;
        }
    }

    public: iterator begin() const
    {
        return iterator(root);
    }

    public: iterator end()  const
    {
        return iterator();
    }

    //unit tests
    public: void checkStructure () const
    {
        assert (root != NULL);
        std::set <const Node*> visited;
        root->checkStructure (visited);
    }

    private: class Node {
        public: static Node NULL_NODE;
        public: T data;
        public: int height;
        public: std::size_t size;
        public: Node* left;
        public: Node* right;

        public: Node()     //empty Node
        {
            height = 0;
            size = 0;
            left = NULL;
            right = NULL;
        }

        public: Node (const T &data)
        {
            this->data = data;
            height = 1;
            size = 1;
            left = &NULL_NODE;
            right = &NULL_NODE;
        }

        public: ~Node()
        {
            if (left != &NULL_NODE)   delete left;
            if (right != &NULL_NODE)  delete right;
        }

        public: Node* getNodeAt (std:: size_t index)
        {
            assert (index < size);      //to ensure that we have a valid index
            std:: size_t leftSize = left->size;
            if (index < leftSize)               return left->getNodeAt(index);
            else if (index > leftSize)          return right->getNodeAt(index-leftSize-1);
            else                                return this;
        }

        public: Node* insertAt (std::size_t index, const T& val)
        {
            assert (index <= size);
            if (this == &NULL_NODE)             return new Node(val);   //first node in the list
            std::size_t leftSize = left->size;
            if (index <= leftSize)              left = left->insertAt(index, val);
            else                                right = right->insertAt(index-leftSize-1, val);
            updateNode();
            return balancedTree();
        }

        public: Node* removeAt (std::size_t index, Node **delNode)
        {
            assert (index < size);
            std::size_t leftSize = left->size;
            if (index < leftSize)                   left = left->removeAt(index, delNode);
            else if (index > leftSize)              right = right->removeAt(index-leftSize-1, delNode);
            else if (left == &NULL_NODE && right == &NULL_NODE)
            {
                assert (*delNode == NULL);
                *delNode = this;
                return &NULL_NODE;
            }
            else if (left != &NULL_NODE && right == &NULL_NODE)
            {
                Node* resNode = left;
                left = NULL;
                assert(*delNode == NULL);
                *delNode = this;
                return resNode;
            }
            else if (left == &NULL_NODE && right != &NULL_NODE)
            {
                Node* resNode = right;
                right = NULL;
                assert(*delNode == NULL);
                *delNode = this;
                return resNode;
            }
            else
            {
                Node* suc = right;
                while (suc->left != &NULL_NODE)     suc = suc->left;
                data = suc->data;
                right = right->removeAt(0, delNode);
            }
            updateNode();
            return balancedTree();
        }

        //balances the subtree and returns the new Head of balanced subtree(balancedNode)
        private: Node* balancedTree ()
        {
            int bal = getBalance();
            assert (std::abs(bal) <= 2);
            Node* balancedNode = this;
            if (bal == 2)
            {
                assert (std::abs(right->getBalance()) <= 1);
                if (right->getBalance() == -1)      right = right->rotateRight();
                balancedNode = rotateLeft();
            }
            else if (bal == -2)
            {
                assert (std::abs(left->getBalance()) <= 1);
                if (left->getBalance() == 1)        left = left->rotateLeft();
                balancedNode = rotateRight();
            }
            assert (std::abs(balancedNode->getBalance()) <= 1);
            return balancedNode;
        }

        private: Node* rotateRight()
        {
            assert (left != &NULL_NODE);
            Node* newHead = this->left;
            this->left = newHead->right;
            newHead->right = this;
            this->updateNode();
            newHead->updateNode();
            return newHead;
        }

        private: Node* rotateLeft()
        {
            assert (right != &NULL_NODE);
            Node *newHead = this->right;
			this->right = newHead->left;
			newHead->left = this;
			this->updateNode();
			newHead->updateNode();
			return newHead;
        }

        //updates height and size values
        private : void updateNode ()
        {
            assert (this != &NULL_NODE);
            assert (left->height >= 0 && right->height >= 0);
            assert (left->size >= 0 && right->size >= 0);
            height = std::max(left->height, right->height) + 1;
            size = left->size + right->size + 1;
            assert (height >= 0 && size >= 0);
        }

        private : int getBalance () const
        {
            return (right->height - left->height);
        }

        //unit test
        public: void checkStructure (std::set <const Node*> &visitedNodes) const
        {
            if (this == &NULL_NODE)     return;

            if (visitedNodes.find(this) != visitedNodes.end())  //node already in set (already visited)
            {
                throw std::logic_error("TreeList structure violated: Not a tree");
            }
            visitedNodes.insert(this);
            left->checkStructure(visitedNodes);
            right->checkStructure(visitedNodes);

            if (height != std::max(left->height, right->height) + 1)
            {
                throw std::logic_error("TreeList structure violated: Incorrect height");
            }
            if (size != left->size + right->size + 1)
            {
                throw std::logic_error("TreeList structure violated: Incorrect size");
            }
            if (std::abs(getBalance()) > 1)
            {
                throw std::logic_error("TreeList structure violated: Tree Not Balanced");
            }
        }
    };

    public: class iterator {
        private: std::stack <Node*> pathStack;
        private: Node* root;

        public: iterator ()             //used to invoke end()function
        {
            while (!pathStack.empty())  pathStack.pop();
            root = &Node::NULL_NODE;
        }

        public: iterator (Node* node)   //used to invoke start() function
        {
            while (!pathStack.empty())  pathStack.pop();
            while (node != &Node::NULL_NODE)
            {
                pathStack.push(node);
                node = node->left;
            }
            if (pathStack.empty())          throw std::underflow_error("Not a valid initialization");
            this->root = pathStack.top();
            pathStack.pop();
        }

        public: const bool operator != (iterator other)
        {
            return this->root != other.root;
        }

        public: const T &operator * ()
        {
            if (root == &Node::NULL_NODE)   throw std::out_of_range("Iterator does not point to a valid entry");
            return root->data;
        }

        public: const iterator &operator ++ ()
        {
            assert (root != &Node::NULL_NODE);
            if (root->right != &Node::NULL_NODE)
            {
                root = root->right;
                while (root != &Node::NULL_NODE)
                {
                    pathStack.push(root);
                    root = root->left;
                }
            }
            if (pathStack.empty())              //return end()
            {
                this->root = &Node::NULL_NODE;
                return *this;
            }
            else                                //return next element
            {
                this->root = pathStack.top();
                pathStack.pop();
                return *this;                   //* has been overloaded
            }
        }
    };
};

template <typename T>
typename TreeList<T>::Node TreeList<T>::Node::NULL_NODE;
