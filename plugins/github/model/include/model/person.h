#ifndef CC_MODEL_PERSON_H
#define CC_MODEL_PERSON_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <odb/core.hxx>

#include <model/issue.h>
#include <model/pull.h>

namespace cc
{
namespace model
{
struct Pull;
struct Issue;

#pragma db object
struct Person
{
  enum UserType
  {
    User,
    Organization
  };

  #pragma db id
  std::uint64_t id;

  #pragma db not_null
  std::string username;

  #pragma db not_null
  UserType type;

  #pragma db not_null
  std::string url;

  #pragma db not_null
  unsigned contributions;

  #pragma db null
  std::string name;

  #pragma db null
  std::string company;

  #pragma db value_not_null inverse(assignees)
  std::vector<std::weak_ptr<Issue>> assignedIssues;

  #pragma db value_not_null inverse(assignees)
  std::vector<std::weak_ptr<Pull>> assignedPulls;

  #pragma db value_not_null inverse(reviewers)
  std::vector<std::weak_ptr<Pull>> reviewedPulls;
};
} // model
} // cc

#endif // CC_MODEL_PERSON_H