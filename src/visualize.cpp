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

int	main(void)
{
	std::string	cmd;
	PhoneBook	phonebook;

	LOG("Welcome to your PhoneBook!");

	// main loop
	while (cmd != EXIT)
	{
		LOG("What would you like to do?");
		LOG("(ADD, SEARCH, EXIT)");
		std::cout << "> ";

		// receive instruction
		getline(std::cin, cmd);

		// do each instruction
		if (cmd == ADD)
			phonebook.contact_add();
		else if (cmd == SEARCH)
			phonebook.contacts_search();
		else if (cmd != EXIT)
			LOG("Not a valid Command!");
	}
	return (0);
}