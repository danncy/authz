#ifndef AUTHZ_PLUGIN_H_
#define AUTHZ_PLUGIN_H_

#include <string>
#include <functional>

namespace Twf {

struct Plugin {
  Plugin();
  ~Plugin();

  int run();

private:
  std::string url_;

  std::function<void()> init_;
  std::function<int()> main_;
  std::function<void()> destroy_;
};

}
#endif // !AUTHZ_PLUGIN_H_
