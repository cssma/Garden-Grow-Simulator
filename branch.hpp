//Martyna Cios

#include "iostream"

class TREE_CLASS;
class FRUIT_CLASS;

class BRANCH_CLASS {
    unsigned int length;
    unsigned int fruitsAmount;
    unsigned int fruitsWeight;
    unsigned int height;
    BRANCH_CLASS* next;
    BRANCH_CLASS* prev;
    FRUIT_CLASS* first;
    FRUIT_CLASS* last;
    TREE_CLASS* brTree;

public:
    BRANCH_CLASS();
    BRANCH_CLASS( const BRANCH_CLASS& );
    BRANCH_CLASS( unsigned int, TREE_CLASS* );
    ~BRANCH_CLASS();

    unsigned int getFruitsTotal();
    unsigned int getWeightsTotal();
    unsigned int getHeight();
    unsigned int getLength();
    void growthBranch();
    void fadeBranch();
    void harvestBranch( unsigned int );
    void cutBranch( unsigned int );
    FRUIT_CLASS* getFruitPointer( unsigned int );
    TREE_CLASS* getTreePointer();

    void createAndAddFruit();
    void setTree ( TREE_CLASS* );
    void setHeight ( unsigned int x );
    TREE_CLASS* getTree();
    BRANCH_CLASS* getNext();
    BRANCH_CLASS* getPrev();
    FRUIT_CLASS* getFirst();
    FRUIT_CLASS* getLast();
    void setNext( BRANCH_CLASS* );
    void setPrev ( BRANCH_CLASS* );
    void setFirst( FRUIT_CLASS* );
    void setLast( FRUIT_CLASS* );
    void addWeight( unsigned int );
    void subtractWeight( unsigned int );
    void addFruits( unsigned int );
    void subtractFruits( unsigned int );

};
