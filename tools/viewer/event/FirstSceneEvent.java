/**
 *  Classname: FirstSceneEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: FirstSceneEvent.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.animation.*;

/**
 *
 * Implementation <code>FirstSceneThreadEvent</code> for
 * going to the first scene of a <code>Script</code>.
 *
 */
public class FirstSceneEvent extends PlayThreadEvent
{
  /**
   * The constructor
   */
  public FirstSceneEvent()
  {}

  /**
   * Handle this <code>FirstSceneEvent</code>
   */
  public void handle(PlayThread xplayThread)
  {
    if(abort)
      return;

    xplayThread.first();
  }
}
