/*
Author:		Dawid Jasionowski
Class:		CIS-2542-002
Date:		10/06/2018
File:		main file
Descr:
This program uses the card, deck, and player classes to run
a simple simulation of a card game. Each turn, players' names
are displayed, one card from each player is discarded, and 
the value of the cards for each player is displayed. The
program ends when all the cards have been played.
*/


#include <string>
#include <iostream>
#include <vector>
#include <chrono>

#include "Deck.h"
#include "Player.h"
#include <iomanip>
using namespace std;

int main()
{
	Deck d;
	cout << "Shuffling cards..." << endl;
	d.shuffle();
	cout << "Lets shuffle one more time..." << endl;
	d.shuffle();

	Player p(string("FOO"));

	vector<Player> players;
	players.push_back(Player("David"));
	players.push_back(Player("Olivia"));
	players.push_back(Player("Patrick"));
	players.push_back(Player("Katie"));

	cout << "Dealing cards..." << endl;
	cout << "--------------------------" << endl;
	d.deal(players);

	cout << "Press enter to see the players' names and their cards: " << endl;
	cin.get();

	size_t temp = players.size();




	for (int i = 0; i < temp; i++) {
		players[i%temp].Player::showCards();
		cout << endl << "Press 'Enter' to continue" << endl;
		cin.get();
	}
	
	cout << "Now let's start removing cards, starting from the end";
	cout << "Press 'Enter' to start.";
	cin.get();
	

	// loop for removing cards
	// 4 players with 13 cards each
	for (int i = 0; i < 13; i++)
	{
		for (auto it = players.begin(); it != players.end(); ++it)
		{
			Card c = it->remove_card();
			cout << it->get_name() << " removed " << c << endl <<
				it->get_name()<< "'s new value:  " << it->hand_value() << endl <<
				"--------------------------" << endl;
			
		}
		cout << endl;
		cout << "Press 'Enter' to continue";
		cin.get();
	}

	return EXIT_SUCCESS;;
}


