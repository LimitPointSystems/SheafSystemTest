#
# $RCSfile: component_definitions.cmake,v $ $Revision: 1.12 $ $Date: 2012/07/05 19:18:15 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#
# This file contains declarations and functions unique to this component.
#

#
# Include functions and definitions common to all components.
# 
include(${CMAKE_MODULE_PATH}/LPSCommon.cmake)

#
# Include cmake test functions and macros
#
include(CTest)

#
# Define the clusters for this component.
#
set(clusters base_spaces dof_iterators dof_maps evaluators fiber_spaces general 
    id_spaces iterators matrices section_spaces examples)

#
# Specify component prerequisite include directories.
#
include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(${SHEAVES_IPATH})   

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Create the library targets for this component.
#
function(add_library_targets)

    if(WIN64INTEL OR WIN64MSVC)

        # Tell the linker where to look for this project's libraries.
        link_directories(${${COMPONENT}_OUTPUT_DIR})
        # Create the DLL.
        add_library(${${COMPONENT}_DYNAMIC_LIB} SHARED ${${COMPONENT}_SRCS})
        add_dependencies(${${COMPONENT}_DYNAMIC_LIB} ${SHEAVES_IMPORT_LIB})

        target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${SHEAVES_IMPORT_LIB} )
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES FOLDER "Component Library Targets")

        # Override cmake's placing of "${${COMPONENT}_DYNAMIC_LIB}_EXPORTS into the preproc symbol table.
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")

    else() # Linux
    
        # Static library
        add_library(${${COMPONENT}_STATIC_LIB} STATIC ${${COMPONENT}_SRCS})
        add_dependencies(${${COMPONENT}_STATIC_LIB} ${SHEAVES_STATIC_LIB})
        set_target_properties(${${COMPONENT}_STATIC_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )

        # Shared library
        add_library(${${COMPONENT}_SHARED_LIB} SHARED ${${COMPONENT}_SRCS})
        add_dependencies(${${COMPONENT}_SHARED_LIB} ${SHEAVES_SHARED_LIB})
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} LINKER_LANGUAGE CXX)

        # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
        # CMake apparently detects the presence of cdecl_dllspec in the source and places
        # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
 
        # Define the library version.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES VERSION ${LIB_VERSION}) 
    
        # Library alias definitions
        add_dependencies(${PROJECT_NAME}-shared-lib ${${COMPONENT}_SHARED_LIB} ${SHEAVES_SHARED_LIB})
        add_dependencies(${PROJECT_NAME}-static-lib ${${COMPONENT}_STATIC_LIB} ${SHEAVES_STATIC_LIB})
    
        target_link_libraries(${${COMPONENT}_SHARED_LIB} ${SHEAVES_SHARED_LIB})
        target_link_libraries(${${COMPONENT}_STATIC_LIB} ${SHEAVES_STATIC_LIB})
    endif()

endfunction(add_library_targets)

