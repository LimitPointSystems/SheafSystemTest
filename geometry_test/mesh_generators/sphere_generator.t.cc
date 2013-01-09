
// $RCSfile$ $Revision$ $Date$

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example sphere_generator.t.cc
/// Simple test driver for the tetgen mesh generator.

// Given a triangulated spherical surface (radius 1.5)
// composed of 288 triangles with 146 vertices,
// generate a tetrahedral mesh.

#include "fiber_bundles_namespace.h"
#include "geometry.h"
#include "index_space_iterator.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_at1_space.h"
#include "sec_e3.h"
#include "sec_rep_descriptor.h"
#include "section_space_schema_poset.h"
#include "std_fstream.h"
#include "std_sstream.h"
#include "std_string.h"
#include "storage_agent.h"
#include "subposet.h"
#include "subposet_member_iterator.h"
#include "tetgen_generator.h"
#include "unstructured_block.h"
#include "unstructured_block_builder.h"

//#define DIAGNOSTIC_OUTPUT

using namespace geometry;

namespace
{

//$$SCRIBBLE: Except for the following two functions, several test cases
//            have the same code.  It might make sense to put them into
//            a common class or stand alone functions file.

//==============================================================================

void
get_connectivities(vector<mesh_generator::pod_type>& xconns)
{
  const size_type lnode_id_ct = 864;
  const pod_index_type lnode_ids[864] =
  {
    2,     0,     1,
    0,     3,     4,
    0,     2,     3,
    0,     4,     1,
    6,     2,     5,
    5,     1,     7,
   14,     3,     8,
    1,     4,     9,
    3,     2,     8,
    2,     6,     8,
    4,    10,     9,
    4,     3,    11,
    7,     1,     9,
    3,    14,    11,
    4,    11,    10,
    5,     2,     1,
   25,    22,     5,
   25,     5,     7,
   10,    11,    17,
   11,    13,    17,
   22,     6,     5,
   14,    13,    11,
   20,    14,     8,
    9,    10,    15,
   26,     7,     9,
   21,    20,     8,
   26,     9,    15,
    6,    21,     8,
   10,    16,    15,
   12,    14,    20,
   13,    14,    12,
   10,    17,    16,
   34,     7,    26,
   34,    25,     7,
   30,     6,    22,
   30,    21,     6,
   29,    21,    30,
   22,    24,    32,
   16,    17,    41,
   17,    18,    41,
   30,    22,    32,
   36,    26,    15,
   37,    36,    15,
   19,    21,    29,
   16,    37,    15,
   13,    18,    17,
   20,    21,    19,
   25,    24,    22,
   23,    25,    34,
   24,    25,    23,
   13,    43,    18,
   13,    12,    43,
   31,    34,    26,
   36,    31,    26,
   12,    20,    27,
   27,    20,    19,
   28,    29,    30,
   12,    46,    43,
   33,    34,    31,
   46,    12,    27,
   16,    40,    37,
   28,    30,    32,
   16,    41,    40,
   23,    34,    33,
   35,    36,    37,
   19,    29,    52,
   35,    37,    38,
   37,    40,    38,
   29,    53,    52,
   28,    53,    29,
   50,    49,    41,
   18,    50,    41,
   55,    28,    32,
   55,    32,    39,
   41,    49,    40,
   32,    24,    39,
   50,    18,    42,
   56,    24,    23,
   24,    56,    39,
   18,    43,    42,
   60,    27,    19,
   60,    19,    52,
   36,    58,    31,
   35,    58,    36,
   57,    33,    31,
   46,    45,    43,
   58,    57,    31,
   61,    23,    33,
   43,    45,    42,
   59,    46,    27,
   60,    59,    27,
   56,    23,    61,
   40,    66,    38,
   33,    57,    63,
   44,    45,    46,
   49,    66,    40,
   44,    46,    59,
   61,    33,    63,
   54,    53,    28,
   54,    28,    55,
   52,    53,    82,
   86,    55,    39,
   51,    35,    38,
   56,    76,    39,
   76,    86,    39,
   47,    48,    50,
   60,    52,    91,
   47,    50,    42,
   48,    49,    50,
   87,    58,    35,
   51,    87,    35,
   91,    52,    82,
   86,    95,    55,
   53,    92,    82,
   53,    54,    92,
   66,    70,    38,
   70,    51,    38,
   95,    54,    55,
   49,    48,    67,
   49,    67,    66,
   72,    76,    56,
   84,    57,    58,
   59,    60,    65,
   85,    47,    42,
   60,    91,    65,
   72,    56,    61,
   45,    85,    42,
   87,    84,    58,
   57,    62,    63,
   44,    59,    68,
   74,    72,    61,
   74,    61,    63,
   45,    44,    64,
   85,    45,    64,
   68,    59,    65,
   57,    84,    62,
   75,    74,    63,
   44,    79,    64,
   67,    69,    66,
   79,    44,    68,
   54,    95,    93,
   69,    70,    66,
   62,    75,    63,
   92,    54,    93,
   48,   111,    67,
  111,    48,   112,
   74,    73,    72,
   69,    67,    71,
   67,   111,    71,
   77,    76,    72,
   71,   107,    70,
   69,    71,    70,
   73,    77,    72,
   96,    74,    75,
   76,    77,    78,
  107,   102,    51,
   70,   107,    51,
   79,    68,    80,
  100,    68,    65,
  102,    83,    87,
   48,    47,   112,
  112,    47,    81,
   68,   100,    80,
   73,    74,    96,
  102,    87,    51,
   91,    90,    65,
   90,   100,    65,
   47,    85,    81,
   81,    85,    99,
   92,   104,    82,
  104,    89,    82,
   84,    83,    97,
   99,    85,    64,
   80,    99,    64,
   76,    78,    86,
   79,    80,    64,
   83,    84,    87,
   86,    78,    88,
   97,    96,    62,
   90,    91,    89,
   92,    93,    94,
   84,    97,    62,
   96,    75,    62,
   93,    95,    94,
   95,    88,    94,
   89,    91,    82,
   86,    88,    95,
  104,    92,    94,
   80,   100,   114,
  111,   110,    71,
  105,   104,    94,
   97,    98,    96,
   99,    80,   114,
   88,   105,    94,
   71,   110,   107,
   98,    73,    96,
  120,    73,    98,
   77,    73,   120,
  117,    99,   114,
  117,    81,    99,
   98,    97,   122,
   97,    83,   122,
  100,    90,   101,
  100,   101,   114,
  113,    81,   117,
   78,    77,   126,
  126,    77,   120,
  112,    81,   113,
   90,   116,   101,
   83,   103,   122,
  102,   103,    83,
   90,    89,   116,
  105,   106,   104,
  110,   108,   107,
  106,    89,   104,
  107,   108,   102,
  110,   111,   109,
   88,   128,   105,
  109,   111,   112,
   78,   128,    88,
  128,    78,   126,
  108,   103,   102,
   89,   106,   116,
  109,   112,   113,
  108,   110,   129,
  118,   117,   114,
  105,   128,   115,
  110,   109,   129,
  120,    98,   121,
  101,   118,   114,
  106,   105,   115,
   98,   122,   121,
  116,   133,   101,
  125,   126,   120,
  122,   123,   121,
  117,   118,   119,
  125,   120,   121,
  101,   133,   118,
  113,   117,   119,
  103,   123,   122,
  116,   124,   133,
  127,   126,   125,
  130,   109,   113,
  130,   113,   119,
  103,   134,   123,
  103,   108,   134,
  127,   128,   126,
  106,   124,   116,
  109,   130,   129,
  128,   127,   115,
  108,   129,   134,
  124,   106,   115,
  115,   127,   135,
  124,   115,   135,
  118,   133,   138,
  125,   121,   139,
  129,   131,   134,
  130,   131,   129,
  119,   118,   138,
  121,   123,   139,
  124,   136,   133,
  130,   119,   140,
  140,   119,   138,
  127,   125,   132,
  123,   134,   141,
  133,   136,   138,
  123,   141,   139,
  132,   125,   139,
  131,   130,   140,
  134,   131,   141,
  136,   124,   135,
  127,   132,   135,
  144,   131,   140,
  141,   131,   144,
  136,   145,   138,
  141,   142,   139,
  135,   132,   137,
  145,   140,   138,
  136,   135,   137,
  142,   132,   139,
  145,   144,   140,
  142,   141,   144,
  136,   137,   145,
  132,   142,   137,
  145,   137,   143,
  142,   144,   143,
  137,   142,   143,
  144,   145,   143
  };

  xconns.assign(lnode_ids, lnode_ids+lnode_id_ct);
}

void
get_coordinates(vector<e3_lite>& xcoords)
{
  const int lcoords_ct = 146;
  const e3_lite lcoords_array[146] =
  {
    e3_lite(1.5,  1.5, 0),
    e3_lite(1.5,  1.1117699999999999, 0.051110000000000003),
    e3_lite(1.1117699999999999,  1.5, 0.051110000000000003),
    e3_lite(1.5,  1.8882300000000001, 0.051110000000000003),
    e3_lite(1.8882300000000001,  1.5, 0.051110000000000003),
    e3_lite(1.06982,  1.0216499999999999, 0.14496000000000001),
    e3_lite(0.75,  1.5, 0.20096),
    e3_lite(1.5,  0.75, 0.20096),
    e3_lite(1.06982,  1.9783500000000001, 0.14496000000000001),
    e3_lite(1.93018,  1.0216499999999999, 0.14496000000000001),
    e3_lite(2.25,  1.5, 0.20096),
    e3_lite(1.93018,  1.9783500000000001, 0.14496000000000001),
    e3_lite(1.5,  2.5606599999999999, 0.43934000000000001),
    e3_lite(1.93415,  2.39764, 0.37939000000000001),
    e3_lite(1.5,  2.25, 0.20096),
    e3_lite(2.3217500000000002,  0.97446999999999995, 0.36046),
    e3_lite(2.5606599999999999,  1.5, 0.43934000000000001),
    e3_lite(2.3217500000000002,  2.0255299999999998, 0.36046),
    e3_lite(2.32158,  2.44868, 0.67842000000000002),
    e3_lite(0.67842000000000002,  2.44868, 0.67842000000000002),
    e3_lite(1.06585,  2.39764, 0.37939000000000001),
    e3_lite(0.67825000000000002,  2.0255299999999998, 0.36046),
    e3_lite(0.67825000000000002,  0.97446999999999995, 0.36046),
    e3_lite(1.08111,  0.29386000000000001, 0.71274999999999999),
    e3_lite(0.67842000000000002,  0.55132000000000003, 0.67842000000000002),
    e3_lite(1.06585,  0.60236000000000001, 0.37939000000000001),
    e3_lite(1.93415,  0.60236000000000001, 0.37939000000000001),
    e3_lite(1.08111,  2.70614, 0.71274999999999999),
    e3_lite(0.20096,  1.5, 0.75),
    e3_lite(0.36046,  2.0255299999999998, 0.67825000000000002),
    e3_lite(0.43934000000000001,  1.5, 0.43934000000000001),
    e3_lite(1.91889,  0.29386000000000001, 0.71274999999999999),
    e3_lite(0.36046,  0.97446999999999995, 0.67825000000000002),
    e3_lite(1.5,  0.20096, 0.75),
    e3_lite(1.5,  0.43934000000000001, 0.43934000000000001),
    e3_lite(2.6206,  0.60236000000000001, 1.06585),
    e3_lite(2.32158,  0.55132000000000003, 0.67842000000000002),
    e3_lite(2.6395400000000002,  0.97446999999999995, 0.67825000000000002),
    e3_lite(2.8550399999999998,  1.0216499999999999, 1.06982),
    e3_lite(0.37939000000000001,  0.60236000000000001, 1.06585),
    e3_lite(2.7990400000000002,  1.5, 0.75),
    e3_lite(2.6395400000000002,  2.0255299999999998, 0.67825000000000002),
    e3_lite(2.2872499999999998,  2.70614, 1.08111),
    e3_lite(1.91889,  2.70614, 0.71274999999999999),
    e3_lite(1.5,  2.94889, 1.1117699999999999),
    e3_lite(1.90089,  2.8887299999999998, 1.09911),
    e3_lite(1.5,  2.7990400000000002, 0.75),
    e3_lite(2.5606599999999999,  2.5606599999999999, 1.5),
    e3_lite(2.7990400000000002,  2.25, 1.5),
    e3_lite(2.8550399999999998,  1.9783500000000001, 1.06982),
    e3_lite(2.6206,  2.39764, 1.06585),
    e3_lite(2.7990400000000002,  0.75, 1.5),
    e3_lite(0.37939000000000001,  2.39764, 1.06585),
    e3_lite(0.14496000000000001,  1.9783500000000001, 1.06982),
    e3_lite(0.051110000000000003,  1.5, 1.1117699999999999),
    e3_lite(0.14496000000000001,  1.0216499999999999, 1.06982),
    e3_lite(0.71274999999999999,  0.29386000000000001, 1.08111),
    e3_lite(1.90089,  0.11126999999999999, 1.09911),
    e3_lite(2.2872499999999998,  0.29386000000000001, 1.08111),
    e3_lite(1.09911,  2.8887299999999998, 1.09911),
    e3_lite(0.71274999999999999,  2.70614, 1.08111),
    e3_lite(1.09911,  0.11126999999999999, 1.09911),
    e3_lite(1.8882300000000001,  0.051110000000000003, 1.5),
    e3_lite(1.5,  0.051110000000000003, 1.1117699999999999),
    e3_lite(1.8882300000000001,  2.94889, 1.5),
    e3_lite(0.75,  2.7990400000000002, 1.5),
    e3_lite(2.94889,  1.5, 1.1117699999999999),
    e3_lite(2.94889,  1.8882300000000001, 1.5),
    e3_lite(1.1117699999999999,  2.94889, 1.5),
    e3_lite(3,  1.5, 1.5),
    e3_lite(2.94889,  1.1117699999999999, 1.5),
    e3_lite(2.94889,  1.5, 1.8882300000000001),
    e3_lite(0.75,  0.20096, 1.5),
    e3_lite(1.09911,  0.11126999999999999, 1.90089),
    e3_lite(1.1117699999999999,  0.051110000000000003, 1.5),
    e3_lite(1.5,  0, 1.5),
    e3_lite(0.43934000000000001,  0.43934000000000001, 1.5),
    e3_lite(0.71274999999999999,  0.29386000000000001, 1.91889),
    e3_lite(0.37939000000000001,  0.60236000000000001, 1.93415),
    e3_lite(1.5,  3, 1.5),
    e3_lite(1.5,  2.94889, 1.8882300000000001),
    e3_lite(2.2872499999999998,  2.70614, 1.91889),
    e3_lite(0.20096,  2.25, 1.5),
    e3_lite(2.2872499999999998,  0.29386000000000001, 1.91889),
    e3_lite(2.25,  0.20096, 1.5),
    e3_lite(2.25,  2.7990400000000002, 1.5),
    e3_lite(0.20096,  0.75, 1.5),
    e3_lite(2.5606599999999999,  0.43934000000000001, 1.5),
    e3_lite(0.14496000000000001,  1.0216499999999999, 1.93018),
    e3_lite(0.37939000000000001,  2.39764, 1.93415),
    e3_lite(0.71274999999999999,  2.70614, 1.91889),
    e3_lite(0.43934000000000001,  2.5606599999999999, 1.5),
    e3_lite(0.051110000000000003,  1.8882300000000001, 1.5),
    e3_lite(0,  1.5, 1.5),
    e3_lite(0.051110000000000003,  1.5, 1.8882300000000001),
    e3_lite(0.051110000000000003,  1.1117699999999999, 1.5),
    e3_lite(1.5,  0.051110000000000003, 1.8882300000000001),
    e3_lite(1.90089,  0.11126999999999999, 1.90089),
    e3_lite(1.5,  0.20096, 2.25),
    e3_lite(1.90089,  2.8887299999999998, 1.90089),
    e3_lite(1.09911,  2.8887299999999998, 1.90089),
    e3_lite(1.08111,  2.70614, 2.2872499999999998),
    e3_lite(2.6206,  0.60236000000000001, 1.93415),
    e3_lite(2.32158,  0.55132000000000003, 2.32158),
    e3_lite(0.14496000000000001,  1.9783500000000001, 1.93018),
    e3_lite(0.20096,  1.5, 2.25),
    e3_lite(0.36046,  2.0255299999999998, 2.3217500000000002),
    e3_lite(2.8550399999999998,  1.0216499999999999, 1.93018),
    e3_lite(2.6395400000000002,  0.97446999999999995, 2.3217500000000002),
    e3_lite(2.6395400000000002,  2.0255299999999998, 2.3217500000000002),
    e3_lite(2.7990400000000002,  1.5, 2.25),
    e3_lite(2.8550399999999998,  1.9783500000000001, 1.93018),
    e3_lite(2.6206,  2.39764, 1.93415),
    e3_lite(2.32158,  2.44868, 2.32158),
    e3_lite(1.5,  2.7990400000000002, 2.25),
    e3_lite(0.43934000000000001,  1.5, 2.5606599999999999),
    e3_lite(0.67842000000000002,  2.44868, 2.32158),
    e3_lite(1.91889,  2.70614, 2.2872499999999998),
    e3_lite(1.5,  2.5606599999999999, 2.5606599999999999),
    e3_lite(1.93415,  2.39764, 2.6206),
    e3_lite(1.08111,  0.29386000000000001, 2.2872499999999998),
    e3_lite(1.5,  0.43934000000000001, 2.5606599999999999),
    e3_lite(1.91889,  0.29386000000000001, 2.2872499999999998),
    e3_lite(1.93415,  0.60236000000000001, 2.6206),
    e3_lite(0.67825000000000002,  2.0255299999999998, 2.6395400000000002),
    e3_lite(1.06585,  0.60236000000000001, 2.6206),
    e3_lite(0.67842000000000002,  0.55132000000000003, 2.32158),
    e3_lite(0.67825000000000002,  0.97446999999999995, 2.6395400000000002),
    e3_lite(0.36046,  0.97446999999999995, 2.3217500000000002),
    e3_lite(2.5606599999999999,  1.5, 2.5606599999999999),
    e3_lite(2.3217500000000002,  2.0255299999999998, 2.6395400000000002),
    e3_lite(2.25,  1.5, 2.7990400000000002),
    e3_lite(1.06982,  1.0216499999999999, 2.8550399999999998),
    e3_lite(1.06585,  2.39764, 2.6206),
    e3_lite(2.3217500000000002,  0.97446999999999995, 2.6395400000000002),
    e3_lite(0.75,  1.5, 2.7990400000000002),
    e3_lite(1.06982,  1.9783500000000001, 2.8550399999999998),
    e3_lite(1.1117699999999999,  1.5, 2.94889),
    e3_lite(1.5,  2.25, 2.7990400000000002),
    e3_lite(1.5,  0.75, 2.7990400000000002),
    e3_lite(1.93018,  1.9783500000000001, 2.8550399999999998),
    e3_lite(1.93018,  1.0216499999999999, 2.8550399999999998),
    e3_lite(1.5,  1.1117699999999999, 2.94889),
    e3_lite(1.5,  1.5, 3),
    e3_lite(1.8882300000000001,  1.5, 2.94889),
    e3_lite(1.5,  1.8882300000000001, 2.94889)
  };

  xcoords.assign(lcoords_array, lcoords_array+lcoords_ct);
}

//==============================================================================
//==============================================================================

// Making these paths global so they are all in one place and
// not scattered around.

static const poset_path lrep_path = tetgen_generator::rep_path();

static const string lproto_poset_name =
  unstructured_block::prototypes_poset_name();

static const poset_path ltetra_proto_path =
  tetgen_generator::tetra_proto_path();
                             
static const poset_path ltriangle_proto_path(lproto_poset_name,
                                             "triangle_complex");

static const poset_path lsurface_base_space_path("surface_base_space",
                                                 "surface_triangles_block");

static const poset_path lsurface_coordinates_path("surface_coordinates_space",
                                                  "surface_coordinates");

//==============================================================================

// Create a file for viewing with paraview or other vtk viewer.
// The file created is a "legacy" vtk file as opposed to the newer
// xml based file formats.

// If parameter xis_tetra is true, we assume that tetrahedrons are being
// passed in xconns; otherwise we assume triangles.

void
create_vtk_file(const vector<e3_lite>& xcoords,
                const vector<mesh_generator::pod_type>& xconns,
                const string& xfilename,
                bool xis_tetra = true)
{
  // Preconditions:

  require(xis_tetra ? (xcoords.size() >= 4) : (xcoords.size() >= 3));
  require(xis_tetra ? (xconns.size() >= 4) : (xconns.size() >= 3));
  require(xis_tetra ? (xconns.size()%4 == 0) : (xconns.size()%3 == 0));
  require(!xfilename.empty());

  // Body:

  ofstream lofs(xfilename.c_str());
  if(!lofs.is_open())
  {
    cerr << "Warning: Could not open file " << xfilename << endl;
  }
  else
  {
    //==========================================================================

    lofs << "# vtk DataFile Version 2.0" << endl;
    lofs << "Unstructured Grid Example" << endl;
    lofs << "ASCII" << endl;
    lofs << endl;
    lofs << "DATASET UNSTRUCTURED_GRID" << endl;

    //==========================================================================

    size_type lnum_pts = xcoords.size();

    lofs << "POINTS " << lnum_pts << " double" << endl;

    e3_lite lfiber;
    for(size_type i=0; i<lnum_pts; ++i)
    {
      lfiber = xcoords[i];
      lofs << setw(12) << lfiber[0]
           << setw(12) << lfiber[1]
           << setw(12) << lfiber[2] << endl;
    }

    //==========================================================================

    int lnodes_per_element = xis_tetra ? 4 : 3;
    int lvtk_cell_type =  xis_tetra ? 10 : 5;

    size_type lnum_cells = xconns.size()/lnodes_per_element;

    lofs << "CELLS " << lnum_cells << " "
         << lnum_cells*(lnodes_per_element+1) << endl;

    for(size_type i=0, j=0; i<lnum_cells; ++i)
    {
      lofs << lnodes_per_element;
      for(size_type k = 0; k<lnodes_per_element; ++k)
      {
        lofs << setw(8) << xconns[j++];
      }
      lofs << endl;
    }

    lofs << "CELL_TYPES " << lnum_cells << endl;
    for(size_type i=0; i<lnum_cells; ++i)
    {
      lofs << lvtk_cell_type << endl;
    }

    //==========================================================================

    lofs.close();
  }

  // Postconditions:

  // Exit:

}

// This function is only used for debugging.  It just prints
// the members ot the cells (not d_cells) subposet.

void
print_cells_subposet(const base_space_poset& xbase_space)
{
  // Preconditions:

  require(xbase_space.state_is_read_accessible());

  // Body:

  // Print the "cells" subposet.

  cout << endl;
  cout << "Cells subposet members:" << endl;
  cout << endl;

  base_space_member lmbr;
  const subposet& lcells_sp = xbase_space.cells();
  subposet_member_iterator* litr = lcells_sp.member_iterator();
  while(!litr->is_done())
  {
    lmbr.attach_to_state(&xbase_space, litr->index());
    cout << setw(8) << litr->index().hub_pod()
         << "  :  " << lmbr.name() << endl;
    litr->next();
  }

  cout << endl;

  lmbr.detach_from_state();

  delete litr;

  // Postconditions:

  // Exit:

  return;
}

base_space_poset*
create_base_space(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create a base space.

  const string& lbase_name = lsurface_base_space_path.poset_name();
  const string& lmbr_name  = lsurface_base_space_path.member_name();

  base_space_poset* lbase_space =
    &xns.new_base_space<unstructured_block>(lbase_name, "", "", 3, true);

  lbase_space->get_read_write_access();

  // Create the surface connectivities.

  vector<mesh_generator::pod_type> lconns;
  get_connectivities(lconns);

  //unstructured_block_builder::put_name_mode(true);

  unstructured_block lblock(lbase_space,
                            ltriangle_proto_path,
                            &lconns[0],
                            lconns.size(),
                            true);

  lblock.put_name(lmbr_name, true, false);

  // Give members names.

  tetgen_generator::make_names(*lbase_space, 2, "face");
  tetgen_generator::make_names(*lbase_space, 1, "edge");
  tetgen_generator::make_names(*lbase_space, 0, "vertex");

  lblock.detach_from_state();

  // Postconditions:

  ensure(lbase_space->is_attached());

  // Exit:

  return lbase_space;
}

sec_at1_space*
create_coordinates_section(fiber_bundles_namespace& xns,
                           const poset_path& xbase_path)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create the coordinates section space.

