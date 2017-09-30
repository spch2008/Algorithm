#include "opt_loser_tree.h"
#include <vector>
#include <iostream>
using namespace std;

int main() {
  vector<int> v1;
  v1.push_back(2);
  v1.push_back(5);

  vector<int> v2;
  v2.push_back(3);
  v2.push_back(6);


  Player* player1 = new Player(v1);
  Player* player2 = new Player(v2);

  LoserTree loser_tree;
  loser_tree.AddPlayer(player1);
  loser_tree.AddPlayer(player2);

  while (loser_tree.PlayNextGame()) {
    LoserTree::Element element = loser_tree.GetWinner();
    cout << "val: " << element.val << endl;
  }
  
  return 0;
}
