
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "fiber_bundles_namespace.h"
#include "sec_e2.h"
#include "structured_block_2d.h"
#include "test_sections.impl.h"

using namespace std;
using namespace fiber_bundle;

void test()
{
  fiber_bundles_namespace lns("test.t");
  lns.get_read_write_access();

  const poset_path lbase_path("test_mesh", "test_mesh_block"); 

  base_space_poset* lmesh =
    &lns.new_base_space<structured_block_2d>(lbase_path.poset_name());

  structured_block_2d lblock(lmesh, 2, 2, true);
  lblock.put_name(lbase_path.member_name(), true, true);
  lblock.detach_from_state();

  const poset_path lpath = "test_space";
  const poset_path
     lrep_path(fiber_bundles_namespace::standard_sec_rep_descriptor_poset_name(),
               "element_element_constant");

  const string lname0("test_section0");
  const string lname1("test_section1");

  sec_rep_space* lhost = &lns.new_section_space<sec_e2>(lpath.poset_name(),
							lbase_path,
							lrep_path,
							true);
  sec_e2 lsection0(lhost);
  lsection0.put_name(lname0, true, true);
  
  sec_e2 lsection1(lhost);
  lsection1.put_name(lname1, true, true);

  lsection0.get_read_write_access();
  lsection1.get_read_write_access();

  cout << endl;
  cout << "Before assign lsection1 = lsection0" << endl;
  lsection1 = lsection0;
  //lsection1 = static_cast<abstract_poset_member&>(lsection0);
  cout << "After assign lsection1 = lsection0" << endl;
  cout << endl;

  lsection0.release_access();
  lsection1.release_access();

  cout << endl;
  cout << "Before lsection0.detach_from_state()" << endl;
  lsection0.detach_from_state();
  cout << "After lsection0.detach_from_state()" << endl;
  cout << endl;

  cout << endl;
  cout << "Before lsection1.detach_from_state()" << endl;
  lsection1.detach_from_state();
  cout << "After lsection1.detach_from_state()" << endl;
  cout << endl;

  return;
}

//==============================================================================

class class_a
{
public:
  class_a() { } //cout << "class_a()" << endl; }

  /*virtual*/ class_a& operator=(const class_a& xother)
  {
    cout << "class_a::operator=(const class_a& xother)" << endl;
    return *this;
  }
};

class class_b : public class_a
{
public:
  class_b() { } //cout << "class_b()" << endl; }

  class_b& operator=(const class_a& xother)
  {
    cout << "class_b::operator=(const class_a& xother)" << endl;
    return *this;
  }
};

class class_c : public class_b
{
public:
  class_c() { } //cout << "class_c()" << endl; }

  class_c& operator=(const class_a& xother)
  {
    cout << "class_c::operator=(const class_a& xother)" << endl;
    return *this;
  }
};

void simple_test()
{
  class_a a;
  class_b b;
  class_c c;

  cout << endl;

  a = a;
  a = b;
  a = c;

  cout << endl;

  b = a;
  b = b;
  b = c;

  cout << endl;

  c = a;
  c = b;
  c = c;

  cout << endl;

  return;
}

//==============================================================================

int main()
{
  simple_test();

  test();

  return 0;
}
