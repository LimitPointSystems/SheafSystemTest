/**
 * Classname: SheafScopeSchemaPane
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: SheafScopeSchemaPane.java,v $ $Revision: 1.14 $
 *
 * $Date: 2012/03/01 00:41:41 $
 *
 * Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import bindings.java.*;

import java.awt.*;
import javax.swing.*;

/**
 * SheafScopeSchemaPane specializes <code>SheafScopeAbstractTreePane</code>
 * to allow display of schema info.<p> 
 */
public class SheafScopeSchemaPane extends SheafScopeAbstractTreePane
{

  /**
   * Constructor
   *
   * @param xposetPane The <code>SheafScopePosetPane</code> to act upon.
   * @param xmember The current <code>poset_member</code>.
   */
  public SheafScopeSchemaPane(SheafScopePosetPane xposetPane, abstract_poset_member xmember)
  {
    super(xposetPane, xmember);

    String name = "N/A";
    try
    {
      if(xmember != null)
        name = xmember.name();
    }
    catch(Exception ex)
    {
      // $$HACK: Need better error handling.

      ex.printStackTrace();
    }

    setTitle("Schema: " + name);
  }

  /**
   *
   */
  protected void annotate()
  {}
}
