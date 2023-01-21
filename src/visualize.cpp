#include <stdlib.h>

#include "tree/Visualizer.hpp"

int	main( void ) {
	Visualizer	visualizer;

    {
        Tree<int>	tree;
        for (int i = 1; i < 10; i++) {
            tree.insert(i);
        }
        tree.erase(6);
        visualizer.call(tree);
    }

    {
        Tree<int>	tree;
        for (int i = -2; i < 10; i++) {
            tree.insert(i);
        }
        visualizer.call(tree);
    }

    {
        Tree<int>	tree;
        for (int i = 1; i < 20; i++) {
            tree.insert(rand() % 100);
        }
        tree.erase(65);
        visualizer.call(tree);
    }

    return 0;
}