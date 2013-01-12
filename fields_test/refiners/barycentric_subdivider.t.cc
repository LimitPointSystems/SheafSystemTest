
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//


/// @example barycentric_subdivider.t.cc
/// The members of a d-simplex can be associated with the
/// lattice 2^(d+1). For a tetrahedron we have:
///
/// Vertices:
///
/// v0 ~ {0} = 0001 = 1
/// v1 ~ {1} = 0010 = 2
/// v2 ~ {2} = 0100 = 4
/// v3 ~ {3} = 1000 = 8
///
/// Edges:
///
/// e0 ~ {2, 3} = 1100 = 12
/// e1 ~ {1, 3} = 1010 = 10
/// e2 ~ {1, 2} = 0110 = 6
/// e3 ~ {0, 3} = 1001 = 9
/// e4 ~ {0, 2} = 0101 = 5
/// e5 ~ {0, 1} = 0011 = 3
///
/// Faces:
///
/// f0 ~ {1, 2, 3} = 1110 = 14
/// f1 ~ {0, 2, 3} = 1101 = 13
/// f2 ~ {0, 1, 3} = 1011 = 11
/// f3 ~ {0, 1, 2} = 0111 = 7
///
/// Tetrathedron
///
/// t0 ~ {0, 1, 2, 3} = 1111
///
/// The tetrahedra in the barycentric subdivision correspond to
/// paths in the cover relation graph of 2^(d+1).

/// @file
/// Generates data for barycentric subdivision of d-simplex.

#include "assert_contract.h"
#include "std_bitset.h"
#include "std_iostream.h"
#include "std_iomanip.h"
#include "std_vector.h"

namespace
{
///
/// Computes the factorial of xi.
///
size_t factorial(size_t xi)
{
  size_t result = 1;
  for(size_t i= 2; i<=xi; ++i)
  {
    result *= i;
  }

  return result;
}

///
/// Traverses every path in the down set of xmbr.
///
template <int D>
void dft(bitset<D>& xmbr,
         unsigned long xconn[][D],
         double xcoords[][D],
         unsigned long& xct)
{
  static const string names[] =
    {
      "null", "vertex", "edge", "triangle", "tetrahedron"
    };

  static unsigned long path[D];

  // Previsit:

  int lct = xmbr.count();
  unsigned long mbr_id = xmbr.to_ulong() - 1;

  path[lct-1] = mbr_id;

  double lctr = lct > 0 ? 1.0/static_cast<double>(lct) : 0.0;
  for(int i=0; i<D; ++i)
  {
    xcoords[mbr_id][i] = xmbr[i] ? lctr : 0.0;
  }

  if(lct == 1)
  {
    // This is a vertex, the end of a path
    // associated with a new zone.
    // Increment the new zone counter.

    for(int i=0; i<D; ++i)
    {
      xconn[xct][i] = path[i];
    }

    ++xct;
  }
  else
  {
    // This is some member above the vertices;
    // visit its lower cover.

    for(int i=0; i<D; ++i)
    {
      if(xmbr[i])
      {
        bitset<D> lesser(xmbr);
        lesser[i] = 0;
        dft<D>(lesser, xconn, xcoords, xct);
      }
    }
  }


  // Postvisit:

  // Exit:

  return;
}


///
/// Sub divide the triangle.
///
void subdivide_triangle()
{
  const int D = 2;
  const int DPLUS1 = D + 1;
  const int NEW_TRI_CT = 6; // 6 = (d+1)!
  const int NEW_VERTEX_CT = 7; // 7 = 2^(d+1) - 1

  unsigned long tri_conn[NEW_TRI_CT][DPLUS1];

  double tri_coords[NEW_VERTEX_CT][DPLUS1];

  bitset<DPLUS1> triangle(string("111"));

  unsigned long tri_ct = 0;
  dft<DPLUS1>(triangle, tri_conn, tri_coords, tri_ct);

  cout << "vertices: " << endl << endl;

  for(int i=0; i<NEW_VERTEX_CT; ++i)
  {
    cout << "v" << i;
    for(int j=0; j<DPLUS1; ++j)
    {
      cout << " " << setw(10) << tri_coords[i][j];
    }
    cout << endl;
  }

  cout << endl << "connectivity: " << endl << endl;
  for(int i=0; i<NEW_TRI_CT; ++i)
  {
    cout << "t" << i;
    for(int j=0; j<DPLUS1; ++j)
    {
      cout << " " << setw(4) << tri_conn[i][j];
    }
    cout << endl;
  }

  return;
}

///
/// Sub divide the tetrahedron.
///
void subdivide_tetrahedron()
{
  const int D = 3;
  const int DPLUS1 = D+1;
  const int NEW_TET_CT = 24; // 24 = (d+1)!
  const int NEW_VERTEX_CT = 15; // 15 = 2^(d+1) - 1

  unsigned long tet_conn[NEW_TET_CT][DPLUS1];

  double tet_coords[NEW_VERTEX_CT][DPLUS1];

  bitset<DPLUS1> tetrahedron(string("1111"));

  unsigned long tet_ct = 0;
  dft<DPLUS1>(tetrahedron, tet_conn, tet_coords, tet_ct);

  cout << "vertices: " << endl << endl;

  for(int i=0; i<NEW_VERTEX_CT; ++i)
  {
    cout << "v" << i;
    for(int j=0; j<DPLUS1; ++j)
    {
      cout << " " << setw(10) << tet_coords[i][j];
    }
    cout << endl;
  }

  cout << endl << "connectivity: " << endl << endl;
  for(int i=0; i<NEW_TET_CT; ++i)
  {
    cout << "t" << i;
    for(int j=0; j<DPLUS1; ++j)
    {
      cout << " " << setw(4) << tet_conn[i][j];
    }
    cout << endl;
  }

  return;
}


}

///
/// Main routine.
///
int main()
{
  subdivide_triangle();

  subdivide_tetrahedron();

  return 0;
}

