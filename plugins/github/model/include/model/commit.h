#ifndef CC_MODEL_COMMIT_H
#define CC_MODEL_COMMIT_H

#include <cstdint>
#include <string>
#include <vector>

#include <odb/core.hxx>
#include <odb/lazy-ptr.hxx>

#include <model/person.h>

namespace cc
{
namespace model
{

#pragma db object
struct Commit
{
  #pragma db id
  std::string sha;

  #pragma db not_null
  std::string message;

  #pragma db not_null
  std::string url;

  #pragma db null
  odb::lazy_shared_ptr<model::Person> user;

  #pragma db not_null
  std::string date;

  #pragma db unordered id_column("commit_sha") value_column("parent_sha")
  std::vector<std::string> parents;

  #pragma db not_null
  unsigned additions;

  #pragma db not_null
  unsigned deletions;

  #pragma db not_null
  unsigned changes;

  #pragma db not_null
  unsigned comments;
};
} // model
} // cc

#endif // CC_MODEL_COMMIT_H
