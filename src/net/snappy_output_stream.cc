#include <net/snappy_output_stream.h>

#include <base/assert.h>

#include <third_party/snappy/exported/snappy.h>

namespace dist_clang {
namespace net {

SnappyOutputStream::SnappyOutputStream(ZeroCopyOutputStream* sub_stream,
                                       ui64 chunk_size)
    : sub_stream_(sub_stream), chunk_size_(chunk_size) {
  DCHECK(sub_stream);
}

bool SnappyOutputStream::Next(void** data, int* size) {
  if (!success_) {
    return false;
  }

  buffers_.emplace_back(new char[chunk_size_], chunk_size_);
  DCHECK(data);
  DCHECK(size);
  *data = buffers_.back().first;
  *size = chunk_size_;
  total_size_ += chunk_size_;

  return true;
}

void SnappyOutputStream::BackUp(int count) {
  CHECK(count >= 0);
  CHECK(!buffers_.empty());
  CHECK(count <= buffers_.back().second);

  buffers_.back().second -= count;
  total_size_ -= count;
}

bool SnappyOutputStream::Flush() {
  if (!success_) {
    return false;
  }
  success_ = false;

  String uncompressed;
  uncompressed.reserve(total_size_);
  for (const auto& buffer : buffers_) {
    uncompressed.append(static_cast<const char*>(buffer.first), buffer.second);
  }
  buffers_.clear();

  String compressed;
  snappy::Compress(uncompressed.data(), uncompressed.size(), &compressed);

  void* buffer = nullptr;
  int size = 0;
  size_t sent = 0u;
  while (sub_stream_->Next(&buffer, &size)) {
    auto remains = compressed.size() - sent;

    if (static_cast<size_t>(size) < remains) {
      strncpy(static_cast<char*>(buffer), compressed.data() + sent, size);
      sent += size;
      continue;
    }

    strncpy(static_cast<char*>(buffer), compressed.data() + sent, remains);
    sub_stream_->BackUp(static_cast<int>(size - remains));
    sent = compressed.size();
    break;
  }

  return sent == compressed.size();
}

}  // namespace net
}  // namespace dist_clang
