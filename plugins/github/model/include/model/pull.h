#ifndef CC_MODEL_PULL_H
#define CC_MODEL_PULL_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <odb/core.hxx>
#include <odb/lazy-ptr.hxx>

#include <model/person.h>
#include <model/milestone.h>
#include <model/label.h>
#include <model/review.h>
#include <model/comment.h>
#include <model/pullfile.h>

namespace cc
{
namespace model
{

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

  #pragma db null
  odb::lazy_shared_ptr<Person> user;

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
  odb::lazy_shared_ptr<Milestone> milestone;

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
  std::string mergeable;

  #pragma db null
  std::string mergeableState;

  #pragma db null
  odb::lazy_shared_ptr<Person> mergedBy;

  #pragma db not_null
  unsigned commentCount;

  #pragma db not_null
  unsigned reviewCommentCount;

  #pragma db not_null
  unsigned commitCount;

  #pragma db not_null
  unsigned additions;

  #pragma db not_null
  unsigned deletions;

  #pragma db not_null
  unsigned changedFiles;

  #pragma db value_not_null unordered id_column("pull_num") value_column("label_id")
  std::vector<odb::lazy_shared_ptr<Label>> labels;

  #pragma db value_not_null unordered id_column("pull_num") value_column("pull_file_id")
  std::vector<odb::lazy_shared_ptr<PullFile>> pullFiles;

  #pragma db value_not_null unordered id_column("pull_num") value_column("review_id")
  std::vector<odb::lazy_shared_ptr<Review>> reviews;

  #pragma db value_not_null unordered id_column("pull_num") value_column("comment_id")
  std::vector<odb::lazy_shared_ptr<Comment>> reviewComments;

  #pragma db value_not_null unordered
  std::vector<std::shared_ptr<Person>> assignees;

  #pragma db value_not_null unordered
  std::vector<std::shared_ptr<Person>> reviewers;
};
} // model
} // cc

#endif // CC_MODEL_PULL_H
