
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

/// @example concurrency/parallel.t.cc
/// Test of parallel operation

#include "std_iostream.h"
#include "std_string.h"
#include "std_fstream.h"
#include "std_strstream.h"
/*
#ifdef PARALLEL_MPI
#include "mpi++.h"
 
#ifndef SHEAF_FILE_H
#include "sheaf_file.h"
#endif
*/
/* @hack
   needs to be completely rewritten for the new poset cluster...
 
void      two_proc();
void      count_poset(poset *top, ostream *outfile);
poset    *create_poset();
void      print_poset(poset *top, ostream *outfile);
ofstream *setup_io();
 
void      three_proc();
 
int       rank;
int       size;
*/
int main(int argc, char **argv)
{

  cout << "No tests implemented." << endl;

  /*
  assertion(MPI_Init(&argc, &argv) == MPI_SUCCESS);

  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  if (size == 2)
    two_proc();
  else if (size == 3)
    three_proc();
  else if (rank == 0)
    cout << "usage: mpirun -np [23] parallel.t\n";

  MPI_Finalize();
  */

  return 0;
}

/*
ofstream *
setup_io() {
 
  string ofile = "parallel.t.cout.";
 
  ostrstream num;
 
  num << size << '.' << rank;
  ofile += num.str();
  ofstream *result = new ofstream(ofile.c_str());
 
  return result;
}
 
poset *
create_poset() {
 
  // preconditions:
 
  require(size == 2);
 
  // body:
 
  int    rank;
  poset *result;
  int    rtncode;
 
  switch (rank) {
  case 0:
    {
      result = poset::make_poset(1,2,1);
      result->request_read_write_access();
      int index = result->create_member(0,0,1);
      result->create_cover_link(index,result->index(),0);
      result->release_access();
    }
    break;
  case 1:
    result = poset::make_poset(0,1,1);
    break;
  }
 
  return result;
}
 
void
count_poset(poset *top, ostream *outfile) {
 
  // preconditions:
 
  require(top != 0);
  require(outfile != 0);
 
  poset_counter pc(top,0);
 
  *outfile << "My poset has "
    << pc.equivalence_ct()
    << " equivalences and "
    << pc.member_ct()
    << " members and "
    << pc.cover_link_ct()
    << " cover links"
    << endl;
}
 
void
print_poset(poset *top, ostream *outfile) {
 
  // preconditions:
 
  require(top != 0);
  require(outfile != 0);
 
  // body:
 
  poset_printer pp;
 
  pp.print(top,*outfile);
}
 
void
three_proc() {
 
  // preconditions:
 
  require(size == 3);
 
  // body:
 
  MPI_Comm  comm[3];
  MPI_Group world_group;
  bool      mpi_calls_succeeded = false;
 
  if (MPI_Comm_group(MPI_COMM_WORLD,&world_group) == MPI_SUCCESS) {
    for (int i = 0; i < 3; ++i) {
 
      MPI_Group group;
 
      if (MPI_Group_excl(world_group,1,&i,&group) == MPI_SUCCESS)
 if (MPI_Comm_create(MPI_COMM_WORLD,group,comm+i) == MPI_SUCCESS) {
   mpi_calls_succeeded = true;
   MPI_Group_free(&group);
 }
 else {
   mpi_calls_succeeded = false;
   MPI_Group_free(&group);
   break;
 }
    }
    MPI_Group_free(&world_group);
    if (mpi_calls_succeeded == false) {
      MPI_Finalize();
      assertion(0);
    }
  }
 
  sheaf_file sf;
 
  string name("parallel.t.3.hdf");
 
  sf.create(&name,1024);
 
  ofstream *my_file = setup_io();
  poset *top = 0;
 
  *my_file << "Original poset:\n\n";
 
  switch(rank) {
  case 0: {
    //          top
    //           /\
    //          /  \
    //         p1   p2
    
    top = poset::make_poset(2,3,2);
    top->request_read_write_access();
    poset *p1  = new poset(top->storage(),top->create_member(1,0,1));
    poset *p2  = new poset(top->storage(),top->create_member(1,0,1));
    top->insert_cover_link(p1,0);
    top->insert_cover_link(p2,0);
    p1->make_equivalence(comm[2]);
    MPI_Barrier(MPI_COMM_WORLD);
    p2->make_equivalence(comm[1]);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    top->release_access();
    top->storage()->print(*my_file);
    top->storage()->write(&sf);
 
    break;
  }
  case 1: {
    //           p1
    //           /\
    //          /  \
    //         a    b
    poset *p1  = poset::make_poset(1,3,2);
    p1->request_read_write_access();
    poset *a   = new poset (p1->storage(),p1->create_member(0,0,1));
    poset *b   = new poset (p1->storage(),p1->create_member(0,0,1));
    p1->insert_cover_link(a,0);
    p1->insert_cover_link(b,0);
    p1->make_equivalence(comm[2]);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    a->make_equivalence(comm[0]);
    MPI_Barrier(MPI_COMM_WORLD);
    b->make_equivalence(comm[0]);
    p1->release_access();
    p1->storage()->print(*my_file);
    p1->storage()->write(&sf);
    break;
  }
  case 2: {
    //           p2
    //           /\
    //          /  \
    //         a    b
    poset *p2  = poset::make_poset(1,3,2);
    p2->request_read_write_access();
    poset *a   = new poset(p2->storage(),p2->create_member(0,0,1));
    poset *b   = new poset(p2->storage(),p2->create_member(0,0,1));
    p2->insert_cover_link(a,0);
    p2->insert_cover_link(b,0);
    MPI_Barrier(MPI_COMM_WORLD);
    p2->make_equivalence(comm[1]);
    MPI_Barrier(MPI_COMM_WORLD);
    a->make_equivalence(comm[0]);
    MPI_Barrier(MPI_COMM_WORLD);
    b->make_equivalence(comm[0]);
    p2->release_access();
    p2->storage()->print(*my_file);
    p2->storage()->write(&sf);
    break;
  }
  }
 
  sf.close();
 
  sf.open(&name,1024);
 
  poset_storage new_storage(&sf);
 
  *my_file << "\n\nPoset from disk:\n\n";
  new_storage.print(*my_file);
 
  sf.close();
}
 
void
two_proc() {
 
  // preconditions:
 
  require(size == 2);
 
  // body:
 
  ofstream *my_file = setup_io();
 
  *my_file << "Original poset:\n\n";
 
  // every proc has a copy of this, the processor decomposition:
 
  //          top
  //           /\
  //          /  \
  //         p1   p2
    
  poset *top = poset::make_poset(2,5,4);
  top->request_read_write_access();
  poset *p1  = new poset(top->storage(),top->create_member(1,0,1));
  poset *p2  = new poset(top->storage(),top->create_member(1,0,1));
  top->insert_cover_link(p1,0);
  top->insert_cover_link(p2,0);
  switch(rank) {
    // proc 0 has more:
  case 0: {
    //          top
    //           /\
    //          /  \
    //         p1   p2
    //         /\
    //        /  \
    //       a    b
    poset *a   = new poset (p1->storage(),p1->create_member(0,0,1));
    poset *b   = new poset (p1->storage(),p1->create_member(0,0,1));
    p1->insert_cover_link(a,0);
    p1->insert_cover_link(b,0);
    b->make_equivalence(MPI_COMM_WORLD);
    break;
  }
  // proc 1 also has more:
  case 1: {
    //          top
    //           /\
    //          /  \
    //         p1   p2
    //              /\
    //             /  \
    //            b    c
    p2->request_read_write_access();
    poset *b   = new poset(p2->storage(),p2->create_member(0,0,1));
    poset *c   = new poset(p2->storage(),p2->create_member(0,0,1));
    p2->insert_cover_link(b,0);
    p2->insert_cover_link(c,0);
    b->make_equivalence(MPI_COMM_WORLD);
    break;
  }
  }
  top->storage()->print(*my_file);
  top->release_access();
 
  sheaf_file sf;
 
  string name("parallel.t.2.hdf");
  sf.create(&name,1024);
 
  top->storage()->write(&sf);
 
  sf.close();
 
  sf.open(&name,1024);
 
  sheaf_file_index contents(&sf);
 
  contents.print();
 
  poset_storage from_disk(&sf);
 
  *my_file << "\n\nPoset from disk:\n\n";
  from_disk.print(*my_file);
 
}
 
#else // no PARALLEL_MPI
 
main() {
 
  cout << "Not built with -DPARALLEL_MPI\n";
}
 
#endif // no PARALLEL_MPI
*/
