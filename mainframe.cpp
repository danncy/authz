#include "mainframe.h"
#include "common.h"
#include <sstream>
#include <boost/algorithm/string.hpp>

namespace Twf {

std::unordered_multimap<std::string, std::string> g_hook_plugin_urls {
    {"auth/psw/__enter", "auth/psw/__enter/login"},
    {"auth/psw/__exit", "auth/psw/__enter/logout"},
    {"auth/psw/__exit", "auth/psw/__enter/logout1"}
};

std::unordered_map<std::string, Plugin> g_plugin_map {
    {"auth/psw/__enter/login", Plugin()},
    {"auth/psw/__exit/logout", Plugin()},
    {"auth/psw/__exit/logout1", Plugin()},
    {"auth/sms/default", Plugin()},
};

const std::string kEnter = "__enter";
const std::string kDefault = "default";
const std::string kExit = "__exit";

MainFrame::MainFrame(const Request& req, const Response& res) 
  : req_(req),
    res_(res) {

}

bool MainFrame::addService(const std::string& service_name) {
  if (service_name.empty()) {
    // TODO
    // LOG ERROR
    return false;
  }

  service_chain_.emplace_back(service_name);
  return true;
}

bool MainFrame::addPlugin(const std::string& plugin_url, PluginRelation relation = AND) {
  if (plugin_url.empty()) {
    // TODO
    // LOG ERROR
    return false;
  }

  auto iter = g_plugin_map.find(plugin_url);
  if (iter == g_plugin_map.end()) {
    // TODO
    // LOG need
    return false;
  }

  switch(relation) {
    case AND :
      plugin_chain_.emplace_back(iter->second);
      break;
    case OR :
      multi_choice_plugin_chain_.emplace_back(iter->second);
      break;
    default:
      break;
  }

  return true;
}

bool MainFrame::run() {
  std::string url = "auth/test";
  std::vector<std::string> v;
  url = boost::trim_copy_if(url, boost::is_any_of("/"));
  boost::split(v, url, boost::is_any_of("/"), boost::token_compress_on);

  if (v.size() != 2) {
    // LOG error.
    return false;
  }

  std::vector<std::string> exec_urls;
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
      if (!handlePluginResult(it->second.run(&req_, &res_))) {
        break;
      }
    }
  }

  return true;
}

bool MainFrame::handlePluginResult(int result) {
  bool ret = true;

  switch(result) {
    case PluginFailed : {
      ret = false;
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

  return ret;
}

}