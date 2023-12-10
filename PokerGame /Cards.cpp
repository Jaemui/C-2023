// BEK - I inserted some errors, to be found with testing.

#include "Cards.h"

#include <random>
#include <algorithm>

// Function: Constructor
// Purpose: Draws 5 cards from the supplied deck, and sorts them
// by rank
// Input: Takes in a ITPVector of cards for the deck
// Returns: Nothing
PokerHand::PokerHand(std::vector<Card>& deck)
{
	// Draw five cards from the deck
	for (int i = 0; i < 5; i++)
	{
		mHand.push_back(deck.back());
		deck.pop_back();
	}

	// Sort the hand
	sortHand();
}

// Function: getBestPokerHand
// Purpose: Returns a string describing the poker hand this PokerHand
// contains
// Input: None
// Returns: The name of the best poker hand
std::string PokerHand::getBestPokerHand() const
{
	if (hasStraight() && hasFlush())
	{
		return "straight flush";
	}
	else if (hasFourOfAKind())
	{
		return "four of a kind";
	}
	else if (hasFullHouse())
	{
		return "full house";
	}
	else if (hasFlush())
	{
		return "flush";
	}
	else if (hasStraight())
	{
		return "straight";
	}
	else if (hasThreeOfAKind())
	{
		return "three of a kind";
	}
	else if (hasTwoPairs())
	{
		return "two pairs";
	}
	else if (hasPair())
	{
		return "pair";
	}
	else
	{
		return "high card";
	}
}

// Function: hasStraight
// Purpose: Determines if the hand has a straight
// Input: None
// Returns: true if there's a straight
bool PokerHand::hasStraight() const
{
	bool retVal = false;
	if (mHand[0].mRank + 1 == mHand[1].mRank &&
		mHand[1].mRank + 1 == mHand[2].mRank &&
		mHand[2].mRank + 1 == mHand[3].mRank &&
		mHand[3].mRank + 1 == mHand[4].mRank)
	{
		retVal = true;
	}

	return retVal;
}

// Function: hasFlush
// Purpose: Determines if the hand has a flush
// Input: None
// Returns: true if there's a flush
bool PokerHand::hasFlush() const
{
    bool retVal = false;
    if (mHand[0].mSuit == mHand[1].mSuit &&
        mHand[1].mSuit == mHand[2].mSuit &&
        mHand[2].mSuit == mHand[3].mSuit &&
        mHand[3].mSuit == mHand[4].mSuit)
    {
        retVal = true;
    }
	return retVal;
	
}

// Function: hasFourOfAKind
// Purpose: Determines if the hand has a 4 of a kind
// Input: None
// Returns: true if there's a 4 of a kind
bool PokerHand::hasFourOfAKind() const
{
	// Since it's sorted, there are only two possibilities:
	// x x x x y
	// or
	// x y y y y
	bool retVal = false;
	if (mHand[0].mRank == mHand[1].mRank &&
		mHand[1].mRank == mHand[2].mRank &&
		mHand[2].mRank == mHand[3].mRank)
	{
		retVal = true;
	}

	if (mHand[1].mRank == mHand[2].mRank &&
		mHand[2].mRank == mHand[3].mRank &&
		mHand[3].mRank == mHand[4].mRank)
	{
		retVal = true;
	}

	return retVal;
}

// Function: hasFullHouse
// Purpose: Determines if the hand has a full house
// Input: None
// Returns: true if there's a full house
bool PokerHand::hasFullHouse() const
{
	// Since it's sorted, there are only two possibilities:
	// x x x y y
	// or
	// x x y y y
	bool retVal = false;
	if (mHand[0].mRank == mHand[1].mRank &&
		mHand[1].mRank == mHand[2].mRank &&
		mHand[3].mRank == mHand[4].mRank)
	{
		retVal = true;
	}

	if (mHand[0].mRank == mHand[1].mRank &&
		mHand[2].mRank == mHand[3].mRank &&
		mHand[3].mRank == mHand[4].mRank)
	{
		retVal = true;
	}

	return retVal;
}

