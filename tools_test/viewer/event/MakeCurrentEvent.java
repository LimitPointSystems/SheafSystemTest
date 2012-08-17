/**
 *  Classname: MakeCurrentEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: MakeCurrentEvent.java,v $ $Revision: 1.6 $
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
