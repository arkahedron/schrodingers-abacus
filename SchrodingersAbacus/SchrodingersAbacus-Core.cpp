#include <iostream>
#include <ctime>
#include <string>
#include <random>
#include <windows.h>

using namespace std;


//Colored Text Function
//> clText(colorNumber, firstString, firstInteger, secondString, goNextLineBool);
void clText(int cNum1, string s1, int tNum1, string s2, bool goNextL) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cNum1);  //set text color to defined value

	if (s1 != "x") { cout << s1; } //first string to print

	if (tNum1 != -99) { cout << tNum1; } //first integer to print

	if (s2 != "x") { cout << s2; } //second string to print

	if (goNextL == 1) { cout << "\n"; } //if text following function should be on next line

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //resets text color to default after function
}


int main()
{

	int num1 = 7; //clText color, Default: white
	string s1 = ""; //clText first string
	int tNum1 = 0; //clText first number
	string s2 = ""; //clText second string
	bool goNextL = 0; //clText go next line bool

	string eKey; //Input key value

	int currentVal = 0; //Abacus current value
	int capVal = 1; //Abacus maximum value
	int randomVal = 1; //Abacus randomly rolled value

	int highScore = 0; //Highest achieved abacus score

	int changeVal = 0; //Difference of abacus value from previous
	string changeStr = ""; //Abacus value change symbol

	bool autoMode = 0; //Automatic mode toggle bool


	//RNG initializer seed
	default_random_engine generator;
	generator.seed(time(0));


	//Introduction text print
	cout << "\n";
	cout << "|-----{WELCOME TO ";
	clText(13, "SCHRODINGER'S ABACUS", -99, "x", 0);
	cout << "}-----" << endl;
	cout << "| You begin at ";
	clText(11, "|[", 0, "]|", 0);
	cout << "  Press ENTER to roll." << endl;
	cout << "|-------------------------------------------";

	cin.ignore(); //User input start line


	while (true) //Loop body for abacus, ends program if "x" is input
	{
		//Check for and adjust value change
		changeVal = randomVal - currentVal;
		if (randomVal > currentVal) { changeStr = " +"; }
		else if (randomVal == currentVal) { changeStr = "  "; }
		else { changeStr = " "; }

		//Run abacus randomize
		currentVal = randomVal;
		capVal = currentVal + 1;
		uniform_int_distribution<int> distribution(1, capVal);
		randomVal = distribution(generator);

		//Print score change
		cout << "| " << "Change:";
		clText(10, changeStr, changeVal, "x", 0);

		//Checkl, set, and print increase chance
		double chanceVal = capVal;
		chanceVal = 100.0 / chanceVal;
		cout << "  Chance to Increase: ";
		clText(2, "%", (chanceVal), "x", 1);

		//Print current score
		cout << "| " << "Current Score: ";
		clText(11, "|[", currentVal, "]|", 0);

		//Check, Set, and print highscore
		if (currentVal > highScore) { highScore = currentVal; }
		cout << "  Highscore: ";
		clText(13, "x", highScore, "x", 1);


		//Continue or exit prompt text
		cout << "| " << "Press ENTER to Roll Again ";
		clText(12, "(type x to exit)", -99, "x", 1);
		cout << "|-------------------------------------------";

		if (autoMode == 0) { getline(cin, eKey); } //User input prompt if auto mode is not enabled


		//Auto mode state toggle
		if (eKey == "auto") { autoMode = 1; }

		//Break loop if player inputs "x"
		if (eKey == "x") { clText(4, "exiting program...", -99, "x", 1); break; }
	}

	return 0;
}