/*
Shuffling cards...
Lets shuffle one more time...
Dealing cards...
--------------------------
Press enter to see the players' names and their cards:

*** David's cards: ***
The Ace of Spades,
The Two of Spades,
The Eight of Spades,
The Six of Hearts,
The Ten of Hearts,
The Six of Spades,
The Eight of Clubs,
The Nine of Diamonds,
The Nine of Spades,
The Ten of Spades,
The Jack of Spades,
The Queen of Diamonds,
The King of Clubs,

Press 'Enter' to continue

*** Olivia's cards: ***
The Ace of Hearts,
The Two of Hearts,
The Three of Hearts,
The Four of Hearts,
The Eight of Hearts,
The Queen of Clubs,
The Seven of Hearts,
The Seven of Clubs,
The Queen of Spades,
The Six of Clubs,
The Jack of Hearts,
The Queen of Hearts,
The Four of Spades,

Press 'Enter' to continue

*** Patrick's cards: ***
The Ace of Clubs,
The Two of Clubs,
The Three of Clubs,
The Five of Hearts,
The Four of Clubs,
The Nine of Hearts,
The Five of Clubs,
The Three of Spades,
The Jack of Diamonds,
The Five of Spades,
The Jack of Clubs,
The King of Spades,
The Nine of Clubs,

Press 'Enter' to continue

*** Katie's cards: ***
The Ace of Diamonds,
The Two of Diamonds,
The Three of Diamonds,
The Four of Diamonds,
The Five of Diamonds,
The Six of Diamonds,
The King of Hearts,
The Ten of Diamonds,
The Seven of Spades,
The King of Diamonds,
The Eight of Diamonds,
The Seven of Diamonds,
The Ten of Clubs,

Press 'Enter' to continue

Now let's start removing cards, starting from the endPress 'Enter' to start.
David removed The King of Clubs
David's new value:  92
--------------------------
Olivia removed The Four of Spades
Olivia's new value:  85
--------------------------
Patrick removed The Nine of Clubs
Patrick's new value:  72
--------------------------
Katie removed The Ten of Clubs
Katie's new value:  79
--------------------------

Press 'Enter' to continue
David removed The Queen of Diamonds
David's new value:  80
--------------------------
Olivia removed The Queen of Hearts
Olivia's new value:  73
--------------------------
Patrick removed The King of Spades
Patrick's new value:  59
--------------------------
Katie removed The Seven of Diamonds
Katie's new value:  72
--------------------------

Press 'Enter' to continue
David removed The Jack of Spades
David's new value:  69
--------------------------
Olivia removed The Jack of Hearts
Olivia's new value:  62
--------------------------
Patrick removed The Jack of Clubs
Patrick's new value:  48
--------------------------
Katie removed The Eight of Diamonds
Katie's new value:  64
--------------------------

Press 'Enter' to continue
David removed The Ten of Spades
David's new value:  59
--------------------------
Olivia removed The Six of Clubs
Olivia's new value:  56
--------------------------
Patrick removed The Five of Spades
Patrick's new value:  43
--------------------------
Katie removed The King of Diamonds
Katie's new value:  51
--------------------------

Press 'Enter' to continue
David removed The Nine of Spades
David's new value:  50
--------------------------
Olivia removed The Queen of Spades
Olivia's new value:  44
--------------------------
Patrick removed The Jack of Diamonds
Patrick's new value:  32
--------------------------
Katie removed The Seven of Spades
Katie's new value:  44
--------------------------

Press 'Enter' to continue
David removed The Nine of Diamonds
David's new value:  41
--------------------------
Olivia removed The Seven of Clubs
Olivia's new value:  37
--------------------------
Patrick removed The Three of Spades
Patrick's new value:  29
--------------------------
Katie removed The Ten of Diamonds
Katie's new value:  34
--------------------------

Press 'Enter' to continue
David removed The Eight of Clubs
David's new value:  33
--------------------------
Olivia removed The Seven of Hearts
Olivia's new value:  30
--------------------------
Patrick removed The Five of Clubs
Patrick's new value:  24
--------------------------
Katie removed The King of Hearts
Katie's new value:  21
--------------------------

Press 'Enter' to continue
David removed The Six of Spades
David's new value:  27
--------------------------
Olivia removed The Queen of Clubs
Olivia's new value:  18
--------------------------
Patrick removed The Nine of Hearts
Patrick's new value:  15
--------------------------
Katie removed The Six of Diamonds
Katie's new value:  15
--------------------------

Press 'Enter' to continue
David removed The Ten of Hearts
David's new value:  17
--------------------------
Olivia removed The Eight of Hearts
Olivia's new value:  10
--------------------------
Patrick removed The Four of Clubs
Patrick's new value:  11
--------------------------
Katie removed The Five of Diamonds
Katie's new value:  10
--------------------------

Press 'Enter' to continue
David removed The Six of Hearts
David's new value:  11
--------------------------
Olivia removed The Four of Hearts
Olivia's new value:  6
--------------------------
Patrick removed The Five of Hearts
Patrick's new value:  6
--------------------------
Katie removed The Four of Diamonds
Katie's new value:  6
--------------------------

Press 'Enter' to continue
David removed The Eight of Spades
David's new value:  3
--------------------------
Olivia removed The Three of Hearts
Olivia's new value:  3
--------------------------
Patrick removed The Three of Clubs
Patrick's new value:  3
--------------------------
Katie removed The Three of Diamonds
Katie's new value:  3
--------------------------

Press 'Enter' to continue
David removed The Two of Spades
David's new value:  1
--------------------------
Olivia removed The Two of Hearts
Olivia's new value:  1
--------------------------
Patrick removed The Two of Clubs
Patrick's new value:  1
--------------------------
Katie removed The Two of Diamonds
Katie's new value:  1
--------------------------

Press 'Enter' to continue
David removed The Ace of Spades
David's new value:  0
--------------------------
Olivia removed The Ace of Hearts
Olivia's new value:  0
--------------------------
Patrick removed The Ace of Clubs
Patrick's new value:  0
--------------------------
Katie removed The Ace of Diamonds
Katie's new value:  0
--------------------------

Press 'Enter' to continue*/