#include <service/githubservice.h>
#include <util/dbutil.h>
#include <odb/database.hxx>
#include <odb/result.hxx>
#include <vector>

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

void GithubServiceHandler::getContributorList(
  std::vector<model::Person>& return_)
{
  _transaction([&, this]() {
    odb::result<model::Person> res (_db->query<model::Person>());

    return_.insert(return_.begin(), res.begin(), res.end());
  });
}

void GithubServiceHandler::getPullList(
  std::vector<model::Pull>& return_)
{
  _transaction([&, this]() {
    odb::result<model::Pull> res (_db->query<model::Pull>());

    return_.insert(return_.begin(), res.begin(), res.end());
  });
}

void GithubServiceHandler::getIssueList(
  std::vector<model::Issue>& return_)
{
  _transaction([&, this]() {
    odb::result<model::Issue> res (_db->query<model::Issue>());

    return_.insert(return_.begin(), res.begin(), res.end());
  });
}

void GithubServiceHandler::getGithubString(std::string& str_)
{
  str_ = _config["github-result"].as<std::string>();
}

} // github
} // service
} // cc
