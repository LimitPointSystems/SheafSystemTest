/**
 *  Classname: InvokeViewerEventRunnable
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: InvokeViewerEventRunnable.java,v $ $Revision: 1.5 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
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
