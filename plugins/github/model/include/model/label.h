#ifndef CC_MODEL_LABEL_H
#define CC_MODEL_LABEL_H

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
struct Issue;
struct Pull;

#pragma db object
struct Label
{
  #pragma db id
  std::uint64_t id;

  #pragma db not_null
  std::string name;

  #pragma db not_null
  std::string description;

  #pragma db value_not_null inverse(labels)
  std::vector<std::weak_ptr<Issue>> issues;

  #pragma db value_not_null inverse(labels)
  std::vector<std::weak_ptr<Pull>> pulls;
};
} // model
} // cc

#endif // CC_MODEL_LABEL_H