
//
// Copyright (c) 2014 Limit Point Systems, Inc.
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

/// @example io/file_rewrite.t.cc
/// Tests multiple writes of a single namespace to new and existing files.

#include "ComLimitPoint/sheaf/namespace_poset.h"
#include "std_iostream.h"
#include "ComLimitPoint/sheaf/storage_agent.h"

string filename;

int
main(int argc, char** argv)
{
  if (argc > 1)
  {
    filename = argv[1];
  }
  else
  {
    cerr << "usage: rewrite.t sheaf_file\n";
    exit(1);
  }

  // Make the default namespace

  namespace_poset ns("test");

  // Read the namespace from the file;
  // need write access in order to read it.

  ns.get_read_write_access();

  cout << endl;
  cout << endl;
  cout << "#######################################" << endl;
  cout << "Reading input file" << endl;
  cout << "#######################################" << endl;
  cout << endl;
  cout << endl;

  storage_agent* sa1 = new storage_agent(filename,
                                         sheaf_file::READ_ONLY,
                                         true,
                                         false);
  sa1->read_entire(ns);
  delete sa1;


  // Write the namespace to a file with a different name.

  cout << endl;
  cout << endl;
  cout << "#######################################" << endl;
  cout << "Writing second_ file" << endl;
  cout << "#######################################" << endl;
  cout << endl;
  cout << endl;

  string second_filename = "second_" + filename;
  storage_agent* sa2 = new storage_agent(second_filename,
                                         sheaf_file::READ_WRITE,
                                         true,
                                         false);
  sa2->write_entire(ns);
  delete sa2;

  // Write the namespace to a file with another different name.

  cout << endl;
  cout << endl;
  cout << "#######################################" << endl;
  cout << "Writing third_ file" << endl;
  cout << "#######################################" << endl;
  cout << endl;
  cout << endl;

  string third_filename = "third_" + filename;
  storage_agent* sa3 = new storage_agent(third_filename,
                                         sheaf_file::READ_WRITE,
                                         true,
                                         false);
  sa3->write_entire(ns);
  delete sa3;

  // Try to overwrite the original namespace file.

  cout << endl;
  cout << endl;
  cout << "#######################################" << endl;
  cout << "Rewriting original file" << endl;
  cout << "#######################################" << endl;
  cout << endl;
  cout << endl;

  storage_agent* sa4 = new storage_agent(filename,
                                         sheaf_file::READ_WRITE,
                                         true,
                                         false);
  sa4->write_entire(ns);
  delete sa4;

  // Try to overwrite a previously written file.

  cout << endl;
  cout << endl;
  cout << "#######################################" << endl;
  cout << "Rewriting second_ file" << endl;
  cout << "#######################################" << endl;
  cout << endl;
  cout << endl;

  storage_agent* sa5 = new storage_agent("second_" + filename,
                                         sheaf_file::READ_WRITE,
                                         true,
                                         false);
  sa5->write_entire(ns);
  delete sa5;

  return 0;
}
