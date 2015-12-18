//This code is adapted from Bison 3.0.2's Calc++ example

#include "ul-driver.hh"
#include "ul-parser.hh"
#include <iostream>

ul_driver::ul_driver()
  : trace_scanning (false), trace_parsing (false)
{
//  variables["one"] = 1;
//  variables["two"] = 2;
    currentBranch = &script;
}

ul_driver::~ul_driver()
{
}

int ul_driver::parse(const std::string &f)
{
  file = f;
  scan_begin();
  yy::ul_parser parser(*this);
  parser.set_debug_level(trace_parsing);
  int res = parser.parse();
  scan_end();
  return res;
}

void ul_driver::error(const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void ul_driver::error(const std::string& m)
{
  std::cerr << m << std::endl;
}

void ul_driver::pushLine()
{
    dialogueLine line;
    lineStack.push(line);
}

void ul_driver::popLineToScript()
{
    currentBranch->push_back(lineStack.top());
    lineStack.pop();
    std::cout<<"line added\n";
}

dialogueLine& ul_driver::getCurrentLine()
{
    return lineStack.top();
}

void ul_driver::printScript(std::vector<dialogueLine>* script)
{
    for (std::vector<dialogueLine>::iterator it = script->begin(); it != script->end(); ++it)
    {
        std::cout<<"NEW LINE ====="<<std::endl;
        std::cout<<"Character: "<<(*it).character<<std::endl;
        std::cout<<"Expression: "<<(*it).expression<<std::endl;
        std::cout<<"Dialogue: "<<(*it).dialogue<<std::endl;
        if ((*it).hasOptions)
        {
            std::cout<<"Option 1: "<<(*it).option1<<" Option 2: "<<(*it).option2<<std::endl;
            std::cout<<"NEW BRANCH - OPTION 1 *******************"<<std::endl;
            printScript(&(*it).branch1);
            std::cout<<"NEW BRANCH - OPTION 2 *******************"<<std::endl;
            printScript(&(*it).branch1);
            std::cout<<"END OF BRANCH *******************"<<std::endl;
        }
        else
        {
            std::cout<<"This is not an option line"<<std::endl;
        }
    }
}

void ul_driver::printLine(dialogueLine line)
{
    std::cout<<"NEW LINE ====="<<std::endl;
    std::cout<<"Character: "<<line.character<<std::endl;
    std::cout<<"Expression: "<<line.expression<<std::endl;
    std::cout<<"Dialogue: "<<line.dialogue<<std::endl;
    if (line.hasOptions)
    {
        std::cout<<"Option 1: "<<line.option1<<" Option 2: "<<line.option2<<std::endl;
    }
    else
    {
        std::cout<<"This is not an option line"<<std::endl;
    }
    std::cout<<"=============="<<std::endl;
}

void ul_driver::pushBranch()
{
    //lineStack.push(line);
    currentBranch = &lineStack.top().branch1;
    isProcessingBranch1 = true;
    std::cout<<"branch pushed\n";
}

void ul_driver::switchToBranch2()
{
    currentBranch = &lineStack.top().branch2;
    isProcessingBranch1 = false;
    std::cout<<"branch switched\n";
}

void ul_driver::popBranch()
{
    if (!lineStack.empty())
    {
        if (isProcessingBranch1)
        {
            currentBranch = &lineStack.top().branch1;
            std::cout<<"popped to branch 1\n";
        }
        else
        {
            currentBranch = &lineStack.top().branch2;
            std::cout<<"popped to branch 2\n";
        }
    }
    else
    {
        std::cout<<"invalid pointer, dummy"<<std::endl;
        currentBranch = &script;
    }
    
    //lineStack.pop();
}