// Function: hasThreeOfAKind
// Purpose: Determines if the hand has a three of a kind
// Input: None
// Returns: true if there's a three of a kind
bool PokerHand::hasThreeOfAKind() const
{
    bool retVal = false;
    if(mHand[0].mRank == mHand[1].mRank &&
       mHand[1].mRank == mHand[2].mRank)
    {
        retVal = true;
    }
    
    if(mHand[1].mRank == mHand[2].mRank &&
       mHand[2].mRank == mHand[3].mRank)
    {
        retVal = true;
    }
    if(mHand[2].mRank == mHand[3].mRank &&
       mHand[3].mRank == mHand[4].mRank)
    {
        retVal = true;
    }
	return retVal;
	
}

// Function: hasTwoPairs
// Purpose: Determines if the hand has two pairs
// Input: None
// Returns: true if there's two pairs
bool PokerHand::hasTwoPairs() const
{
	// There are three possibilities:
	// x x y y z
	// x y y z z
	// x x y z z
	bool retVal = false;
	if (mHand[0].mRank == mHand[1].mRank &&
		mHand[2].mRank == mHand[3].mRank)
	{
		retVal = true;
	}

	if (mHand[1].mRank == mHand[2].mRank &&
		mHand[3].mRank == mHand[4].mRank)
	{
		retVal = true;
	}

	if (mHand[0].mRank == mHand[1].mRank &&
		mHand[3].mRank == mHand[4].mRank)
	{
		retVal = true;
	}

	return retVal;
}

// Function: hasPair
// Purpose: Determines if there's a pair
// Input: None
// Returns: true if there's a pair
bool PokerHand::hasPair() const
{
    // BEK remove this to fix
	// There's a pair if any neighbors are equal to each other
	bool retVal = false;
	if (mHand[0].mRank == mHand[1].mRank ||
		mHand[1].mRank == mHand[2].mRank ||
		mHand[2].mRank == mHand[3].mRank ||
		mHand[3].mRank == mHand[4].mRank)
	{
		retVal = true;
	}

	return retVal;
}

void PokerHand::sortHand()
{
	// Selection sort
	for (unsigned i = 0; i < mHand.size(); i++)
	{
		// Find the smallest value from element i
		unsigned smallIndex = i;
		Card smallCard = mHand[i];

		// Start looking at i...
		for (unsigned j = i; j < mHand.size(); j++)
		{
			// Is this item smaller?
			if (mHand[j] < smallCard)
			{
				smallCard = mHand[j];
				smallIndex = j;
			}
		}

		// Do the swap
		mHand[smallIndex] = mHand[i];
		mHand[i] = smallCard;
	}
}

// Function: createDeck
// Purpose: Given an empty ITPVector of Cards, inserts a
// standard 52 card deck and shuffles it
// Input: An ITPVector of Cards (by reference)
// Returns: nothing
void createDeck(std::vector<Card>& deck)
{
	for (int i = 0; i < 4; i++)
	{
		Suit suit = Suit(i);
		for (int value = 2; value <= 14; value++)
		{
			deck.push_back(Card(value, suit));
		}
	}

	// Shuffle the deck
	// LEAVE THIS HERE!
	std::sort(&deck[0], &deck[0] + deck.size());
	std::random_shuffle(&deck[0], &deck[0] + deck.size());
}

// Function: << operator for Card
// Purpose: Outputs the name and suit of the card
// Input: ostream and card
// Returns: ostream, with card data output to it
std::ostream& operator<<(std::ostream& os, const Card& card)
{
	// Output value
	if (card.mRank < 11) // Number card
	{
		os << card.mRank;
	}
	else // Face card
	{
		switch (card.mRank)
		{
		case 11:
			os << "Jack";
			break;
		case 12:
			os << "Queen";
			break;
		case 13:
			os << "King";
			break;
		case 14:
			os << "Ace";
			break;
		default:
			os << "Invalid";
			break;
		}
	}

	// Output suit
	os << " of ";
	switch (card.mSuit)
	{
	case CLUBS:
		os << "Clubs";
		break;
	case DIAMONDS:
		os << "Diamonds";
		break;
	case HEARTS:
		os << "Hearts";
		break;
	case SPADES:
		os << "Spades";
		break;
	default:
		os << "Invalid";
		break;
	}

	return os;
}


// Function: < comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left < right
bool operator<(const Card& left, const Card& right)
{
	// If their values are the same, compare the suits
	if (left.mRank == right.mRank)
	{
		return left.mSuit < right.mSuit;
	}
	else
	{
		return left.mRank < right.mRank;
	}
}

