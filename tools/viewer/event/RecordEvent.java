/**
 *  Classname: RecordEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: RecordEvent.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.animation.*;

/**
 *
 * Implementation <code>PlayThreadEvent</code> for
 * recording a <code>Script</code>.
 *
 */
public class RecordEvent extends PlayThreadEvent
{
  /**
   * The constructor
   */
  public RecordEvent()
  {}

  /**
   * Handle this <code>RecordEvent</code>
   */
  public void handle(PlayThread xplayThread)
  {
    if(abort)
      return;

    boolean result = xplayThread.initMovie();

    if(!result || abort)
      return;

    xplayThread.play();

    if(abort)
      return;

    xplayThread.finalizeMovie();
  }
}
