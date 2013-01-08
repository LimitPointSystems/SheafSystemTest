// $RCSfile: block_scaling_test.impl.h,v $ $Revision: 1.14.24.1 $ $Date: 2013/01/08 14:59:48 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @file block_scaling_test.impl.h
/// Implementation for template functions of block_scaling_test.h

#ifndef BLOCK_SCALING_TEST_H
#include "block_scaling_test.h"
#endif


#ifndef BASE_SPACE_FACTORY_H
#include "base_space_factory.h"
#endif

#ifndef FIBER_BUNDLES_NAMESPACE_H
#include "fiber_bundles_namespace.h"
#endif

#ifndef INDEX_SPACE_ITERATOR_H
#include "index_space_iterator.h"
#endif

#ifndef PLOT_H
#include "plot.h"
#endif

#ifndef POSTORDER_ITR_H
#include "postorder_itr.h"
#endif

#ifndef PREORDER_ITR_H
#include "preorder_itr.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

#ifndef STD_STRSTREAM_H
#include "std_strstream.h"
#endif

#ifndef STOP_WATCH_H
#include "stop_watch.h"
#endif

#ifndef STORAGE_AGENT_H
#include "storage_agent.h"
#endif

#ifndef TEST_SECTIONS_IMPL_H
#include "test_sections.impl.h"
#endif

#ifdef _WIN32
#undef USE_RUSAGE
#endif

#ifdef USE_RUSAGE
#include <sys/time.h>
#include <sys/resource.h>
#endif // USE_RUSAGE

namespace fiber_bundle
{
  
