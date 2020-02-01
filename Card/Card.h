/*
Author:		Dawid Jasionowski
Class:		CIS-2542-002
Date:		10/06/2018
File:		Card.h; specification file for the Card class
Descr:
This program uses the card, deck, and player classes to run
a simple simulation of a card game. Each turn, players' names
are displayed, one card from each player is discarded, and
the value of the cards for each player is displayed. The
program ends when all the cards have been played.
*/

#pragma once
#include <string>
#include <iostream>

using namespace std;

// using enumerated type for card ranks
enum Rank {
	Ace = 1,
	Two = 2,
	Three = 3,
	Four = 4,
	Five = 5,
	Six = 6,
	Seven = 7,
	Eight = 8,
	Nine = 9,
	Ten = 10,
	Jack = 11,
	Queen = 12,
	King = 13,
};

// using enumerated type for card suits
enum Suit { spade, heart, club, diamond };

// Card class declaration
class Card
{
private:
	// members
	Suit suit;
	Rank rank;

public:
	// constructors
	Card();
	Card(Suit, Rank);

	// deconstructor
	~Card();

	// accessor functions
	Suit getSuit() const;
	int getRank() const;

	// mutator functions
	void setSuit(Suit newsuit);
	void setRank(Rank newrank);

	// overloaded operator function to display rank and suit
	friend ostream & operator << (ostream&, const Card&);
	// overloaded operator function to return combined value of cards
	friend int operator+(const Card &a, const Card&b);
	// overloaded operator function to return rank and hand value
	friend int operator+(const Card &a, int val);
	// overloaded operator function to assign suit and rank
	void operator=(const Card &a);
};
// overloaded operator function to display rank
ostream & operator<< (ostream& out, const Rank &r);
// overloaded operator function to display suit
ostream & operator<< (ostream& out, const Suit &s);