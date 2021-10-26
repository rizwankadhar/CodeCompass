#include <githubparser/githubparser.h>

#include <boost/filesystem.hpp>

#include <util/logutil.h>

#include <memory>

namespace cc
{
namespace parser
{
const std::string GithubParser::commitUri = "/repos/Ericsson/CodeCompass/commits";

ResType GithubParser::resolve(
  asio::io_context& ctx,
  std::string const& hostname)
{
  tcp::resolver resolver{ctx};
  return resolver.resolve(hostname, "https");
}

Socket GithubParser::connect(
  asio::io_context& ctx,
  std::string const& hostname)
{
  tcp::socket socket{ctx};
  asio::connect(socket, resolve(ctx, hostname));
  return socket;
}

std::unique_ptr<SSLStream> GithubParser::connect(
  asio::io_context& ctx,
  ssl::context& ssl_ctx,
  std::string const& hostname)
{
  auto stream = boost::make_unique<ssl::stream<tcp::socket>>(connect(ctx, hostname), ssl_ctx);
  // tag::stream_setup_source[]
  boost::certify::set_server_hostname(*stream, hostname);
  boost::certify::sni_hostname(*stream, hostname);
  // end::stream_setup_source[]

  stream->handshake(ssl::stream_base::handshake_type::client);
  return stream;
}

HTTPResponse GithubParser::get(
  ssl::stream<tcp::socket>& stream,
  boost::string_view hostname,
  boost::string_view uri)
{
  http::request<http::empty_body> request;
  request.method(http::verb::get);
  request.target(uri);
  request.keep_alive(false);
  request.set(http::field::host, hostname);
  request.set(http::field::user_agent, "CodeCompass");
  http::write(stream, request);

  http::response<http::string_body> response;
  beast::flat_buffer buffer;
  http::read(stream, buffer, response);

  return response;
}

GithubParser::GithubParser(ParserContext& ctx_): AbstractParser(ctx_)
{
}

bool GithubParser::accept(const std::string& path_)
{
  std::string ext = boost::filesystem::extension(path_);
  return ext == ".github";
}

bool GithubParser::parse()
{        
  for(std::string path : _ctx.options["input"].as<std::vector<std::string>>())
  {
    if(accept(path))
    {
      LOG(info) << "GithubParser parse path: " << path;
    }
  }

  asio::io_context ctx;
  ssl::context ssl_ctx{ssl::context::tls_client};
  auto const hostname = std::string{"api.github.com"};
  ssl_ctx.set_verify_mode(ssl::context::verify_peer |
                          ssl::context::verify_fail_if_no_peer_cert);
  ssl_ctx.set_default_verify_paths();
  // tag::ctx_setup_source[]
  boost::certify::enable_native_https_server_verification(ssl_ctx);
  // end::ctx_setup_source[]
  auto stream_ptr = connect(ctx, ssl_ctx, hostname);
  auto response = get(*stream_ptr, hostname, commitUri);
  LOG(info) << response.body();

  boost::system::error_code ec;
  stream_ptr->shutdown(ec);
  stream_ptr->next_layer().close(ec);

  return true;
}

GithubParser::~GithubParser()
{
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern "C"
{
  boost::program_options::options_description getOptions()
  {
    boost::program_options::options_description description("Github Plugin");

    description.add_options()
        ("github-arg", po::value<std::string>()->default_value("Github arg"),
          "This argument will be used by the github parser.");

    return description;
  }

  std::shared_ptr<GithubParser> make(ParserContext& ctx_)
  {
    return std::make_shared<GithubParser>(ctx_);
  }
}
#pragma clang diagnostic pop

} // parser
} // cc
