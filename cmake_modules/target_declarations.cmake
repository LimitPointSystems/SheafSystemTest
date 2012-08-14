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
        COMMAND ${CMAKE_COMMAND} -E echo "    check"
        COMMAND ${CMAKE_COMMAND} -E echo "    coverage"
        COMMAND ${CMAKE_COMMAND} -E echo "    doc"


        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "all [default]:"
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds and runs all unit tests. "
        COMMAND ${CMAKE_COMMAND} -E echo "    Provided make -j1, execution will be in component order. That is -- all "
        COMMAND ${CMAKE_COMMAND} -E echo "    tests for a component will be built and executed in serial order before moving "
        COMMAND ${CMAKE_COMMAND} -E echo "    on to the next component. If value of j is greater than 1, behavior may vary."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: check."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands: none."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "bin:"
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds all unit test routines and examples." 
        COMMAND ${CMAKE_COMMAND} -E echo "    Does not execute any compiled code."
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
        COMMAND ${CMAKE_COMMAND} -E echo "        Bin targets can be invoked per component. All prerequisite libraries "
        COMMAND ${CMAKE_COMMAND} -E echo "        and executables will be constructed in dependency order if needed."
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields_test-bin"
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make sheaves_test-bin"
        COMMAND ${CMAKE_COMMAND} -E echo "    "
    
        COMMAND ${CMAKE_COMMAND} -E echo "check:    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds and runs all unit tests. "
        COMMAND ${CMAKE_COMMAND} -E echo "    Provided make -j1, execution will be in component order. That is -- all "
        COMMAND ${CMAKE_COMMAND} -E echo "    tests for a component will be built and executed in serial order before moving "
        COMMAND ${CMAKE_COMMAND} -E echo "    on to the next component. If value of j is greater than 1, behavior may vary."
        COMMAND ${CMAKE_COMMAND} -E echo "    "            
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
        COMMAND ${CMAKE_COMMAND} -E echo "        Check targets can be invoked per component. All prerequisite libraries "
        COMMAND ${CMAKE_COMMAND} -E echo "        will be constructed in dependency order if needed."
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields_test-check"
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make sheaves_test-check"
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "coverage:    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Only available if C++ compiler is Intel"
        COMMAND ${CMAKE_COMMAND} -E echo "    Builds all unit test routines using '-prof-gen=srcpos' on  " 
        COMMAND ${CMAKE_COMMAND} -E echo "    linux, or '/Qprof-gen:srcpos' on Windows , executes the unit tests, and generates coverage documentation"
        COMMAND ${CMAKE_COMMAND} -E echo "    Provided make -j1, execution will be in component order. That is -- all"
        COMMAND ${CMAKE_COMMAND} -E echo "    tests for a component will be built and executed in serial order before moving"
        COMMAND ${CMAKE_COMMAND} -E echo "    on to the next component. If value of j is greater than 1, behavior may vary."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    NOTE: The SheafSystem must be built '-prof-gen=srcpos' on linux. or "
        COMMAND ${CMAKE_COMMAND} -E echo "    '/Qprof-gen:srcpos' on Windows for this target to produce coverage results. "
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Aliases: none."
        COMMAND ${CMAKE_COMMAND} -E echo "    "
        COMMAND ${CMAKE_COMMAND} -E echo "    Related commands:"
        COMMAND ${CMAKE_COMMAND} -E echo "        Coverage targets can be invoked per component. All prerequisite libraries "
        COMMAND ${CMAKE_COMMAND} -E echo "        and executables will be constructed in dependency order if needed."
        COMMAND ${CMAKE_COMMAND} -E echo "    " 
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make fields_test-coverage"
        COMMAND ${CMAKE_COMMAND} -E echo "        example: make sheaves_test-coverage"
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
  
    )


endif()



