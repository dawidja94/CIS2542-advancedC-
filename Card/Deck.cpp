/*
Author:		Dawid Jasionowski
Class:		CIS-2542
Date:		10/06/2018
File:		Deck.cpp; implementation file for the Deck class
Descr:
This program uses the card, deck, and player classes to run
a simple simulation of a card game. Each turn, players' names
are displayed, one card from each player is discarded, and
the value of the cards for each player is displayed. The
program ends when all the cards have been played.
*/


#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// constructor
Deck::Deck()
{
	int index = 0;
	for (int rank = 1; rank < 14; rank++) {
		for (int suit = 0; suit < 4; suit++) {
			Suit s = static_cast<Suit>(suit);
			sequence[index] = Card(s, Rank(rank));
			index++;
		}
	}
}

// deconstructor
Deck::~Deck()
{
}

// function to shuffle the deck of cards
void Deck::shuffle() {
	srand((unsigned)time(0));
	size_type random1;
	size_type random2;
	for (int i = 0; i < SIZE; i++) {
		random1 = i+ (rand() % (52 - i));
		random2 = i+ (rand() % (52 - i));
		//swap
		swap(random1, random2);


	}
}
//function to swap cards in a deck
void Deck::swap(size_type index1, size_type index2) {
	value_type temp = sequence[index1];
	//assign cards from index2 to index1
	sequence[index1] = sequence[index2];
	sequence[index2] = temp;
}



// function to deal cards to players
void Deck::deal(vector<Player>& players)
{
	size_t num = players.size();
	for (int i = 0; i < Deck::SIZE; ++i)
	{
		players[i%num].deal_card(sequence[i]);
	}
}

// overloaded function to display cards
ostream& operator << (ostream& out, const Deck& d) {
	for (int i = 0; i < Deck::SIZE; ++i) {
		out << d.sequence[i] << " ";
	}
	out << endl;
	return out;
}