
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

/// @example basis_transform.t.cc
/// Test driver for class gl3 and transform_basis_by routines.

#include "assert_contract.h"
#include "e3.h"
#include "gl3.h"
#include "st2_e3.h"

using namespace std;
using namespace fiber_bundle;
using namespace fiber_bundle::vd_algebra;

void
print_ehat(const e3_lite& ehatx,
           const e3_lite& ehaty,
           const e3_lite& ehatz)
{
  cout << "ehat basis: " << endl;
  cout << "ehatx: " << ehatx << endl;
  cout << "ehaty: " << ehaty << endl;
  cout << "ehatz: " << ehatz << endl;
  cout << endl;
}

void
print_fhat(const e3_lite& fhatx,
           const e3_lite& fhaty,
           const e3_lite& fhatz)
{
  cout << "fhat basis: " << endl;
  cout << "fhatx: " << fhatx << endl;
  cout << "fhaty: " << fhaty << endl;
  cout << "fhatz: " << fhatz << endl;
  cout << endl;
}

void
test_basis_transforms_lite()
{

  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "test_basis_transforms_lite" << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

  // Make basis vectors.

  // Create the component vectors for the f-hat basis
  // Note that compoents are w.r.t. the f-hat basis.

  e3_lite fhatx(1.0, 0.0, 0.0);
  e3_lite fhaty(0.0, 1.0, 0.0);
  e3_lite fhatz(0.0, 0.0, 1.0);

  print_fhat(fhatx, fhaty, fhatz);

  // Create the component vectors for the e-hat basis
  // Note that compoents are w.r.t. the e-hat basis.

  e3_lite ehatx(1.0, 0.0, 0.0);
  e3_lite ehaty(0.0, 1.0, 0.0);
  e3_lite ehatz(0.0, 0.0, 1.0);

  print_ehat(ehatx, ehaty, ehatz);

  //============================================================================

  // Make transforms.

  // Create a rescale transformation

  gl3_lite rescale;
  rescale.rescale(0.1, 0.2, 0.3);

  cout << "rescale: " << endl << rescale << endl;

  // Invert the rescale

  gl3_lite rescale_inv;
  inverse(rescale, rescale_inv);

  cout << "rescale_inv: " << endl << rescale_inv << endl;

  // Create a z rotation

  gl3_lite rotz;
  rotz.rotate_z(rad(90.0));

  cout << "rotz: " << endl << rotz << endl;

  // Invert the z rotation

  gl3_lite rotz_inv;
  inverse(rotz, rotz_inv);

  cout << "rotz_inv: " << endl<< rotz_inv << endl;

  // Create an euler rotation

  gl3_lite rote;
  rote.rotate_euler(rad(90.0), rad(90.0), 0.0);

  cout << "rote: " << endl << rote << endl;

  // Invert the euler rotation

  gl3_lite rote_inv;
  inverse(rote, rote_inv);

  cout << "rote_inv: " << endl << rote_inv << endl;

  //============================================================================

  // Rescale the fhat components into the ehat basis.

  transform_basis_by(fhatx, rescale);
  transform_basis_by(fhaty, rescale);
  transform_basis_by(fhatz, rescale);

  print_fhat(fhatx, fhaty, fhatz);

  // Rescale the fhat components back into the fhat basis.

  transform_basis_by(fhatx, rescale_inv);
  transform_basis_by(fhaty, rescale_inv);
  transform_basis_by(fhatz, rescale_inv);

  print_fhat(fhatx, fhaty, fhatz);

  // Rotate the fhat components into the ehat basis.

  transform_basis_by(fhatx, rotz);
  transform_basis_by(fhaty, rotz);
  transform_basis_by(fhatz, rotz);

  print_fhat(fhatx, fhaty, fhatz);

  // Rotate the fhat components back into the fhat basis.

  transform_basis_by(fhatx, rotz_inv);
  transform_basis_by(fhaty, rotz_inv);
  transform_basis_by(fhatz, rotz_inv);

  print_fhat(fhatx, fhaty, fhatz);

  //============================================================================

  // Create a stress tensor.

  st2_e3_lite stress(1, 2, 3, 4, 5, 6);

  cout << "stress: " << stress << endl;

  // Rescale the stress components into the ehat basis.

  transform_basis_by(stress, rescale, true);

  cout << "rescaled stress: " << stress << endl;

  // Rescale the stress components back into the fhat basis.

  transform_basis_by(stress, rescale_inv, true);

  cout << "re-rescaled stress: " << stress << endl;

  // Rotate the stress components into the ehat basis.

  transform_basis_by(stress, rotz, true);

  cout << "rotated stress: " << stress << endl;

  // Rotate the stress components back into the fhat basis.

  transform_basis_by(stress, rotz_inv, true);

  cout << "re-rotated stress: " << stress << endl;

  // Rotate the stress components into the ehat basis.

  transform_basis_by(stress, rote, true);

  cout << "rotated stress: " << stress << endl;

  // Rotate the stress components back into the fhat basis.

  transform_basis_by(stress, rote_inv, true);

  cout << "re-rotated stress: " << stress << endl;

  cout << endl;
  
}

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  test_basis_transforms_lite();

  // Postconditions:

  // Exit:

  return 0;
}
