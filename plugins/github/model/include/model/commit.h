#ifndef CC_MODEL_COMMIT_H
#define CC_MODEL_COMMIT_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <odb/core.hxx>

#include <model/pull.h>

namespace cc
{
namespace model
{
struct Pull;

#pragma db object
struct Commit
{
  #pragma db id
  std::string sha;

  #pragma db not_null
  std::string message;

  #pragma db not_null
  std::string url;

  #pragma db not_null
  std::uint64_t userId;

  #pragma db not_null
  std::string date;

  #pragma db null
  std::string parent1;

  #pragma db null
  std::string parent2;

  #pragma db not_null
  unsigned additions;

  #pragma db not_null
  unsigned deletions;

  #pragma db not_null
  unsigned changes;

  #pragma db not_null
  unsigned comments;

  #pragma db value_not_null inverse(commits)
  std::vector<std::weak_ptr<Pull>> pulls;
};
} // model
} // cc

#endif // CC_MODEL_COMMIT_H
