
#include "svd.h"
#include "std_iostream.h"

using namespace fiber_bundle;

int
main()
{

//     -0.5     -0.25         0
//      0.5     -0.25         0
//      0.5      0.25         0
//     -0.5      0.25         0


// -0.166667    0.333333   0.0
// -0.166667   -0.166667   0.0
//  0.333333   -0.166667   0.0

// 1 2 1
// 2 3 2
// 1 2 1

// 1    2
// 3    4
// 5    6
// 7    8

//   // Example from MATLAB:
//   int nrows = 4; // not constant.
//   int ncols = 2; // constant.
//   double M[8] = {1, 2, 3, 4, 5, 6, 7, 8};
//   double V[4];
//   double W[2];

  // Example from www.nr.com/forum:
  int nrows = 3;
  int ncols = 3;
  double M[9] = { 0.299000,    0.587000,    0.114000,
                 -0.168636,  -0.331068,    0.499704,
                  0.499813,   -0.418531,   -0.081282};
  double V[9];
  double W[3];

//   // Example from OCTAVE:
//   int nrows = 3;
//   int ncols = 4;
//   double M[12] =  {1, 3, -2, 3, 3, 5, 1, 5, -2, 1, 4, 2};
//   double V[16];
//   double W[4];

//   int nrows = 3; // not constant.
//   int ncols = 3; // constant.

//   double M[9] = {1, 2, 1,  2, 3, 2,  1, 2, 1}; // nrows*ncols = 9

//   double W[3]; // ncols = 3
//   double V[9]; // 3*3 = 9

  svd_decompose(M, W, V, nrows, ncols);

  for(int i=0; i<nrows*ncols; ++i)
  {
    cout << "M[" << i << "] = " << M[i] << endl;
  }
  cout << endl;


  // Note: The smallest eigenvalue is W[2]^2 and the
  //       corresponding eigenvector is V[i][3].

  for(int i=0; i<ncols; ++i)
  {
    cout << "W[" << i << "] = " << W[i] << endl;
  }
  cout << endl;

  for(int i=0; i<ncols; ++i)
  {
    cout << "W[" << i << "]^2 = " << W[i]*W[i] << endl;
  }

  cout << endl;
  for(int j=0; j<ncols; ++j)
  {
    for(int i=0; i<ncols; ++i)
    {
      cout << "  " << V[j*ncols+i]; // Transpose.
    }
    cout << endl;
  }
  cout << endl;

  //============================================================================

  int min_index = 0;
  double minW = W[0];

  if(minW > W[1])
  {
    min_index = 1;
    minW = W[1];
  }

  if(minW > W[2])
  {
    min_index = 2;
    minW = W[2];
  }

  cout << "minW^2 = " << minW*minW << endl;

  cout << "V[min_index] = "; 
  for(int j=0; j<3; ++j)
  {
    cout << "  " << V[j*3+min_index];
  }
  cout << endl;

  //============================================================================

  return 0;
}
