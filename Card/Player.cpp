/*
Author:		Dawid Jasionowski
Class:		CIS-2542-002
Date:		10/06/2018
File:		Player.cpp; implementation file for the Player class
Descr:
This program uses the card, deck, and player classes to run
a simple simulation of a card game. Each turn, players' names
are displayed, one card from each player is discarded, and
the value of the cards for each player is displayed. The
program ends when all the cards have been played.
*/


#include "Player.h"

using namespace std;

// constructors
Player::Player(const string name) :
	name(name)
{}
Player::Player(const Player & p)
{
	name = p.name;
	hand = p.hand;
}

// deconstructor
Player::~Player()
{
	hand.clear();
}

// function for dealing card
void Player::deal_card(Card & in)
{
	hand.push_back(in);
}

// function for discarding the last card
Card Player::remove_card()
{
	Card retval = hand.back();
	hand.pop_back();
	return retval;
}

// function for returning the value of cards
int Player::hand_value() const
{
	int retval = 0;
	for (auto it = hand.begin(); it != hand.end(); ++it)
	{
		retval = it->getRank() + retval;
	}
	return retval;
}
void Player::showCards() {
	
		cout << "*** " << this->get_name() << "'s cards: ***" << endl;
		for (Card v : this->hand) {
			cout << v << ", " << endl;

		}
			
	}


// overloaded function to display players' names and hand values
ostream & operator<<(ostream &out, const Player &p)
{
	out << p.name << " hand value: " << p.hand_value() << endl;
	for (auto it = p.hand.begin(); it != p.hand.end(); ++it)
	{
		out << *it << " ";
	}
	return out;
}