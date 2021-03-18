#include <util/logutil.h>

#include <boost/log/utility/setup.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>

namespace bl = boost::log;

namespace cc
{
namespace util
{

namespace
{

void logFormatter(
  const bl::record_view& rec, bl::formatting_ostream& strm)
{
  auto severity = rec[bl::trivial::severity];

  if (severity)
  {
    // Set the color
    switch (severity.get())
    {
      case bl::trivial::debug:
        strm << "\033[32m";
        break;
      case bl::trivial::warning:
        strm << "\033[33m";
        break;
      case bl::trivial::error:
      case bl::trivial::fatal:
        strm << "\033[31m";
        break;
      default:
        break;
    }
  }

  std::string sLevel = bl::trivial::to_string(severity.get());
  std::transform(sLevel.begin(), sLevel.end(), sLevel.begin(), ::toupper);

  strm << "[" << sLevel << "] " << rec[bl::expressions::smessage];

  // Restore the default color
  if (severity)
  {
    strm << "\033[0m";
  }
}

}

bl::trivial::severity_level getSeverityLevel()
{
 return bl::attribute_cast<
   bl::attributes::mutable_constant<bl::trivial::severity_level>>(
     bl::core::get()->get_global_attributes()["Severity"]).get();
}

void initbl()
{
  // Create file sink for: trace, debug, info
  auto debugFileSink = bl::add_file_log(
    bl::keywords::file_name = "debug.log",
    bl::keywords::auto_flush = true,
    bl::keywords::format = (
      bl::expressions::stream
        << "[" << bl::trivial::severity << "] "
        << bl::expressions::smessage
    )
  );

  // Could be replaced with:
  debugFileSink->set_filter(
    bl::trivial::severity <= bl::trivial::info
  );

  // Create file sink for: warning, error, fatal
  auto errorFileSink = bl::add_file_log(
    bl::keywords::file_name = "error.log",
    bl::keywords::auto_flush = true,
    bl::keywords::format = (
      bl::expressions::stream
        << "[" << bl::trivial::severity << "] "
        << bl::expressions::smessage
    )
  );

  // Could be replaced with:
  errorFileSink->set_filter(
    bl::trivial::severity > bl::trivial::warning
  );

  // Create console sink
  auto consoleSink = bl::add_console_log(
    std::cout,
    bl::keywords::auto_flush = true);

  consoleSink->set_formatter(&logFormatter);

}

} // util
} // cc
