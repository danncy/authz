#ifndef AUTHZ_MAINFRAME_H_
#define AUTHZ_MAINFRAME_H_

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

#include "requrest.h"
#include "plugin.h"

namespace Twf {

  std::unordered_multimap<std::string, std::string> g_hook_plugin_urls;
  std::unordered_map<std::string, Plugin> g_plugin_map;

struct MainFrame {
  MainFrame() = default;
  ~MainFrame() = default;
  
  bool run();
  
private:
  std::vector<std::string> split(const std::string& url,  char delim);

private:
  Request req_;
  Reposne res_;
};

}
#endif // !AUTHZ_MAINFRAM_E_H
