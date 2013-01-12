/**
 *  Classname: MakeCurrentEvent
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
 * making the interactor current.
 *
 */
public class MakeCurrentEvent extends RenderThreadEvent
{
  /**
   * The constructor
   */
  public MakeCurrentEvent()
  {}

  /**
   * Handle this <code>MakeCurrentEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    xrenderThread.makeCurrent();
  }
}
