#ifndef AUTHZ_REQUEST_H_
#define AUTHZ_REQUEST_H_

#include <unordered_map>
#include <string>
#include <memory>

#include "common.h"

namespace Twf {

struct twf_request {
   void* data;
};

typedef struct twf_request twf_request_t;
typedef struct twf_request twf_response_t;

class MainFrame;

struct Request {
  Request();
  ~Request();

  /**
   * @brief 往request里插入或修改键值对
   * 
   * @param key 字符串键值
   * @param value 指定的值
   * 
   * @see operator.[]
   */
  void assign(const std::string& key, const std::string& value);

  /**
   * @brief 判断指定key是否存在
   * 
   * @param key 指定的键值
   * 
   * @return 返回值说明
   *        <em>true</em> succeed
   *        <em>false</em> failed
   * 
   */
  bool hasKey(const std::string& key);

  /**
   * @brief Request键值访问运算符
   * 
   * @param key 用户指定的字符串键值
   * @note 可以通过[]方法修改key对应的值
   * 
   * @return 返回值说明
   *      指定的键对应的值
   * 
   */
  std::string& operator[](const std::string& key);

  /**
   * @brief Request键值访问运算符
   * 
   * @param key 用户指定的右值字符串键值
   * @note 可以通过[]方法修改key对应的值
   * @return 返回值说明
   *      指定的键对应的值
   * 
   */
  std::string& operator[](std::string&& key);

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

  /**
   * @brief 设置mainframe指针对象，该指针不能释放
   * @param [in] mainframe 主框架对象指针
   * 
   * @note 每个Request必须设置mainframe.
   * @see Mainframe
   * 
   */
  void setMainFrame(const std::shared_ptr<MainFrame>& mainframe) {
    mainframe_ = mainframe;
  }

private:
    std::weak_ptr<MainFrame> mainframe_;
    std::string undefined_;
    std::unordered_map<std::string, std::string> params_;
};

using Response = Request;

static Request*  fromTwfRequest(const twf_request_t& req);
static Response* fromTwfResponse(const twf_response_t& res);

}
#endif // !AUTHZ_REQUEST_H_
