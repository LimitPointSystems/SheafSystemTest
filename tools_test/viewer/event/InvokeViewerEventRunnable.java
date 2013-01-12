/**
 *  Classname: InvokeViewerEventRunnable
 *
 *
 *
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.user.*;

import java.awt.*;


/**
 * Invoke a viewer event.
 */
public class InvokeViewerEventRunnable implements Runnable
{
  /**
   * The viewer
   */
  protected Viewer viewer;

  /**
   * The event
   */
  protected ViewerEvent event;

  /**
   * The constructor.
   */
  public InvokeViewerEventRunnable(Viewer xviewer, ViewerEvent xevent)
  {
    viewer = xviewer;
    event = xevent;
  }

  /**
   * The run method.
   */
  public void run()
  {
    viewer.handleEvent(event);
  }
}
