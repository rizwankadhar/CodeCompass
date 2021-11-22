#ifndef CC_MODEL_LABEL_H
#define CC_MODEL_LABEL_H

#include <cstdint>
#include <string>

#include <odb/core.hxx>


namespace cc
{
namespace model
{
#pragma db object
struct Label
{
  #pragma db id
  std::uint64_t id;

  #pragma db not_null
  std::string name;

  #pragma db not_null
  std::string description;
};
} // model
} // cc

#endif // CC_MODEL_LABEL_H
