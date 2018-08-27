#include "common.h"
#include "plugin.h"

namespace Twf {

Plugin::Plugin() {

}

Plugin::~Plugin() {
  
}

int Plugin::run(Request* req, Response* res) {
  int rv = main_(req, res);
  return rv;
}

}