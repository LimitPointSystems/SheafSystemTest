/**
 *  Classname: LastSceneEvent
 *
 *
 *
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
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
