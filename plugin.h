#ifndef AUTHZ_PLUGIN_H_
#define AUTHZ_PLUGIN_H_

#include <string>
#include <functional>

#include "common.h"
#include "request.h"

namespace Twf {

struct Plugin {
  Plugin();
  ~Plugin();

  int run(Request* req, Response* res);

private:
  std::string name_;
  // 插件在全局映射表里的URL
  std::string origin_url;
  
  PluginType type_;
  // 访问node插件的URL
  std::string url_;
  
  std::function<void()> init_;
  std::function<int(Request* req, Response* res)> main_;
  std::function<void()> destroy_;
};

}
#endif // !AUTHZ_PLUGIN_H_
