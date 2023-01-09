#include "BrickBreak.hpp"

int main() {
	srand(static_cast <unsigned int> (time(0)));
	char in;

	while (1) {
		system("cls");
		system("Color B0");

		mainMenu();

		in = getch();

		if (in == '1') {
			playMenu();
		}
		else if (in == '2') {
			infoMenu();
		}
		else if (in == '3') {
			quitMenu();
			break;
		}
	}
	return 0;
}