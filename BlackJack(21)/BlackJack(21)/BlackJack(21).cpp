#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>

using namespace std;

const int PACK_SIZE = 52;

// ascii codes for suit symbols
#define HEARTS 'H'
#define DIAMONDS 'D'
#define CLUBS 'C'
#define SPADES 'S'

#define TLC 218         // top left corner
#define HL 196          //  horzontal line
#define TRC 191         // top right corner
#define VL 179          // vertical line
#define BLC 192         // Bottom left corner
#define BRC 217         // bottom right corner

enum Suit { Hearts, Diamonds, Clubs, Spades };

struct Card
{
	Suit suit; // H, D, C or S
	int value; // Value is 1 to 13 (1 = Ace, 13 = King)
	int score; // 1 to 11
};

void gotoxy(int x, int y);
void setTextColour(int colour);

Card Pack[PACK_SIZE];

int topOfDeck = 0;

int playerScore = 0;
int xPlayerCardPos = 0;

int computerScore = 0;
int xComputerCardPos = 0;

void displayPack();

void setupHearts();
void setupDiamonds();
void setupClubs();
void setupSpades();
void setupPack();

string displaySuit(Suit currentSuit);
string cardValue(int currentValue);
void shufflePack();
void dealCardToPlayer();
void dealCardToComputer();

void displayMenu();
void processChoices();

void play();
void about();
void help();

void drawBox(int xpos, int ypos, int width, int height);
void drawCard(int xpos, int ypos, int width, int height, Suit suit, int value);
int determineAceScore();

int main()
{
	setupPack();
	shufflePack();
	
	processChoices();

	return 0;
}

void play()
{
	char choice;

	playerScore = 0;       // Resets the score to zero.
	computerScore = 0;     // Resets th score to zero for the dealer.
	xPlayerCardPos = 35;   // Reset to left hand side of the screen, for drawing cards.
	xComputerCardPos = 40; // Reset to left hand side of the screen, for drawing computer cards.

	system("cls");
	
	cout << "Hand of Black Jack" << endl << endl;

	//Deals cards to computer
	dealCardToComputer();
	cout << endl << endl << endl << endl;
	dealCardToComputer();

	//Deals cards to the player
	dealCardToPlayer();
	cout << endl << endl << endl;
	dealCardToPlayer();

	if (Pack[topOfDeck].value == 1)
	{
		playerScore += determineAceScore();
	}
	else
	{
		playerScore += Pack[topOfDeck].value;
	}

	cout << endl << "Stick or Twist? (S or T) : ";
	
	choice = toupper(_getwch());

	while ((choice != 'S') && (playerScore <= 21)) // Stick stops the loop.
	{
		if (choice == 'T') // Deal Card
		{
			cout << endl << endl << endl << endl << endl << endl;
			dealCardToPlayer();
		}
		if (playerScore < 21) // Stops if going above 21 score.
		{
			gotoxy(0, 200);
			cout << "Stick or Twist? (S or T) : ";
			choice = toupper(_getwch());
		}
	} // while

	while ((choice != 'T') && (computerScore <= 21))
	{
		//when the player finishes drawing cards
		if (computerScore < 21)
		{
			cout << endl << endl << endl << endl << endl << endl << endl;
			dealCardToComputer();
		}
		if (computerScore < playerScore)
		{
			cout << "Player Wins!" << endl;
		}
		else if (computerScore > 21)
		{
			cout << "Computer Busts - Player Wins!" << endl;
		}
	}

	if (playerScore > 21)
	{
		// bust
		cout << endl << "Player Busts - Computer Wins!" << endl << endl;
	}
	else if (playerScore == computerScore)
	{
		// Draw
		cout << endl << "Computer Wins!" << endl << endl;
	}
	else if (playerScore > computerScore)
	{
		// Player Wins
		cout << endl << "Player Wins!" << endl << endl;
	}

	
	system("pause");
} // void play ()

