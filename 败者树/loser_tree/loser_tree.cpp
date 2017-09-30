#include "loser_tree.h"
#include <iostream>

#define LOSER_TREE_SENTINEL -1
#define LOSER_TREE_MAX_VALUE INT_MAX

LoserTree::LoserTree() {
  is_build_ = false;
}

LoserTree::~LoserTree() {
  for (size_t i = 0; i < players_.size(); ++i) {
    delete players_[i];
  }
}

void LoserTree::AddPlayer(Player* player) {
  if (player) {
    players_.push_back(player);
  }
}

bool LoserTree::BuildTree() {
  if (players_.empty()) {
    return false;
  }

  // Init inner node.
  inner_node_.reserve(players_.size());
  for (size_t i = 0; i < players_.size(); ++i) {
    inner_node_.push_back(LOSER_TREE_SENTINEL);
  }

  for (int i = players_.size() - 1; i >= 0; --i) {
    BuildImpl(i);
  }

  return true;
}

void LoserTree::BuildImpl(const int player_slot) {
  int winner_slot = player_slot;
  int slot = player_slot + inner_node_.size();
  for (int parent = slot / 2; parent > 0; parent /= 2) {
    int parent_slot = inner_node_[parent];
    if (parent_slot == LOSER_TREE_SENTINEL) {
      inner_node_[parent] = winner_slot;
      break;
    }

    // winner becomes loser, record loser.
    if (players_[winner_slot]->Value() >
        players_[parent_slot]->Value()) {
      inner_node_[parent] = winner_slot;
      winner_slot = parent_slot;
    }
  }

  // Update winner.
  inner_node_[0] = winner_slot;
}

bool LoserTree::PlayNextGame() {
  if (!is_build_) {
    is_build_ = true;
    return BuildTree();
  }

  if (inner_node_.empty()) {
    return false;
  }

  int winner_slot = inner_node_[0];
  if (winner_slot == LOSER_TREE_SENTINEL ||
      players_[winner_slot]->Value() == LOSER_TREE_MAX_VALUE) {
    return false;
  }
  
  players_[winner_slot]->Next();
  BuildImpl(winner_slot);

  return players_[inner_node_[0]]->Value() != LOSER_TREE_MAX_VALUE;
}

LoserTree::Element LoserTree::GetWinner() {
  int winner_slot = inner_node_[0];
  Element element;
  element.val = players_[winner_slot]->Value();
  element.user_data = players_[winner_slot];
  return element;
}


Player::Player(const std::vector<int>& container) 
    : container_(container) {
  container_index_ = 0;
}

Player::~Player() {
}

void Player::Next() {
  container_index_++;
}

int Player::Value() {
  if (container_index_ < container_.size()) {
    return container_[container_index_];
  } else {
    return LOSER_TREE_MAX_VALUE;
  }
}
