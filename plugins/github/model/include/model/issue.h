#ifndef CC_MODEL_ISSUE_H
#define CC_MODEL_ISSUE_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <odb/core.hxx>
#include <odb/lazy-ptr.hxx>

#include <model/milestone.h>
#include <model/label.h>
#include <model/person.h>

namespace cc
{
namespace model
{
struct Milestone;
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

  #pragma db null
  odb::lazy_shared_ptr<model::Person> user;

  #pragma db not_null
  bool isOpen;

  #pragma db not_null
  std::string createdAt;

  #pragma db not_null
  std::string updatedAt;

  #pragma db null
  std::string closedAt;

  #pragma db null
  odb::lazy_shared_ptr<Milestone> milestone;

  #pragma db value_not_null unordered id_column("issue_num") value_column("label_id")
  std::vector<odb::lazy_shared_ptr<Label>> labels;

  /*#pragma db value_not_null unordered
  std::vector<std::shared_ptr<Person>> assignees;*/
};
} // model
} // cc

#endif // CC_MODEL_ISSUE_H