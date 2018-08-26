#include "requrest.h"

namespace Twf {

void Request::assign(const string& key, const string& value) {
  params_[key] = value;
}

bool Request::has_key(const string& key) {
  return params_.find(key) != params_.end();
}

string& Request::operator[](const string& key) {
  if (!has_key(key))
    return undefined_;

  return params_[key];
}

string& Request::operator[](string&& key) {
  if (!has_key(key))
    return undefined_;

  return params_[key];
}

}