void displayMenu()
{
	system("cls");

	cout << "Black Jack - Main Menu" << endl << endl;
	cout << " P - Play" << endl;
	cout << " A - About" << endl;
	cout << " H - Help" << endl;
	cout << " E - Exit" << endl;
	cout << "Enter Choice : ";
} // Void displayMenu()

void processChoices()
{
	char choice;

	// read first
	displayMenu();
	choice = toupper(_getwch());

	while (choice != 'E')
	{
		if (choice == 'P')
		{
			play();
		}
		else if (choice == 'A')
		{
			about();

		}
		else if (choice == 'H')
		{
			help();
		}

		// read next
		displayMenu();
		choice = toupper(_getwch());

	} // while (choice != 'E')

} // void processChoices()

void displayPack()
{
	for (int loop = 0; loop < PACK_SIZE; loop++)
	{
		cout << "Loop = " << loop << " Suit = " << displaySuit(Pack[loop].suit);
		cout << " Value = " << cardValue(Pack[loop].value);
		cout << " Score = " << Pack[loop].score << endl;
	}
}; // void displayPack

void setupHearts()
{
	for (int loop = 0; loop <= 12; loop++)
	{
		Pack[loop].suit = Hearts;
		Pack[loop].value = loop + 1;
		Pack[loop].score = loop + 1;
	}

	Pack[10].score = 10; //Jack
	Pack[11].score = 10; //Queen
	Pack[12].score = 10; //King
}; // setupHearts

void setupDiamonds()
{
	for (int loop = 13; loop <= 25; loop++)
	{
		Pack[loop].suit = Diamonds;
		Pack[loop].value = loop + 1 - 13;
		Pack[loop].score = loop + 1 - 13;
	}

	Pack[23].score = 10; //Jack
	Pack[24].score = 10; //Queen
	Pack[25].score = 10; //King
} // setupDiamonds

void setupClubs()
{
	for (int loop = 26; loop <= 38; loop++)
	{
		Pack[loop].suit = Clubs;
		Pack[loop].value = loop + 1 - 26;
		Pack[loop].score = loop + 1 - 26;
	}

	Pack[36].score = 10; //Jack
	Pack[37].score = 10; //Queen
	Pack[38].score = 10; //King
}

void setupSpades()
{
	for (int loop = 39; loop <= 51; loop++)
	{
		Pack[loop].suit = Spades;
		Pack[loop].value = loop + 1 - 39;
		Pack[loop].score = loop + 1 - 39;
	}

	Pack[49].score = 10; //Jack
	Pack[50].score = 10; //Queen
	Pack[51].score = 10; //King
}

void setupPack()
{
	setupHearts();
	setupDiamonds();
	setupClubs();
	setupSpades();

} // void setupPack()

string displaySuit(Suit currentSuit)
{
	string Suit;
	if (currentSuit == Hearts)
	{
		Suit = "Hearts";
	}
	else if (currentSuit == Diamonds)
	{
		Suit = "Diamonds";
	}
	else if (currentSuit == Clubs)
	{
		Suit = "Clubs";
	}
	else if (currentSuit == Spades)
	{
		Suit = "Spades";
	}

	return Suit;
}

string cardValue(int currentValue)
{
	string cardName;

	if ((currentValue >= 2) && (currentValue <= 10))
	{
		cardName = to_string(currentValue);
	}
	else if (currentValue == 1)
	{
		cardName = "Ace";
	}
	else if (currentValue == 11)
	{
		cardName = "Jack";
	}
	else if (currentValue == 12)
	{
		cardName = "Queen";
	}
	else if (currentValue == 13)
	{
		cardName = "King";
	}

	return cardName;
}

void shufflePack()
{
	int random1, random2;

	Card tempCard;

	unsigned seed = time(0);
	srand(seed);

	for (int loop = 1; loop <= 50; loop++)
	{
		random1 = rand() % PACK_SIZE;
		random2 = rand() % PACK_SIZE;

		//swap
		tempCard = Pack[random1];
		Pack[random1] = Pack[random2];
		Pack[random2] = tempCard;
	}
}  // shufflePack

