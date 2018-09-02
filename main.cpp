#include "common.h"
#include "mainframe.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace logging=boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

void init_logging()
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
    logging::add_common_attributes();

}

using namespace logging::trivial;
src::severity_logger<logging::trivial::severity_level> lg;

int main(int argc, char** argv) {

    init_logging();
    ::testing::InitGoogleMock(&argc, argv);

    Twf::Request req;
    Twf::Request res;
    std::unique_ptr<Twf::MainFrame> mainframe(new Twf::MainFrame(req, res));
    mainframe->run();

    return RUN_ALL_TESTS();
}
