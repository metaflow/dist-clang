#pragma once

#include <base/aliases.h>

namespace dist_clang {
namespace client {
// Tries to send specified command to daemon.
// Returns true if command should be issued to local clang instead.
bool DoMain(int argc, const char* const argv[], Immutable socket_path,
            Immutable clang_path, Immutable version, ui32 read_timeout_secs,
            ui32 send_timeout_secs, ui32 read_min_bytes,
            const HashMap<String, String>& plugins);

}  // namespace client
}  // namespace dist_clang
