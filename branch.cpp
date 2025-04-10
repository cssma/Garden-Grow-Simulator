//Martyna Cios
#include <iostream>
#include "branch.hpp"
#include "fruit.hpp"
#include "tree.hpp"
#include "garden.hpp"

BRANCH_CLASS::BRANCH_CLASS()
        : length(0), fruitsAmount(0), fruitsWeight(0), height(0),
          next(NULL), prev(NULL), first(NULL), last(NULL), brTree(NULL) {}


BRANCH_CLASS::BRANCH_CLASS( const BRANCH_CLASS& otherBranch )
        : length(otherBranch.length), fruitsAmount(otherBranch.fruitsAmount),
          fruitsWeight(otherBranch.fruitsWeight), next(NULL), prev(NULL),
          brTree(NULL), first(NULL), last(NULL) {
    if (otherBranch.first != NULL) {
        FRUIT_CLASS* srcFruit = otherBranch.first;
        first = new FRUIT_CLASS(*srcFruit);
        first->setBranch(this);
        last = first;

        srcFruit = srcFruit->getNext();
        while (srcFruit) {
            FRUIT_CLASS* newFruitCopy = new FRUIT_CLASS(*srcFruit);
            newFruitCopy->setBranch(this);

            newFruitCopy->setPrev(last);
            last->setNext(newFruitCopy);
            last = newFruitCopy;

            srcFruit = srcFruit->getNext();
        }
        last->setNext(NULL);

    }
}

BRANCH_CLASS::BRANCH_CLASS( unsigned int hght, TREE_CLASS *ptr )
        : height(hght), brTree(ptr), fruitsWeight(0), fruitsAmount(0),
          length(0), next(NULL), prev(NULL), first(NULL), last(NULL) {
    if ( brTree )
    {
        brTree->addBranches( 1 );
        GARDEN_CLASS* garden = brTree->getGarden();

        if ( garden )
        {
            garden->addBranches( 1 );
        }
    }
}

BRANCH_CLASS::~BRANCH_CLASS() {
    if ( this->getPrev() )
        this->getPrev()->setNext( this->getNext() );
    if ( this->getNext() )
        this->getNext()->setPrev( this->getPrev() );

    FRUIT_CLASS* currentFruit = first;
    while( currentFruit ) {
        FRUIT_CLASS* tempFruit = currentFruit;
        currentFruit = currentFruit->getNext();
        delete tempFruit;
    }
    first = NULL;
    last = NULL;

    if ( brTree )
    {
        brTree->subtractBranches( 1 );
        GARDEN_CLASS* garden = brTree->getGarden();

        if (garden) {
            garden->subtractBranches( 1 );
        }


        if ( this == brTree->getFirst() ) {
            brTree->setFirst( this->getNext() );
            if ( brTree->getFirst() )
                brTree->getFirst()->setPrev( NULL );
            else
                brTree->setLast( NULL );
        } else if ( this == brTree->getLast() ) {
            brTree->setLast(this->getPrev());
            if ( brTree->getLast() )
                brTree->getLast()->setNext( NULL );
            else {
                brTree->setFirst(NULL);
            }
        }
    }
}

unsigned int BRANCH_CLASS::getFruitsTotal() {
    return fruitsAmount;
}

unsigned int BRANCH_CLASS::getWeightsTotal() {
    return fruitsWeight;
}

unsigned int BRANCH_CLASS::getHeight() {
    return height;
}

unsigned int BRANCH_CLASS::getLength() {
    return length;
}

void BRANCH_CLASS::createAndAddFruit() {
    FRUIT_CLASS* pointer_fruit = new FRUIT_CLASS(length, this);
    if (first == NULL)
    {
        first = pointer_fruit;
    }
    else
    {
        last->setNext(pointer_fruit);
        pointer_fruit->setPrev(last);
    }
    last = pointer_fruit;
    pointer_fruit->setNext(NULL);
}

