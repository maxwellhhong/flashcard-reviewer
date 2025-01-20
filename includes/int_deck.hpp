#ifndef INT_DECK
#define INT_DECK

#include "int_node.hpp"

#include <stdexcept>
#include <cstdlib>
#include <iostream>

class IntDeck {
public:
  IntDeck() = default;
  IntDeck(size_t count);
  ~IntDeck();

  IntNode* GetCurrentFlag() { return current_flag; };
  void SetReinsertedTrue() { reinserted = true; };
  void SetReinsertedFalse() { reinserted = false; };

  void RandomChoose();
  void Reset();

private:
  IntNode* current_flag = nullptr;
  const size_t original_size = 0;
  size_t current_size = 0;
  bool reinserted = true;

  void NumCycleConstructor(size_t count);
  void DeleteIntNodeCycle();
};

void DeleteIntNodeList(IntNode*& current_to_del);
IntNode* TraverseIntNodes(IntNode* start, size_t steps);

#endif