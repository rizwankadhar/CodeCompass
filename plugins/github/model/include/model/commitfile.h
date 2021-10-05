#ifndef CC_MODEL_COMMITFILE_H
#define CC_MODEL_COMMITFILE_H

#include <cstdint>
#include <string>

#include <odb/core.hxx>

namespace cc
{
namespace model
{
#pragma db object
struct CommitFile
{
  enum FileStatus
  {
    added,
    modified,
    removed,
    renamed
  };

  #pragma db id auto
  std::uint64_t id;

  #pragma db not_null
  std::string sha;

  #pragma db not_null
  std::string path;

  #pragma db not_null
  FileStatus status;

  #pragma db not_null
  std::string commitSha;

  #pragma db not_null
  unsigned additions;

  #pragma db not_null
  unsigned deletions;

  #pragma db not_null
  unsigned changes;

  #pragma db not_null
  std::string patch;
};
} // model
} // cc

#endif // CC_MODEL_COMMITFILE_H