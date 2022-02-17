namespace cpp cc.service.github
namespace java cc.service.github

struct Person
{
  1:string username
}

service GitHubService
{
  string getGitHubString()
  list<Person> getContributorList()
}