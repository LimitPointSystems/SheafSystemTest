/**
 *  Classname: SetSizeEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: SetSizeEvent.java,v $ $Revision: 1.6 $
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
 * setting the size of the render window.
 *
 */
public class SetSizeEvent extends RenderThreadEvent
{
  /**
   * The width
   */
  protected int width;

  /**
   * The height
   */
  protected int height;

  /**
   * The constructor
   */
  public SetSizeEvent(int xwidth, int xheight)
  {
    width = xwidth;
    height = xheight;
  }

  /**
   * Handle this <code>SetSizeEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    xrenderThread.setSize(width, height);
  }
}
