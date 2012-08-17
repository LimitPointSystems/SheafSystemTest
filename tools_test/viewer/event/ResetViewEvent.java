/**
 *  Classname: ResetViewEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: ResetViewEvent.java,v $ $Revision: 1.6 $
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
 * resetting the view.
 *
 */
public class ResetViewEvent extends RenderThreadEvent
{
  /**
   * The constructor
   */
  public ResetViewEvent()
  {}

  /**
   * Handle this <code>ResetViewEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    xrenderThread.resetView();

    if(abort)
      return;

    xrenderThread.render();
  }
}
