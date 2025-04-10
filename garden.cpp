//Martyna Cios
#include <iostream>
#include "garden.hpp"
#include "tree.hpp"

GARDEN_CLASS::GARDEN_CLASS() : theWeight(0), treesAmount(0), branchesAmount(0), fruitsAmount(0), first(NULL), last(NULL) {}

GARDEN_CLASS::~GARDEN_CLASS() {
    TREE_CLASS* current=first;
    while(current) {
        TREE_CLASS* toDelete = current;
        current = current->getNext();
        delete toDelete;
    }
    first = last = NULL;
}

unsigned int GARDEN_CLASS::getTreesTotal() {
    return treesAmount ;
}

unsigned int GARDEN_CLASS::getBranchesTotal() {
    return branchesAmount ;
}

unsigned int GARDEN_CLASS::getFruitsTotal() {
    return fruitsAmount ;
}

unsigned int GARDEN_CLASS::getWeightsTotal() {
    return theWeight ;
}
void GARDEN_CLASS::plantTree()
{
    TREE_CLASS* helper;
    TREE_CLASS* secondHelper = first;
    TREE_CLASS* thirdHelper;
    TREE_CLASS* currentTree = first;
    int treeCounter = 0;

    if (treesAmount == 0) {
        thirdHelper = new TREE_CLASS(0, this);
        last = thirdHelper;
        first = thirdHelper;
        thirdHelper->setNext(NULL);
        thirdHelper->setPrev(NULL);

    } else if (last && treesAmount == (last->getNumber() + 1)) {
        helper = new TREE_CLASS((last->getNumber() + 1), this);
        last->setNext(helper);
        helper->setPrev(last);
        last = helper;

    } else {
        while (currentTree) {
            if (currentTree->getNumber() != treeCounter)
                break;
            secondHelper = currentTree;
            currentTree = currentTree->getNext();
            treeCounter++;
        }

        if (!treeCounter) {
            currentTree = new TREE_CLASS(0, this);
            currentTree->setNext(first);
            first->setPrev(currentTree);
            first = currentTree;

        } else {
            TREE_CLASS* nextTree = secondHelper->getNext();
            currentTree = new TREE_CLASS(secondHelper->getNumber() + 1, this);
            currentTree->setNext(nextTree);
            currentTree->setPrev(secondHelper);
            secondHelper->setNext(currentTree);
            if(nextTree) nextTree->setPrev(currentTree);
        }
    }
}

void GARDEN_CLASS::extractTree(unsigned int treeNum ) {
    if (!(treesAmount == 0 || treeNum > last->getNumber() || treeNum < first->getNumber()))
    {

        TREE_CLASS *pointer = last;
        while (pointer) {
            if (pointer->getNumber() == treeNum) {
                if (pointer->getPrev()) pointer->getPrev()->setNext(pointer->getNext());
                else first = pointer->getNext();
                if (pointer->getNext()) pointer->getNext()->setPrev(pointer->getPrev());
                else last = pointer->getPrev();

                delete pointer;
                return;
            }
            pointer = pointer->getPrev();
        }
    }
}

void GARDEN_CLASS::growth_helper( TREE_CLASS* pointer ){
    if ( pointer ) {
        pointer->growthTree();
        growth_helper( pointer->getNext() );
    }
}

void GARDEN_CLASS::growthGarden() {
    growth_helper( first );
}

void GARDEN_CLASS::fade_helper( TREE_CLASS* pointer ){
    if ( pointer ) {
        pointer->fadeTree();
        fade_helper( pointer->getNext() );
    }
}

void GARDEN_CLASS::fadeGarden() {
    fade_helper( first );
}

void GARDEN_CLASS::harvest_helper( TREE_CLASS* pointer, unsigned int minWght ){
    if( pointer ){
        pointer->harvestTree( minWght );
        harvest_helper( pointer->getNext(), minWght );
    }
}

void GARDEN_CLASS::harvestGarden( unsigned int minWght ) {
    harvest_helper( first, minWght );
}

