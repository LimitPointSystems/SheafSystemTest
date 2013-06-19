
//
// Copyright (c) 2010 Limit Point Systems, Inc.
//

/// @example kd_lattice/kd_lattice.t.cc
/// Unit test driver for class kd_lattice.

#include "base_space_member.h"
#include "base_space_member_prototype.h"
#include "cohort.h"
#include "e3.h"
#include "geometry_namespace.h"
#include "index_space_iterator.h"
#include "kd_enums.h"
#include "kd_face.h"
#include "kd_lattice.h"
#include "kd_plane.h"
#include "kd_point.h"
#include "kd_region.h"
#include "kd_segment.h"
#include "kd_surface.h"
#include "kd_triangle.h"
#include "kd_zone.h"
#include "postorder_itr.h"
#include "sec_at1_space.h"
#include "sec_e3.h"
#include "std_iostream.h"
#include "std_cmath.h"
#include "vertex_cohort.h"

using namespace fiber_bundle;
using namespace geometry;

// class null_action
// {
// public:
//   null_action() {return;};
//   void previsit(kd_lattice& xhost, const scoped_index& xid){return;};
//   void postvisit(kd_lattice& xhost, const scoped_index& xid){return;};
//   ~null_action() {return;};
// };  

// class count_action
// {
// public:
//   count_action() {ct = 0;};
//   void previsit(kd_lattice& xhost, const scoped_index& xid){};
//   void postvisit(kd_lattice& xhost, const scoped_index& xid){ct++;};
//   ~count_action() {};
//   size_type ct;
// };  

// class connectivity_action
// {
// public:
//   connectivity_action(vtkIdTypeArray* xconn) : cell_ct(0), conn(xconn) {};
//   void previsit(kd_lattice& xhost, const scoped_index& xid){};
//   void postvisit(kd_lattice& xhost, const scoped_index& xid)
//   {
//     if(xhost.leaves().contains(xid))
//     {
//       cell_ct++;
//       kd_zone::vertices(xhost, xid, vertex_ids);
//       for(int i=0; i<kd_zone::VERTEX_CT; ++i)
//       {
// 	int lvid = xhost.vertices().id_space().pod(vertex_ids[i]);
// 	conn->InsertNextValue(lvid);
//       }
//     }
//   };
//   ~connectivity_action() {};
//   int cell_ct;
//   vtkIdTypeArray* conn;
//   scoped_index vertex_ids[kd_zone::VERTEX_CT];
// };  

// class cell_action
// {
// public:
//   cell_action(vtkCellArray* xcells) : cell_ct(0), cells(xcells) {};
//   void previsit(kd_lattice& xhost, const scoped_index& xid){};
//   void postvisit(kd_lattice& xhost, const scoped_index& xid)
//   {
//     if(xhost.leaves().contains(xid))
//     {
//       cell_ct++;
//       kd_zone::vertices(xhost, xid, vertex_ids);
//       index_space& lvertex_id_space = xhost.coords().schema().discretization_id_space();
//       for(int i=0; i<kd_zone::VERTEX_CT; ++i)
//       {
// 	vertex_pods[i] = lvertex_id_space.pod(vertex_ids[i]);
//       }
//       cells->InsertNextCell(kd_zone::VERTEX_CT, vertex_pods);

//       cout << "leaf id: " << xid << endl;
//       cout << "  vertex ids: ";
//       for(int i=0; i<kd_zone::VERTEX_CT; ++i)
//       {
// 	cout << "  " << vertex_ids[i];
//       }
//       cout << endl;

//       cout << "  disc id: ";
//       for(int i=0; i<kd_zone::VERTEX_CT; ++i)
//       {
// 	cout << "  " << vertex_pods[i];
//       }
//       cout << endl;
//     }
//   };
//   ~cell_action() {};
//   int cell_ct;
//   vtkCellArray* cells;
//   scoped_index vertex_ids[kd_zone::VERTEX_CT];
//   vtkIdType vertex_pods[kd_zone::VERTEX_CT];
// };  



