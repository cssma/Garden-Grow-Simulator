//Martyna Cios
#include <iostream>
#include "tree.hpp"
#include "garden.hpp"
#include "branch.hpp"

TREE_CLASS::TREE_CLASS() : number(0), height(0), treeFruitsAmount(0), fruitsWght(0), branchesAmount(0), next(NULL), prev(NULL), first(NULL), last(NULL), trGarden(NULL) {}

TREE_CLASS::TREE_CLASS( const TREE_CLASS& otherTree ) {
    next = prev = NULL;
    trGarden = NULL;
    number = otherTree.number;
    height = otherTree.height;
    treeFruitsAmount = otherTree.treeFruitsAmount;
    fruitsWght = otherTree.fruitsWght;
    branchesAmount = otherTree.branchesAmount;

    if ( otherTree.first == NULL ) {
        first = last = NULL;
        return;
    }

    BRANCH_CLASS* srcBranch = otherTree.first;
    BRANCH_CLASS* lastBranchCopy = new BRANCH_CLASS( *srcBranch );
    lastBranchCopy->setTree( this );
    lastBranchCopy->setHeight(srcBranch->getHeight() );
    first = lastBranchCopy;

    while ( srcBranch = srcBranch->getNext() ) {
        BRANCH_CLASS* newBranchCopy = new BRANCH_CLASS( *srcBranch );
        newBranchCopy->setTree( this );
        newBranchCopy->setHeight( srcBranch->getHeight() );

        lastBranchCopy->setNext( newBranchCopy );
        newBranchCopy->setPrev( lastBranchCopy );

        lastBranchCopy = newBranchCopy;
    }
    last = lastBranchCopy;
}

TREE_CLASS::TREE_CLASS( unsigned int number, GARDEN_CLASS *ptr )
        : number(number), trGarden(ptr), height(0),
          treeFruitsAmount(0), fruitsWght(0), branchesAmount(0),
          next(NULL), prev(NULL), first(NULL), last(NULL) {
    if ( trGarden ) {
        trGarden->addTrees( 1 );
    }
}

TREE_CLASS::~TREE_CLASS() {
    while(first) {
        BRANCH_CLASS* current = first;
        first = first->getNext();
        delete current;
    }

    last = NULL;

    if(trGarden) {
        trGarden->subtractTrees(1);

        if (this == trGarden->getFirst()) {
            trGarden->setFirst(this->getNext());

            if (this == trGarden->getLast()) {
                trGarden->setLast(NULL);
            } else {
                trGarden->getFirst()->setPrev(NULL);
            }
            return;
        }

        else if (this == trGarden->getLast()) {
            trGarden->setLast(this->getPrev());
            trGarden->getLast()->setNext(NULL);
            return;
        }
    }

    if (this->getPrev()) {
        this->getPrev()->setNext(this->getNext());
    }
    if (this->getNext()) {
        this->getNext()->setPrev(this->getPrev());
    }
}

unsigned int TREE_CLASS::getBranchesTotal ()
{
    return branchesAmount;
}

unsigned int TREE_CLASS::getFruitsTotal ()
{
    return treeFruitsAmount;
}

unsigned int TREE_CLASS::getWeightsTotal ()
{
    return fruitsWght;
}

unsigned int TREE_CLASS::getNumber ()
{
    return number;
}

unsigned int TREE_CLASS::getHeight ()
{
    return height;
}

void TREE_CLASS::growthTree() {
    BRANCH_CLASS* previous = NULL;
    for ( BRANCH_CLASS* iterator = first; iterator; iterator = iterator->getNext() ){
        iterator->growthBranch();
        previous = iterator;
    }

    ++height;

    if ( height % 3 == 0 && height > 0 ) {
        if( first ) {
            last = new BRANCH_CLASS( height, this );
            last->setNext( NULL );
            last->setPrev( previous );
            previous->setNext( last );
        } else {
            first = new BRANCH_CLASS( height, this );
            first->setNext( NULL );
            first->setPrev( NULL );
            last = first;
        }
    }
}

void TREE_CLASS::fadeTree () {
    if ( height > 0 ) {
        this->cutTree( height - 1 );

        BRANCH_CLASS* pointer = first;
        while ( pointer ) {
            pointer->fadeBranch();
            pointer = pointer->getNext();
        }
    }
}

void TREE_CLASS::harvestTree ( unsigned int minWght ) {
    BRANCH_CLASS* pointer= first;

    while( pointer ) {
        pointer->harvestBranch( minWght );
        pointer=pointer->getNext();
    }
}

