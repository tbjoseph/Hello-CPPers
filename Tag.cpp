/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName) : /* TODO(student): initialize */ tagName(tagName) {
  // TODO(student): implement constructor checks
  if (tagName.size() < 2) throw std::invalid_argument("post constructor: invalid parameter values");
  if (tagName.at(0) != '#') throw std::invalid_argument("post constructor: invalid parameter values");
  if (!isalpha(tagName.at(1))) throw std::invalid_argument("post constructor: invalid parameter values");
  
  for (unsigned int i = 1; i < tagName.size(); i++) {
    if (isupper(tagName.at(i))) throw std::invalid_argument("post constructor: invalid parameter values");
  }

  switch (tagName.at(tagName.size()-1)) {
    case '!':
    case ',':
    case '.':
    case '?':
      throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

string Tag::getTagName() {
  // TODO(student): implement getter
  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  // TODO(student): implement getter
  return tagPosts;
}

void Tag::addTagPost(Post* post) {
  // TODO(student): add post to tag posts
  if(post == nullptr) {
    throw std::invalid_argument("addTagPost");
  }
  tagPosts.push_back(post);

}

//g++ -std=c++17 -Wall -Wextra -pedantic -g -fsanitize=address,undefined Network.cpp User.cpp Post.cpp Tag.cpp Cppeers-main.cpp