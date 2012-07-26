/**
 *  Classname: ViewerEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: ViewerEvent.java,v $ $Revision: 1.5 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.user.*;

/**
 *
 * Abstract class for a <code>Viewer</code> event
 *
 */
public abstract class ViewerEvent
{
  /**
   * The abort flag
   */
  protected boolean abort = false;

  /**
   * Abort this <code>ViewerEvent</code>
   */
  public void abort()
  {
    abort = true;
  }

  /**
   * Handle this <code>ViewerEvent</code>
   */
  public abstract void handle(Viewer xrenderThread);
}