  const string& lspace_name = lsurface_coordinates_path.poset_name();
  const string& lmbr_name   = lsurface_coordinates_path.member_name();

  sec_at1_space* lcoords_space = 
    &(xns.new_section_space<sec_e3>(lspace_name, xbase_path, lrep_path, true));

  lcoords_space->get_read_write_access();

  // Create a coordinates section.

  base_space_member lbase_mbr(&xns, xbase_path);

  sec_e3 lcoords_mbr(lcoords_space, lbase_mbr);

  lcoords_mbr.put_name(lmbr_name, true, false);

  // Add the coordinates to the coordinates section.

  vector<e3_lite> lcoords;
  get_coordinates(lcoords);
 
  index_space_iterator& ldisc_itr =
    lcoords_mbr.schema().discretization_id_space().get_iterator();

  size_type i = 0;
  while(!ldisc_itr.is_done())
  {
    lcoords_mbr.put_fiber(ldisc_itr.pod(), lcoords[i++]);
    ldisc_itr.next();
  }

  lcoords_mbr.schema().discretization_id_space().release_iterator(ldisc_itr);

  lbase_mbr.detach_from_state();
  lcoords_mbr.detach_from_state();

  // Postconditions:

  ensure(lcoords_space->is_attached());

  // Exit:

  return lcoords_space;
}