void BRANCH_CLASS::growthBranch() {
    if (length != 0)
    {
        FRUIT_CLASS* pointer_fruit = first;
        length++;
        while(pointer_fruit)
        {
            pointer_fruit->growthFruit();
            pointer_fruit = pointer_fruit->getNext();
        }

        if( length % 2 == 0 )
        {
            createAndAddFruit();
        }
    }
    else
    {
        length++;
    }
}

void BRANCH_CLASS::fadeBranch() {
    if ( length > 0 )
    {
        cutBranch( length - 1 );

        FRUIT_CLASS* pointer_fruit = first;

        while ( pointer_fruit )
        {
            pointer_fruit->fadeFruit();
            pointer_fruit = pointer_fruit->getNext();
        }
    }
}

void BRANCH_CLASS::harvestBranch ( unsigned int minWght ) {
    FRUIT_CLASS* pointer_fruit=first;
    while ( pointer_fruit )
    {
        if ( !( pointer_fruit->getWeight() < minWght ))
        {
            pointer_fruit->pluckFruit();
        }
        pointer_fruit=pointer_fruit->getNext();
    }
}

void BRANCH_CLASS::cutBranch (unsigned int arg) {
    FRUIT_CLASS *pointer_fruit = first;
    FRUIT_CLASS *previ = NULL;

    if (arg < length) {
        length = arg;

        while (pointer_fruit != NULL) {
            if (pointer_fruit->getLength() <= arg) {
                pointer_fruit = pointer_fruit->getNext();
            } else {
                while (pointer_fruit != NULL) {
                    previ = pointer_fruit;
                    pointer_fruit = pointer_fruit->getNext();
                    delete previ;
                }
            }
        }
    }
}

FRUIT_CLASS* BRANCH_CLASS::getFruitPointer(unsigned int arg) {
    if ( ( length<arg ) || ( arg<=0 ) || fruitsAmount==0 || ( arg%2==1 ) ) {
        return NULL;
    }

    FRUIT_CLASS* fruitPointer = first;

    while (fruitPointer) {
        if (fruitPointer->getLength() == arg) {
            return fruitPointer;
        }
        fruitPointer = fruitPointer->getNext();
    }

    return NULL;
}

TREE_CLASS* BRANCH_CLASS::getTreePointer() {
    return brTree;
}

void BRANCH_CLASS:: setTree( TREE_CLASS* tree ) {
    brTree = tree;
}

void BRANCH_CLASS::setHeight(unsigned int hght) {
    height = hght;
}

TREE_CLASS* BRANCH_CLASS::getTree() {
    return brTree;
}

BRANCH_CLASS* BRANCH_CLASS::getNext() {
    return next;
}

BRANCH_CLASS* BRANCH_CLASS::getPrev() {
    return prev;
}

FRUIT_CLASS* BRANCH_CLASS::getFirst() {
    return first;
}

FRUIT_CLASS* BRANCH_CLASS::getLast() {
    return last;
}

void BRANCH_CLASS::setNext( BRANCH_CLASS* nextBranch ) {
    this->next = nextBranch;
}
void BRANCH_CLASS::setPrev( BRANCH_CLASS* prevBranch ) {
    this->prev = prevBranch;
}

void BRANCH_CLASS::setFirst( FRUIT_CLASS* frst ) {
    this->first = frst;
}

void BRANCH_CLASS::setLast( FRUIT_CLASS* last ) {
    this->last = last;
}

void BRANCH_CLASS::addWeight( unsigned int amount ) {
    fruitsWeight += amount;
}
void BRANCH_CLASS::subtractWeight( unsigned int amount ) {
    fruitsWeight -= amount;
}

void BRANCH_CLASS::addFruits( unsigned int amount ) {
    fruitsAmount += amount;
}
void BRANCH_CLASS::subtractFruits( unsigned int amount ) {
    fruitsAmount -= amount;
}

