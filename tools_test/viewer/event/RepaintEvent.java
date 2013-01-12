/**
 *  Classname: RepaintEvent
 *
 *
 *
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.render.*;

/**
 *
 * Implementation <code>RenderThreadEvent</code> for
 * repainting the current scene.
 *
 */
public class RepaintEvent extends RenderThreadEvent
{
  /**
   * The constructor
   */
  public RepaintEvent()
  {}

  /**
   * Handle this <code>RepaintEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    xrenderThread.render();
  }
}
