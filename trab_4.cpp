#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

typedef string TreeEntry;

class BinarySearchTree {
  public:
    BinarySearchTree() : root(nullptr) {}
    void searchInsert(TreeEntry x);
    int altura();
    int folhas();
    int diff();
    int total();
    int comparacoes();

  private:
    struct TreeNode;

    typedef TreeNode *TreePointer;

    struct TreeNode {
        TreeEntry entry;
        int count;
        TreePointer leftNode, rightNode;
    };

    TreePointer root;
    int comp = 0;           // n comparações
    int differentWords = 0; // n de palavras diferentes
    int h = 0;              // altura
    int totalCount = 0;     // n palavras total
    void searchInsert(TreeEntry x, TreePointer &t, int &sentinelMoves);
    int folhas(TreePointer &t);
};

void BinarySearchTree::searchInsert(TreeEntry x) {
    int sentinelMoves = 0;
    searchInsert(x, root, sentinelMoves);
}

void BinarySearchTree::searchInsert(TreeEntry x, TreePointer &t,
                                    int &sentinelMoves) {
    TreePointer sentinel;
    if (t == NULL) {
        t = new TreeNode;
        t->entry = x;
        t->count = 1;
        t->leftNode = t->rightNode = NULL;
        differentWords++;
        totalCount++;
        if (sentinelMoves > h) {
            h++; // a quantidade de movimentos da sentinela será
                 // igual à altura em relação ao TreeNode
                 // adicionado assim, ao inserir uma nova palavra
                 // em uma altura menor ou igual que a da árvore
                 // atual, h não aumentará pois a sentinela não se
                 // moverá mais vezes que a altura atual da raiz,
                 // apenas ao fazer uma inserção de altura maior.
        }
        return;
    }

    if (x < t->entry) {
        sentinel = t;
        sentinelMoves++;
        comp++;
        searchInsert(x, t->leftNode, sentinelMoves);
        return;
    }

    if (x > t->entry) {
        comp++;
        sentinel = t;
        sentinelMoves++;
        searchInsert(x, t->rightNode, sentinelMoves);
        return;
    }

    comp++;
    t->count++;
    totalCount++;
}

int BinarySearchTree::altura() { return h; }

int BinarySearchTree::folhas() { return folhas(root); }

int BinarySearchTree::folhas(TreePointer &t) {
    int n = 0;
    if (t->leftNode == NULL && t->rightNode == NULL) {
        n++;
    } else {
        folhas(t->leftNode);
        folhas(t->rightNode);
    }
    return n;
}

int BinarySearchTree::comparacoes() { return comp; }

int BinarySearchTree::diff() { return differentWords; }
int BinarySearchTree::total() { return totalCount; }

class AVLTree {

  public:
    AVLTree() : root(nullptr) {}
    void searchInsert(TreeEntry x);
    int altura();
    int folhas();
    int diff();
    int total();
    int comparacoes();

  private:
    struct TreeNode;

    typedef TreeNode *TreePointer;

    struct TreeNode {
        TreeEntry entry;
        int count;
        int bal;
        TreePointer leftNode, rightNode;
    };

    TreePointer root;
    int comp = 0;           // n comparações
    int differentWords = 0; // n de palavras diferentes
    int height = 0;         // altura
    int totalCount = 0;
    int rot = 0;
    void searchInsert(TreeEntry x, TreePointer &pA, bool &h);
    int folhas(TreePointer &t);
};

void AVLTree::searchInsert(TreeEntry x) {
    bool h = false;
    searchInsert(x, root, h);
}

void AVLTree::searchInsert(TreeEntry x, TreePointer &pA, bool &h) {
    TreePointer pB, pC;
    TreePointer sentinel;
    int sentinelMoves = 0;

    if (pA == NULL) {
        pA = new TreeNode;
        h = true;
        pA->entry = x;
        pA->count = 1;
        pA->leftNode = pA->rightNode = NULL;
        pA->bal = 0;
        differentWords++;
        totalCount++;
        return;
    }

    if (x < pA->entry) {
        sentinel = pA;
        sentinelMoves++;
        comp++;
        searchInsert(x, pA->leftNode, h);
        if (h) {
            switch (pA->bal) {
            case -1:
                pA->bal = 0;
                h = false;
                break;

            case 0:
                pA->bal = 1;
                break;

            case 1:
                pB = pA->leftNode;
                if (pB->bal == 1) {
                    pA->leftNode = pB->rightNode;
                    pB->rightNode = pA;
                    pA->bal = 0;
                    pA = pB;

                } else {
                    pC = pB->rightNode;
                    pB->rightNode = pC->leftNode;
                    pC->leftNode = pB;
                    pA->leftNode = pC->rightNode;
                    pC->rightNode = pA;
                    if (pC->bal == 1) {
                        pA->bal = -1;
                    } else {
                        pA->bal = 0;
                    }

                    if (pC->bal == -1) {
                        pA->bal = +1;
                    } else {
                        pB->bal = 0;
                    }

                    pA = pC;
                }
                pA->bal = 0;
                h = false;
                sentinelMoves--;
                rot++;
            }
        }
    } else {
        if (x > pA->entry) {
            sentinel = pA;
            sentinelMoves++;
            comp++;
            searchInsert(x, pA->rightNode, h);
            if (h) {
                switch (pA->bal) {
                case 1:
                    pA->bal = 0;
                    h = false;
                    break;

                case 0:
                    pA->bal = -1;
                    break;

                case -1:
                    pB = pA->rightNode;
                    if (pB->bal == -1) {
                        pA->rightNode = pB->leftNode;
                        pB->leftNode = pA;
                        pA->bal = 0;
                        pA = pB;
                    } else {
                        pC = pB->leftNode;
                        pB->leftNode = pC->rightNode;
                        pC->rightNode = pB;
                        pA->rightNode = pC->leftNode;
                        pC->leftNode = pA;
                        if (pC->bal == -1) {
                            pA->bal = 1;
                        } else {
                            pA->bal = 0;
                        }
                        if (pC->bal == +1) {
                            pB->bal = -1;
                        } else {
                            pB->bal = 0;
                        }
                        pA = pC;
                    }
                    rot++;
                    sentinelMoves--;
                    pA->bal = 0;
                    h = false;
                }
            }
        } else {
            pA->count++;
        }
    }
    if (sentinelMoves > height) {
        height++;
    }
}

