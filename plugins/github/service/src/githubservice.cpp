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

GitHubServiceHandler::GitHubServiceHandler(
  std::shared_ptr<odb::database> db_,
  std::shared_ptr<std::string> /*datadir_*/,
  const cc::webserver::ServerContext& context_)
    : _db(db_), _transaction(db_), _config(context_.options)
{
}

void GitHubServiceHandler::getContributorList(
  std::vector<Person>& return_)
{
  _transaction([&, this]() {
    odb::result<model::Person> res (_db->query<model::Person>());
    for(auto iter = res.begin(); iter!=res.end(); ++iter)
    {
      Person p;
      p.username = iter->username;
      return_.emplace_back(p);
      LOG(info) << p.username;
    }
  });
}

/*void GitHubServiceHandler::getPullList(
  std::vector<model::Pull>& return_)
{
  _transaction([&, this]() {
    odb::result<model::Pull> res (_db->query<model::Pull>());

    return_.insert(return_.begin(), res.begin(), res.end());
  });
}

void GitHubServiceHandler::getIssueList(
  std::vector<model::Issue>& return_)
{
  _transaction([&, this]() {
    odb::result<model::Issue> res (_db->query<model::Issue>());

    return_.insert(return_.begin(), res.begin(), res.end());
  });
}*/

void GitHubServiceHandler::getGitHubString(std::string& str_)
{
  str_ = "test";
  //str_ = _config["github-result"].as<std::string>();
}

} // github
} // service
} // cc
