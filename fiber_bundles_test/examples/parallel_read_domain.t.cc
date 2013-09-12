
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

/// @example examples/parallel_read_domain.t.cc

#include "std_iostream.h"
#include "namespace_poset.h"
#include "sec_rep_space.h"
#include "storage_agent.h"
#ifdef PARALLEL
#include "mpi.h"
#endif

string filename;

int
main(int argc, char** argv)
{

#ifdef PARALLEL

  MPI::Init(argc,argv);

  // Which processor am I?
  int rank = MPI::COMM_WORLD.Get_rank();
  /// @todo check return value and take appropriate action.

  // How many processors are there?
  int proc_ct = MPI::COMM_WORLD.Get_size();
  /// @todo check return value and take appropriate action.

  if (argc > 1)
  {
    filename = argv[1];
  }
  else
  {
    cerr << "usage: mpirun -np 2 parallel_read_domain.t sheaf_file\n";
    exit(1);
  }

  // Preconditions:

  require(MPI::Is_initialized());
  require(proc_ct <= 2);
  /// @hack domain_id[] below is hardwired for 2 processors.

  // Body:

  // An array of internal member ids.  domain_id[rank] should
  // be the id of a jrm in poset "polyline" whose downset is
  // the portion of the mesh local to this processor.  It is
  // sufficient that domain_id[rank] be the index of an existing
  // member of "polyline".  Otherwise the subsequent call to
  // sa.read will violate an assertion on processor "rank".

  int domain_id[2] =
    {
      3,4
    };


  // Make the default namespace

  namespace_poset ns("test");

  // Read the namespace from the file;
  // need write access in order to read it.

  ns.get_read_write_access();
  storage_agent sa(filename, sheaf_file::READ_ONLY, false);
  sa.put_member_record_buffer_ub(15);
  sa.put_dof_tuple_record_buffer_ub(15);

  // Read the namespace poset

  sa.read(ns);

  // Attach a poset handle to the mesh poset

  poset p(&ns, "polyline");

  // Read appropriate domain.

  sa.read(p, domain_id[rank]);

  // Output a text version to stdout

  p.get_read_access();

  // Serialize the output so it doesn't get scrambled.

  MPI::Status status;

  if (rank == 0)
  {
    // ... then we're first.  Don't wait - just write.
    cout << p << endl;
    // Send processor 1 a simple message to let him know it's his turn.
    // The contents are irrelevant (it's the waiting that's important)
    // so we send him a message with no data
    if (proc_ct > 1)
      MPI::COMM_WORLD.Send(0,0,MPI::INTEGER,rank+1,0);
    // Note: MPI seems to throw an exception if invalid arguments are supplied
    // to Send().  There is no return code as in C.
  }
  else if (rank != proc_ct-1)
  {
    // ... then we're neither first nor last.  Wait until the previous processor
    // finished before starting to write.
    MPI::COMM_WORLD.Recv(0,0,MPI::INTEGER,rank-1,0,status);
    assertion(status.Get_error() == MPI::SUCCESS);
    cout << p << endl;
    // We're done writing; let processor `rank+1' know it's his turn:
    MPI::COMM_WORLD.Send(0,0,MPI::INTEGER,rank+1,0);
  }
  else
  {
    // We're last.  Wait until the previous processor finished before starting to write.
    MPI::COMM_WORLD.Recv(0,0,MPI::INTEGER,rank-1,0,status);
    assertion(status.Get_error() == MPI::SUCCESS);
    cout << p << endl;
  }

  // Clean up resources acquired above before exit.

  p.release_access();

  // Detach the poset handle before
  // the destructor gets called to avoid
  // it complaining about needing access.

  p.detach_from_state();

  MPI::Finalize();

  ///assertion(Is_finalized()); /// @hack not implemented in mpich-1.2.2.2.  Not in any .[ah] file.

  // Exit:

  return 0;
#else // not PARALLEL

  cout << "Not built with -DPARALLEL\n";
#endif // PARALLEL
}