// Function: > comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left > right
bool operator>(const Card& left, const Card& right)
{
	// If their values are the same, compare the suits
	if (left.mRank == right.mRank)
	{
		return left.mSuit > right.mSuit;
	}
	else
	{
		return left.mRank > right.mRank;
	}
}

// Function: << operator
// Purpose: Prints out the hand
std::ostream& operator<<(std::ostream& os, const PokerHand& hand)
{
	os << "{ ";
	for (unsigned i = 0; i < hand.mHand.size(); i++)
	{
		if (i < hand.mHand.size() - 1)
		{
			os << hand.mHand[i] << ", ";
		}
		else
		{
			os << hand.mHand[i];
		}
	}
	os << " }";
	return os;
}





/*
* 
* I am commenting out all of the starter code, and pasting
* in the answer, to see if it works.
* 
#include "Cards.h"

#include <random>
#include <algorithm>

// Function: Constructor
// Purpose: Draws 5 cards from the supplied deck, and sorts them
// by rank
// Input: Takes in a ITPVector of cards for the deck
// Returns: Nothing
PokerHand::PokerHand(std::vector<Card>& deck)
{
	// TODO: Complete function
}

// Function: getBestPokerHand
// Purpose: Returns a string describing the poker hand this PokerHand
// contains
// Input: None
// Returns: The name of the best poker hand
std::string PokerHand::getBestPokerHand() const
{
	// TODO: Complete function, fix return value
	return "";
}

// Function: hasStraight
// Purpose: Determines if the hand has a straight
// Input: None
// Returns: true if there's a straight
bool PokerHand::hasStraight() const
{
	// TODO: Complete function, fix return value
	return true;
}

// Function: hasFlush
// Purpose: Determines if the hand has a flush
// Input: None
// Returns: true if there's a flush
bool PokerHand::hasFlush() const
{
	// TODO: Complete function, fix return value
	return true;
}

// Function: hasFourOfAKind
// Purpose: Determines if the hand has a 4 of a kind
// Input: None
// Returns: true if there's a 4 of a kind
bool PokerHand::hasFourOfAKind() const
{
	// TODO: Complete function, fix return value

	return true;
}

// Function: hasFullHouse
// Purpose: Determines if the hand has a full house
// Input: None
// Returns: true if there's a full house
bool PokerHand::hasFullHouse() const
{
	// TODO: Complete function, fix return value
	
	return true;
}

// Function: hasThreeOfAKind
// Purpose: Determines if the hand has a three of a kind
// Input: None
// Returns: true if there's a three of a kind
bool PokerHand::hasThreeOfAKind() const
{
	// TODO: Complete function, fix return value
	
	return true;
}

// Function: hasTwoPairs
// Purpose: Determines if the hand has two pairs
// Input: None
// Returns: true if there's two pairs
bool PokerHand::hasTwoPairs() const
{
	// TODO: Complete function, fix return value

	return true;
}

// Function: hasPair
// Purpose: Determines if there's a pair
// Input: None
// Returns: true if there's a pair
bool PokerHand::hasPair() const
{
	// TODO: Complete function, fix return value

	return true;
}

void PokerHand::sortHand()
{
	// TODO: Complete function
}

// Function: createDeck
// Purpose: Given an empty ITPVector of Cards, inserts a
// standard 52 card deck and shuffles it
// Input: An ITPVector of Cards (by reference)
// Returns: nothing
void createDeck(std::vector<Card>& deck)
{
	// TODO: Complete function
}

// Function: << operator for Card
// Purpose: Outputs the name and suit of the card
// Input: ostream and card
// Returns: ostream, with card data output to it
std::ostream& operator<<(std::ostream& os, const Card& card)
{
	// TODO: Complete function
	return os;
}


// Function: < comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left < right
bool operator<(const Card& left, const Card& right)
{
	// TODO: Complete function, fix return value
	return true;
}

// Function: > comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left > right
bool operator>(const Card& left, const Card& right)
{
	// TODO: Complete function, fix return value
	return true;
}

// Function: << operator
// Purpose: Prints out the hand
std::ostream& operator<<(std::ostream& os, const PokerHand& hand)
{
	// TODO: Complete function
	return os;
}

*/
