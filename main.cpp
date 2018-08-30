#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

#include "common.h"
#include "mainframe.h"



namespace logging=boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

void init1()
{
    logging::add_file_log
    (
        keywords::file_name = "sample_%N.log",                                        /*< file name pattern >*/
        keywords::rotation_size = 10 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
        keywords::open_mode = (std::ios::out | std::ios::app),
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(12, 0, 0), /*< ...or at midnight >*/
        keywords::format = "[%TimeStamp%]: %Message%"                                 /*< log record format >*/
    );
    
    logging::core::get()->set_filter(logging::trivial::severity>=logging::trivial::info);

}

using namespace logging::trivial;
src::severity_logger<logging::trivial::severity_level> lg;

int main()
{

    init1();


    logging::add_common_attributes();

    
    LOG(fatal) << "A fatal severity message opopopopopopopopo";

    /*BOOST_LOG_SEV(lg, trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, debug) << "A debug severity message";
    BOOST_LOG_SEV(lg, info) << "An informational severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";
*/
    LOG(error) << "error -------------- .";

    Twf::Request req;
    Twf::Request res;
    std::unique_ptr<Twf::MainFrame> mainframe(new Twf::MainFrame(req, res));
    mainframe->run();

    return 0;
}
