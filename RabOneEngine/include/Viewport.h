#pragma once
#include "Prerequisites.h"

// Forward declarations
class Window;
class DeviceContext;

class
Viewport {
public:
  Viewport() = default;
  ~Viewport() = default;

  // Initializes the viewport using a Window instance.
  HRESULT
  init(const Window& window);

  // Initializes the viewport with the specified dimensions.
  HRESULT
  init(unsigned int width, unsigned int height);

  // Updates the viewport settings when any changes to the dimensions are required.
  void
  update();

  // Renders the viewport using the given DeviceContext method.
  void
  render(DeviceContext& deviceContext);

  // Releases the resources from the viewport.
  void
  destroy();

public:
  D3D11_VIEWPORT m_viewport;
};