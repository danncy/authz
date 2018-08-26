#ifndef AUTHZ_REQUEST_H_
#define AUTHZ_REQUEST_H_

#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

namespace Twf {

struct Request {
  Request() = default;
  ~Request() = default;

  void assign(const string& key, const string& value);
  bool has_key(const string& key);

  string& operator[](const string& key);
  string& operator[](string&& key);

  private:
    string undefined_;
    unordered_map<string, string> params_;
};

using Reposne = Request;

}
#endif // !AUTHZ_REQUEST_H_
