#include "githubdataconverter.h"

#include <utility>
#include <util/logutil.h>
#include <util/odbtransaction.h>

namespace cc
{
namespace parser
{
std::vector<model::Label> GithubDataConverter::ConvertLabels(pt::ptree& ptree)
{
  std::vector<model::Label> labels;
  for (pt::ptree::value_type &labelData : ptree)
  {
    model::Label label;

    label.id = labelData.second.get<std::uint64_t>("id");
    label.name = labelData.second.get<std::string>("name");
    label.description = labelData.second.get<std::string>("description");

    labels.push_back(label);
  }
  return labels;
}

std::vector<model::Milestone> GithubDataConverter::ConvertMilestones(pt::ptree& ptree)
{
  std::vector<model::Milestone> milestones;
  for (pt::ptree::value_type &milestoneData : ptree)
  {
    model::Milestone milestone;

    milestone.number = milestoneData.second.get<unsigned>("number");
    milestone.title = milestoneData.second.get<std::string>("title");
    milestone.url = milestoneData.second.get<std::string>("html_url");
    milestone.description = milestoneData.second.get<std::string>("description");
    milestone.openIssues = milestoneData.second.get<unsigned>("open_issues");
    milestone.closedIssues = milestoneData.second.get<unsigned>("closed_issues");
    milestone.isOpen = milestoneData.second.get<std::string>("state") == "open";
    milestone.createdAt = milestoneData.second.get<std::string>("created_at");
    milestone.updatedAt = milestoneData.second.get<std::string>("updated_at");
    milestone.dueOn = milestoneData.second.get<std::string>("due_on");
    milestone.closedAt = milestoneData.second.get<std::string>("closed_at");

    milestones.push_back(milestone);
  }
  return milestones;
}

std::vector<std::pair<std::string, unsigned>> GithubDataConverter::ConvertContributors(pt::ptree &ptree)
{
  std::vector<std::pair<std::string, unsigned>>  contributors;
  for (pt::ptree::value_type &contributorData : ptree)
  {
    std::string username = contributorData.second.get<std::string>("login");
    unsigned contributions = contributorData.second.get<unsigned>("contributions");

    std::pair<std::string, unsigned> contributor{username, contributions};
    contributors.push_back(contributor);
  }
  return contributors;
}

model::Person GithubDataConverter::ConvertUser(pt::ptree& ptree, unsigned contributions)
{
  model::Person user;

  user.username = ptree.get<std::string>("login");
  user.url = ptree.get<std::string>("html_url");
  user.name = ptree.get<std::string>("name");
  user.company = ptree.get<std::string>("company");
  user.contributions = contributions;
  user.type = (ptree.get<std::string>("type")=="User") ? model::Person::UserType::User : model::Person::UserType::Organization;

  return user;
}

std::vector<model::Commit> GithubDataConverter::ConvertCommits(pt::ptree& ptree)
{
  std::vector<model::Commit> commits;
  for (pt::ptree::value_type &commitData : ptree)
  {
    model::Commit commit;

    commit.sha = commitData.second.get<std::string>("sha");
    LOG(error) << commit.sha;
    commit.message = commitData.second.get_child("commit").get<std::string>("message");
    commit.url = commitData.second.get<std::string>("html_url");
    if (!commitData.second.get_child("author").empty())
    {
      commit.user = commitData.second.get_child("author").get<std::string>("login");
    }
    commit.date = commitData.second.get_child("commit").get_child("author").get<std::string>("date");
    commit.comments = commitData.second.get_child("commit").get<unsigned>("comment_count");

    for (auto const parent : commitData.second.get_child("parents"))
    {
      commit.parents.push_back(parent.second.get<std::string>("sha"));
    }
    commits.push_back(commit);
  }
  return commits;
}

std::vector<model::CommitFile> GithubDataConverter::ConvertCommitFiles(pt::ptree &ptree, model::Commit &commit)
{
  LOG(error) << commit.sha << " commit filejai";
  commit.additions = ptree.get_child("stats").get<unsigned>("additions");
  commit.deletions = ptree.get_child("stats").get<unsigned>("deletions");
  commit.changes = ptree.get_child("stats").get<unsigned>("total");

  std::vector<model::CommitFile> commitFiles;
  for (pt::ptree::value_type &commitData : ptree.get_child("files"))
  {
    model::CommitFile commitFile;

    commitFile.sha = commitData.second.get<std::string>("sha");
    commitFile.path = commitData.second.get<std::string>("filename");
    LOG(error) << commitFile.path;
    commitFile.status = commitData.second.get<std::string>("filename");
    commitFile.commitSha = commit.sha;
    commitFile.additions = commitData.second.get<unsigned>("additions");
    commitFile.deletions = commitData.second.get<unsigned>("deletions");
    commitFile.changes = commitData.second.get<unsigned>("changes");
    if (commitData.second.get_child_optional("patch").is_initialized())
    {
      commitFile.patch = commitData.second.get<std::string>("patch");
    }

    commitFiles.push_back(commitFile);
  }
  return commitFiles;
}


std::vector<model::Issue> GithubDataConverter::ConvertIssues(pt::ptree &ptree, ParserContext &ctx)
{
  std::vector<model::Issue> issues;
  for (pt::ptree::value_type &issueData : ptree)
  {
    model::Issue issue;

    issue.number = issueData.second.get<std::uint64_t>("number");
    issue.title = issueData.second.get<std::string>("title");
    LOG(error) << issue.title;
    issue.body = issueData.second.get<std::string>("body");
    issue.url = issueData.second.get<std::string>("html_url");
    if (!issueData.second.get_child("user").empty())
    {
      issue.user = issueData.second.get_child("user").get<std::string>("login");
    }
    issue.isOpen = issueData.second.get<std::string>("state") == "open";

    issue.createdAt = issueData.second.get<std::string>("created_at");
    issue.updatedAt = issueData.second.get<std::string>("updated_at");
    issue.closedAt = issueData.second.get<std::string>("closed_at");

    /*if (!issueData.second.get_child("milestone").empty())
    {
      issue.milestone = issueData.second.get_child("milestone").get<unsigned>("number");
    }*/

    if (!issueData.second.get_child("milestone").empty())
    {
      util::OdbTransaction trans(ctx.db);
      trans([&, this]
        {
          typedef odb::query<model::Milestone> query;
          query q(
            query::number == issueData.second.get_child("milestone").get<unsigned>("number"));
          issue.milestone = (ctx.db->query_one<model::Milestone>(q));
        });
    }

    issues.push_back(issue);
  }
  return issues;
}

}
}