void TREE_CLASS::cutTree( unsigned int hig ) {

    BRANCH_CLASS* pointer_branch = first;
    BRANCH_CLASS* previ = NULL;
    bool finish_cycling = false;

    if ( hig < height ) {
        while (pointer_branch != NULL && !finish_cycling) {
            if (pointer_branch->getHeight() > hig) {
                while (pointer_branch) {
                    previ = pointer_branch;
                    pointer_branch = pointer_branch->getNext();
                    delete previ;

                    if (pointer_branch == NULL) {
                        height = hig;
                        finish_cycling = true;
                        break;
                    }
                }
            } else {
                pointer_branch = pointer_branch->getNext();
            }
        }
        if (!finish_cycling) {
            height = hig;
        }
    }
}

void TREE_CLASS::cloneBranch( BRANCH_CLASS* branchToClone ) {
    if ( branchToClone ) {
        BRANCH_CLASS* pointer = first;
        BRANCH_CLASS* prevBranch = NULL;

        while (pointer) {
            if (pointer->getLength() == 0) {
                BRANCH_CLASS* newBranch = new BRANCH_CLASS(*branchToClone);
                newBranch->setTree(this);
                newBranch->setHeight(pointer->getHeight());
                newBranch->setNext(pointer->getNext());
                newBranch->setPrev(prevBranch);
                delete pointer;

                if (prevBranch == NULL) {
                    first = newBranch;
                } else {
                    prevBranch->setNext(newBranch);
                }

                if (newBranch->getNext() == NULL) {
                    last = newBranch;
                } else {
                    newBranch->getNext()->setPrev(newBranch);
                }
                branchesAmount++;
                fruitsWght += newBranch->getWeightsTotal();
                treeFruitsAmount += newBranch->getFruitsTotal();

                GARDEN_CLASS* garden = this->trGarden;
                if (garden) {
                    garden->addBranches(1);
                    garden->addFruits(branchToClone->getFruitsTotal());
                    garden->addWeight(branchToClone->getWeightsTotal());
                }
                break;
            } else {
                prevBranch = pointer;
                pointer = pointer->getNext();
            }
        }
    }
}

GARDEN_CLASS* TREE_CLASS::getGardenPointer() {
    return trGarden;
}

BRANCH_CLASS* TREE_CLASS::getBranchPointer(unsigned int x) {

    BRANCH_CLASS* pointer_branch=first;

    if (branchesAmount==0) {
        return NULL;
    }
    if (last) {
        if ( x>last->getHeight()||x%3!=0||x<first->getHeight() ) {
            return NULL;
        }
        while ( pointer_branch ) {
            if(pointer_branch->getHeight() == x) {
                return pointer_branch;
            }
            pointer_branch = pointer_branch->getNext();
        }
    }
    return NULL;
}

void TREE_CLASS::setNumber ( unsigned int nr ) {
    number = nr;
}

void TREE_CLASS::setGarden ( GARDEN_CLASS* grdn ) {
    trGarden = grdn;
}

BRANCH_CLASS* TREE_CLASS::getFirst() {
    return first;
}

BRANCH_CLASS* TREE_CLASS::getLast() {
    return last;
}
void TREE_CLASS::setFirst( BRANCH_CLASS* first ) {
    this->first = first;
}

void TREE_CLASS::setLast( BRANCH_CLASS* last ) {
    this->last = last;
}

void TREE_CLASS::addFruits( unsigned int amount ) {
    treeFruitsAmount += amount;
}
void TREE_CLASS::subtractFruits( unsigned int amount ) {
    treeFruitsAmount -= amount;
}
void TREE_CLASS::addBranches( unsigned int amount ) {
    branchesAmount += amount;
}
void TREE_CLASS::subtractBranches( unsigned int amount ) {
    branchesAmount -= amount;
}
void TREE_CLASS::addWeight( unsigned int amount ) {
    fruitsWght += amount;
}
void TREE_CLASS::subtractWeight( unsigned int amount ) {
    fruitsWght -= amount;
}
unsigned int TREE_CLASS::getNum() {
    return number;
}

void TREE_CLASS::setNext( TREE_CLASS* nextTree ) {
    this->next = nextTree;
}
void TREE_CLASS::setPrev( TREE_CLASS* prevTree ) {
    this->prev = prevTree;
}
GARDEN_CLASS* TREE_CLASS::getGarden() {
    return trGarden;
}

TREE_CLASS* TREE_CLASS::getNext() {
    return next;
}
TREE_CLASS* TREE_CLASS::getPrev() {
    return prev;
}


