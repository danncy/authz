#include "request.h"
#include "mainframe.h"

namespace Twf {

Request::Request() {}

Request::~Request() {
  mainframe_.reset();
}

void Request::assign(const std::string& key, const std::string& value) {
  params_[key] = value;
}

bool Request::hasKey(const std::string& key) {
  return params_.find(key) != params_.end();
}

std::string& Request::operator[](const std::string& key) {
  if (!hasKey(key))
    return undefined_;

  return params_[key];
}

std::string& Request::operator[](std::string&& key) {
  if (!hasKey(key))
    return undefined_;

  return params_[key];
}

bool Request::addService(const std::string& service_name) {
  auto mainframe = mainframe_.lock();
  if (!mainframe) {
    // LOG ERROR
    return false;
  }

  return mainframe->addService(service_name);
}

bool Request::addPlugin(const std::string& plugin_url, PluginRelation relation) {
  auto mainframe = mainframe_.lock();
  if (!mainframe) {
    // LOG ERROR
    return false;
  }

  return mainframe->addPlugin(plugin_url, relation);
}

}