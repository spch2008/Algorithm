

#ifndef _LOSER_TREE_H_
#define _LOSER_TREE_H_

#include <climits>
#include <vector>

class Player {
 public:
  explicit Player(const std::vector<int>& container);
  ~Player();

  void Next();
  int Value();

 private:
   const std::vector<int>& container_;
   int container_index_;
};

class LoserTree {
 public:
  struct Element {
    int val;
    void* user_data;
  };

  LoserTree();
  ~LoserTree();

  // AddPlayer takes the ownership of player.
  void AddPlayer(Player* player);
  bool PlayNextGame();
  Element GetWinner();

 private:

  bool BuildTree();
  void BuildImpl(const int players_slot);

  bool is_build_;
  std::vector<Player*> players_;
  std::vector<int> inner_node_;
};


#endif
