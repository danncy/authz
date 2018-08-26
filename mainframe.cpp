#include "mainframe.h"
#include "common.h"
#include <sstream>

namespace Twf {

const std::string kEnter = "__enter";
const std::string kDefault = "default";
const std::string kExit = "__exit";

std::vector<string> MainFrame::split(const std::string& str, char delim) {
  std::stringstream ss(str);
  std::vector<string> elems;
  std::string el;

  while(std::getline(ss, el, delim)) {
    elems.emplace_back(el);
  }

  return elems;
}

bool MainFrame::run() {
  std::string url = "auth/test";
  std::vector<string> v = split(url, '/');

  if (v.size() != 2) {
    // LOG error.
    return false;
  }

  std::vector<string> exec_urls;
  exec_urls.emplace_back(v[0] + "/" + kEnter);
  exec_urls.emplace_back(url  + "/" + kEnter);
  exec_urls.emplace_back(url  + "/" + kDefault);
  exec_urls.emplace_back(url  + "/" + kExit);
  exec_urls.emplace_back(v[0] + "/" + kExit);

  int rv = PluginFailed;

  for (auto el : exec_urls) {
    if (el.compare("auth/test/default")) {
      // TODO
      // auth/test/default should be finished in  auth/test/__enter
      continue;
    }
    auto it = g_plugin_map.find(el);
    if (it != g_plugin_map.end()) {
      rv = it->second.run();
      switch(rv) {
        case PluginFailed : {
          break;
        }
        case PluginOK : {
          break;
        }
        case PluginContinue : {
          break;
        }
        default : {
          break;
        }
      }
    }
  }

  return true;
}

}