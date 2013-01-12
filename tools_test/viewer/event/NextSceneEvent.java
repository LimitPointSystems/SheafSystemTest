/**
 *  Classname: NextSceneEvent
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
 * Implementation <code>NextSceneThreadEvent</code> for
 * going to the next scene of a <code>Script</code>.
 *
 */
public class NextSceneEvent extends PlayThreadEvent
{
  /**
   * The constructor
   */
  public NextSceneEvent()
  {}

  /**
   * Handle this <code>NextSceneEvent</code>
   */
  public void handle(PlayThread xplayThread)
  {
    if(abort)
      return;

    xplayThread.next();
  }
}
