#pragma once

#include <base/aliases.h>
#include <base/attributes.h>

#include <third_party/protobuf/exported/google/protobuf/io/zero_copy_stream.h>

namespace dist_clang {
namespace net {

class SnappyOutputStream : public google::protobuf::io::ZeroCopyOutputStream {
 public:
  explicit SnappyOutputStream(ZeroCopyOutputStream* WEAK_PTR sub_stream,
                              ui64 chunk_size = 1024);
  virtual ~SnappyOutputStream() { Flush(); }

  virtual bool Next(void** data, int* size) override;
  virtual void BackUp(int count) override;
  virtual i64 ByteCount() const override { return total_size_; }

  bool Flush();

 private:
  ZeroCopyOutputStream* WEAK_PTR sub_stream_;
  const ui64 chunk_size_;
  bool success_ = true;
  List<Pair<void*, int>> buffers_;
  ui64 total_size_ = 0u;
};

}  // namespace net
}  // namespace dist_clang