  using namespace sheaf;
  
template<typename T>
T* make_block(fiber_bundles_namespace* xns, size_type xsizes[], size_type xdi)
{
  // Preconditions:

  require(xns != 0);
  require(xns->state_is_read_write_accessible());
  require_for_all(i, 0, xdi, xsizes[i] > 0);

  // Body:

  poset_path lpath("mesh", "block");
    
  base_space_factory<T> lfactory;

  for(size_type l=0; l<xdi; ++l)
  {
    lfactory.index_ubs.push_back(xsizes[l]);
  }

  T* result = lfactory.new_base(*xns, lpath);

  result->get_read_access();
    
  // Postconditions:

  ensure(result->state_is_read_accessible());
    
  return result;
};

template<typename T>
void
time_block(string xname, size_type xsizes[], size_type xdi, plot& xtime_plot, plot& xmem_plot)
{
  // Preconditions:

  // Body:

  // Create the name of the namespace.

  strstream lname_str;
  lname_str << xname;
  for(int m=0; m<xdi; ++m)
  {
    lname_str << "_" << xsizes[m];
  }
  string lname;
  lname_str >> lname;

  // Create the filename.

  string lfilename = lname + ".hdf";

  // Construct the namespace.
  
  double lpoint[32];

  fiber_bundles_namespace lns(lname);
  lns.get_read_write_access();

  // Time block constructor.

  stop_watch lwatch;
  lwatch.start();

  T* lblock = make_block<T>(&lns, xsizes, xdi);
  lblock->get_read_access();

  lwatch.stop();

  int lzone_ct = 1;
  for(int l=0; l<xdi; ++l)
  {
    lzone_ct *= xsizes[l];
  }

  int pid = 0;

  lpoint[pid++] = lzone_ct;
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  cout << "  zone ct: " << setw(12) << lzone_ct
       << "  member ct: " << setw(12) << lblock->host()->member_ct()
       << "  ctor time: " << setw(12) << lwatch.time(stop_watch::MILLISECONDS);

#ifdef TEST_SECTION

  // Time construction of section.

  lwatch.reset();
  lwatch.start();
  
  sec_at0::host_type& lprop_space = make_scalar_section_space<T>(lns, *lblock);
 
  sec_at0 lprop(&lprop_space);
  lprop.get_read_write_access();
  lprop.put_name("property", true, false);

  lwatch.stop();
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  cout << "\tsec ctor time: "
       << setw(8) << lwatch.time(stop_watch::MILLISECONDS);

  // Time assignment of section.

  lwatch.reset();
  lwatch.start();
  
  sec_at0::fiber_type::volatile_type lfiber = 2.0;
  lprop = lfiber;

  lwatch.stop();
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  cout << "\tassign sec time: "
       << setw(8) << lwatch.time(stop_watch::MILLISECONDS);

  lprop.detach_from_state();

#endif // TEST_SECTION

#ifdef TEST_ITR

  // Time postorder iterator.

  lwatch.reset();
  lwatch.start();

  size_type litr_ct = 0;

  postorder_itr<zn_to_bool> lpost_itr(*lblock, DOWN, NOT_STRICT);
  while(!lpost_itr.is_done())
  {
    lpost_itr.next();
    ++litr_ct;
  }

  lwatch.stop();
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  cout << "\tpost itr time: " 
       << setw(8) << lwatch.time(stop_watch::MILLISECONDS);

  cout << "\tpost ct: "
       << setw(8) << litr_ct;

  // Time iterator reset.

  lwatch.reset();
  lwatch.start();

  lpost_itr.reset();

  lwatch.stop();
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  // Force done so iterator doesn't delete anchor
  // when iterator goes out of scope.

  lpost_itr.force_is_done();

  cout << "\treset time: " << setw(8) << lwatch.time(stop_watch::MILLISECONDS);

  // Time preorder iterator.

  lwatch.reset();
  lwatch.start();

  litr_ct = 0;

  preorder_itr<zn_to_bool> lpre_itr(*lblock, DOWN, NOT_STRICT);
  while(!lpre_itr.is_done())
  {
    lpre_itr.next();
    ++litr_ct;
  }

  lwatch.stop();
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  cout << "\tpre itr time: "
       << setw(8) << lwatch.time(stop_watch::MILLISECONDS);

  cout << "\tpre ct: "
       << setw(8) << litr_ct;

  // Time connectivity itr.

  lwatch.reset();
  lwatch.start();

  index_space_iterator& lzone_itr = lblock->get_zone_iterator(false);
  while(!lzone_itr.is_done())
  {
    index_space_iterator& ladj_itr =
      lblock->get_connectivity_iterator(lzone_itr.hub_pod(), false);
    while(!ladj_itr.is_done())
    {
      ladj_itr.next();
    }
    lblock->release_connectivity_iterator(ladj_itr, false);

    lzone_itr.next();
  }
  lblock->release_zone_iterator(lzone_itr, false);
    
  lwatch.stop();
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  cout << "\tconn itr time: "
       << setw(8) << lwatch.time(stop_watch::MILLISECONDS);

  // Time adjacency itr.

  lwatch.reset();
  lwatch.start();

  index_space_iterator& lvertex_itr = lblock->get_vertex_iterator(false);
  while(!lvertex_itr.is_done())
  {
    index_space_iterator& ladj_itr =
      lblock->get_adjacency_iterator(lvertex_itr.hub_pod(), false);
    while(!ladj_itr.is_done())
    {
      ladj_itr.next();
    }
    lblock->release_adjacency_iterator(ladj_itr, false);

    lvertex_itr.next();
  }
  lblock->release_vertex_iterator(lvertex_itr, false);

  lwatch.stop();
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  cout << "\tadj itr time: "
       << setw(8) << lwatch.time(stop_watch::MILLISECONDS);

  // Time lower cover itr.

  lwatch.reset();
  lwatch.start();

  lzone_itr = lblock->get_zone_iterator(false);
  while(!lzone_itr.is_done())
  {
    index_space_iterator& lcover_itr =
      lblock->host()->get_cover_iterator(LOWER, lzone_itr.hub_pod());
    while(!lcover_itr.is_done())
    {
      lcover_itr.next();
    }
    lblock->release_cover_iterator(lcover_itr);

    lzone_itr.next();
  }
  lblock->release_zone_iterator(lzone_itr, false);
    
  lwatch.stop();
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  cout << "\tlower itr time: "
       << setw(8) << lwatch.time(stop_watch::MILLISECONDS);

  // Time upper cover itr.

  lwatch.reset();
  lwatch.start();

  lvertex_itr = lblock->get_vertex_iterator(false);
  while(!lvertex_itr.is_done())
  {
    index_space_iterator& lcover_itr =
      lblock->host()->get_cover_iterator(UPPER, lvertex_itr.hub_pod());
    while(!lcover_itr.is_done())
    {
      lcover_itr.next();
    }
    lblock->release_cover_iterator(lcover_itr);

    lvertex_itr.next();
  }
  lblock->release_vertex_iterator(lvertex_itr, false);

  lwatch.stop();
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  cout << "\tupper itr time: "
       << setw(8) << lwatch.time(stop_watch::MILLISECONDS);

#endif // TEST_ITR

#ifdef TEST_IO

  // Time write.

  lwatch.reset();
  lwatch.start();

  storage_agent sa(lfilename, sheaf_file::READ_WRITE, true, false);
  sa.write_entire(lns);

  lwatch.stop();
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  cout << "\twrite time: "
       << setw(8) << lwatch.time(stop_watch::MILLISECONDS);

  // Time read.

  namespace_poset lread_ns(lname);
  lread_ns.get_read_write_access();

  lwatch.reset();
  lwatch.start();

  storage_agent read_sa(lfilename, sheaf_file::READ_ONLY, false);
  read_sa.put_member_record_buffer_ub(15);
  read_sa.put_dof_tuple_record_buffer_ub(15);
  read_sa.read_entire(lread_ns);

  lwatch.stop();
  lpoint[pid++] = lwatch.time(stop_watch::MILLISECONDS);

  cout << "\tread time: "
       << setw(8) << lwatch.time(stop_watch::MILLISECONDS);

#endif // TEST_IO

  // Add times to time plot.

  xtime_plot.add_point(lpoint);  

  // Test memory usage.

  pid = 1;

  // Get the "deep size" of the base space poset.

  base_space_poset* lmesh = reinterpret_cast<base_space_poset*>(lblock->host());  
  lmesh->get_read_access();

  size_t lmemory_parts[4];
  size_t lmemory = deep_size(*lmesh, true, lmemory_parts);

  lmesh->release_access();

  lpoint[pid++] = static_cast<double>(lmemory);
  lpoint[pid++] = static_cast<double>(lmemory_parts[0]);
  lpoint[pid++] = static_cast<double>(lmemory_parts[1]);
  lpoint[pid++] = static_cast<double>(lmemory_parts[2]);
  lpoint[pid++] = static_cast<double>(lmemory_parts[3]);

  cout << " \tmemory: " << lmemory;
  cout << " \tposet_crg_state: " << lmemory_parts[0];
  cout << " \tposet_id_space: " << lmemory_parts[1];
  cout << " \tposet_powerset_state: " << lmemory_parts[2];
  cout << " \tposet_table_state: " << lmemory_parts[3];

  // Get the deep size of the static handle pools.

  size_type lhandle_ct, lhandle_deep_size;

  pools_size(lhandle_ct, lhandle_deep_size);

  lpoint[pid++] = static_cast<double>(lhandle_deep_size);

  cout << " \thandle ct: " << lhandle_ct;
  cout << " \thandle deep size: " << lhandle_deep_size;

#ifdef USE_RUSAGE

  // Use rusage to test memory performance.

  rusage lrusage;

  int lusage_result = getrusage(RUSAGE_SELF, &lrusage);

  assertion(lusage_result == 0);

  // Convert rusage into bytes.

  int maxrss = lrusage.ru_maxrss * 100;

  lpoint[pid++] = static_cast<double>(maxrss);

  cout << " \tmax resident size: " << maxrss;

#endif // USE_RUSAGE

  // Finished output for this increment.

  cout << endl;
  
  // Add point to memory plot.

  xmem_plot.add_point(lpoint);

  // Clean-up

  lblock->detach_from_state();
  delete lblock;
    

  // Postconditions:

  // Exit:
};
  
template<typename T, int D>
void
test_scaling(int xargc, char* xargv[],
	     plot::plot_type xtime_plot_types[12],
	     plot::plot_type xmem_plot_types[7])
{
  // Command line processing:

  size_type max_elements = (xargc > 1) ? atoi(xargv[1]): 16000;

  // Preconditions:

  //  require(max_elements >= 8000);

  // Body:

  string lpath = string(xargv[0]);
  size_t lindex = lpath.find_last_of("/\\");
  string lname = (lindex == string::npos) ? lpath : lpath.substr(lindex+1);

  // Create times plot instance.

  int lnum_curves = 1;

#ifdef TEST_SECTION
  lnum_curves += 2;
#endif

#ifdef TEST_ITR
  lnum_curves += 7;
#endif

#ifdef TEST_IO
  lnum_curves += 2;
#endif

  int cid = 0;
  const char** lcurve_labels = new const char*[lnum_curves];
  lcurve_labels[cid++] = "block ctor";
#ifdef TEST_SECTION
  lcurve_labels[cid++] = "sec ctor";
  lcurve_labels[cid++] = "assign sec";
#endif

#ifdef TEST_ITR
  lcurve_labels[cid++] = "postorder";
  lcurve_labels[cid++] = "reset";
  lcurve_labels[cid++] = "preorder";
  lcurve_labels[cid++] = "connectivity";
  lcurve_labels[cid++] = "adjacency";
  lcurve_labels[cid++] = "lower cover";
  lcurve_labels[cid++] = "upper cover";
#endif

#ifdef TEST_IO
  lcurve_labels[cid++] = "write";
  lcurve_labels[cid++] = "read";
#endif

  plot ltime_plot(xargv[0],
                  lcurve_labels,
                  lnum_curves,
                  "Zone Count",
                  "Time(ms)",
		  xtime_plot_types);

  // Create memory plot instance.

#ifdef USE_RUSAGE
  int lnum_mem_curves = 7;
#else
  int lnum_mem_curves = 6;
#endif

  const char** lmem_curve_labels = new const char*[lnum_mem_curves];
  lmem_curve_labels[0] = "total memory";
  lmem_curve_labels[1] = "cover relation graph";
  lmem_curve_labels[2] = "id spaces";
  lmem_curve_labels[3] = "subposets";
  lmem_curve_labels[4] = "dof tuples";
  lmem_curve_labels[5] = "static pools";
#ifdef USE_RUSAGE
  lmem_curve_labels[6] = "max resident set";
#endif

  // Create the memory plot.

  string lmem_name = (lindex == string::npos) ? "mem_" + lname :
    lpath.substr(0, lindex+1) + "mem_" + lname;
  plot lmem_plot(lmem_name.c_str(),
                 lmem_curve_labels,
                 lnum_mem_curves,
                 "Member Count",
                 "Memory(bytes)",
		 xmem_plot_types);

  // Strip the '.t' from the name.

  lindex = lname.find_last_of(".");
  lname = lname.substr(0, lindex);

  // Add data points to the plots.

  int ldi = D;

  assertion(ldi <=3);
  
  // hack point_blocks can't deal with 1x.
  // size_type lsizes[3] = {2,1,1};

  size_type lsizes[3] = {2,2,2};
  int l = 0;
  int lzone_ct = 1;
  for(int m=0; m<ldi; ++m)
  {
    lzone_ct *= lsizes[m];
  }  
  
  while(lzone_ct <= max_elements)
  {
    time_block<T>(lname, lsizes, ldi, ltime_plot, lmem_plot);

    l = (l+1) % ldi;
    lsizes[l] *= 2;
    lzone_ct *= 2;
  }

  // Postconditions:

  // Exit:
}

} // namespace fiber_bundle