void dealCardToPlayer()
{
	
	cout << endl << endl << endl << endl << endl << "Suit = " << displaySuit(Pack[topOfDeck].suit) << endl;
	cout << "Value = " << cardValue(Pack[topOfDeck].value);
	

	drawCard(xPlayerCardPos, 3, 5, 7, Pack[topOfDeck].suit, Pack[topOfDeck].value);

	xPlayerCardPos = xPlayerCardPos + 7; //step of 7 chars on the x axis

	playerScore = playerScore + Pack[topOfDeck].score;

	gotoxy(50, 0); //Display player score on the top left corner.
	cout << "Player Score = " << playerScore << endl;

	topOfDeck++; // Next Card
}

void dealCardToComputer()
{
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << "Suit = " << displaySuit(Pack[topOfDeck].suit) << endl;
	cout << "Value = " << cardValue(Pack[topOfDeck].value);
	
	drawCard(xComputerCardPos, 13, 5, 7, Pack[topOfDeck].suit, Pack[topOfDeck].value);

	xComputerCardPos = xComputerCardPos + 7; //step of 7 chars on the x axis

	computerScore = computerScore + Pack[topOfDeck].score;

	gotoxy(90, 0);
	cout << "Computer Score = " << computerScore << endl;

	topOfDeck++; // Next Card
}

void gotoxy(int x, int y)
{
	// handles to define a position on the screen for whatever element on screen.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
} // void gotoxy(int x, int y)

void setTextColour(int colour)
{
	// a function that allows text colour to change.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
} // void setTextColour(int colour)

void drawBox(int xpos, int ypos, int width, int height)
{
	gotoxy(xpos, ypos);

	//top line of the box
	cout << char(TLC);
	for (int loop = 1; loop <= width; loop++)
	{
		cout << char(HL);
	}
	cout << char(TRC);

	// vertical lines
	for (int loop = 1; loop <= height; loop++)
	{
		gotoxy(xpos, ypos + loop);
		cout << char(VL);

		gotoxy(xpos + width + 1, ypos + loop);
		cout << char(VL);
	}

	//Last line
	gotoxy(xpos, ypos + height);
	cout << char(BLC);
	for (int loop = 1; loop <= width; loop++)
	{
		cout << char(HL);
	}
	cout << char(BRC);

} //void drawBox(int xpos, int ypos, int width, int height)

