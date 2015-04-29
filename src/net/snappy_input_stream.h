#pragma once

#include <base/aliases.h>
#include <base/attributes.h>

#include <third_party/protobuf/exported/google/protobuf/io/zero_copy_stream.h>

namespace dist_clang {
namespace net {

class SnappyInputStream : public google::protobuf::io::ZeroCopyInputStream {
 public:
  explicit SnappyInputStream(ZeroCopyInputStream* WEAK_PTR sub_stream);

  virtual bool Next(const void** data, int* size) override;
  virtual void BackUp(int count) override;
  virtual bool Skip(int count) override;
  virtual i64 ByteCount() const override { return offset_; }

 private:
  bool success_ = false;
  String uncompressed_;
  i64 offset_ = 0;
};

}  // namespace net
}  // namespace dist_clang
