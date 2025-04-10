#include <iostream>
#include "branch.hpp"
#include "garden.hpp"
#include "tree.hpp"
#include "fruit.hpp"


int main() {
    std::cout << "  SIMULATION OF BRANCHES AND TREES  " << std::endl;

    GARDEN_CLASS* garden = new GARDEN_CLASS();

    TREE_CLASS* tree = new TREE_CLASS(1, garden);

    BRANCH_CLASS* branch = new BRANCH_CLASS(1, tree);

    for (int i = 0; i < 6; ++i) {
        branch->growthBranch();
    }

    std::cout << "Branch length: " << branch->getLength() << std::endl;
    std::cout << "Number of fruits: " << branch->getFruitsTotal() << std::endl;
    std::cout << "Fruits weight: " << branch->getWeightsTotal() << std::endl;

    branch->harvestBranch(3);
    std::cout << "After harvesting - fruits weight: " << branch->getWeightsTotal() << std::endl;

    branch->fadeBranch();
    std::cout << "After fading - fruits weight: " << branch->getWeightsTotal() << std::endl;

    delete branch;
    delete tree;
    delete garden;

    std::cout << "Simulation completed." << std::endl;

    return 0;
}
