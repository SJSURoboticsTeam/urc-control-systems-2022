#pragma once

#include "utility/log.hpp"

namespace sjsu::common
{
class Heartbeat
{
 public:
  int GetHeartbeatCount() const
  {
    return heartbeat_count_;
  }

  void IncrementHeartbeatCount()
  {
    heartbeat_count_++;
  }

  bool IsSyncedWithMissionControl(int heartbeat_count)
  {
    if (heartbeat_count_ != heartbeat_count)
    {
      // TODO: Should throw error ?
      sjsu::LogError("Heartbeat out of sync - resetting!");
      ResetHeartbeatCount();
      return false;
    }
    return true;
  }

 private:
  void ResetHeartbeatCount()
  {
    heartbeat_count_ = 0;
  }

  int heartbeat_count_ = 0;
};
}  // namespace sjsu::common