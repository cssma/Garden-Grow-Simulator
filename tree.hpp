//Martyna Cios

class GARDEN_CLASS;
class BRANCH_CLASS;

class TREE_CLASS {
    unsigned int number;
    unsigned int height;
    unsigned int treeFruitsAmount;
    unsigned int fruitsWght;
    unsigned int branchesAmount;
    TREE_CLASS* next;
    TREE_CLASS* prev;
    BRANCH_CLASS* first;
    BRANCH_CLASS* last ;
    GARDEN_CLASS* trGarden;

public:
    TREE_CLASS();
    TREE_CLASS( const TREE_CLASS& );
    TREE_CLASS( unsigned int, GARDEN_CLASS* );
    ~TREE_CLASS();

    unsigned int getBranchesTotal();
    unsigned int getFruitsTotal();
    unsigned int getWeightsTotal();
    unsigned int getNumber();
    unsigned int getHeight();
    void growthTree();
    void fadeTree();
    void harvestTree( unsigned int );
    void cutTree( unsigned int );
    void cloneBranch( BRANCH_CLASS* );
    GARDEN_CLASS* getGardenPointer();
    BRANCH_CLASS* getBranchPointer( unsigned int );

    void setNumber ( unsigned int );
    void setGarden ( GARDEN_CLASS* );
    unsigned int getNum();
    void addFruits( unsigned int );
    void subtractFruits( unsigned int );
    void addBranches( unsigned int );
    void subtractBranches ( unsigned int );
    void addWeight( unsigned int );
    void subtractWeight( unsigned int );
    void setNext( TREE_CLASS* );
    void setPrev( TREE_CLASS* );
    void setFirst( BRANCH_CLASS* );
    void setLast( BRANCH_CLASS* );
    TREE_CLASS* getNext();
    TREE_CLASS* getPrev();
    BRANCH_CLASS* getFirst();
    BRANCH_CLASS* getLast();
    GARDEN_CLASS* getGarden();

};

