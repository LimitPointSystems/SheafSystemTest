
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

/// @example base_spaces/time_polyline.t.cc

#include "fiber_bundles_namespace.h"
#include "assert_contract.h"
#include "namespace_poset.h"
#include "std_iostream.h"
#include "std_fstream.h"
#include "std_cstdio.h"
#include "unstructured_block.h"
#include "poset_bounds_descriptor.h"
#include "std_string.h"
#include "std_strstream.h"
#include "std_ctime.h"
#include "std_unistd.h"
#include "storage_agent.h"

using namespace std;
using namespace fiber_bundle;

// OBSOLETE: This test driver is obsolete

// Define CLOCKS_PER_SEC if the system hasn't already.  Can't use CLK_TCK
// all the time because some systems set CLK_TCK to clocks per milliseconds
// instead of clocks per second.

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC CLK_TCK
#endif


static const char* OUTPUT_FILENAME="time_polyline.t.txt";

int edge_ct;

int* edges;
double* write_time;
double* read_time;

// Generates a file which contain comma separated data to be loaded
// into Microsoft Excel.
//
// time_polyline.txt - Contains three comma separated columns; the edge counts,
//                     the time it took to write out the polylines to a file,
//                     and the time it took to read a domain from the file.

void
time_write(storage_agent* xsa, int xedge_ct, int xdomain_ct, int xindex)
{
  fiber_bundles_namespace* ns = new fiber_bundles_namespace("time_polyline.t");

  ns->get_read_write_access();

  // Make line mesh

  base_space_poset* lmesh =
    &ns->new_base_space<unstructured_block>("polyline", "", "", 1, true);
  lmesh->get_read_write_access();

  // Make triangle block base space

  poset_path lproto_path(unstructured_block::prototypes_poset_name(),
                         "segment_complex");

  unstructured_block lbase_space(lmesh, lproto_path, xedge_ct);
  lbase_space.put_name("line_block", true, false);

  // Record the start time

  clock_t start = clock();

  // Write it to a file

  xsa->write_entire(*ns);

  // Record the total time to execute storage

  clock_t end = clock();
  write_time[xindex] = ((double) end) / ((double) CLOCKS_PER_SEC) -
                       ((double) start) / ((double) CLOCKS_PER_SEC);

  // Clean-up

  lbase_space.detach_from_state();
  lmesh->release_access();
  delete ns;
}

void
time_read_domain(storage_agent* xsa, int xdomain_ct, int xdomain_id, int xindex)
{
  // Make the default namespace

  namespace_poset ns("test");

  // Read the namespace from the file;
  // need write access in order to read it.

  ns.get_read_write_access();

  // Read the namespace poset

  xsa->read(ns);

  //
  /// @error The read() call above only reads the top of the namespace.
  ///          When the poset constructor below is called it returns a
  ///          poset that is not attached.  And hence, the call to
  ///          get_read_access() fails.
  ///

  // Attach a poset handle to the mesh poset

  poset* p = ns.member_poset<poset>(string("polyline"), false);
  p->get_read_access();

  ///@todo Convert from strstream to stringstream (also delete the "ends").

  strstream domain_id_stream;
  string    domain_name;

  domain_id_stream << "domain_" << xdomain_id << ends;
  domain_id_stream >> domain_name;

  poset_member domain(p, domain_name);

  poset_bounds_descriptor domain_bounds(poset_bounds_descriptor::MEMBER_MEMBER,
                                        scoped_index(BOTTOM_INDEX),
                                        domain.index());

  // Record the start time

  clock_t start = clock();

  // Read specified domain.

  xsa->read(*p, domain_bounds);

  // Record the total time to execute storage

  clock_t end = clock();
  read_time[xindex] = ((double) end) / ((double) CLOCKS_PER_SEC) -
                      ((double) start) / ((double) CLOCKS_PER_SEC);

  // Detach the handles before
  // the destructors get called to avoid
  // them complaining about needing access.

  domain.detach_from_state();
  p->release_access();

}

void
write_output(int xiterations, int xdomain_ct)
{

  // Create the file output stream

  ofstream output(OUTPUT_FILENAME);

  // Write out the current date
  time_t t;
  time(&t);
  cout << ctime(&t) << endl;
  output << ctime(&t) << endl;

  // Write out input arguments
  cout << "domain_ct = " << xdomain_ct << endl
  << "iterations = " << xiterations << endl << endl;
  output << "domain_ct = " << xdomain_ct << endl
  << "iterations = " << xiterations << endl << endl;

  // Write the column headers

  cout << "Edge Count, Write Time, Read Time" << endl;
  output << "Edge Count, Write Time, Read Time" << endl;

  // Write the data table

  for(int i=0;i<xiterations;i++)
  {
    cout << edges[i] << ", "
    << write_time[i] << ", "
    << read_time[i] << endl;
    output << edges[i] << ", "
    << write_time[i] << ", "
    << read_time[i] << endl;
  }

  output.close();

}

const char*
hdf_filename(int xiteration)
{
  static char result[1024];
  sprintf(result,"polyline.t.%i.hdf",xiteration);

  return (const char*) result;
}

void
remove
  (int xiteration)
{
  int result = unlink(hdf_filename(xiteration));
}

int
main(int argc, char** argv)
{

  int domain_ct  = 1;
  int domain_id  = 3;
  int iterations = 1;

  // Process the input arguments

  if (argc > 1)
  {
    domain_ct = atoi(argv[1]);
  }

  if (argc > 2)
  {
    domain_id = atoi(argv[2]);
  }

  if (argc > 3)
  {
    iterations = atoi(argv[3]);
  }

  bool keep_results = false;

  if (argc > 4)
  {
    keep_results=true;
  }

  // Preconditions:

  require(domain_ct>0);
  require(domain_id>=3);
  require(iterations>0);

  // Initialize arrays of results

  edges = new int[iterations];
  write_time = new double[iterations];
  read_time = new double[iterations];

  // Set the initial edge count to the number of domains

  edge_ct = domain_ct;

  for(int i=0; i<iterations; i++)
  {

    // Create the storage agent.

    storage_agent* sa = new storage_agent(hdf_filename(i),
                                          sheaf_file::READ_WRITE);
    sa->put_member_record_buffer_ub(15);
    sa->put_dof_tuple_record_buffer_ub(15);

    // Increment the edge count if it is not the first time through the loop

    if (i!=0)
      edge_ct *= 2;

    // Store the edge count

    edges[i] = edge_ct;

    // Time the writing out of the hdf file and record

    time_write(sa, edge_ct, domain_ct, i);

    // Time the reading of a single domain and record

    time_read_domain(sa, domain_ct, domain_id, i);

    // If the user doesn't want the hdf files, then remove the temp file

    if (!keep_results)
      remove
        (i);

    // Delete the storage_agent

    //     delete sa;
  }

  // Write the output table to the text file

  write_output(iterations, domain_ct);

  // Delete the result arrays

  delete edges;
  delete write_time;
  delete read_time;
}
