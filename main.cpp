#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

#include "mainframe.h"

int main()
{
    Twf::Request req;
    Twf::Request res;
    std::unique_ptr<Twf::MainFrame> mainframe(new Twf::MainFrame(req, res));
    mainframe->run();

    return 0;
}