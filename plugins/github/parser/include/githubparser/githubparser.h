#ifndef CC_PARSER_GITHUBPARSER_H
#define CC_PARSER_GITHUBPARSER_H

#include <parser/abstractparser.h>
#include <parser/parsercontext.h>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http/empty_body.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/write.hpp>

#include <certify/extensions.hpp>
#include <certify/https_verification.hpp>

namespace cc
{
namespace parser
{
namespace beast = boost::beast;
namespace asio = boost::asio;
namespace ssl = asio::ssl;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

typedef tcp::resolver::results_type ResType;
typedef ssl::stream<tcp::socket> SSLStream;
typedef tcp::socket Socket;
typedef http::response<http::string_body> HTTPResponse;

class GithubParser : public AbstractParser
{
public:
  GithubParser(ParserContext& ctx_);
  virtual ~GithubParser();
  bool parse() override;
private:
  static const std::string commitUri;

  bool accept(const std::string& path_);
  ResType resolve(
    asio::io_context& ctx,
    std::string const& hostname);
  Socket connect(
    asio::io_context& ctx,
    std::string const& hostname);
  std::unique_ptr<SSLStream> connect(
    asio::io_context& ctx,
    ssl::context& ssl_ctx,
    std::string const& hostname);
  HTTPResponse get(
    ssl::stream<tcp::socket>& stream,
    boost::string_view hostname,
    boost::string_view uri);
};
  
} // parser
} // cc

#endif // CC_PARSER_GITHUBPARSER_H
