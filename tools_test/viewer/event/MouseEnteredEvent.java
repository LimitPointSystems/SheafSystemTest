/**
 *  Classname: MouseEnteredEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: MouseEnteredEvent.java,v $ $Revision: 1.6 $
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
 * processing a mouse entered event.
 *
 */
public class MouseEnteredEvent extends RenderThreadEvent
{
  /**
   * The <code>MouseEvent</code>
   */
  protected MouseEvent mouseEvent;

  /**
   * The constructor
   */
  public MouseEnteredEvent(MouseEvent xmouseEvent)
  {
    mouseEvent = xmouseEvent;
  }

  /**
   * Handle this <code>MouseEnteredEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    xrenderThread.mouseEntered(mouseEvent);
  }
}
