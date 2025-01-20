#ifndef DECK_HPP
#define DECK_HPP

#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <cctype>

#include "int_deck.hpp"

class Deck {
public:
  Deck() = delete;
  Deck(const std::string &filename);
  ~Deck();
  std::string** Flashcards() { return flashcards; };

  void Draw();
  void Show();
  void PrintSide(size_t side);
  void Reset() { (*shuffle_representation).Reset(); show_lock = true; };
  void Reinsert() { (*shuffle_representation).SetReinsertedTrue(); }
  // void SetDefaultSide();
  void Interface();
private:
  std::string** flashcards;
  size_t flashcards_len = 0;
  size_t flashcards_width = 0;
  IntDeck* shuffle_representation;

  bool show_lock = true;
  size_t default_front = 0;
  size_t default_back = 1;

  std::string GetSide(size_t card_num, size_t side) { return flashcards[card_num][side]; };
  void CommandInterpreterDigit();
  void CommandInterpreterChar(char ch);
};

void ConstructEmpty2dStringArray(std::string** &ptr, size_t length, size_t width);
void Fill2dStringArray(std::ifstream &input, std::string** &ptr, size_t length, size_t width);

void ClearTerm();
void Help();
void More();
void FlashcardDeckFormatting();

#endif