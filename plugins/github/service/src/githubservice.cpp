#include <service/githubservice.h>
#include <util/dbutil.h>

namespace cc
{
namespace service
{
namespace github
{

GithubServiceHandler::GithubServiceHandler(
  std::shared_ptr<odb::database> db_,
  std::shared_ptr<std::string> /*datadir_*/,
  const cc::webserver::ServerContext& context_)
    : _db(db_), _transaction(db_), _config(context_.options)
{
}

void GithubServiceHandler::getGithubString(std::string& str_)
{
  str_ = _config["github-result"].as<std::string>();
}

} // github
} // service
} // cc
