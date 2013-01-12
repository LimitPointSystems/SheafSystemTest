/**
 *  Classname: XAxisRolePanel
 *
 *
 *
 *
 *  Copyright (c) 2013 Limit Point Systems, Inc.
 */

package tools.viewer.application;

import bindings.java.*;

import javax.swing.*;

/**
 * Implementation of <code>ScalarRolePanel</code> for a x-axis section.
 */
public class XAxisRolePanel extends ScalarRolePanel
{
  /**
   * The constructor
   */
  public XAxisRolePanel()
  {
    super();
  }

  /**
   * Return the role text
   */
  protected String getRole()
  {
    return "X-Axis Section";
  }
}
