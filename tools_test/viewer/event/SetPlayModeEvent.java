/**
 *  Classname: SetPlayModeEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: SetPlayModeEvent.java,v $ $Revision: 1.5 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.user.*;

import java.awt.*;

/**
 *
 * Implementation <code>ViewerEvent</code> for setting the play mode.
 *
 */
public class SetPlayModeEvent extends ViewerEvent
{
  /**
   * The mode
   */
  protected boolean mode;

  /**
   * The constructor
   */
  public SetPlayModeEvent(boolean xmode)
  {
    mode = xmode;
  }

  /**
   * Handle this <code>SetPlayModeEvent</code>
   */
  public void handle(Viewer xviewer)
  {
    if(abort)
      return;

    xviewer.setPlayMode(mode);
  }
}
