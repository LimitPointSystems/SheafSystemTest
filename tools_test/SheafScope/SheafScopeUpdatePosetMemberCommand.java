
/**
 * Classname: SheafScopeUpdatePosetMemberCommand
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: SheafScopeUpdatePosetMemberCommand.java,v $ $Revision: 1.13 $
 *
 * $Date: 2012/03/01 00:41:41 $
 *
 * Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import javax.swing.event.*;

/**
 * SheafScopeUpdatePosetMemberCommand is a specialized
 * <code>TreeSelectionListener</code> to suit the needs of the SheafScope.
 * Listens for single node selections on the tree and updates the table
 * model accordingly.<p> 
 */
public class SheafScopeUpdatePosetMemberCommand implements TreeSelectionListener
{
  private SheafScopePosetPane posetPane;

  /**
   * Constructor
   * @param xposetPane The <code>SheafScopePosetPane</code> containing the tree
   *                  this listener is registered on.
   */
  public SheafScopeUpdatePosetMemberCommand(SheafScopePosetPane xposetPane)
  {
    posetPane = xposetPane;
  }

  /**
   * The action to be taken when a single treenode selection
   * event is detected.<p>
   *
   * @param event The detected <code>TreeSelectionEvent</code>.
   *
   * 
   */
  public void valueChanged(TreeSelectionEvent event)
  {
    //common.util.LPSDebug.println("event = " + event);

    posetPane.updateMember();
  }
}