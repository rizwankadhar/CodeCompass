#ifndef CC_MODEL_MILESTONE_H
#define CC_MODEL_MILESTONE_H

#include <cstdint>
#include <string>

#include <odb/core.hxx>

namespace cc
{
namespace model
{
#pragma db object
struct Milestone
{
  #pragma db id
  unsigned number;

  #pragma db not_null
  std::string title;

  #pragma db not_null
  std::string url;

  #pragma db not_null
  std::string description;

  #pragma db not_null
  unsigned openIssues;

  #pragma db not_null
  unsigned closedIssues;

  #pragma db not_null
  bool isOpen;

  #pragma db not_null
  std::string createdAt;

  #pragma db not_null
  std::string updatedAt;

  #pragma db null
  std::string dueOn;

  #pragma db null
  std::string closedAt;
};
} // model
} // cc

#endif // CC_MODEL_MILESTONE_H