/*
Author:		Dawid Jasionowski
Class:		CIS-2542-002
Date:		10/06/2018
File:		Player.h; specification file for the Player class
Descr:
This program uses the card, deck, and player classes to run
a simple simulation of a card game. Each turn, players' names
are displayed, one card from each player is discarded, and
the value of the cards for each player is displayed. The
program ends when all the cards have been played.
*/

#pragma once
#include <string>
#include <list>  //for pop_back(); back(); functions
#include "Card.h"
#include <vector>
using namespace std;

// Player class declaration
class Player
{
private:
	// members
	string name;
	list<Card> hand;

public:
	// constructors
	Player(const string name);
	Player(const Player &p);

	// deconstructor
	~Player();
	
	// function to deal card to players from deck
	void deal_card(Card &in);
	// function to discard the last card
	Card remove_card();
	//function to show cards for each player
	void showCards();
	// function to display value of cards in players hands
	int hand_value() const;
	// function to return players' names
	string get_name() const { return name; }
	// overloaded function to to display players' names and hand values
	friend ostream & operator << (ostream& out, const Player&);
};