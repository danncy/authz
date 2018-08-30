#ifndef AUTHZ_DEF_H_
#define AUTHZ_DEF_H_

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

extern boost::log::sources::severity_logger<boost::log::trivial::severity_level> lg;

#define LOG(lvl) BOOST_LOG_SEV(lg, lvl) 

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
