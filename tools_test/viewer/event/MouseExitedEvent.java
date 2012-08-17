/**
 *  Classname: MouseExitedEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: MouseExitedEvent.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.render.*;

import java.awt.event.*;

/**
 *
 * Implementation <code>RenderThreadEvent</code> for
 * processing a mouse exited event.
 *
 */
public class MouseExitedEvent extends RenderThreadEvent
{
  /**
   * The <code>MouseEvent</code>
   */
  protected MouseEvent mouseEvent;

  /**
   * The constructor
   */
  public MouseExitedEvent(MouseEvent xmouseEvent)
  {
    mouseEvent = xmouseEvent;
  }

  /**
   * Handle this <code>MouseExitedEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    xrenderThread.mouseExited(mouseEvent);
  }
}
