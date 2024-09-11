#include "assets/gltf/gltf_camera_serializer.h"

#include <tiny_gltf.h>

#include <algorithm>
#include <cctype>

#include "assets/components/camera_asset.h"
#include "tinygltf/tinygltf_utils.h"

bool ichar_equals(char a, char b) {
  return std::tolower(static_cast<unsigned char>(a)) ==
         std::tolower(static_cast<unsigned char>(b));
}

namespace wunder {
std::optional<camera_asset> gltf_camera_serializer::serialize(
    const tinygltf::Camera& gltf_camera,
    tinygltf::ExtensionMap gltf_node_extensions) {
  ReturnUnless(std::ranges::equal(gltf_camera.type,
                                  GLTF_PERSPECTIVE_CAMERA_TYPE, ichar_equals),
               std::nullopt);

  camera_asset camera;

  auto gltf_perspective_camera = gltf_camera.perspective;
  camera.m_perspective_camera_data.aspect_ratio =
      gltf_perspective_camera.aspectRatio;
  camera.m_perspective_camera_data.fov =
      gltf_perspective_camera.yfov;

  // If the node has the Iray extension, extract the camera information.
  if (tinygltf::utils::has_element_name(gltf_node_extensions,
                                        EXTENSION_ATTRIB_IRAY)) {
    auto& iray_ext = gltf_node_extensions.at(EXTENSION_ATTRIB_IRAY);
    auto& attributes = iray_ext.Get("attributes");
    tinygltf::utils::get_array_value(attributes, "iview:position", camera.eye);
    tinygltf::utils::get_array_value(attributes, "iview:interest",
                                     camera.center);
    tinygltf::utils::get_array_value(attributes, "iview:up", camera.up);
  }

  return camera;
}
}  // namespace wunder