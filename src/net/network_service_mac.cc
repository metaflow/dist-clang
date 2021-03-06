#include <net/network_service_impl.h>

#include <base/c_utils.h>
#include <net/event_loop_mac.h>

using namespace std::placeholders;

namespace dist_clang {
namespace net {

NetworkServiceImpl::NetworkServiceImpl(ui32 connect_timeout_secs,
                                       ui32 send_timeout_secs,
                                       ui32 read_min_bytes,
                                       ui32 read_timeout_secs)
    : connect_timeout_secs_(connect_timeout_secs),
      read_timeout_secs_(read_timeout_secs),
      send_timeout_secs_(send_timeout_secs),
      read_min_bytes_(read_min_bytes) {
  auto callback =
      std::bind(&NetworkServiceImpl::HandleNewConnection, this, _1, _2);
  event_loop_.reset(new KqueueEventLoop(callback));
}

NetworkServiceImpl::ConnectedStatus
NetworkServiceImpl::WaitForConnection(const base::Handle& fd, String* error) {
  base::Kqueue waiter;
  if (!waiter.IsValid()) {
    waiter.GetCreationError(error);
    return ConnectedStatus::FAILED;
  }

  if (!waiter.Add(fd, EVFILT_WRITE | EV_ONESHOT, error)) {
    return ConnectedStatus::FAILED;
  }

  std::array<struct kevent, 1> event;
  auto events_count = waiter.Wait(event, connect_timeout_secs_);
  // TODO: handle EINTR?
  if (events_count == -1) {
    base::GetLastError(error);
    return ConnectedStatus::FAILED;
  }

  DCHECK(events_count < 2);
  return events_count == 1 ? ConnectedStatus::CONNECTED :
                             ConnectedStatus::TIMED_OUT;
}

}  // namespace net
}  // namespace dist_clang