int AVLTree::altura() { return height; }

int AVLTree::folhas() { return folhas(root); }

int AVLTree::folhas(TreePointer &t) {
    int n = 0;
    if (t->leftNode == NULL && t->rightNode == NULL) {
        n++;
    } else {
        folhas(t->leftNode);
        folhas(t->rightNode);
    }
    return n;
}

int AVLTree::diff() { return differentWords; }
int AVLTree::total() { return totalCount; }
int AVLTree::comparacoes() { return comp; }

void die(const string &msg) {
    cout << msg << ": Oops!\n";
    exit(1);
}

template <typename Entry> class AVL {
  public:
    void searchInsert(Entry val) {
        root = searchInsert(root, val);
        totalWords++;
    }
    int altura() {
        if (root) {
            return root->height - 1;
        }
        return -1;
    }
    int diff() { return count; }
    int comparacoes() { return comps; }
    int total() { return totalWords; }

    void print() {
        print(root, 0);
        cout << "\n-----------------------------------\n\n";
    }

  private:
    struct AVLNode {
        Entry val;
        int height = 1;
        AVLNode *left = nullptr;
        AVLNode *right = nullptr;
        void updateHeight() {
            height = 1;
            if (left && left->height + 1 > height) {
                height = left->height + 1;
            }
            if (right && right->height + 1 > height) {
                height = right->height + 1;
            }
        }
    };

    AVLNode *root = nullptr;
    int count = 0;
    int comps = 0;
    int totalWords = 0;

    void print(AVLNode *root, int depth) {
        if (!root) {
            return;
        }
        print(root->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            cout << "    ";
        }
        cout << root->val << endl;
        print(root->left, depth + 1);
    }
    AVLNode *leftRotate(AVLNode *root) {
        if (!root) {
            die("leftRotate");
        }
        if (!root->right) {
            die("leftRotate");
        }
        AVLNode *newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;
        root->updateHeight();
        return newRoot;
    }
    AVLNode *rightRotate(AVLNode *root) {
        if (!root) {
            die("rightRotate");
        }
        if (!root->left) {
            die("rightRotate");
        }
        AVLNode *newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
        root->updateHeight();
        return newRoot;
    }
    AVLNode *leftRightRotate(AVLNode *root) {
        if (!root->left) {
            die("leftRightRotate");
        }
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    AVLNode *rightLeftRotate(AVLNode *root) {
        if (!root->right) {
            die("rightRotate");
        }
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    int balanceFactor(AVLNode *root) {
        if (!root) {
            return 0;
        }
        int left = 0;
        int right = 0;
        if (root->left) {
            left = root->left->height;
        }
        if (root->right) {
            right = root->right->height;
        }
        return left - right;
    }
    AVLNode *searchInsert(AVLNode *root, Entry val) {
        if (!root) {
            count++;
            root = new AVLNode;
            root->val = val;
            return root;
        }
        comps++;
        if (root->val == val) {
            return root;
        }
        comps++;
        if (root->val > val) {
            root->left = searchInsert(root->left, val);
            root->updateHeight();
        } else {
            root->right = searchInsert(root->right, val);
            root->updateHeight();
        }
        int bf = balanceFactor(root);
        if (bf > 1) {
            if (balanceFactor(root->left) > 0) {
                root = rightRotate(root);
            } else {
                root = leftRightRotate(root);
            }
        } else if (bf < -1) {
            if (balanceFactor(root->right) < 0) {
                root = leftRotate(root);
            } else {
                root = rightLeftRotate(root);
            }
        }
        return root;
    }
};

int main() {
    BinarySearchTree bst;
    AVL<string> avl;
    std::string word;
    ifstream theInput("mam-na-np-lo.txt");
    // ler cada palavra do arquivo e inserir na ABB e na AVL
    while (theInput >> word) {
        bst.searchInsert(word);
        avl.searchInsert(word);
    }
    theInput.close();
    ofstream theOutput("Info_ABB.txt");
    theOutput << "Palavras distintas " << bst.diff()
              << " // Número total de palavras: " << bst.total()
              << " // Altura: " << bst.altura()
              << " // Comparacoes: " << bst.comparacoes() << endl;
    theOutput.close();
    theOutput.open("Info_AVL.txt");
    theOutput << "Palavras distintas " << avl.diff()
              << " // Número total de palavras: " << avl.total()
              << " // Altura: " << avl.altura()
              << " // Comparacoes: " << avl.comparacoes() << endl;
    theOutput.close();
    return 0;
}
