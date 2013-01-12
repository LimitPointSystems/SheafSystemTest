/**
 *  Classname: PreviousSceneEvent
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
