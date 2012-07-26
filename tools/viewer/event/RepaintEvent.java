/**
 *  Classname: RepaintEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: RepaintEvent.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
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
