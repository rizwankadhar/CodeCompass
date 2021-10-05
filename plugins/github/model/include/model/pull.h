#ifndef CC_MODEL_PULL_H
#define CC_MODEL_PULL_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <odb/core.hxx>

#include <model/label.h>
#include <model/person.h>
#include <model/commit.h>

namespace cc
{
namespace model
{
struct Label;
struct Person;
struct Commit;

#pragma db object
struct Pull
{
  #pragma db id
  std::uint64_t number;

  #pragma db not_null
  std::string title;

  #pragma db not_null
  std::string body;

  #pragma db not_null
  std::string url;

  #pragma db not_null
  std::uint64_t userId;

  #pragma db not_null
  bool isOpen;

  #pragma db not_null
  std::string createdAt;

  #pragma db not_null
  std::string updatedAt;

  #pragma db null
  std::string closedAt;

  #pragma db null
  std::string mergedAt;

  #pragma db null
  std::uint64_t milestone;

  #pragma db not_null
  std::string headLabel;

  #pragma db not_null
  std::uint64_t headRepoId;

  #pragma db not_null
  std::string baseLabel;

  #pragma db not_null
  std::uint64_t baseRepoId;

  #pragma db not_null
  bool isMerged;

  #pragma db null
  bool isMergeable;

  #pragma db null
  std::uint64_t mergedBy;

  #pragma db not_null
  unsigned comments;

  #pragma db not_null
  unsigned reviewComments;

  #pragma db not_null
  unsigned commitCount;

  #pragma db not_null
  unsigned additions;

  #pragma db not_null
  unsigned deletions;

  #pragma db not_null
  unsigned changedFiles;

  #pragma db value_not_null unordered
  std::vector<std::shared_ptr<Label>> labels;

  #pragma db value_not_null unordered
  std::vector<std::shared_ptr<Person>> assignees;

  #pragma db value_not_null unordered
  std::vector<std::shared_ptr<Person>> reviewers;

  #pragma db value_not_null unordered
  std::vector<std::shared_ptr<Commit>> commits;
};
} // model
} // cc

#endif // CC_MODEL_PULL_H