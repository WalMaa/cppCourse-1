#include <iostream>
#include "room.h"

/**
 * Room Default Constructor
 * Creates a blank (uninitialized) room
 */
Room::Room()
    : capacity(0), count(0), max_letters(26), letters(NULL), letterCount(0)
{
	// std::cout << "/* Room: Default constructing */" << std::endl;
 }

/**
 * Main Room constructor
 * Creates an empty room with the given name and capacity
 */
Room::Room(const string & init_name, int init_capacity)
	: name(init_name), capacity(init_capacity), count(0), max_letters(26), letterCount(0)
{
	// std::cout << "/* Room: Param constructing */" << std::endl;
	letters = new Letter[max_letters];
	// std::cout << "Room: Done param constructing" << std::endl;
}

/**
 * Room copy constructor
 */
Room::Room(const Room & other)
{
	copy(other);
}

/**
 * Room assignment operator
 */
Room & Room::operator=(const Room & other)
{
	// std::cout << "/*Room: Assigning room */" << std::endl;
	if (this != &other) {
		clear();
		copy(other);
	}
	// std::cout << "/* Done assigning room */" << std::endl;
	return *this;
}

/**
 * Room destructor
 */
Room::~Room()
{
	// std::cout << "/* Room destructor */" << std::endl;
	clear();
}

/**
 * Allocates a letter group to this room
 */
void Room::addLetter(const Letter & L)
{
	// std::cout << "Room: Adding Letter" << std::endl;
	if (letters != nullptr && letterCount < max_letters)
	{
	// std::cout << "Room: Addletter if at: "<< letterCount << std::endl;
	letters[letterCount++] = L;
	count += L.count;
	}
	// std::cout << "Added Letter. LetterCount: " << letterCount << std::endl;
}

/**
 * Returns the number of empty seats remaining in the room after current
 * allocations
 */
int Room::spaceRemaining()
{
	return capacity - count;
}

/**
 * Outputs the room to cout
 */
void Room::print()
{
	cout << name << " (" << count << "/" << capacity << "):";
	for (int L = 0; L < letterCount; L++)
		cout << " " << letters[L].letter;
	cout << endl;
}

/**
 * Destructor/assignment operator clear helper function
 */
void Room::clear()
{
	if (letters != nullptr){
		delete []letters;
		letters = nullptr;
	}
}

/**
 * Cctor/assignment operator copy helper function
 */
void Room::copy(const Room & other)
{
	name        = other.name;
	capacity    = other.capacity;
	count       = other.count;
	letterCount = other.letterCount;

	letters = new Letter[max_letters];
    for (int i = 0; i < letterCount; ++i) {
        letters[i] = other.letters[i];
	}
}

