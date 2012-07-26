/**
 *  Classname: PickEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: PickEvent.java,v $ $Revision: 1.5 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.user.*;

/**
 *
 * Implementation <code>ViewerEvent</code> for picking a position on the screen.
 *
 */
public class PickEvent extends ViewerEvent
{
  /**
   * The position
   */
  protected double[] position;

  /**
   * The constructor
   */
  public PickEvent(double[] xposition)
  {
    position = xposition;
  }

  /**
   * Handle this <code>PickEvent</code>
   */
  public void handle(Viewer xviewer)
  {
    if(abort)
      return;

    xviewer.pick(position);
  }
}
