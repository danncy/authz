#ifndef AUTHZ_MAINFRAME_H_
#define AUTHZ_MAINFRAME_H_

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <deque>

#include "common.h"
#include "request.h"
#include "plugin.h"

namespace Twf {

extern  std::unordered_multimap<std::string, std::string> g_hook_plugin_urls;
extern  std::unordered_map<std::string, Plugin> g_plugin_map;

/**
 * @brief 认证主框架类(MainFrame)
 * 
 * 主框架包含了业务链，插件链（分AND，OR两种），记录当前认证的状态
 * 提供了 addService 接口添加业务，
 * 提供了 addPlugin 接口添加 AND 或 OR的插件到对应的插件链
 * 
 */
struct MainFrame {
  MainFrame(const Request& req, const Response& res);
  ~MainFrame() {}
  
  bool run();

  /**
   * @brief 添加业务到业务链
   * @param [in] service_name 业务名称
   * 
   * @return 返回值说明
   *        <em>true</em> succeed
   *        <em>false</em> failed
   */
  bool addService(const std::string& service_name);

  /**
   * @brief 添加插件到插件链
   * @param [in] plugin_url 插件的URL，类似 auth/sms/default
   * @param [in] relation 插件链的运行逻辑，只能输入如下参数
   *  -# AND : 表示加入必须全部执行通过的插件链，类似逻辑与
   *  -# OR ：表示加入必须只需一个插件执行通过即可的插件链，类似逻辑或
   * 
   * @return 返回值说明
   *        <em>true</em> succeed
   *        <em>false</em> failed
   */
  bool addPlugin(const std::string& plugin_url, PluginRelation relation /*= AND */);
  
private:
  bool handlePluginResult(int result);

private:
  int status_;
  std::string session_id_;

  std::deque<std::string> service_chain_;
  std::deque<Plugin> plugin_chain_;
  std::deque<Plugin> multi_choice_plugin_chain_;

  Request req_;
  Response res_;
};

}
#endif // !AUTHZ_MAINFRAM_E_H