void
create_surface_in_name_space(fiber_bundles_namespace& xns)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Create a base space.

  base_space_poset* lbase_space = create_base_space(xns);

  // Create the coordinates section space.

  sec_at1_space* lcoords_space =
    create_coordinates_section(xns, lsurface_base_space_path);

#ifdef DIAGNOSTIC_OUTPUT
  print_cells_subposet(*lbase_space);
  cout << *lbase_space << endl;
  cout << *lcoords_space << endl;
#endif

  // Postconditions:

  // Exit:

  return;
}

void
run_tetgen(fiber_bundles_namespace& xns,
           const string& xtetgen_switches,
           const string& xfilename)
{
  // Preconditions:

  require(xns.state_is_read_write_accessible());

  // Body:

  // Instantiate a tetgen mesh generator.

  tetgen_generator lgenerator(xns,
                              lsurface_base_space_path,
                              lsurface_coordinates_path,
                              xtetgen_switches);

  // Invoke the generator's generate function.

  lgenerator.generate();

#ifdef DIAGNOSTIC_OUTPUT

  // Create vtk files for input in ParaView, etc.

  // ParaView does not like files with more than 1 ".".
  // So, it will not read "xyz.t.vtk".  Replace "." with "_".

  string lrootname = xfilename;
  int lpos = lrootname.find(".");
  while(lpos != string::npos) 
  {
      lrootname.replace(lpos, 1, "_" );
      lpos = lrootname.find(".", lpos+1);
  } 

  // First create a file from the original (input) surface triangles.

  create_vtk_file(lgenerator.tri_coordinates(),
                  lgenerator.tri_connectivities(),
                  lrootname + "_in.vtk",
                  false);

  // Create a second file from the tetgen generated tetrahedrons.

  create_vtk_file(lgenerator.tet_coordinates(),
                  lgenerator.tet_connectivities(),
                  lrootname + "_out.vtk",
                  true);
#endif

  // Postconditions:

  // Exit:

  return;
}


} // end namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  const string lfilename = filename_from_cmdline(xargv[0]);

  string ltetgen_switches = "pq1.2YV"; // 'Y' preserves the original boundaries.
                                       // 'V' makes tetgen verbose.
  if(xargc >= 2)
  {
    ltetgen_switches = xargv[1];
  }

  fiber_bundles_namespace lns(lfilename);
  lns.get_read_write_access();

  create_surface_in_name_space(lns);

  run_tetgen(lns, ltetgen_switches, lfilename);

  cout << lns << endl;

  storage_agent sa(lfilename + ".hdf");
  sa.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}