TREE_CLASS* GARDEN_CLASS::getTreePointer( unsigned int nr ) {
    TREE_CLASS* pointer = NULL;

    if (last && treesAmount > 0 && nr >= first->getNumber() && nr <= last->getNumber()) {
        pointer = first;

        while ( pointer && pointer->getNum() <= nr ) {
            if ( pointer->getNum() == nr ) {
                break;
            }
            pointer = pointer->getNext();
        }

        if ( pointer && pointer->getNum() != nr ) {
            pointer = NULL;
        }
    }
    return pointer;
}

void GARDEN_CLASS::cloneTree(unsigned int nr) {
    TREE_CLASS* targetTree = getTreePointer(nr);
    TREE_CLASS* pointer = first;
    TREE_CLASS* currentTree;
    TREE_CLASS* newTree;
    int counter = 0;

    if (targetTree != NULL) {
        if (treesAmount == 0) {
            newTree = new TREE_CLASS(*targetTree);
            newTree->setNumber(0);
            newTree->setGarden(this);
            last = newTree;
            first = newTree;
            newTree->setNext(NULL);
            newTree->setPrev(NULL);
            addTrees(1);
            addWeight(targetTree->getWeightsTotal());
            addBranches(targetTree->getBranchesTotal());
            addFruits(targetTree->getFruitsTotal());
        } else if (treesAmount == (last->getNumber() + 1)) {
            newTree = new TREE_CLASS(*targetTree);
            newTree->setNumber(last->getNumber() + 1);
            newTree->setGarden(this);
            last->setNext(newTree);
            newTree->setPrev(last);
            newTree->setNext(NULL);
            addTrees(1);
            addWeight(targetTree->getWeightsTotal());
            addBranches(targetTree->getBranchesTotal());
            addFruits(targetTree->getFruitsTotal());
            last = newTree;
        } else {
            while (pointer != NULL) {
                if (pointer->getNumber() != counter) {
                    break;
                } else {
                    currentTree = pointer;
                    pointer = pointer->getNext();
                    counter++;
                }
            }
            if (counter == 0) {
                pointer = new TREE_CLASS(*targetTree);
                pointer->setGarden(this);
                pointer->setNumber(0);
                pointer->setNext(first);
                pointer->setPrev(NULL);
                addTrees(1);
                addWeight(targetTree->getWeightsTotal());
                addBranches(targetTree->getBranchesTotal());
                addFruits(targetTree->getFruitsTotal());
                first = pointer;
            } else {
                TREE_CLASS *nextTree = currentTree->getNext();
                pointer = new TREE_CLASS(*targetTree);
                pointer->setGarden(this);
                pointer->setNumber(currentTree->getNumber() + 1);
                pointer->setNext(nextTree);
                pointer->setPrev(currentTree);
                currentTree->setNext(pointer);
                nextTree->setPrev(pointer);
                addTrees(1);
                addWeight(targetTree->getWeightsTotal());
                addBranches(targetTree->getBranchesTotal());
                addFruits(targetTree->getFruitsTotal());
            }
        }
    }
}

TREE_CLASS* GARDEN_CLASS::getFirst() {
    return first;
}

TREE_CLASS* GARDEN_CLASS::getLast() {
    return last;
}

void GARDEN_CLASS::setLast( TREE_CLASS* lst ) {
    last = lst;
}
void GARDEN_CLASS::setFirst( TREE_CLASS* fst ) {
    first = fst;
}

void GARDEN_CLASS::addFruits( int amount ) {
    fruitsAmount += amount;
}
void GARDEN_CLASS::subtractFruits( int amount ) {
    fruitsAmount -= amount;
}
void GARDEN_CLASS::addWeight( int amount ) {
    theWeight += amount;
}
void GARDEN_CLASS::subtractWeight( int amount ) {
    theWeight -= amount;
}
void GARDEN_CLASS::addTrees( int amount ) {
    treesAmount += amount;
}
void GARDEN_CLASS::subtractTrees( int amount ) {
    treesAmount -= amount;
}

void GARDEN_CLASS::addBranches( int amount ) {
    branchesAmount += amount;
}
void GARDEN_CLASS::subtractBranches( int amount ) {
    branchesAmount -= amount;
}

