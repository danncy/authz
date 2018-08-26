#include "common.h"
#include "plugin.h"

namespace Twf {

Plugin::Plugin() {

}

Plugin::~Plugin() {
  
}

int Plugin::run() {

  int rv = main_();

  return rv;
}

}