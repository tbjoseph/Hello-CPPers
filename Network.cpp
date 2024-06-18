/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file
  std::ifstream file = std::ifstream(fileName);
  if (!file.is_open()) throw std::invalid_argument("Cannot open file"); //check if file opened corrctly

  string text0;
  string text1;
  int text2;

  string line0;
  while (getline(file, line0)) {
    std::istringstream line(line0);
    line >> text0;
    if (text0 == "User") {
      text0 = "";
      line >> text0;
      try {
        addUser(text0);
      }
      catch(std::invalid_argument) {
        throw std::runtime_error("File contains invalid data");
      }

    }
    else if (text0 == "Post") {
      if ( !(line >> text2) ) throw std::runtime_error("File contains invalid data"); //ID
      line >> text0; //Username
      getline(line, text1); //Post contents
      try {
      addPost(text2, text0, text1);
      }
      catch(std::invalid_argument) {
        throw std::runtime_error("File contains invalid data");
      }
    }
    else throw std::runtime_error("File contains invalid data");
  }

}

void Network::addUser(string userName) {
  // TODO(student): create user and add it to network
  for (unsigned int i = 0; i < userName.size(); i++) userName.at(i) = tolower(userName.at(i));

  for (unsigned int i = 0; i < users.size(); i++) {
    if (users.at(i)->getUserName() == userName) throw std::invalid_argument("add user");
  }

  User* x = new User(userName);
  users.push_back(x);
  std::cout << "Added User " << userName << std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
  // TODO(student): create post and add it to network
  for (unsigned int i = 0; i < posts.size(); i++) {
    if (posts.at(i)->getPostId() == postId) throw std::invalid_argument("add post");
  }

  bool found0 = false;
  for (unsigned int i = 0; i < users.size(); i++) {
    if (users.at(i)->getUserName() == userName) found0 = true;
  }
  if (!found0) throw std::invalid_argument("add post");

  Post* x = new Post(postId, userName, postText);
  posts.push_back(x);
  

  for (unsigned int i = 0; i < users.size(); i++) {
    if (users.at(i)->getUserName() == userName) users.at(i)->addUserPost(x);
  }

  for (unsigned int i = 0; i < x->findTags().size(); i++) {
    bool found = false;
    for (unsigned int j = 0; j < tags.size(); j++) {
      if (x->findTags().at(i) == tags.at(j)->getTagName()) found = true;
    }
    if (!found) {
      try {
        Tag* y = new Tag(x->findTags().at(i));
        tags.push_back(y);
      }
      catch(std::invalid_argument) {}
    }
  }

  for (unsigned int i = 0; i < x->findTags().size(); i++) {
    for (unsigned int j = 0; j < tags.size(); j++) {
      if (x->findTags().at(i) == tags.at(j)->getTagName()) tags.at(j)->addTagPost(x); 
    }
  }

  std::cout << "Added Post " << postId << " by " << userName << std::endl;

}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user
  for (unsigned int i = 0; i < users.size(); i++) {
    if (users.at(i)->getUserName() == userName) return users.at(i)->getUserPosts();
  }
  throw std::invalid_argument("get posts by user");
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag
  for (unsigned int i = 0; i < tags.size(); i++) {
    if (tags.at(i)->getTagName() == tagName) return tags.at(i)->getTagPosts();
  }
  throw std::invalid_argument("get posts by tag");
}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts
  vector<string> x;

  unsigned int max = tags.at(0)->getTagPosts().size();
  for (unsigned int i = 1; i < tags.size(); i++) {
    if (tags.at(i)->getTagPosts().size() > max) max = tags.at(i)->getTagPosts().size();
  }
  for (unsigned int i = 0; i < tags.size(); i++) {
    if (tags.at(i)->getTagPosts().size() == max) x.push_back( tags.at(i)->getTagName() );
  }
  return x;
}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
