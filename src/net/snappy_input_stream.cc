#include <net/snappy_input_stream.h>

#include <base/assert.h>

#include <third_party/snappy/exported/snappy.h>

namespace dist_clang {
namespace net {

SnappyInputStream::SnappyInputStream(ZeroCopyInputStream* sub_stream) {
  List<Pair<const void*, int>> buffers;
  ui64 total_size = 0u;

  const void* buffer = nullptr;
  int size = 0;
  while (sub_stream->Next(&buffer, &size)) {
    if (size) {
      buffers.emplace_back(buffer, size);
      total_size += size;
    }
  }

  String compressed;
  compressed.reserve(total_size);
  for (const auto& buffer : buffers) {
    compressed.append(static_cast<const char*>(buffer.first), buffer.second);
  }

  success_ =
      snappy::Uncompress(compressed.data(), compressed.size(), &uncompressed_);
}

bool SnappyInputStream::Next(const void** data, int* size) {
  if (!success_) {
    return false;
  }

  DCHECK(data);
  DCHECK(size);
  *data = uncompressed_.data() + offset_;
  *size = uncompressed_.size() - offset_;
  success_ = false;

  return true;
}

void SnappyInputStream::BackUp(int count) {
  CHECK(count >= 0);
  CHECK(count <= offset_);
  offset_ -= count;
}

bool SnappyInputStream::Skip(int count) {
  if (!success_) {
    return false;
  }

  CHECK(count >= 0);
  offset_ = std::min<i64>(offset_ + count, uncompressed_.size());
  if (offset_ == static_cast<i64>(uncompressed_.size())) {
    success_ = false;
  }

  return true;
}

}  // namespace net
}  // namespace dist_clang
