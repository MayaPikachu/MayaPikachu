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
    void searchInsert(TreeEntry x, TreePointer &t);
    int folhas(TreePointer &t);
};

void BinarySearchTree::searchInsert(TreeEntry x) { searchInsert(x, root); }

void BinarySearchTree::searchInsert(TreeEntry x, TreePointer &t) {
    TreePointer sentinel;
    int sentinelMoves = 0;
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

    } else {
        if (x < t->entry) {
            sentinel = t;
            sentinelMoves++;
            comp++;
            searchInsert(x, t->leftNode);
        } else {
            if (x > t->entry) {
                comp++;
                sentinel = t;
                sentinelMoves++;
                searchInsert(x, t->rightNode);
            } else {
                comp++;
                t->count++;
                totalCount++;
            }
        }
    }
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
    }

    else {
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

int main() {
    BinarySearchTree bst;
    AVLTree avl;
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
    return 0;
}
