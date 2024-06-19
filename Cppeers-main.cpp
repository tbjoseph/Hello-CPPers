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
#include "Network.h"

using std::cout, std::cin, std::endl;
using std::string, std::vector;

void printMenu() {
  cout << "Welcome to CPPeers" << endl;
  cout << "The options are: " << endl;
  cout << "1. load data file and add information" << endl;
  cout << "2. show posts by user" << endl;
  cout << "3. show posts with hashtag" << endl;
  cout << "4. show most popular hashtag" << endl;
  cout << "9. quit" << endl;
  cout << "--------> Enter your option: ";
}

void processLoad(Network& cppeers) {
  string fileName = "";
  cout << "Enter filename: ";
  cin >> fileName;
  cppeers.loadFromFile(fileName);
  printf("\n");
}

void processPostsByUser(Network& cppeers) {
  // TODO(student): implement
  string userName;

  cout << "Enter username: " << endl;
  cin >> userName;

  for (unsigned int i = 0; i < cppeers.getPostsByUser(userName).size(); i++) {
    cout << cppeers.getPostsByUser(userName).at(i)->getPostText() << endl;
  }

  printf("\n");
}

void processPostsWithHashtags(Network& cppeers) {
  // TODO(student): implement
  string tag;

  cout << "Enter tagname: ";
  cin >> tag;

  for (unsigned int i = 0; i < cppeers.getPostsWithTag(tag).size(); i++) {
    cout << cppeers.getPostsWithTag(tag).at(i)->getPostText() << endl;
  }

  printf("\n");
}

void processMostPopularHashtag(Network& cppeers) {
  // TODO(student): implement

  vector<string> tags = cppeers.getMostPopularHashtag();

  for (unsigned int i = 0; i < tags.size(); i++) {
    cout << tags.at(i) << endl;
  }

  printf("\n");
}

int main() {

  Network cppeers;

  int choice = 0;

  // present menu
  do {
    printMenu();

    if ( !(cin >> choice) ) {
      std::cin.clear();  // Clear error flags
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore incorrect input until the end of line
      std::cout << "Invalid input. Must enter an integer.\n\n";
      continue;
    }

    switch(choice) {
      case 1: {
        processLoad(cppeers);
        break;
      }
      case 2: {
        processPostsByUser(cppeers);
        break;
      }
      case 3: {
        processPostsWithHashtags(cppeers);
        break;
      }
      case 4: {
        processMostPopularHashtag(cppeers);
        break;
      }
      default: break;
    }
  } while (choice != 9);


  return 0;
}

//TAMU-csce121-small.txt
//ajitjain
