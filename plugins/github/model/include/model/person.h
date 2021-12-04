#ifndef CC_MODEL_PERSON_H
#define CC_MODEL_PERSON_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <odb/core.hxx>

namespace cc
{
namespace model
{

#pragma db object
struct Person
{
  #pragma db id
  std::string username;

  #pragma db not_null
  std::string type;

  #pragma db not_null
  std::string url;

  #pragma db not_null
  unsigned contributions;

  #pragma db null
  std::string name;

  #pragma db null
  std::string company;

  /*
  #pragma db value_not_null inverse(reviewers)
  std::vector<std::weak_ptr<Pull>> reviewedPulls;
  */
};
} // model
} // cc

#endif // CC_MODEL_PERSON_H