#ifndef CC_MODEL_PERSON_H
#define CC_MODEL_PERSON_H

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
struct Person
{
  enum UserType
  {
    Organization,
    User,
    Anonymous
  };

  #pragma db id
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

  /*#pragma db value_not_null inverse(reviewers)
  std::vector<std::weak_ptr<Pull>> reviewedPulls;*/
  //ez majd marad
};
} // model
} // cc

#endif // CC_MODEL_PERSON_H