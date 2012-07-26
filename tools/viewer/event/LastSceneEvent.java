/**
 *  Classname: LastSceneEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: LastSceneEvent.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.animation.*;

/**
 *
 * Implementation <code>LastSceneThreadEvent</code> for
 * going to the last scene of a <code>Script</code>.
 *
 */
public class LastSceneEvent extends PlayThreadEvent
{
  /**
   * The constructor
   */
  public LastSceneEvent()
  {}

  /**
   * Handle this <code>LastSceneEvent</code>
   */
  public void handle(PlayThread xplayThread)
  {
    if(abort)
      return;

    xplayThread.last();
  }
}
