#ifndef RENDERER_API_H
#define RENDERER_API_H

namespace wunder {

struct renderer_properties;
struct renderer_capabilities;

class renderer_api {
 public:
  virtual ~renderer_api();

 public:
  void init(const renderer_properties& properties);

  virtual void update(int dt) = 0;

  virtual const renderer_capabilities& get_capabilities() const = 0;
 protected:
  virtual void init_internal(const renderer_properties& properties) = 0;
};
}  // namespace wunder
#endif