void drawCard(int xpos, int ypos, int width, int height, Suit suit, int value)
{
	setTextColour(7);

	drawBox(xpos, ypos, width, height);

	gotoxy(xpos, ypos); // position cursor top left corner on screen

	// top line of the box
	cout << char(TLC);
	for (int loop = 1; loop <= width; loop++)
	{
		cout << char(HL);
	}
	cout << char(TRC);

	// vertical lines
	for (int loop = 1; loop <= height; loop++)
	{
		gotoxy(xpos, ypos + loop);
		cout << char(VL);

		gotoxy(xpos + width + 1, ypos + loop);
		cout << char(VL);
	}

	// last line
	gotoxy(xpos, ypos + height);
	cout << char(BLC);
	for (int loop = 1; loop <= width; loop++)
	{
		cout << char(HL);
	}
	cout << char(BRC);

	// display card value and suit
	//top left

	if ((suit == Hearts))
	{
		setTextColour(12); // red
	}
	else if ((suit == Diamonds))
	{
		setTextColour(9); // blue
	}
	else if ((suit == Spades))
	{
		setTextColour(6); //Yellow
	}
	else if ((suit == Clubs))
	{
		setTextColour(3); //Light Blue
	}

	gotoxy(xpos + 1, ypos + 1);
	if ((value == 1))
	{
		cout << 'A';
	}
	else if ((value == 11))
	{
		cout << 'J';
	}
	else if ((value == 12))
	{
		cout << 'Q';
	}
	else if ((value == 13))
	{
		cout << 'K';
	}
	else
	{
		cout << value;
	}

	if ((suit == Hearts))
	{
		cout << HEARTS;
	}
	else if ((suit == Diamonds))
	{
		cout << DIAMONDS;
	}
	else if ((suit == Spades))
	{
		cout << SPADES;
	}
	else if ((suit == Clubs))
	{
		cout << CLUBS;
	}

	cout << char(suit + 3);

	// bottom right
	if (value == 10)
	{
		gotoxy(xpos + width - 2, ypos + height - 1);
	}
	else
	{
		gotoxy(xpos + width - 1, ypos + height - 1);
	}

	//sets the blackjack card value based on the Ace, jack, queen and king
	if ((value == 1))
	{
		cout << 'A';
	}
	else if ((value == 11))
	{
		cout << 'J';
	}
	else if ((value == 12))
	{
		cout << 'Q';
	}
	else if ((value == 13))
	{
		cout << 'K';
	}
	else
	{
		cout << value;
	}

	//sets the letter for each suit.
	if ((suit == Hearts))
	{
		cout << HEARTS;
	}
	else if ((suit == Diamonds))
	{
		cout << DIAMONDS;
	}
	else if ((suit == Spades))
	{
		cout << SPADES;
	}
	else if ((suit == Clubs))
	{
		cout << CLUBS;
	}
	cout << char(suit + 3);
}

//About Menu
void about()
{
	char choice;

	system("cls");

	cout << "BlackJack About" << endl << endl;
	cout << "BlackJack is a game where you are delt 2 cards at random from 1 to 10, " << endl;
	cout << "you have to keep the total number below 21 otherwise you lose, " << endl;
	cout << "if you can beat the computer where you have a number higher than the " << endl;
	cout << "computer but below 21 in order to win." << endl << endl;

	cout << "P - Play" << endl;
	cout << "M - Menu" << endl;
	cout << "H - Help" << endl;
	cout << "E - Exit" << endl;

	cout << "Enter choice: ";
	choice = toupper(_getwch());

	while (choice != 'E')
	{
		if (choice == 'M')
		{
			main();
		}
		else if (choice == 'H')
		{
			help();
		}
		else if (choice == 'P')
		{
			play();
		}

		about();
		choice = toupper(_getwch());
	}
}

// Help menu
void help()
{
	char choice;

	system("cls");

	cout << "BlackJack Help" << endl << endl;
	cout << "when playing the game, you have the option to Twist(Add another card), " << endl;
	cout << "or Stick(Stop getting new cards), is how you play the game of blackjack, " << endl;
	cout << "you can win the game by keeping the score below 21 and above the " << endl;
	cout << "computer's score in order to win." << endl << endl;

	cout << "P - Play" << endl;
	cout << "M - Menu" << endl;
	cout << "A - About" << endl;
	cout << "E - Exit" << endl;

	cout << "Enter choice: ";
	choice = toupper(_getwch());

	while (choice != 'E')
	{
		if (choice == 'M')
		{
			main();
		}
		else if (choice == 'A')
		{
			about();
		}
		else if (choice == 'P')
		{
			play();
		}

		about();
		choice = toupper(_getwch());
	}
}

// function to determine the value of Ace card
int determineAceScore()
{
	char selection = ' ';
	bool selected = false;
	int score = 0;

	cout << endl << "Do you want your Ace to be 1 or 11?";
	cout << endl << "Y or N for your choice: ";

	// when the user has selected 1 of two options
	while (!selected)
	{
		selection = toupper(_getwch());

		if (selection == 'Y')
		{
			score = 11;

			selected = true;
		}
		else if (selection == 'N')
		{
			score = 1;

			selected = true;
		}
	}

	return score;
}
