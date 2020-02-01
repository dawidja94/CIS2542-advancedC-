/*
Author:		Dawid Jasionowski
Class:		CIS-2542-002
Date:		10/06/2018
File:		Card.cpp; implementation file for the Card class
This program uses the card, deck, and player classes to run
a simple simulation of a card game. Each turn, players' names
are displayed, one card from each player is discarded, and
the value of the cards for each player is displayed. The
program ends when all the cards have been played.
*/


#include "Card.h"

using namespace std;

// constructors
Card::Card()
{
}
Card::Card(Suit suit, Rank rank) : suit(suit), rank(rank) {}

// deconstructor
Card::~Card()
{
}

// overloaded operator function to assign suit and rank
void Card::operator=(const Card & a){
	suit = a.suit;
	rank = a.rank;
}

// getSuit function definition
Suit Card::getSuit() const {
	return suit;
}

// getRank function definition
int Card::getRank() const {
	return rank;
}

// setSuit function definition
void Card::setSuit(Suit newsuit) {
	suit = newsuit;
}

// setRank function definition
void Card::setRank(Rank newrank) {
	rank = newrank;
}

// overloaded function to display rank and suit
ostream& operator<< (ostream& out, const Card& c) {
	out << "The " << c.rank << " of " << c.suit;
	return out;
}

int operator+(const Card &a, const Card&b)
{
	// overloaded operator function for adding ranks of cards
	return a.rank + b.rank;
}

// overloaded operator function to return the rank and hand value
int operator+(const Card &a, int val)
{
	return a.rank + val;
}

// overloaded operator function to display rank
ostream & operator<<(ostream & out, const Rank & r)
{
	switch (r) {
	case Ace: out << "Ace"; break;
	case Two: out << "Two"; break;
	case Three: out << "Three"; break;
	case Four: out << "Four"; break;
	case Five: out << "Five"; break;
	case Six: out << "Six"; break;
	case Seven: out << "Seven"; break;
	case Eight: out << "Eight"; break;
	case Nine: out << "Nine"; break;
	case Ten: out << "Ten"; break;
	case Jack: out << "Jack"; break;
	case Queen: out << "Queen"; break;
	case King: out << "King"; break;
	}
	return out;
}

// overloaded operator function to display suit
ostream & operator<<(ostream & out, const Suit & s)
{
	switch (s) {
	case spade: out << "Spades"; break;
	case heart: out << "Hearts"; break;
	case club: out << "Clubs";	break;
	case diamond: out << "Diamonds"; break;
	}
	return out;
}