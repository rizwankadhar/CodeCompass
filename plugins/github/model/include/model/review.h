#ifndef CC_MODEL_REVIEW_H
#define CC_MODEL_REVIEW_H

#include <cstdint>
#include <string>

#include <odb/core.hxx>
#include <odb/lazy-ptr.hxx>

#include <model/person.h>

namespace cc
{
namespace model
{

#pragma db object
struct Review
{
  #pragma db id
  std::uint64_t id;

  #pragma db null
  odb::lazy_shared_ptr<Person> user;

  #pragma db not_null
  std::string state;

  #pragma db not_null
  std::string body;

  #pragma db not_null
  std::string url;

  #pragma db not_null
  std::string submittedAt;
};
} // model
} // cc

#endif // CC_MODEL_REVIEW_H
