#include "opt_loser_tree.h"
#include <iostream>

#define LOSER_TREE_SENTINEL -1
#define LOSER_TREE_MAX_VALUE INT_MAX

LoserTree::LoserTree() {
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

  int match_size = std::max(2, static_cast<int>(players_.size()));
  matches_.clear();
  matches_.reserve(match_size);
  for (int i = 0; i < match_size; ++i) {
    Match match;
    match.loser  = LOSER_TREE_SENTINEL;
    match.winner = LOSER_TREE_SENTINEL;
    matches_.push_back(match);
  }

  // Init leaf node.
  for (int i = players_.size() - 1; i >= 0; --i) {
    int player_index = i + matches_.size();
    int match_index =  player_index / 2;

    int& loser  = matches_[match_index].loser;
    int& winner = matches_[match_index].winner;

    if (loser == LOSER_TREE_SENTINEL || winner == LOSER_TREE_SENTINEL) {
      winner = i;
      loser = i;
    } else if (players_[i]->Value() > players_[loser]->Value()) {
      loser = i;
    } else {
      winner = i;
    }
  }

  // Build match node.
  for (int i = matches_.size() - 1; i > 1; --i) {
    int parent = i / 2;
    int& winner = matches_[parent].winner;
    int& loser  = matches_[parent].loser;

    if ((i & 1) == 0) { // does not has brother
      int curr_winner = matches_[i].winner;
      if (players_[curr_winner]->Value() > players_[winner]->Value()) {
        loser = curr_winner;
      } else {
        winner = curr_winner;
      }
    } else {
      int right_winner = matches_[i].winner;
      int left_winner = matches_[--i].winner;

      if (players_[right_winner]->Value() >
          players_[left_winner]->Value()) {
        winner = left_winner;
        loser  = right_winner;
      } else {
        winner = right_winner;
        loser  = left_winner;
      }
    }
  }
  return true;
}

/*
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
*/

void LoserTree::Adjust(const int player) {
  int winner = player;
  int son = player + matches_.size();
  for (int parent = son / 2; parent > 0; parent /= 2) {
    int& parent_loser  = matches_[parent].loser;
    int& parent_winner = matches_[parent].winner;

    if (players_[winner]->Value() > players_[parent_loser]->Value()) {
      parent_winner = parent_loser;
      parent_loser  = winner;
    } else {
      parent_winner = winner;
    }
    winner = parent_winner;
  }
}

bool LoserTree::PlayNextGame() {
  if (matches_.empty()) {
    return BuildTree();
  }

  if (matches_.size() <= 1) {
    return false;
  }

  const int& winner = matches_[1].winner;
  players_[winner]->Next();

  Adjust(winner);
  return players_[winner]->Value() != LOSER_TREE_MAX_VALUE;
}

LoserTree::Element LoserTree::GetWinner() {
  int winner = matches_[1].winner;
  Element element;
  element.val = players_[winner]->Value();
  element.user_data = players_[winner];
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
