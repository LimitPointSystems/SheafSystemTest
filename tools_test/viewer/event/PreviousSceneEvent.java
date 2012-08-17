/**
 *  Classname: PreviousSceneEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: PreviousSceneEvent.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.animation.*;

/**
 *
 * Implementation <code>PreviousSceneThreadEvent</code> for
 * going to the previous scene of a <code>Script</code>.
 *
 */
public class PreviousSceneEvent extends PlayThreadEvent
{
  /**
   * The constructor
   */
  public PreviousSceneEvent()
  {}

  /**
   * Handle this <code>PreviousSceneEvent</code>
   */
  public void handle(PlayThread xplayThread)
  {
    if(abort)
      return;

    xplayThread.previous();
  }
}
