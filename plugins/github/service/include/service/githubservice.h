#ifndef CC_SERVICE_GITHUB_GITHUBSSERVICE_H
#define CC_SERVICE_GITHUB_GITHUBSSERVICE_H

#include <memory>
#include <vector>

#include <boost/program_options/variables_map.hpp>

#include <odb/database.hxx>
#include <util/odbtransaction.h>
#include <webserver/servercontext.h>

#include <GithubService.h>

namespace cc
{
namespace service
{
namespace github
{

class GithubServiceHandler : virtual public GithubServiceIf
{
public:
  GithubServiceHandler(
    std::shared_ptr<odb::database> db_,
    std::shared_ptr<std::string> datadir_,
    const cc::webserver::ServerContext& context_);

  void getGithubString(std::string& str_);

private:
  std::shared_ptr<odb::database> _db;
  util::OdbTransaction _transaction;

  const boost::program_options::variables_map& _config;
};

} // github
} // service
} // cc

#endif // CC_SERVICE_GITHUB_GITHUBSSERVICE_H
