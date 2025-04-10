//Martyna Cios

class BRANCH_CLASS;

class FRUIT_CLASS {
    unsigned int weight;
    unsigned int length;
    FRUIT_CLASS* next;
    FRUIT_CLASS* prev;
    BRANCH_CLASS* frBranch;

public:
    FRUIT_CLASS();
    FRUIT_CLASS( const FRUIT_CLASS& );
    FRUIT_CLASS( unsigned int, BRANCH_CLASS* );
    ~FRUIT_CLASS();

    unsigned int getLength();
    unsigned int getWeight();
    void growthFruit();
    void fadeFruit();
    void pluckFruit();
    BRANCH_CLASS* getBranchPointer();

    void setBranch ( BRANCH_CLASS* );
    FRUIT_CLASS* getNext();
    FRUIT_CLASS* getPrev();
    void setNext( FRUIT_CLASS* );
    void setPrev( FRUIT_CLASS* );

};
