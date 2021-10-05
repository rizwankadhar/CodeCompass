#ifndef CC_MODEL_REPOSITORY_H
#define CC_MODEL_REPOSITORY_H

#include <string>

#include <odb/core.hxx>

namespace cc
{
namespace model
{
#pragma db object
struct Repository
{
  #pragma db id
  std::uint64_t id;

  #pragma db not_null
  std::string name;

  #pragma db not_null
  std::string fullName;

  #pragma db not_null
  bool isPrivate;

  #pragma db not_null
  std::string url;

  #pragma db not_null
  std::string description;

  #pragma db not_null
  bool isFork;

  #pragma db not_null
  std::uint64_t ownerId;
};
} // model
} // cc

#endif // CC_MODEL_REPOSITORY_H