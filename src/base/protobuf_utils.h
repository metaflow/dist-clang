#pragma once

#include <base/aliases.h>
#include <base/logging.h>

namespace google::protobuf {
  class Message;
}  // namespace google::protobuf

namespace dist_clang {
namespace base {

template <>
Log& Log::operator<<(const google::protobuf::Message& info);

bool LoadFromFile(const String& path, google::protobuf::Message* message);
bool SaveToFile(const String& path, const google::protobuf::Message& message);

}  // namespace base
}  // namespace dist_clang