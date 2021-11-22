#ifndef CC_PARSER_GITHUBDATACONVERTER_H
#define CC_PARSER_GITHUBDATACONVERTER_H

#include <vector>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <odb/database.hxx>

#include <parser/parsercontext.h>

#include <model/label.h>
#include <model/milestone.h>
#include <model/milestone-odb.hxx>
#include <model/person.h>
#include <model/commit.h>
#include <model/commitfile.h>
#include <model/issue.h>

namespace cc
{
namespace parser
{
namespace pt = boost::property_tree;

class GithubDataConverter
{
public:
  std::vector<model::Label> ConvertLabels(pt::ptree& ptree);
  std::vector<model::Milestone> ConvertMilestones(pt::ptree& ptree);
  std::vector<std::pair<std::string, unsigned>>  ConvertContributors(pt::ptree& ptree);
  model::Person ConvertUser(pt::ptree& ptree, unsigned contributions);
  std::vector<model::Commit> ConvertCommits(pt::ptree& ptree);
  std::vector<model::CommitFile> ConvertCommitFiles(pt::ptree& ptree, model::Commit& commit);
  std::vector<model::Issue> ConvertIssues(pt::ptree& ptree, ParserContext& ctx);

};

}
}

#endif
