#ifndef INT_NODE_HPP
#define INT_NODE_HPP

struct IntNode {
  int num = -1;
  IntNode* next = nullptr;
  IntNode(unsigned int num): num(num) {}
  IntNode(unsigned int num, IntNode* next): num(num), next(next) {}
};

#endif