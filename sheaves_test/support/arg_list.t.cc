
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// Unit test driver for class error_message.

#include "arg_list.h"
#include "assert_contract.h"
#include "index_space_family.h"
#include "namespace_relative_member_index.h"
#include "namespace_relative_subposet_index.h"
#include "schema_descriptor.h"
#include "sheaves_namespace.h"
#include "std_iostream.h"
#include "std_sstream.h"
#include "scoped_index.h"
#include "wsv_block.h"

using namespace sheaf;

/// @todo Update to match expanded set of primitives.

namespace
{
  class arg_list_child : public arg_list
  {
  public:
    arg_list_child() {}
    virtual ~arg_list_child() {}
  };
}

int
main()
{
  arg_list test1;

  // Create and index space family and some ids for testing.

  index_space_family lid_spaces;
  lid_spaces.new_id(10);
  lid_spaces.new_id(12);
  lid_spaces.new_id(14);
  lid_spaces.new_id(16);

  scoped_index id_10(lid_spaces.hub_id_space(), 10);
  scoped_index id_12(lid_spaces.hub_id_space(), 12);
  scoped_index id_14(lid_spaces.hub_id_space(), 14);
  scoped_index id_16(lid_spaces.hub_id_space(), 16);

  // ===========================================================
  // Test each insertion operator individually:
  // ===========================================================

  // size_t insertion operator.

  cout << endl;

  test1 << "size_t_dof" << static_cast<size_t>(0) ;
  cout << "ct: " << test1.ct() << " should be 1" << endl
  << "arg_list:  " << test1
  << "should be: size_t_dof  SIZE_TYPE  0"
  << endl << endl;
  test1.clear();

  // Int insertion operator.

  cout << endl;

  test1 << "int_dof" << 0 ;
  cout << "ct: " << test1.ct() << " should be 1" << endl
  << "arg_list:  " << test1
  << "should be: int_dof  INT  0"
  << endl << endl;
  test1.clear();

  // Double insertion operator.

  test1 << "double_dof" << 1.0;
  cout << "ct: " << test1.ct() << " should be 1" << endl
  << "arg_list:  " << test1
  << "should be: double_dof  DOUBLE  1.0"
  << endl << endl;
  test1.clear();

  // Char_ptr insertion operator.

  char* char_ptr_dof = "this_is_a_test";
  const char* xxx = "char_ptr_dof";
  //  test1 << xxx;
  test1 << "char_ptr_dof" << char_ptr_dof;
  cout << "ct: " << test1.ct() << " should be 1" << endl
  << "arg_list:  " << test1
  << "should be: char_ptr_dof  C_STRING  "
  << static_cast<void*>(char_ptr_dof)
  << endl << endl;
  test1.clear();

  // String insertion  operator.

  string string_dof("this_is_a_test");
  test1 << "string_dof" << string_dof;
  cout << "ct: " << test1.ct() << " should be 1" << endl
  << "arg_list:  " << test1
  << "should be: string_dof  C_STRING  "
  << static_cast<const void*>(string_dof.c_str())
  << endl << endl;
  test1.clear();

  // Void_ptr insertion operator.

  void* void_ptr_dof = char_ptr_dof;
  test1 << "void_ptr_dof" << void_ptr_dof;
  cout << "ct: " << test1.ct() << " should be 1" << endl
  << "arg_list:  " << test1
  << "should be: void_ptr_dof  VOID_STAR  " << void_ptr_dof
  << endl << endl;
  test1.clear();

  // Char insertion operator.

  char char_dof = 'c';
  test1 << "char_dof" << char_dof;
  cout << "ct: " << test1.ct() << " should be 1" << endl
  << "arg_list:  " << test1
  << "should be: char_dof  CHAR  c"
  << endl << endl;
  test1.clear();

  // Unsigned short insertion operator.

  unsigned short ushort_dof = 4;
  test1 << "ushort_dof" << ushort_dof;
  cout << "ct: " << test1.ct() << " should be 1" << endl
  << "arg_list:  " << test1
  << "should be: ushort_dof  UNSIGNED_SHORT_INT  4"
  << endl << endl;
  test1.clear();

  // Namespace_relative_member_index insertion operator.

  namespace_relative_member_index nrmi_dof;
  nrmi_dof.poset_id = id_10;
  nrmi_dof.member_id = id_12;
  test1 << "nrmi_dof" << nrmi_dof;
  cout << "ct: " << test1.ct() << " should be 1" << endl
  << "arg_list:  " << test1
  << "should be: nrmi_dof  NAMESPACE_RELATIVE_MEMBER_INDEX  10 12"
  << endl << endl;
  test1.clear();

  // Namespace_relative_subposet_index insertion operator.

  namespace_relative_subposet_index nrsi_dof;
  nrsi_dof.poset_id = id_14;
  nrsi_dof.subposet_id = id_16;
  test1 << "nrsi_dof" << nrsi_dof;
  cout << "ct: " << test1.ct() << " should be 1" << endl
  << "arg_list:  " << test1
  << "should be: nrsi_dof  NAMESPACE_RELATIVE_SUBPOSET_INDEX  14 16"
  << endl << endl;
  test1.clear();

  // ===========================================================
  // Test the insertion operators without clearing the list:
  // ===========================================================


  test1 << "size_t_dof" << static_cast<size_t>(0) ;
  test1 << "int_dof" << 0 ;
  test1 << "double_dof" << 1.0;
  test1 << "char_ptr_dof" << char_ptr_dof;
  test1 << "string_dof" << string_dof;
  test1 << "void_ptr_dof" << void_ptr_dof;
  test1 << "char_dof" << char_dof;
  test1 << "ushort_dof" << ushort_dof;
  test1 << "nrmi_dof" << nrmi_dof;
  test1 << "nrsi_dof" << nrsi_dof;
  cout << "ct: " << test1.ct() << " should be 13" << endl
  << "arg_list: " << endl
  << test1
  << endl << endl;
  test1.clear();


  // ===========================================================
  // Test the insertion operators jointly:
  // ===========================================================

  test1 << "size_t_dof" << static_cast<size_t>(0)
  << "int_dof" << 0
  << "double_dof" << 1.0
  << "char_ptr_dof" << char_ptr_dof
  << "string_dof" << string_dof
  << "void_ptr_dof" << void_ptr_dof
  << "char_dof" << char_dof
  << "ushort_dof" << ushort_dof
  << "nrmi_dof" << nrmi_dof
  << "nrsi_dof" << nrsi_dof;

  cout << "ct: " << test1.ct() << " should be 13" << endl
  << "arg_list: " << endl
  << test1
  << endl << endl;
  test1.clear();

  // =============================================================================
  // TEST EXTRACTION OPERATOR FACET
  // =============================================================================

  string linput("size_t_dof\tSIZE_TYPE\t0\n");
  linput += "int_dof\tINT\t2\n";
  linput += "double_dof\tDOUBLE\t1.0\n";
  linput += "string_dof\tC_STRING\tthis is a string\n";
  linput += "empty string dof\tC_STRING\t\n";
  linput += "void_ptr_dof\tVOID_STAR\t0\n";
  linput += "char_dof\tCHAR\tc\n";
  linput += "ushort_dof\tUNSIGNED_SHORT_INT\t0\n";
  linput += "nrmi_dof\tNAMESPACE_RELATIVE_MEMBER_INDEX\t10 12\n";
  linput += "nrsi_dof\tNAMESPACE_RELATIVE_SUBPOSET_INDEX\t14 16\n";

  stringstream lstream(linput);

  lstream >> test1;
  cout << "After stream extraction:" << endl;
  cout << test1 << endl;

  cout << "should be: " << linput << endl;

  test1.clear();


  sheaves_namespace lns("arg_list.t");
  lns.get_read_write_access();

  // ===========================================================
  //  Test conforms_to with row schema.
  // ===========================================================

  // Test row conformance with arg_list that is in order.

  test1 << "size" << static_cast<size_t>(4)
  << "alignment"  << static_cast<size_t>(4)
  << "index" << 3;

  cout << "right: " << endl << test1;
  cout << "conforms_to: "
  << boolalpha << test1.conforms_to(lns.primitives().schema(), false, true)
  << noboolalpha
  << endl << endl;

  test1.clear();

  // Test row conformance with arg_list that is out of order.

  test1 << "size" << static_cast<size_t>(4)
  << "index" << 3
  << "alignment"  << static_cast<size_t>(4);

  cout << "wrong order: " << endl << test1;
  cout << "conforms_to: "
  << boolalpha << test1.conforms_to(lns.primitives().schema(), false, true)
  << noboolalpha
  << endl << endl;

  test1.clear();

  // Test row conformance with arg_list that has wrong dof name.

  test1 << "wrong_dof_name" << static_cast<size_t>(4)
  << "index" << 3
  << "alignment"  << static_cast<size_t>(4);

  cout << "wrong dof name: " << endl << test1;
  cout << "conforms_to: "
  << boolalpha << test1.conforms_to(lns.primitives().schema(), false, true)
  << noboolalpha
  << endl << endl;

  test1.clear();

  // Test row conformance with arg_list that has wrong dof type.

  test1 << "size" << 4.0
  << "index" << 3
  << "alignment"  << static_cast<size_t>(4);

  cout << "wrong dof type: " << endl << test1;
  cout << "conforms_to: "
  << boolalpha << test1.conforms_to(lns.primitives().schema(), false, true)
  << noboolalpha
  << endl<< endl;

  test1.clear();

  // ===========================================================
  // Create a schema with table dofs and inheritance
  // ===========================================================


//   poset* ltest_schema_poset =
//     new poset(&lns, lns.primitives().schema().path(), "test_schema");
//   ltest_schema_poset->get_read_write_access();
//   subposet table_dofs(ltest_schema_poset);
//   table_dofs.put_name(schema_poset_member::table_dof_subposet_name("top"), true, false);

//   subposet row_dofs(ltest_schema_poset);
//   row_dofs.put_name(schema_poset_member::row_dof_subposet_name("top"), true, false);

//   ltest_schema_poset->schematize(&table_dofs, &row_dofs, true);

//   table_dofs.detach_from_state();
//   row_dofs.detach_from_state();

//   ltest_schema_poset->release_access();


//   wsv_block<schema_descriptor> ldof_specs1("d INT true");
//   schema_poset_member lschema1(lns,
//                                "schema1",
//                                "test_schema/bottom",
//                                ldof_specs1,
//                                true,
//                                true);

//   wsv_block<schema_descriptor>
//   ldof_specs2("p POD_INDEX_TYPE true units C_STRING true dx DOUBLE false dy DOUBLE false");
//   schema_poset_member lschema2(lns,
//                                "schema2",
//                                lschema1.path(),
//                                ldof_specs2,
//                                true,
//                                true);


  // ===========================================================
  //  Test conforms_to with table schema.
  // ===========================================================

//   // Test table conformance with arg_list that is right.

//   test1 << "d" << 2;
//   cout << "right: " << endl << test1;
//   cout << "conforms_to: "
//   << boolalpha << test1.conforms_to(lschema1, true, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();


//   // Test table conformance to schema with row dofs and with arg_list that is right.

//   scoped_index lpmi(1);

//   test1 << "d" << 2
//   << "p" << lpmi
//   << "units" << "meters";

//   cout << "right: " << endl << test1;
//   cout << "conforms_to: "
//   << boolalpha << test1.conforms_to(lschema2, true, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();


//   // Test table conformance to schema with row dofs and
//   // with arg_list that is wrong order.

//   test1 << "d" << 2
//   << "units" << "meters"
//   << "p" << lpmi ;


//   cout << "wrong order: " << endl << test1;
//   cout << "conforms_to: "
//   << boolalpha << test1.conforms_to(lschema2, true, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();


//   // Test row conformance to schema with table dofs and with arg_list that is right.

//   test1 << "dx" << 0.0
//   << "dy" << 1.0;

//   cout << "right: " << endl << test1;
//   cout << "conforms_to: "
//   << boolalpha << test1.conforms_to(lschema2, false, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();

//   // Test row conformance to schema with table dofs and
//   // with arg_list that is wrong order.

//   test1 << "dy" << 1.0 << "dx" << 0.0;

//   cout << "wrong order: " << endl << test1;
//   cout << "conforms_to: "
//   << boolalpha << test1.conforms_to(lschema2, false, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();

//   // Test table conformance with wrong name.

//   test1 << "d" << 2
//   << "p" << lpmi
//   << "Units" << "meters";

//   cout << "wrong name: " << endl << test1;
//   cout << "conforms_to: "
//   << boolalpha << test1.conforms_to(lschema2, true, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();

//   // Test table conformance with wrong type.

//   test1 << "d" << 2
//   << "p" << 1.0
//   << "units" << "meters";

//   cout << "wrong type: " << endl << test1;
//   cout << "conforms_to: "
//   << boolalpha << test1.conforms_to(lschema2, true, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();

//   // Test row conformance with wrong type.

//   test1 << "dx" << 0
//   << "dy" << 1.0;

//   cout << "wrong type: " << endl << test1;
//   cout << "conforms_to: "
//   << boolalpha << test1.conforms_to(lschema2, false, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();

  // ===========================================================
  // Test conforms_to_extension
  // ===========================================================

//   // Test table conformance to extension of schema with row dofs and
//   // with arg_list that is right.

//   test1 << "p" << lpmi
//   << "units" << "meters";

//   cout << "right: " << endl << test1;
//   cout << "conforms_to_extension: "
//   << boolalpha << test1.conforms_to_extension(lschema2, lschema1, true, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();

//   // Test table conformance to extension of schema with row dofs and
//   // with arg_list that is wrong order.

//   test1 << "units" << "meters"
//   << "p" << lpmi;

//   cout << "wrong order: " << endl << test1;
//   cout << "conforms_to_extension: "
//   << boolalpha << test1.conforms_to_extension(lschema2, lschema1, true, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();

//   // Test table conformance to extension of schema with row dofs and
//   // with arg_list that is wrong name.

//   test1 << "Units" << "meters"
//   << "p" << lpmi;

//   cout << "wrong name: " << endl << test1;
//   cout << "conforms_to_extension: "
//   << boolalpha << test1.conforms_to_extension(lschema2, lschema1, true, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();

//   // Test table conformance to extension of schema with row dofs and
//   // with arg_list that is wrong type.

//   test1 << "p" << 1.0
//   << "units" << "meters";

//   cout << "wrong type: " << endl << test1;
//   cout << "conforms_to_extension: "
//   << boolalpha << test1.conforms_to_extension(lschema2, lschema1, true, true)
//   << noboolalpha
//   << endl << endl;

//   test1.clear();

//   // ===========================================================
//   //  Test poset_dof_map::put_dof_tuple(arg_list)
//   // ===========================================================

//   cout << "testing poset constructor:" << endl;

//   test1 << "d" << 2
//   << "p" << lpmi
//   << "units" << "meters";

//   cout << test1 << endl;


//   poset* ltest_poset = new poset(&lns, &lschema2, "test_poset", test1);
//   test1.clear();

//   total_poset_member lmbr(ltest_poset);
//   test1 << "dy" << 1.0 << "dx" << 0.0;
//   lmbr.get_read_write_access();
//   lmbr.dof_map(true).put_dof_tuple(test1);

//   cout << *ltest_poset << endl;

//   lmbr.release_access();
//   test1.clear();

  // ===========================================================
  // Clean up
  // ===========================================================


//   lmbr.detach_from_state();
//   lschema2.detach_from_state();
//   lschema1.detach_from_state();

  //============================================================================
  // Miscellaneous (invoke functions to increase coverage).
  //============================================================================

  arg_list larg_list0;

  larg_list0 << "int_dof" << 0;

  arg_list::arg_type larg_type1;
  larg_type1.put_type(0);

  arg_list larg_list1(larg_type1);

  larg_list0 += larg_list1; 

  primitive_value& lvalue = larg_list0.value(0);

  const string& lname = larg_list0.name(0);

  int ltype = larg_list0.type(lname);

  bool lparsing_value = larg_list0.parsing_value();

  bool lparsing_error = larg_list0.parsing_error();

  arg_list::arg_type& lback = larg_list0.back(); 

  const arg_list larg_list_const = larg_list0;;
  const arg_list::arg_type& lback_const = larg_list_const.back(); 

  //============================================================================

  //$$HACK: To get better coverage of CTORs and DTORs.

  arg_list_child* lchild = new arg_list_child;
  delete lchild;

  //============================================================================


  return 0;
}


