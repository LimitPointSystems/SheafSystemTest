/**
 *  Classname: SetScreenCursorEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: SetScreenCursorEvent.java,v $ $Revision: 1.5 $
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
 * Implementation <code>ViewerEvent</code> for rendering being complete
 *
 */
public class SetScreenCursorEvent extends ViewerEvent
{
  /**
   * The cursor
   */
  protected int cursor;

  /**
   * The constructor
   */
  public SetScreenCursorEvent(int xcursor)
  {
    cursor = xcursor;
  }

  /**
   * Handle this <code>SetScreenCursorEvent</code>
   */
  public void handle(Viewer xviewer)
  {
    if(abort)
      return;


    xviewer.getScreen().setCursor(new Cursor(cursor));
  }
}
