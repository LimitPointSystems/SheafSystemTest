#
# $RCSfile: target_declarations.cmake,v $ $Revision: 1.11 $ $Date: 2012/07/07 18:27:55 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#


#
# Library targets
#

if(LINUX64GNU OR LINUX64INTEL)
     # "shared-libs" builds solely shared libs
    add_custom_target(shared-libs)

    # Because the library dependencies are correct, we only
    # need to list the leaf nodes in the dependency list for shared libs.
    add_dependencies(shared-libs tools-shared-lib solvers-shared-lib)

    # Alias for shared lib; backward naming compatability with gnu system
    add_custom_target(lib)
    add_dependencies(lib shared-libs)
    
    # "static-libs" builds solely static libs
    add_custom_target(static-libs)
    
    # Because the library dependencies are correct, we only
    # need to list the leaf nodes in the dependency list for static libs.
    add_dependencies(static-libs tools-static-lib solvers-static-lib)

    # Add a shared and static library target for each component
    foreach(comp ${COMPONENTS})
        add_custom_target(${comp}-shared-lib)
        add_custom_target(${comp}-static-lib)   
    endforeach()  

    #
    # Bindings targets
    #

    # "make bindings" builds libs and bindings for all components.
    # <component>-bindings builds all prerequisite libs and bindings for <component>

    add_custom_target(bindings)
 
    foreach(comp ${COMPONENTS})
        add_custom_target(${comp}-bindings)
        add_custom_target(${comp}-java-binding)
        add_custom_target(${comp}-python-binding)    
    endforeach()

    # Because the library dependencies are correct, we only
    # need to list the leaf nodes in the dependency list for bindings.
    add_dependencies(bindings tools-bindings solvers-bindings)
    
    # Aggregate java bindings target
    add_custom_target(java-bindings)
    foreach(comp ${COMPONENTS})
        list(APPEND JAVA_BINDING_TARGETS ${comp}-java-binding)
    endforeach()
    add_dependencies(java-bindings ${JAVA_BINDING_TARGETS})

    # Aggregate python bindings target
    add_custom_target(python-bindings)
    foreach(comp ${COMPONENTS})
        list(APPEND PYTHON_BINDING_TARGETS ${comp}-python-binding)
    endforeach()
    add_dependencies(python-bindings ${PYTHON_BINDING_TARGETS})


    #
    # clean targets
    #
    add_custom_target(docclean 
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/documentation)
        
    add_custom_target(realclean 
            COMMAND ${CMAKE_COMMAND} --build  ${CMAKE_BINARY_DIR} --target clean
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/documentation)   

    #
    # Documentation targets
    #
    # doc target is defined in LPSCommon
    add_custom_target(java-docs)
    # $$TODO: this list, and the one for bindings above, should be populated programmatically,
    # NOT by hand. Fix it.
    add_dependencies(java-docs sheaves-java-docs fiber_bundles-java-docs geometry-java-docs
                     fields-java-docs solvers-java-docs tools-java-docs)
                 
    add_custom_target(alldocs DEPENDS doc java-docs)

    #
    # Help targets
    # $$TODO: format output to 80 chars
    add_custom_target(help
        COMMAND ${CMAKE_COMMAND} -E echo "" 
        COMMAND ${CMAKE_COMMAND} -E echo "The following top level help targets are available: "
        COMMAND ${CMAKE_COMMAND} -E echo "    help-targets"
        COMMAND ${CMAKE_COMMAND} -E echo "    help-options"
        COMMAND ${CMAKE_COMMAND} -E echo "")
        
    add_custom_target(help-options
        COMMAND ${CMAKE_COMMAND} -E echo "" 
        COMMAND ${CMAKE_COMMAND} -E echo "NOT IMPLEMENTED "
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "")
        
    add_custom_target(help-targets
        COMMAND ${CMAKE_COMMAND} -E echo "" 
        COMMAND ${CMAKE_COMMAND} -E echo "The fundamental targets are: "
        COMMAND ${CMAKE_COMMAND} -E echo "    all"
        COMMAND ${CMAKE_COMMAND} -E echo "    bin" 
        COMMAND ${CMAKE_COMMAND} -E echo "    bindings"
        COMMAND ${CMAKE_COMMAND} -E echo "    check"
        COMMAND ${CMAKE_COMMAND} -E echo "    coverage"
        COMMAND ${CMAKE_COMMAND} -E echo "    doc"
        COMMAND ${CMAKE_COMMAND} -E echo "    lib"        
        COMMAND ${CMAKE_COMMAND} -E echo "    shared-libs"
        COMMAND ${CMAKE_COMMAND} -E echo "    static-libs"
        COMMAND ${CMAKE_COMMAND} -E echo "    SheafScope"


        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "all [default]:"
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds the entire system -- shared libraries, static libraries, bindings, unit test, examples, and all docs "
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands: none."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "bin:    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds all shared libraries, unit test routines, and examples." 
        COMMAND ${CMAKE_COMMAND} -E echo "    Does not execute any compiled code."
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
        COMMAND ${CMAKE_COMMAND} -E echo "        Bin targets can be invoked per component. All prerequisite libraries "
        COMMAND ${CMAKE_COMMAND} -E echo "        and executables will be constructed in dependency order if needed."
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-bin"
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make sheaves-bin"
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "bindings:    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds the shared libraries, bindings libraries, and associated jar files for all"
        COMMAND ${CMAKE_COMMAND} -E echo "    system components -- also builds the SheafScope"
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: SheafScope."
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
        COMMAND ${CMAKE_COMMAND} -E echo "        Bindings targets can be invoked per component as well as per component-language"
        COMMAND ${CMAKE_COMMAND} -E echo "        All prerequisite libraries will be constructed in dependency order if needed."
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-bindings"
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-java-binding"
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-python-binding"                     
        COMMAND ${CMAKE_COMMAND} -E echo "    "            
        COMMAND ${CMAKE_COMMAND} -E echo "check:    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds all shared libraries and unit test routines, then executes the unit " 
        COMMAND ${CMAKE_COMMAND} -E echo "    tests. Provided make -j1, execution will be in component order. That is -- all"
        COMMAND ${CMAKE_COMMAND} -E echo "    tests for a component will be built and executed in serial order before moving on the next"
        COMMAND ${CMAKE_COMMAND} -E echo "    on to the next component. If make -j greater than 1, behavior may vary."
        COMMAND ${CMAKE_COMMAND} -E echo "    "            
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
        COMMAND ${CMAKE_COMMAND} -E echo "        Check targets can be invoked per component. All prerequisite libraries "
        COMMAND ${CMAKE_COMMAND} -E echo "        will be constructed in dependency order if needed."
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-check"
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make sheaves-check"
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "coverage:    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Only available if C++ compiler is Intel"
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds all shared libraries and unit test routines using '-prof-gen=srcpos' on  " 
        COMMAND ${CMAKE_COMMAND} -E echo "    linux, or '/Qprof-gen:srcpos' on Windows , executes the unit tests, and generates coverage documentation"
        COMMAND ${CMAKE_COMMAND} -E echo "    Provided make -j1, execution will be in component order. That is -- all"
        COMMAND ${CMAKE_COMMAND} -E echo "    tests for a component will be built and executed in serial order before moving"
        COMMAND ${CMAKE_COMMAND} -E echo "    on to the next component. If make -j greater than 1, behavior may vary."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
        COMMAND ${CMAKE_COMMAND} -E echo "        Coverage targets can be invoked per component. All prerequisite libraries "
        COMMAND ${CMAKE_COMMAND} -E echo "        and executables will be constructed in dependency order if needed."
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-coverage"
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make sheaves-coverage"
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "doc:    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Constructs system-scope C++ library documentation, placing the output in CMAKE_BINARY_DIR/documentation"
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"                    
        COMMAND ${CMAKE_COMMAND} -E echo "        java-docs -- Builds the system bindings and constructs java documentation for same."
        COMMAND ${CMAKE_COMMAND} -E echo "                     Does not construct the C++ library docs."
        COMMAND ${CMAKE_COMMAND} -E echo "        alldocs   -- Contructs C++ and java documentation    "
        COMMAND ${CMAKE_COMMAND} -E echo ""              
        COMMAND ${CMAKE_COMMAND} -E echo "shared-libs:"
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds the shared libraries, and only the shared libraries, for all system components."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: lib"
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
        COMMAND ${CMAKE_COMMAND} -E echo "        [comp]-shared-lib will invoke the shared library target for [comp], dealing"
        COMMAND ${CMAKE_COMMAND} -E echo "        with dependencies in order."
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-shared-lib"   
        COMMAND ${CMAKE_COMMAND} -E echo ""        
        COMMAND ${CMAKE_COMMAND} -E echo "static-libs:    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds the static libraries, and only the static libraries, for all system components.     "
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
        COMMAND ${CMAKE_COMMAND} -E echo "        \"<comp>\"-static-lib will invoke the static library target for \"<comp>\", dealing"
        COMMAND ${CMAKE_COMMAND} -E echo "        with dependencies in order."
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-static-lib"   
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "SheafScope:    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds the AheafScope and all dependent shared libraries, bindings libraries, and jar files"
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: bindings."
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
        COMMAND ${CMAKE_COMMAND} -E echo "        Bindings targets can be invoked per component as well as per component-language"
        COMMAND ${CMAKE_COMMAND} -E echo "        All prerequisite libraries will be constructed in dependency order if needed."
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make bindings"
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-bindings"
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-java-binding"
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields-python-binding"                     
        COMMAND ${CMAKE_COMMAND} -E echo "    "    
    )


endif()



