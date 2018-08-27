#ifndef AUTHZ_DEF_H_
#define AUTHZ_DEF_H_

enum PluginResult {
  PluginFailed = -1,
  PluginOK = 0,
  PluginContinue = 1,
};

enum PluginType {
  TYPE_C,
  TYPE_NODE,
};

enum PluginRelation {
  AND,
  OR,
};

#endif // !AUTHZ_DEF_H_