//
// Creates a line with xpt_ct points in plane xp.
//
void make_line(const kd_lattice& xhost, const kd_plane& xp, int xpt_ct, list<e3_lite>& xline, bool xclose = true)
{
  cout << endl << "Entering make_line." << endl;
  
  xline.clear();
  
  int lu_id, lv_id;
  xp.local_axes(lu_id, lv_id, true);

  vd_value_type ltolerance = 50.0*(xhost.point_tolerance()[lu_id] + xhost.point_tolerance()[lv_id]);
  vd_value_type lr =  1.0 - ltolerance;

  vd_value_type ld = abs(xp.distance());
  
  //  vd_value_type lh = sqrt(lr*lr - ld*ld);
  //  vd_value_type lh = lr - ld; // only for lpt_ct = 5
  
  const vd_value_type PI = 4.0*atan(1.0);
  
  vd_value_type ldelta = (2.0*PI)/(xpt_ct-1);

  vd_value_type lphi = (PI - ldelta)*0.5;
  vd_value_type lh = lr - (ld/tan(lphi));
  
  e3_lite lpt;
  lpt[xp.alignment()] = xp.distance();

  int ibeg = xclose ? 0 : 1;
  int iend = xclose ? xpt_ct : xpt_ct - 1;
  
  
  for(int i=ibeg; i<iend; ++i)
  {
    lpt[lu_id] = lh*cos(i*ldelta);
    lpt[lv_id] = lh*sin(i*ldelta);

    cout << "  " << lpt << endl;
    
    xline.push_back(lpt);
  }
  
  cout << "Leaving make_line." << endl << endl;
  return;
}

  


