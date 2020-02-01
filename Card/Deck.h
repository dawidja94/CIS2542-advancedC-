/*
Author:		Dawid Jasionowski
Class:		CIS-2542
Date:		10/06/2018
File:		Deck.h; specification file for the Deck class
Descr:
This program uses the card, deck, and player classes to run
a simple simulation of a card game. Each turn, players' names
are displayed, one card from each player is discarded, and
the value of the cards for each player is displayed. The
program ends when all the cards have been played.
*/

#pragma once
#include <vector>
#include "Player.h"
#include "Card.h"

using namespace std;

class Deck
{
	
public:
	
	typedef Card value_type;
	typedef size_t size_type;
	
	// constructor
	Deck();

	// deconstructor
	~Deck();

	// function to shuffle the deck
	void shuffle();
	//swap function
	void swap(size_type index1, size_type index2);
	// function to deal cards to players
	void deal(vector<Player> &players);
	// overloaded function to display cards
	friend ostream & operator << (ostream&, const Deck&);

private: 
	const static int SIZE = 52;
	value_type sequence[SIZE];
	size_type cards_in_deck;
};

