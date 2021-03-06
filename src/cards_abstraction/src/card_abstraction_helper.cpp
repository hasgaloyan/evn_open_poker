#include "card_abstraction_helper.h"

#include <climits>
  
void CardsAbstractionHelper::add_card(
    const Card* c,
    std::vector<std::vector<uint8_t>> *possible_combination) {
  possible_combination->at(c->get_suit()).push_back(c->get_rank());
}

void CardsAbstractionHelper::sort_vector(std::vector<std::vector<uint8_t>> *possible_combination){
    for (uint32_t s = 0; s < possible_combination->size(); ++s) {
        sort(possible_combination->at(s).begin(), possible_combination->at(s).end());
    }
    sort(possible_combination->begin(), possible_combination->end());
}

void CardsAbstractionHelper::erase_emptys(std::vector<std::vector<uint8_t>> *possible_combination){
  for (uint32_t d=0;d<possible_combination->size();d++) {
    if (possible_combination->at(d).empty()) {
      possible_combination->erase(possible_combination->begin()+d);
      --d;
    }
  }
}

void CardsAbstractionHelper::river_optimezer(std::vector<std::vector<uint8_t>> *possible_combination){
  for (uint32_t r = 0; r < possible_combination->size(); r++) {
    if (possible_combination->at(r).size() == 2) {
      possible_combination->resize(possible_combination->size()+1);
      possible_combination->at(possible_combination->size()-1).push_back(possible_combination->at(r)[1]);
      possible_combination->at(r).pop_back();
    }
  }
}

void CardsAbstractionHelper::insert_(
    std::vector<std::vector<uint8_t >> *possible_combination, 
    std::vector<Card>* cards,
    uint32_t *index,
    std::unordered_map<size_t, uint32_t> *index_table,
    std::unordered_map<uint32_t, std::vector<Card>> *card_table) {
  size_t hash_=hash(possible_combination);
  size_t initial_size = index_table->size();

  index_table->insert({{hash_,*index}});
  if(initial_size < index_table->size()) {
      card_table->insert({{*index,*cards}});
      ++(*index);
  }
}

size_t CardsAbstractionHelper::hash(const std::vector<std::vector<uint8_t >>* v) {
    std::hash<uint8_t > hasher;
    size_t seed = 0;
    int helper = INT_MAX;
    for(std::vector<uint8_t > i: *v) {
        for (int j : i) {
            seed ^= hasher(j) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        helper += 55;
        seed ^= hasher(helper) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

