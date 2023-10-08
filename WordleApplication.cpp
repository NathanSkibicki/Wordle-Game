
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "WordleApplication.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <set>


//std::string correctWord = pickRandWrd();

WordleApplication::WordleApplication(const Wt::WEnvironment& env)
  : WApplication(env)
{

  std::string filename = "wordlist.txt";

  setTitle("Wordle Game");  // application title
  root()->addWidget(std::make_unique<Wt::WText>("Enter guess, 5 letters maximum: ")); // show some text

  nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>()); // allow text input
  nameEdit_->setFocus();                              // give focus

  auto button = root()->addWidget(std::make_unique<Wt::WPushButton>("Guess"));  
                                                      // create a button
  button->setMargin(5, Wt::Side::Left);                   // add 5 pixels margin

  root()->addWidget(std::make_unique<Wt::WBreak>());    // insert a line break// empty text

  /*
   * Connect signals with slots
   *
   * - simple Wt-way: specify object and method
   */
  button->clicked().connect(this, &WordleApplication::check);

  /*
   * - using an arbitrary function object, e.g. useful to bind
   *   values with std::bind() to the resulting method call
   */
  nameEdit_->enterPressed().connect(std::bind(&WordleApplication::check, this));

  /*
   * - using a lambda:
   */
  button->clicked().connect([=]() {
      std::cerr << "" << nameEdit_->text() << std::endl;
  });
}


void WordleApplication::check()
{
  /*
   * Update the text, using text input into the nameEdit_ field.
   */
  std::string userGuess = nameEdit_->text().toUTF8();
  std::string correctWord = pickRandWrd();
  int counter = 0;
  std::set <std::string> lSet = {};
  

  //add letters to set
  for (int i = 0; i < correctWord.length(); ++i){
    std::string currLetter = correctWord.substr(i, 1);
    lSet.insert(currLetter);
  }
  //check each indiv letter
  for (int j = 0; j < userGuess.length(); ++j){
    std:: string currUserChar = userGuess.substr(j, 1);
    std::set<std::string>::iterator itr = lSet.find(currUserChar);

  //if user guesses the correct word, prompt them to play again
    if (userGuess == correctWord){
      auto character = root()->addWidget(std::make_unique<Wt::WText>("<span style= 'color: green;'>" + userGuess + "</span>"));
      root()->addWidget(std::make_unique<Wt::WText>("Congratulations! You guessed the word correctly."));
    
      // Add a button to play again
      auto playAgainButton = root()->addWidget(std::make_unique<Wt::WPushButton>("Play Again"));
      playAgainButton->clicked().connect([=]() {
      // Reset the game by picking a new random word
      std::string correctWord = pickRandWrd();
      // Clear the previous game's output
      root()->clear();
      // Call the check function to start a new game
      check();
    });
    }
    
    //letter is right spot
    if (currUserChar == correctWord.substr(j, 1)){
      auto character = root()->addWidget(std::make_unique<Wt::WText>("<span style= 'color: green;'>" + currUserChar + "</span>"));
    }
    //letter not in word
    else if (itr == lSet.end()){
      auto character = root()->addWidget(std::make_unique<Wt::WText>(currUserChar));
    }
    //letter in word, wrong spot
    else {
      auto character = root()->addWidget(std::make_unique<Wt::WText>("<span style= 'color: red;'>" + currUserChar + "</span>"));
    }
  }
  counter += 1;

  if (counter == 6){
    root()->addWidget(std::make_unique<Wt::WText>("all guesses reached"));
  }

  //newline
  auto lineBreak = root()->addWidget(std::make_unique<Wt::WBreak>());
}


std::string WordleApplication::pickRandWrd()
{
  std::vector<std::string> words;
  std::ifstream file("wordlist.txt"); 
  std::string word;
  while (file >> word) {
      words.push_back(word);
  }
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  // Generate a random index to pick a word
  int randomIndex = std::rand() % words.size();

  return words[randomIndex];
}
