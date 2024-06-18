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
#include "User.h"

using std::string;
using std::vector;

User::User(string userName) /* TODO(student): initialize */ : userName(userName) {
  // TODO(student): implement constructor checks
  if (userName == "") throw std::invalid_argument("post constructor: invalid parameter values");
  if (!isalpha(userName.at(0))) throw std::invalid_argument("post constructor: invalid parameter values");

  for (unsigned int i = 0; i < userName.size(); i++) {
    if (isupper(userName.at(i))) throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

string User::getUserName() {
  // TODO(student): implement getter
  return userName;
}

vector<Post*>& User::getUserPosts() {
  // TODO(student): implement getter
  return userPosts;
}

void User::addUserPost(Post* post) {
  // TODO(student): add post to user posts
  if(post == nullptr) {
    throw std::invalid_argument("addUserPost");
  }
  userPosts.push_back(post);
}
