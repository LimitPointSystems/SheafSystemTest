/**
 *  Classname: YAxisRolePanel
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: YAxisRolePanel.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:44 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.application;

import bindings.java.*;

import javax.swing.*;

/**
 * Implementation of <code>ScalarRolePanel</code> for a y-axis section.
 */
public class YAxisRolePanel extends ScalarRolePanel
{
  /**
   * The constructor
   */
  public YAxisRolePanel()
  {
    super();
  }

  /**
   * Return the role text
   */
  protected String getRole()
  {
    return "Y-Axis Section";
  }
}
