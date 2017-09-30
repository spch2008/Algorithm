

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
  struct Match {
    int loser;
    int winner;
  };

  bool BuildTree();
  void Adjust(const int player);

  std::vector<Player*> players_;
  std::vector<Match> matches_;
};


#endif
