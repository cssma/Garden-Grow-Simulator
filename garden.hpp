//Martyna Cios

class TREE_CLASS;

class GARDEN_CLASS {
    TREE_CLASS* first;
    TREE_CLASS* last;
    unsigned int treesAmount;
    unsigned int branchesAmount;
    unsigned int fruitsAmount;
    unsigned int theWeight;

public:
    GARDEN_CLASS();
    ~GARDEN_CLASS();

    unsigned int getTreesTotal();
    unsigned int getBranchesTotal();
    unsigned int getFruitsTotal();
    unsigned int getWeightsTotal();
    void plantTree();
    void extractTree( unsigned int );
    void growthGarden();
    void fadeGarden();
    void harvestGarden( unsigned int );
    TREE_CLASS* getTreePointer( unsigned int );
    void cloneTree( unsigned int );

    void growth_helper( TREE_CLASS* );
    void fade_helper( TREE_CLASS* );
    void harvest_helper( TREE_CLASS*, unsigned int );
    void setLast(  TREE_CLASS* x);
    void addFruits ( int );
    void subtractFruits ( int );
    void addBranches ( int );
    void subtractBranches ( int );
    void addWeight ( int );
    void subtractWeight ( int );
    void addTrees ( int );
    void subtractTrees ( int );
    TREE_CLASS* getFirst();
    TREE_CLASS* getLast();
    void setFirst( TREE_CLASS* );

};



