// Compulsory2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <array>
#include <conio.h>

int cardsDrawn = 0;
int playerTurn = 0;
int roundsPlayed = 1;

struct player
{
	int sum = 0;
	int yourCard = 0;
	int drawn = 0;
	bool ai = false;
	std::string name;
	int money = 100;
};

player house;
player player1;

std::array<int, 13> cardArray{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

void shuffleCards()
{
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::shuffle(cardArray.begin(), cardArray.end(), mt);
}


void drawCard(player& player)
{
	int card = 0;

	// Drawn card inside funtion:
	card = cardArray[cardsDrawn];

	cardsDrawn++;

	if (card > 1 && card <=10)
	{
		std::cout << "\nCard drewn is " << card << "\n";

	}
	// This following section is for checking if card drawn is an ace, and what to do with it
	else if (card==1)
	{
		if (player.ai == false)
		{
			std::cout << "\nCard drewn is an ace. D you want it to be a 1 or an 11?\n";
			int choice = 0;
			while (true)
			{
				std::cin >> choice;
				if (choice==1)
				{
					break;
				}
				else if (choice == 11)
				{
					card = card + 10;
					break;
				}
			}

		}
		if (player.ai == true)
		{
			if (player.sum <=11)
			{
				std::cout << "\nCard drewn is an ace. The house decided it to be an 11.";
				card = card + 10;
			}
			else if (player.sum > 11)
			{
				std::cout << "\nCard drewn is an ace. The house decided it to be a 1.";
			}
		}
	}

	if (card==11)
	{
		std::cout << "\nCard drewn is a Knight\n";
		card = 10;
	}

	if (card == 12)
	{
		std::cout << "\nCard drewn is a Queen\n";
		card = 10;
	}

	if (card == 13)
	{
		std::cout << "\nCard drewn is a King\n";
		card = 10;
	}
	// Card drawn, card sum and number of cards drawn passed out of the function:
	player.sum = player.sum + card;
	player.drawn++;
	player.yourCard = card;


	return ;
}

void resetPlayers(player& player)
{
	player.sum = 0;
	player.yourCard = 0;
	player.drawn = 0;

}

void resetBoard()
{
	resetPlayers(player1);
	resetPlayers(house);
	cardsDrawn = 0;
	playerTurn = 0;
	roundsPlayed++;
	char keyPress = _getch();
}

int main()
{

	// Player 1 turn = 1, House turn = 2

	house.ai = true;
	unsigned int spend = 0;

	shuffleCards();

	while (true)
	{
		if (player1.money < 10)
		{
			system("CLS");
			std::cout << "\nYou are out of money sir, goodbye.";
			char something = _getch();
			return 0;

		}

		else if (house.money < 10)
		{
			system("CLS");
			std::cout << "\nThe house is out of money! You won!";
			char something = _getch();
			return 0;
		}
		// This function is for starting each round
		while (playerTurn ==0)
		{
			system("CLS");

			std::cout
				<< "\nWelcome to Blackjack - Round " << roundsPlayed
				<< "\n\nYou now have " << player1.money << "$"
				<< "\nThe house has " << house.money << "$"
				<< "\n\nPress any key to play, or Q to quit: ";
			char play = _getch(); 
			
			if (play == 'q')
			{
				return 0;
			}
				std::cout << "\n\nHow much do you want to bet? The minimum is 10$\n\n";


			while (true)
			{
				std::cin >> spend;
				if (spend >= 10 && spend <= player1.money)
				{
					player1.money = player1.money - spend;
					house.money = house.money - spend;
					std::cout << "\nMoney bet: " << spend << "$";
					playerTurn = 1;
					break;
				}
				else if (spend < 10)
				{
					std::cout << "\nTo little money bet. Please try again.\n";
				}
				else
				{
					std::cout << "\nWrong input. Please try again.\n";

				}

			}
		}

		while (playerTurn == 1)
		{
			system("CLS");
			drawCard(player1);
			
			std::cout << "\nYour sum is: " << player1.sum;
			std::cout << "\nYou have drawn " << player1.drawn << " cards";

			if (player1.sum > 21)
			{
				std::cout
					<< "\n\nYour sum is over 21. You loose!"
					<< "\nPress a key to play again";
				house.money = house.money + (spend * 2);
				resetBoard();
				break;
			}

			std::cout << "\n\nPress any key to draw one more card, or P to pass: ";
			char keyPress = _getch();
			std::cout << "\n";

			if (keyPress == 'p')
			{
				playerTurn = 2;				
			}
		}

		while (playerTurn == 2)
		{
			system("CLS");
			drawCard(house);
			std::cout << "\nHouse sum is: " << house.sum;
			std::cout << "\nHouse has drawn: " << house.drawn << " cards";
		
			if (house.sum > player1.sum && house.sum <= 21 )
			{
				std::cout
					<< "\n\nHouse won!"
					<< "\nPress a key to play again";
				house.money = house.money + (spend * 2);
				resetBoard();

				break;
			}

			else if (house.sum == player1.sum)
			{
				std::cout << "\n\nIt's a draw!";
				std::cout << "\nPress a key to play again";
				house.money = house.money + spend;
				player1.money = player1.money + spend;
				resetBoard();
				break;

			}
			else if (house.sum > 21)
			{
				std::cout << "\n\nThe house's sum is over 21. Player 1 won";
				player1.money = player1.money + (spend*2);
				resetBoard();
				break;
			}

			else
			{
				std::cout << "\nPress a key to see the next card the house drew:";
				char keyPress = _getch();

			}

		}
	}
	
	


// 	for (int i = 0; i < 10; i++)
// 	{
// 		std::cout << cardArray[i];
// 	}

}

