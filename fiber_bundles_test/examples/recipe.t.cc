
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example examples/recipe.t.cc

#include "arg_list.h"
#include "assert_contract.h"
#include "fiber_bundles_namespace.h"
#include "schema_descriptor.h"
#include "storage_agent.h"
#include "tern.h"
#include "tuple.h"
#include "tuple_space.h"
#include "wsv_block.h"

using namespace fiber_bundle;

int
main(int argc, char* argv[])
{
  /*************************************************************************
     Recipe that we're making:
     
     GRILLED TUNA WITH SPICY TOMATILLO SAUCE AND AVOCADO SALSA

     For the Sauce:
     2 onions, cut in half
     ½ pound tomatillos, halved
     4 cloves of garlic
     3 tablespoons vegetable oil
     1 dried red chile
     juice of 1 lime
     salt
     freshly ground pepper

     For the avocado salsa:
     1 ½ cups of fresh shucked corn kernels, blanched (or 1 can of corn)
     1 ½ cups of rehydrated black beans or 1 can rinsed black beans
     1 large Haas avocado, diced
     ½ teaspoon cumin
     ½ tablespoon balsamic vinegar
     1 tablespoon chopped cilantro
     1 roasted red pepper, diced
     1 jalapeno, small diced
     ½ tablespoon minced garlic
     juice of 1 lime
     salt 
     freshly ground pepper

     For tuna:
     4 8-ounce bluefin or yellowfin tuna filets
     olive oil
     salt 
     freshly ground pepper
     cilantro sprigs


     For the sauce:
     Preheat the oven to 400 degrees F.
     Place the onions, tomatillos and garlic on a sheet pan and roast 
     for 30 minutes, stirring occasionally. In a sauté pan, over high 
     heat, add the oil. When the oil is hot, add the seeded red chile. 
     Cook in the oil 15 seconds per side or until toasted. When the 
     onions, tomatillos and garlic are softened, add to a blender with 
     the toasted chile and the lime juice. Blend until smooth. Season 
     with salt and pepper.

     For the salsa:
     To a bowl add the corn, black beans, diced avocado, cumin, balsamic 
     vinegar, cilantro, roasted red pepper, jalapeno, garlic and lime
     juice. Season with salt and pepper. Gently mix well. Refrigerate until
     chilled.

     For the tuna:
     Rub the tuna with olive oil. Season with salt and pepper. Grill over
     medium high heat to desired doneness. I prefer medium rare, which is
     about 4 to 5 minutes per side. To serve, place sauce on plate, put a
     small spoonful of the salsa on the plate. Place the tuna on top. Put
     another small spoonful of the salsa on top of the tuna. Garnish with
     fresh cilantro sprigs.
  *************************************************************************/

  // Create namespace and tuple.
  fiber_bundles_namespace test_namespace("recipe.t");
  test_namespace.get_read_write_access();
  tuple test_tuple;

  string lmember_names = "Work DOUBLE false Who C_STRING false Cost DOUBLE false Details C_STRING false";

  schema_poset_member lschema(test_namespace,
			      "Tasks",
			      tuple_space::standard_schema_path(),
			      lmember_names,
			      true,
			      true);

  poset_path lschema_path = lschema.path();

  lschema.detach_from_state();

  arg_list largs = tuple_space::make_arg_list(4);
  
  /// @todo Remove.
//   tuple_space* tasks =
//     new tuple_space(test_namespace, "Recipe", largs, lschema_path, true);

  tuple_space& tasks =
    test_namespace.new_fiber_space<tuple>("Recipe", largs, lschema_path, true);

  // Declare the task_dof struct

  struct tasks_dof
  {
    double work;
    const char *who;
    double cost;
    const char *details;
  };

  tasks_dof dof;

  // Create sub tasks and cover links
  tasks.get_read_write_access();

  // Ingredients
  total_poset_member i1(&tasks);
  i1.put_name("Assemble Sauce Ingredients", true, false);
  dof.work = 10.0;
  dof.who = "Purchaser";
  dof.cost = 1.0;
  dof.details = "2 onions (cut in half), 1/2 pound tomatillos (halved), 4 cloves of garlic, 3 tablespoons vegetable oil, 1 dried red chile, juice of 1 lime, salt, freshly ground pepper";
  i1.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member i2(&tasks);
  i2.put_name("Assemble Salsa Ingredients", true, false);
  dof.work = 15.0;
  dof.who = "Purchaser";
  dof.cost = 1.5;
  dof.details = "1 1/2 cups of fresh shucked corn kernels (blanched) or 1 can of corn, 1 1/2 cups of rehydrated black beans or 1 can rinsed black beans, 1 large Haas avocado, diced, 1/2 teaspoon cumin, 1/2 tablespoon balsamic vinegar, 1 tablespoon chopped cilantro, 1 roasted red pepper (diced), 1 jalapeno (small diced), 1/2 tablespoon minced garlic, juice of 1 lime, salt, freshly ground pepper";
  i2.put_dof_tuple(&dof,sizeof(dof));


  total_poset_member i3(&tasks);
  i3.put_name("Assemble Tuna Ingredients", true, false);
  dof.work = 5.0;
  dof.who = "Purchaser";
  dof.cost = 0.5;
  dof.details = "4 8-ounce bluefin or yellowfin tuna filets, olive oil, salt, freshly ground pepper, cilantro sprigs";
  i3.put_dof_tuple(&dof,sizeof(dof));

  // For the sauce:
  total_poset_member s1(&tasks);
  s1.put_name("Roast Onions, Tomatillos and Garlic", true, false);
  dof.work = 5.0;
  dof.who = "Saucier";
  dof.cost = 0.50;
  dof.details = "Place the onions, tomatillos and garlic on a sheet pan and roast for 30 minutes, stirring occasionally.";
  s1.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member s2(&tasks);
  s2.put_name("Heat Oil", true, false);
  dof.work = 1.0;
  dof.who = "Saucier";
  dof.cost = 0.10;
  dof.details = "In a sauté pan, over high heat, add the oil.";
  s2.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member s3(&tasks);
  s3.put_name("Add Chile", true, false);
  dof.work = 4.0;
  dof.who = "Saucier";
  dof.cost = 0.40;
  dof.details = "When the oil is hot, add the seeded red chile.";
  s3.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member s4(&tasks);
  s4.put_name("Cook Until Toasted", true, false);
  dof.work = 1.5;
  dof.who = "Saucier";
  dof.cost = 0.15;
  dof.details = "Cook in the oil 15 seconds per side or until toasted.";
  s4.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member s5(&tasks);
  s5.put_name("Combine Sauce Ingredients", true, false);
  dof.work = 0.5;
  dof.who = "Saucier";
  dof.cost = 0.05;
  dof.details = "When the onions, tomatillos and garlic are softened, add to a blender with the toasted chile and the lime juice.";
  s5.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member s6(&tasks);
  s6.put_name("Blend Sauce", true, false);
  dof.work = 2.0;
  dof.who = "Saucier";
  dof.cost = 0.2;
  dof.details = "Blend until smooth.";
  s6.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member s7(&tasks);
  s7.put_name("Season Sauce", true, false);
  dof.work = 0.2;
  dof.who = "Saucier";
  dof.cost = 0.02;
  dof.details = "Season with salt and pepper.";
  s7.put_dof_tuple(&dof,sizeof(dof));

  tasks.begin_jim_edit_mode();
  s7.create_cover_link(&s6);
  s6.create_cover_link(&s5);
  s5.create_cover_link(&s4);
  s5.create_cover_link(&s1);
  s4.create_cover_link(&s3);
  s3.create_cover_link(&s2);
  s2.create_cover_link(&i1);
  s1.create_cover_link(&i1);
  tasks.end_jim_edit_mode();

  // for salsa
  total_poset_member a1(&tasks);
  a1.put_name("Combine Salsa Ingredients", true, false);
  dof.work = 2.0;
  dof.who = "Assistant Chef";
  dof.cost = 0.20;
  dof.details = "To a bowl add the corn, black beans, diced avocado, cumin, balsamic vinegar, cilantro, roasted red pepper, jalapeno, garlic and lime juice.";
  a1.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member a2(&tasks);
  a2.put_name("Season Salsa", true, false);
  dof.work = 0.5;
  dof.who = "Assistant Chef";
  dof.cost = 0.05;
  dof.details = "Season with salt and pepper.";
  a2.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member a3(&tasks);
  a3.put_name("Mix Salsa", true, false);
  dof.work = 1.0;
  dof.who = "Assistant Chef";
  dof.cost = 0.10;
  dof.details = "Gently mix well.";
  a3.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member a4(&tasks);
  a4.put_name("Refrigerate Salsa", true, false);
  dof.work = 1.0;
  dof.who = "Assistant Chef";
  dof.cost = 0.10;
  dof.details = "Refrigerate until chilled.";
  a4.put_dof_tuple(&dof,sizeof(dof));

  tasks.begin_jim_edit_mode();
  a4.create_cover_link(&a3);
  a3.create_cover_link(&a2);
  a2.create_cover_link(&a1);
  a1.create_cover_link(&i2);
  tasks.end_jim_edit_mode();

  // tuna
  total_poset_member t1(&tasks);
  t1.put_name("Rub In Oil", true, false);
  dof.work = 1.0;
  dof.who = "Head Chef";
  dof.cost = 0.10;
  dof.details = "Rub the tuna with olive oil.";
  t1.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member t2(&tasks);
  t2.put_name("Season Tuna", true, false);
  dof.work = 1.0;
  dof.who = "Head Chef";
  dof.cost = 0.10;
  dof.details = "Season with salt and pepper.";
  t2.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member t3(&tasks);
  t3.put_name("Grill Tuna", true, false);
  dof.work = 1.0;
  dof.who = "Head Chef";
  dof.cost = 0.10;
  dof.details = "Grill over medium high heat to desired doneness. I prefer medium rare, which is about 4 to 5 minutes per side.";
  t3.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member t4(&tasks);
  t4.put_name("Add Salsa and Sauce", true, false);
  dof.work = 1.0;
  dof.who = "Head Chef";
  dof.cost = 0.10;
  dof.details = "Place sauce on plate, put a small spoonful of the salsa on the plate.";
  t4.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member t5(&tasks);
  t5.put_name("Place Tuna", true, false);
  dof.work = 1.0;
  dof.who = "Head Chef";
  dof.cost = 0.10;
  dof.details = "Place the tuna on top.";
  t5.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member t6(&tasks);
  t6.put_name("Top With Salsa", true, false);
  dof.work = 1.0;
  dof.who = "Head Chef";
  dof.cost = 0.10;
  dof.details = "Put another small spoonful of the salsa on top of the tuna.";
  t6.put_dof_tuple(&dof,sizeof(dof));

  total_poset_member t7(&tasks);
  t7.put_name("Garnish Tuna", true, false);
  dof.work = 1.0;
  dof.who = "Head Chef";
  dof.cost = 0.10;
  dof.details = "Garnish with fresh cilantro sprigs.";
  t7.put_dof_tuple(&dof,sizeof(dof));

  tasks.begin_jim_edit_mode();
  t7.create_cover_link(&t6);
  t6.create_cover_link(&t5);
  t5.create_cover_link(&t4);
  t4.create_cover_link(&s7);
  t4.create_cover_link(&a4);
  t4.create_cover_link(&t3);
  t3.create_cover_link(&t2);
  t2.create_cover_link(&t1);
  t1.create_cover_link(&i3);
  tasks.end_jim_edit_mode();

  // create and link jrms

  scoped_index s_idx[7];
  s_idx[0] = s1.index();
  s_idx[1] = s2.index();
  s_idx[2] = s3.index();
  s_idx[3] = s4.index();
  s_idx[4] = s5.index();
  s_idx[5] = s6.index();
  s_idx[6] = s7.index();
  total_poset_member s(&tasks, s_idx, 7, tern::NEITHER, false);
  s.put_name("Create Sauce", true, false);

  scoped_index a_idx[4];
  a_idx[0] = a1.index();
  a_idx[1] = a2.index();
  a_idx[2] = a3.index();
  a_idx[3] = a4.index();
  total_poset_member a(&tasks, a_idx, 4, tern::NEITHER, false);
  a.put_name("Create Salsa", true, false);

  scoped_index t_idx[3];
  t_idx[0] = t1.index();
  t_idx[1] = t2.index();
  t_idx[2] = t3.index();
  total_poset_member t(&tasks, t_idx, 3, tern::NEITHER, false);
  t.put_name("Cook Tuna", true, false);

  scoped_index r_idx[7];
  r_idx[0] = s.index();
  r_idx[1] = a.index();
  r_idx[2] = t.index();
  r_idx[3] = t4.index();
  r_idx[4] = t5.index();
  r_idx[5] = t6.index();
  r_idx[6] = t7.index();
  total_poset_member r(&tasks, r_idx, 7, tern::NEITHER, false);
  r.put_name("GRILLED TUNA WITH SPICY TOMATILLO SAUCE AND AVOCADO SALSA", true, false);

  // Write out sheaf file.

  storage_agent sa("recipe.t.hdf");

  sa.write_entire(test_namespace);

  // Release access and detach.

  i1.detach_from_state();
  i2.detach_from_state();
  i3.detach_from_state();
  s.detach_from_state();
  s1.detach_from_state();
  s2.detach_from_state();
  s3.detach_from_state();
  s4.detach_from_state();
  s5.detach_from_state();
  s6.detach_from_state();
  s7.detach_from_state();
  a.detach_from_state();
  a1.detach_from_state();
  a2.detach_from_state();
  a3.detach_from_state();
  a4.detach_from_state();
  t.detach_from_state();
  t1.detach_from_state();
  t2.detach_from_state();
  t3.detach_from_state();
  t4.detach_from_state();
  t5.detach_from_state();
  t6.detach_from_state();
  t7.detach_from_state();
  r.detach_from_state();

  tasks.release_access();

  return 0;
}