#
# Create the bindings targets for this component.
#
function(add_bindings_targets)

    if((LINUX64INTEL OR LINUX64GNU) AND SWIG_FOUND)
    
        link_directories(${JDK_LIB_DIR} ${JVM_LIB_DIR} ${XAWT_LIB_DIR})
        set(SWIG_CXX_EXTENSION "cc")
        set(CMAKE_SWIG_FLAGS -package bindings.java)
    
        # java 
        include_directories(${JDK_INC_DIR} ${JDK_PLATFORM_INC_DIR})
        include_directories(${SHEAVES_JAVA_BINDING_SRC_DIR})
        include_directories(${SHEAVES_COMMON_BINDING_SRC_DIR})
        include_directories(${${COMPONENT}_JAVA_BINDING_SRC_DIR})
        include_directories(${${COMPONENT}_COMMON_BINDING_SRC_DIR})
        set_source_files_properties(${${COMPONENT}_JAVA_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_JAVA_INTERFACE} PROPERTIES CPLUSPLUS ON)

        # Add the java binding library target
        swig_add_module(${${COMPONENT}_JAVA_BINDING_LIB} java ${${COMPONENT}_JAVA_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_JAVA_INTERFACE})
        add_dependencies(${${COMPONENT}_JAVA_BINDING_LIB} ${SHEAVES_JAVA_BINDING_LIB} ${${COMPONENT}_SHARED_LIB})
        set_target_properties(${${COMPONENT}_JAVA_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)
        
        # Define the library version.
        set_target_properties(${${COMPONENT}_JAVA_BINDING_LIB} PROPERTIES VERSION ${LIB_VERSION})
        target_link_libraries(${${COMPONENT}_JAVA_BINDING_LIB} ${JDK_LIB_OPTIONS} ${HDF5_LIBRARIES} ${SHEAVES_JAVA_BINDING_LIB} ${COMPONENT_LIB}) 
        
        # Set the classpath for this component; for downstream use    
        set(${COMPONENT}_CLASSPATH ${SHEAVES_CLASSPATH}:${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_JAVA_BINDING_JAR} CACHE STRING "Cumulative classpath for ${PROJECT_NAME}")
        mark_as_advanced(FORCE ${COMPONENT}_CLASSPATH)
        
         # Create the bindings jar file 
        add_custom_command(TARGET ${${COMPONENT}_JAVA_BINDING_LIB}
                       POST_BUILD
                       COMMAND cmake -E echo "Compiling Java files..."
                       COMMAND ${JAVAC_EXECUTABLE} -classpath .:${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${SHEAVES_JAVA_BINDING_JAR} -d . *.java
                       COMMAND cmake -E echo "Creating jar file..."
                       COMMAND ${JAR_EXECUTABLE} cvf ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_JAVA_BINDING_JAR}  bindings/java/*.class
        )   

        # Java documentation
        add_custom_target(${PROJECT_NAME}-java-docs 
                    COMMAND ${JDK_BIN_DIR}/javadoc -quiet -classpath .:${${COMPONENT}_CLASSPATH} 
                    -d  ${CMAKE_BINARY_DIR}/documentation/java/${PROJECT_NAME}  
                    -sourcepath ${CMAKE_CURRENT_BINARY_DIR} bindings.java *.java
                    DEPENDS ${${COMPONENT}_JAVA_BINDING_LIB})

        # Python 
        set(CMAKE_SWIG_FLAGS -c++ )

        include_directories(${PYTHON_INCLUDE_DIRS})
        include_directories(${SHEAVES_PYTHON_BINDING_SRC_DIR})

        set_source_files_properties(${${COMPONENT}_PYTHON_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_PYTHON_INTERFACE} PROPERTIES CPLUSPLUS ON)
        swig_add_module(${${COMPONENT}_PYTHON_BINDING_LIB} python ${${COMPONENT}_PYTHON_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_PYTHON_INTERFACE})
        add_dependencies(${${COMPONENT}_PYTHON_BINDING_LIB} ${SHEAVES_PYTHON_BINDING_LIB} ${${COMPONENT}_SHARED_LIB})
        set_target_properties(${${COMPONENT}_PYTHON_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)
        # Define the library version.
        set_target_properties(${${COMPONENT}_PYTHON_BINDING_LIB} PROPERTIES VERSION ${LIB_VERSION})  
        target_link_libraries(${${COMPONENT}_PYTHON_BINDING_LIB} ${HDF5_LIBRARIES} ${${COMPONENT}_SHARED_LIB}) 

        # bindings target aliases already declared at system level. Add dependencies here.
        add_dependencies(${PROJECT_NAME}-bindings ${${COMPONENT}_JAVA_BINDING_LIB} ${${COMPONENT}_PYTHON_BINDING_LIB})
        add_dependencies(${PROJECT_NAME}-java-binding ${${COMPONENT}_JAVA_BINDING_LIB})
        add_dependencies(${PROJECT_NAME}-python-binding ${${COMPONENT}_PYTHON_BINDING_LIB})
   
    endif()

endfunction(add_bindings_targets)

# 
# Set the commands for the install target
#
function(add_install_target)

        install(TARGETS ${${COMPONENT}_SHARED_LIB} LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
        install(TARGETS ${${COMPONENT}_STATIC_LIB} ARCHIVE DESTINATION ${CMAKE_BUILD_TYPE}/lib)

        install(TARGETS ${${COMPONENT}_JAVA_BINDING_LIB} LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
        install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_JAVA_BINDING_JAR} DESTINATION ${CMAKE_BUILD_TYPE}/lib)  
        # Only install python binding if the component has a target for it.
        if(TARGET ${${COMPONENT}_PYTHON_BINDING_LIB})
            install(TARGETS ${${COMPONENT}_PYTHON_BINDING_LIB} LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib)
        endif()      

        # Include files are independent of build type. Includes and docs install at top level.
        # See system level CMakeLists.txt for "documentation" install directive.
     
        install(FILES ${${COMPONENT}_INCS} DESTINATION include)
        #install(TARGETS ${${COMPONENT}_CHECK_EXECS} RUNTIME DESTINATION bin)
        
endfunction(add_install_target)
