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
#include <string>
#include <stdexcept>
#include "Post.h"
#include <sstream>

using std::string;
using std::vector;
using std::istringstream;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  // TODO(student): extracts candidate tags based on occurrences of # in the post
  istringstream tagText(postText);
  string text;
  string add;
  vector<string> tags;
  bool last;
  while (tagText >> text) {
    last = true;
    if (text.at(0) == '#') {
      for (int i = text.size() - 1; i >= 0; i--) {
        if ( isalpha(text.at(i)) || (text.at(i) == '#') ) {
          text.at(i) = tolower(text.at(i));
          last = false;
        }
        else if (last) text.pop_back();
      }
      tags.push_back(text);
    }
  }

  return tags;
  
}
