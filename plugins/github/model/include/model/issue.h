#ifndef CC_MODEL_ISSUE_H
#define CC_MODEL_ISSUE_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <odb/core.hxx>

#include <model/label.h>
#include <model/person.h>

namespace cc
{
namespace model
{
struct Label;
struct Person;

#pragma db object
struct Issue
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
  std::uint64_t closedBy;

  #pragma db null
  std::uint64_t milestone;

  #pragma db value_not_null unordered
  std::vector<std::shared_ptr<Label>> labels;

  #pragma db value_not_null unordered
  std::vector<std::shared_ptr<Person>> assignees;
};
} // model
} // cc

#endif // CC_MODEL_ISSUE_H