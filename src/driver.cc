#include "int_deck.hpp"
#include "deck.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main() { // Bug: [s]how will return a card even if user has not drawn a card yet or has already reinserted the card.

  const std::string kFlashdeckFile = "./flashdecks/flashdeck-example1.txt";
  Deck thingy = Deck(kFlashdeckFile);
  thingy.Interface();

  thingy.~Deck(); // destructor for good practice :)
}

// I don't really feel like implementing a command for reassigning "front" and "back" sides right now.