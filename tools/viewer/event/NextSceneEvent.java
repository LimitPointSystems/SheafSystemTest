/**
 *  Classname: NextSceneEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: NextSceneEvent.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
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
