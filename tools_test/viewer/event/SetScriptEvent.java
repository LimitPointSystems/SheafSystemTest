/**
 *  Classname: SetScriptEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: SetScriptEvent.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.animation.*;

/**
 *
 * Implementation <code>SetScriptThreadEvent</code> for
 * setting the <code>Script</code>.
 *
 */
public class SetScriptEvent extends PlayThreadEvent
{
  /**
   * The script
   */
  protected Script script;

  /**
   * The constructor
   */
  public SetScriptEvent(Script xscript)
  {
    script = xscript;
  }

  /**
   * Handle this <code>SetScriptEvent</code>
   */
  public void handle(PlayThread xplayThread)
  {
    if(abort)
      return;

    xplayThread.setScript(script);
  }
}
