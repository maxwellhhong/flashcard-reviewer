#include "int_deck.hpp"
#include "int_node.hpp"

IntDeck::IntDeck(size_t count) : original_size(count), current_size(count) {
  NumCycleConstructor(count);
  srand(time(NULL));
}

IntDeck::~IntDeck() {
  if (current_flag == nullptr) { return; }
  DeleteIntNodeCycle();
  current_flag = nullptr;
  current_size = 0;
  reinserted = true;
}

void IntDeck::RandomChoose() {
  if (!reinserted) {
    IntNode* temp = current_flag->next;
    current_flag->next = temp->next;
    delete temp;
    --current_size;
  }

  if (current_size == 0) {
    current_flag = nullptr;
    Reset();
  }
  reinserted = true;

  size_t steps = (rand() % current_size);
  current_flag = TraverseIntNodes(current_flag, steps);
}

void IntDeck::Reset() {
  DeleteIntNodeCycle();
  NumCycleConstructor(original_size);
  current_size = original_size;
  reinserted = true;
}

void IntDeck::DeleteIntNodeCycle() {
  if (current_flag == nullptr) { return; }
  IntNode* temp = current_flag->next;
  current_flag->next = nullptr;
  DeleteIntNodeList(temp);
}

void DeleteIntNodeList(IntNode*& current_to_del) {
  if (current_to_del == nullptr) { return; }
  IntNode* next_to_del = current_to_del->next;
  delete current_to_del;
  DeleteIntNodeList(next_to_del);
}

IntNode* TraverseIntNodes(IntNode* start, size_t steps) {
  for (size_t i = 0; i < steps; i++) {
    if (start == nullptr) { throw new std::invalid_argument("Traversal exceeds list length"); }
    start = start->next;
  }
  return start;
}

void IntDeck::NumCycleConstructor(size_t count) { // creates a num cycle with current_flag pointing at arbitrary node
  for (size_t i = 0; i < count; i++) {
    IntNode* temp = new IntNode(i, current_flag);
    current_flag = temp;
  }
  TraverseIntNodes(current_flag, count - 1)->next = current_flag;
}
