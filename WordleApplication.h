#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

/*
 
A simple hello world application class which demonstrates how to react
to events, read input, and give feed-back.
*/
class WordleApplication : public Wt::WApplication
{
public:
  WordleApplication(const Wt::WEnvironment& env);

  std::string pickRandWrd();
private:
  Wt::WLineEdit *nameEdit;
  Wt::WText     *greeting;
  // std::string correctWord;
  void check(); 
};
