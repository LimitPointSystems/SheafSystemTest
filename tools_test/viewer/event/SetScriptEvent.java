/**
 *  Classname: SetScriptEvent
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