int main(int argc, const char* argv[])
{

  bool ldo_display = (argc > 1);
  
  geometry_namespace lns("the_namespace");

  lns.get_read_write_access();

  // Turn on autonaming for cohort members.

  abstract_cohort::auto_name_members() = true;
  
  e3_lite llb(-1.0, -1.0, -1.0);
  e3_lite lub(1.0, 1.0, 1.0);

  kd_lattice lkdl(lns, "test_lattice", llb, lub);
  base_space_poset& lbase = lkdl.base_space();

  lkdl.update_section_space_schema();
  // cout << lkdl << endl;
  
  lkdl.display_expansion_factor() = 5.0;
  
//  lkdl.display_insert_plane() = true;
//  lkdl.display_insert_line()  = true;
//  lkdl.display_remove_line()  = true;
//  lkdl.display(true);

  int ltest_id = 2;
  
  if(ltest_id == 0)
  {
    // Create a plane.

    cout << endl << "########### Creating plane0 and line #############################" << endl << endl;  

    list<e3_lite> lline;
    kd_plane lplane0(Y_AXIS_ALIGNED, -0.5);

    lkdl.insert_plane(lplane0);

    lkdl.update_section_space_schema();
    //cout << lkdl << endl;

    //   e3_lite lpt00(-0.5, -0.5, -0.25);
    //   e3_lite lpt01( 0.5, -0.5,  0.75);
    e3_lite lpt00(-0.5, -0.5,  0.0);
    e3_lite lpt01( 0.5, -0.5,  0.0);
  
    lline.push_back(lpt00);
    lline.push_back(lpt01);
  
    lkdl.insert_line(lline, lplane0);

    lkdl.update_section_space_schema();
    //  cout << lkdl << endl;

    // Create a second plane.

    cout << endl << "########### Creating plane1 and line #############################" << endl << endl;

    kd_plane lplane1(Y_AXIS_ALIGNED, 0.5);

    lkdl.insert_plane(lplane1);

    lkdl.update_section_space_schema();
    //cout << lkdl << endl;

    //   e3_lite lpt10(-0.5, 0.5, -0.25);
    //   e3_lite lpt11( 0.5, 0.5,  0.75);
    e3_lite lpt10(-0.5, 0.5, 0.0);
    e3_lite lpt11( 0.5, 0.5, 0.0);
  
    lline.clear();
    lline.push_back(lpt10);
    lline.push_back(lpt11);
  
    lkdl.insert_line(lline, lplane1);

    lkdl.update_section_space_schema();
    // cout << lkdl << endl;

    // Create a third plane.

    cout << endl << "########### Creating plane2 and line #############################" << endl << endl;

    //  kd_plane lplane2(X_AXIS_ALIGNED, 0.0);
    kd_plane lplane2(X_AXIS_ALIGNED, -0.5);

    lkdl.insert_plane(lplane2);

    lkdl.update_section_space_schema();
  
    //cout << lkdl << endl;

    //   e3_lite lpt20( 0.0, -0.6,  0.25);
    //   e3_lite lpt21( 0.0,  0.6,  0.25);
    e3_lite lpt20( -0.5, -0.5,  0.0);
    e3_lite lpt21( -0.5,  0.75,  0.0);
  
    lline.clear();
    lline.push_back(lpt20);
    lline.push_back(lpt21);
  
    lkdl.insert_line(lline, lplane2);

    lkdl.update_section_space_schema();
    //  cout << lkdl << endl;

    //    e3_lite lregion_lb(-0.4, -0.4, -0.99);
    //    e3_lite lregion_ub(0.4,   0.4, 0.99);
    e3_lite lregion_lb(-0.5, -0.5, -0.99);
    e3_lite lregion_ub(0.5,   0.5, 0.99);
  
    lkdl.insert_region(lregion_lb, lregion_ub);

    //    cout << lkdl.base_space() << endl;

    lkdl.extract_subvolume_surfaces();  
  }  
  else if(ltest_id == 1)
  {
    // Create a plane.

    cout << endl << "########### Creating plane0 and line #############################" << endl << endl;  

    list<e3_lite> lline;
    kd_plane lplane0(Y_AXIS_ALIGNED, -0.5);

    lkdl.insert_plane(lplane0);

    lkdl.update_section_space_schema();
    //cout << lkdl << endl;

    e3_lite lpt00(-0.5, -0.5, -0.25);
    e3_lite lpt01( 0.5, -0.5,  0.75);
  
    lline.push_back(lpt00);
    lline.push_back(lpt01);
  
    lkdl.insert_line(lline, lplane0);

    lkdl.update_section_space_schema();
    //  cout << lkdl << endl;

    // Create a second plane.

    cout << endl << "########### Creating plane1 and line #############################" << endl << endl;

    kd_plane lplane1(Y_AXIS_ALIGNED, 0.5);

    lkdl.insert_plane(lplane1);

    lkdl.update_section_space_schema();
    //cout << lkdl << endl;

    e3_lite lpt10(-0.5, 0.5, -0.25);
    e3_lite lpt11( 0.5, 0.5,  0.75);
  
    lline.clear();
    lline.push_back(lpt10);
    lline.push_back(lpt11);
  
    lkdl.insert_line(lline, lplane1);

    lkdl.update_section_space_schema();
    // cout << lkdl << endl;

    // Create a third plane.

    cout << endl << "########### Creating plane2 and line #############################" << endl << endl;

    kd_plane lplane2(X_AXIS_ALIGNED, 0.0);

    lkdl.insert_plane(lplane2);

    lkdl.update_section_space_schema();
  
    //cout << lkdl << endl;

    e3_lite lpt20( 0.0, -0.6,  0.25);
    e3_lite lpt21( 0.0,  0.6,  0.25);
  
    lline.clear();
    lline.push_back(lpt20);
    lline.push_back(lpt21);
  
    lkdl.insert_line(lline, lplane2);

    lkdl.update_section_space_schema();
    //  cout << lkdl << endl;

    e3_lite lregion_lb(-0.4, -0.4, -0.99);
    e3_lite lregion_ub(0.4,   0.4, 0.99);
  
    lkdl.insert_region(lregion_lb, lregion_ub);

    //    cout << lkdl.base_space() << endl;

    lkdl.extract_subvolume_surfaces();  
  }  
  else if(ltest_id == 2)
  {
    cout << endl << "########### Creating plane0 and line #############################" << endl << endl;

    const int lpt_ct = 17;
  
    // Create a plane.

    list<e3_lite> lline;
    kd_plane lplane0(Y_AXIS_ALIGNED, 0.25);

    lkdl.insert_plane(lplane0);

    lkdl.update_section_space_schema();
    //cout << lkdl << endl;

    make_line(lkdl, lplane0, lpt_ct, lline, false);
  
    lkdl.insert_line(lline, lplane0);

    lkdl.update_section_space_schema();
    //  cout << lkdl << endl;

//     // Create a second plane.

//     cout << endl << "########### Creating plane1 and line #############################" << endl << endl;

//     kd_plane lplane1(X_AXIS_ALIGNED, 0.0);

//     lkdl.insert_plane(lplane1);

//     lkdl.update_section_space_schema();
//     //cout << lkdl << endl;

//     make_line(lkdl, lplane1, lpt_ct, lline);
  
//     lkdl.insert_line(lline, lplane1);

//     lkdl.update_section_space_schema();
//     // cout << lkdl << endl;

    // Create a third plane.

    cout << endl << "########### Creating plane2 and line #############################" << endl << endl;

    kd_plane lplane2(Z_AXIS_ALIGNED, 0.0);

    lkdl.insert_plane(lplane2);

    lkdl.update_section_space_schema();
  
    //cout << lkdl << endl;

    make_line(lkdl, lplane2, lpt_ct, lline, true);
  
    lkdl.insert_line(lline, lplane2);

    lkdl.update_section_space_schema();
    //  cout << lkdl << endl;

    //     cout << endl << "########### Creating plane3 and line #############################" << endl << endl;

    //     kd_plane lplane3(Z_AXIS_ALIGNED, -0.5);

    //     pt_list_list llines;
    //     lkdl.implicit_lines(lplane3, llines);

    //     lkdl.insert_plane(lplane3);

    //     lkdl.update_section_space_schema();

    //     for(pt_list_list::iterator l = llines.begin(); l != llines.end(); ++l)
    //     {
    //       lkdl.insert_line(*l, lplane3);
    //     }

    //     lkdl.update_section_space_schema();

//     e3_lite lregion_lb(-0.3, 0.1, -0.5);
//     e3_lite lregion_ub(0.3,   0.5, 0.5);
  
//     lkdl.insert_region(lregion_lb, lregion_ub);

//     //    cout << lkdl.base_space() << endl;

//     lkdl.extract_subvolume_surfaces();  

  }

  if(false)
  {  
    //    e3_lite lregion_lb(-0.4, -0.4, -0.99);
    //    e3_lite lregion_ub(0.4,   0.4, 0.99);
    e3_lite lregion_lb(-0.5, -0.5, -0.99);
    e3_lite lregion_ub(0.5,   0.5, 0.99);
  
    scoped_index lregion_id;
    lkdl.insert_region(lregion_lb, lregion_ub);

    cout << lkdl.base_space() << endl;
  
    lkdl.base_space().begin_jim_edit_mode(true);
    lkdl.coords().get_read_write_access();
  
    id_list lsubvolumes;
    kd_region::subvolumes(lkdl, lregion_id, lsubvolumes);

    for(id_list::iterator lsv=lsubvolumes.begin(); lsv != lsubvolumes.end(); ++lsv)
    {
      cout << "subvolume: " << lsv->pod() << "  " << kd_member::name(lkdl, *lsv) << endl;
    
      id_list ltris;
      kd_surface::triangles(lkdl, *lsv, ltris);
      cout << "triangles: " << endl << ltris << endl;
    }
  
    lkdl.coords().release_access();
    lkdl.base_space().end_jim_edit_mode(false, true);
  }
  

  //   cout << endl << "########### Deleting line 4 #############################" << endl << endl;

  // lkdl.remove_line(lline_id4, true);
  

  //   lkdl.write_dot("kd_lattice.t.dot");


  lkdl.update_section_space_schema();

  if(ldo_display)
  {
    //lkdl.display(true);
    lkdl.display(false, true);
    //    lkdl.display_subvolumes(true, true);
  }
  
  
  return 0;
}
