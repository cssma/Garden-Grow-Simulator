//Martyna Cios
#include <iostream>
#include "fruit.hpp"
#include "branch.hpp"
#include "tree.hpp"
#include "garden.hpp"

FRUIT_CLASS::FRUIT_CLASS() : weight(0), length(0), next(NULL), prev(NULL), frBranch(NULL) {}

FRUIT_CLASS::FRUIT_CLASS(const FRUIT_CLASS& fruit) : weight( fruit.weight ), length( fruit.length ), next(NULL), prev(NULL), frBranch(NULL) {}

FRUIT_CLASS::FRUIT_CLASS( unsigned int l, BRANCH_CLASS *ptr )
        : length(l), frBranch(ptr), next(NULL), prev(NULL), weight(0) {
    if ( frBranch ) {
        frBranch->addFruits( 1 );
        TREE_CLASS* tree = frBranch->getTree();

        if ( tree ) {
            tree->addFruits(1);
            GARDEN_CLASS* garden = tree->getGarden();

            if ( garden ) {
                garden->addFruits( 1 );
            }
        }
    }
}


FRUIT_CLASS::~FRUIT_CLASS() {
    if ( frBranch ) {
        frBranch->subtractFruits( 1 );
        frBranch->subtractWeight( weight );

        TREE_CLASS* tree = frBranch->getTree();
        if ( tree ) {
            tree->subtractFruits( 1 );
            tree->subtractWeight( weight );

            GARDEN_CLASS* garden = tree->getGarden();
            if ( garden ) {
                garden->subtractFruits( 1 );
                garden->subtractWeight( weight );
            }
        }

        if ( this == frBranch->getFirst() ) {
            frBranch->setFirst( next );
            if ( next )
                next->prev = NULL;
            else
                frBranch->setLast( NULL );
        }
        else if ( this == frBranch->getLast() ) {
            frBranch->setLast( this->getPrev() );
            if ( frBranch->getLast() )
                frBranch->getLast()->setNext( NULL );
        }
    }

    if ( this->getPrev() )
        this->getPrev()->setNext( this->getNext() );
    if ( this->getNext() )
        this->getNext()->setPrev( this->getPrev() );
}

unsigned int FRUIT_CLASS::getLength() {
    return length;
}

unsigned int FRUIT_CLASS::getWeight() {
    return weight;
}

void FRUIT_CLASS::growthFruit() {
    weight++;

    if (frBranch) {
        frBranch->addWeight(1);

        if(frBranch->getTree()) {
            frBranch->getTree()->addWeight(1);

            if (frBranch->getTree()->getGarden()) {
                frBranch->getTree()->getGarden()->addWeight(1);
            }
        }
    }
}

void FRUIT_CLASS::fadeFruit() {
    if (weight > 0) {
        weight--;

        if (frBranch) {
            frBranch->subtractWeight(1);

            if(frBranch->getTree()) {
                frBranch->getTree()->subtractWeight(1);

                if (frBranch->getTree()->getGarden()) {
                    frBranch->getTree()->getGarden()->subtractWeight(1);
                }
            }
        }
    }
}

void FRUIT_CLASS::pluckFruit() {
    if ( weight <= 0 ) {
        return;
    }

    unsigned int help = weight;
    weight = 0;

    if ( frBranch ) {
        frBranch->subtractWeight( help );

        if( frBranch->getTree() ) {
            frBranch->getTree()->subtractWeight( help );

            if ( frBranch->getTree()->getGarden() ) {
                frBranch->getTree()->getGarden()->subtractWeight( help );
            }
            else return;
        }
        else return;
    }
    else return;
}

BRANCH_CLASS* FRUIT_CLASS::getBranchPointer() {
    return frBranch;
}

void FRUIT_CLASS:: setBranch( BRANCH_CLASS* frBranch ) {
    this->frBranch = frBranch;
}

FRUIT_CLASS* FRUIT_CLASS::getNext() {
    return next;
}
FRUIT_CLASS* FRUIT_CLASS::getPrev() {
    return prev;
}

void FRUIT_CLASS::setNext( FRUIT_CLASS* nextFruit ) {
    this->next = nextFruit;
}
void FRUIT_CLASS::setPrev( FRUIT_CLASS* prevFruit ) {
    this->prev = prevFruit;
}
