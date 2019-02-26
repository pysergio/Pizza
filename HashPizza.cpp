#include "include/Pizza.h"

int main(int argc, char const *argv[]) {
	bool	free_spaces_allowed = true;
	bool	print_mask = false;
	if (!--argc)
		RisingError::argvError();
	
	for(int i = 1; i < argc; i++) {
		if ((string)argv[i] == "-pmask")
			print_mask = true;
		else if ((string)argv[i] == "-fsna")
			free_spaces_allowed = false;
		else{
			cout << "invalid key %\"" << argv[i] << '\"' << endl;
			RisingError::argvError();
		}
	}	
	Pizza pizza(argv[argc]);
	pizza.solveIt(free_spaces_allowed);
	if (free_spaces_allowed && print_mask)
		pizza.printFSC();

	if (print_mask)
		pizza.printMask();
	else
		pizza.printList();
	
	return 0;
}
