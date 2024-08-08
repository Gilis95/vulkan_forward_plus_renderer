#ifndef WINDOW_H
#define WINDOW_H

#include <cstdint>
#include <vector>

namespace wunder {
struct window_properties;

struct vulkan_extensions {
 public:
  std::vector<char *> m_extensions;
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class window {
 public:
  window() = default;
  virtual ~window() = default;

 public:
  virtual void init(const window_properties &) = 0;

  virtual void update(int dt) = 0;

  virtual void shutdown() = 0;

  [[nodiscard]] virtual void fill_vulkan_extensions(
      vulkan_extensions & out_extensions) const = 0;
};
}  // namespace wunder

#endif
