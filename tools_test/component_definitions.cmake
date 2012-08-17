#
# $RCSfile: component_definitions.cmake,v $ $Revision: 1.11 $ $Date: 2012/07/05 19:18:17 $
#
#
# Copyright (c) 2012 Limit Point Systems, Inc.
#
#

#
# This file contains declarations and functions unique to this component.
#
set(CMAKE_BACKWARDS_COMPATIBILITY 2.2)
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
set(clusters SheafScope common/client_server common/event common/gui common/util 
    viewer/animation viewer/common viewer/event viewer/render viewer/table 
    viewer/user viewer/application)

#
# Specify component prerequisite include directories.
#
include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(${VTK_INC_DIRS})
include_directories(${JDK_INC_DIR} ${JDK_PLATFORM_INC_DIR})
include_directories(${SHEAVES_IPATH} ${FIBER_BUNDLES_IPATH} ${GEOMETRY_IPATH} ${FIELDS_IPATH})

#------------------------------------------------------------------------------
# FUNCTION DEFINITION SECTION
#------------------------------------------------------------------------------

#
# Establish an aggregate list of files used to build the SHeafScope.
#
function(set_scope_sources)
    # clear the scope srcs var so consecutive cmake runs don't
    # list the same sources n times.
    unset(SHEAFSCOPE_SRCS CACHE)
    foreach(cluster ${clusters})
        file(GLOB scopesrcs ${CMAKE_CURRENT_SOURCE_DIR}/${cluster}/*.java)
        set(SHEAFSCOPE_SRCS ${SHEAFSCOPE_SRCS} ${scopesrcs} CACHE STRING "SheafScope java sources." FORCE)
    endforeach()

endfunction(set_scope_sources)

#
# Create the library targets for this component.
#
function(add_library_targets)

    if(WIN64INTEL OR WIN64MSVC)
    
        # Tell the linker where to look for this project's libraries. 
        link_directories(${${COMPONENT}_OUTPUT_DIR})
    
        # Create the DLL.
        add_library(${${COMPONENT}_DYNAMIC_LIB} SHARED ${${COMPONENT}_SRCS})
        
        target_link_libraries(${${COMPONENT}_DYNAMIC_LIB} ${HDF5_DLL_LIBRARY})
        
        # Override cmake's placing of "${${COMPONENT}_DYNAMIC_LIB}_EXPORTS into the preproc symbol table.
        set_target_properties(${${COMPONENT}_DYNAMIC_LIB} PROPERTIES DEFINE_SYMBOL "SHEAF_DLL_EXPORTS")
    else()
        # Linux
        
        link_directories(${VTK_LIB_DIR})
        link_directories(${JDK_LIB_DIR})
        link_directories(${JVM_LIB_DIR})
        link_directories(${XAWT_LIB_DIR})
 
        # Static library
        add_library(${${COMPONENT}_STATIC_LIB} STATIC ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_STATIC_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
        add_dependencies(${${COMPONENT}_STATIC_LIB} ${FIELDS_STATIC_LIB})
    
        # Shared library
        add_library(${${COMPONENT}_SHARED_LIB} SHARED ${${COMPONENT}_SRCS})
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} LINKER_LANGUAGE CXX)
        add_dependencies(${${COMPONENT}_SHARED_LIB} ${FIELDS_SHARED_LIB})
        
        # Override cmake's placing of "${COMPONENT_LIB}_EXPORTS into the preproc symbol table.
        # CMake apparently detects the presence of cdecl_dllspec in the source and places
        # -D<LIBRARY>_EXPORTS into the preproc symbol table no matter the platform.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES DEFINE_SYMBOL "")
         
        # Define the library version.
        set_target_properties(${${COMPONENT}_SHARED_LIB} PROPERTIES VERSION ${LIB_VERSION}) 
        
        add_dependencies(${PROJECT_NAME}-shared-lib ${${COMPONENT}_SHARED_LIB} ${FIELDS_SHARED_LIB})
        add_dependencies(${PROJECT_NAME}-static-lib ${${COMPONENT}_STATIC_LIB} ${FIELDS_STATIC_LIB})
        # target_link_libraries(${${COMPONENT}_JAVA_BINDING_LIB} ${JDK_LIB_OPTIONS} ${HDF5_LIBRARIES} ${VTK_LIBS} ${FIELDS_JAVA_BINDING_LIB} ${${COMPONENT}_SHARED_LIB} )            
        target_link_libraries(${${COMPONENT}_SHARED_LIB} ${JDK_LIB_OPTIONS} ${VTK_LIBS} ${FIELDS_SHARED_LIB} ${GEOMETRY_SHARED_LIB} ${FIBER_BUNDLES_SHARED_LIB} ${SHEAVES_SHARED_LIB} )
        target_link_libraries(${${COMPONENT}_STATIC_LIB} ${JDK_LIB_OPTIONS} ${VTK_LIBS} ${FIELDS_STATIC_LIB} ${GEOMETRY_STATIC_LIB} ${FIBER_BUNDLES_STATIC_LIB} ${SHEAVES_STATIC_LIB})
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
        include_directories(${FIBER_BUNDLES_JAVA_BINDING_SRC_DIR})
        include_directories(${FIBER_BUNDLES_COMMON_BINDING_SRC_DIR})
        include_directories(${GEOMETRY_JAVA_BINDING_SRC_DIR})
        include_directories(${GEOMETRY_COMMON_BINDING_SRC_DIR})
        include_directories(${FIELDS_JAVA_BINDING_SRC_DIR})
        include_directories(${FIELDS_COMMON_BINDING_SRC_DIR})
        include_directories(${${COMPONENT}_JAVA_BINDING_SRC_DIR})
        include_directories(${${COMPONENT}_COMMON_BINDING_SRC_DIR})
        
        set_source_files_properties(${${COMPONENT}_JAVA_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_JAVA_INTERFACE} PROPERTIES CPLUSPLUS ON)
        # Add the java binding library target
        swig_add_module(${${COMPONENT}_JAVA_BINDING_LIB} java ${${COMPONENT}_JAVA_BINDING_SRC_DIR}/${${COMPONENT}_SWIG_JAVA_INTERFACE})
        add_dependencies(${${COMPONENT}_JAVA_BINDING_LIB} ${FIELDS_JAVA_BINDING_LIB} ${${COMPONENT}_SHARED_LIB})
        set_target_properties(${${COMPONENT}_JAVA_BINDING_LIB} PROPERTIES LINKER_LANGUAGE CXX)
                
        # Define the library version.
        set_target_properties(${${COMPONENT}_JAVA_BINDING_LIB} PROPERTIES VERSION ${LIB_VERSION})
        target_link_libraries(${${COMPONENT}_JAVA_BINDING_LIB} ${JDK_LIB_OPTIONS} ${HDF5_LIBRARIES} ${VTK_LIBS} ${FIELDS_JAVA_BINDING_LIB} ${${COMPONENT}_SHARED_LIB} ) 
        # Set the classpath for this component; for downstream use.    
        set(${COMPONENT}_CLASSPATH ${FIELDS_CLASSPATH}:${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_JAVA_BINDING_JAR}:${VTK_JAR}:${JMF_JAR} 
            CACHE STRING "Cumulative classpath for ${PROJECT_NAME}")
            
        mark_as_advanced(FORCE ${COMPONENT}_CLASSPATH)
        
         # Create the bindings jar file 
        add_custom_command(TARGET ${${COMPONENT}_JAVA_BINDING_LIB} 
                       POST_BUILD
                       COMMAND cmake -E echo "Compiling Java files..."
                       COMMAND ${JAVAC_EXECUTABLE} -classpath .:${${COMPONENT}_CLASSPATH} -d . *.java
                       COMMAND cmake -E echo "Creating jar file..."
                       COMMAND ${JAR_EXECUTABLE} cvf ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${${COMPONENT}_JAVA_BINDING_JAR}  bindings/java/*.class
        ) 
    
        add_custom_target(SheafScope ALL DEPENDS ${${COMPONENT}_JAVA_BINDING_LIB} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/SheafScope.jar)   
     
        # Build the SheafScope jar
        set(LIB_JAR_DIR SheafScope)
        add_custom_command(OUTPUT ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/SheafScope.jar
                       POST_BUILD
                       COMMAND cmake -E make_directory ${LIB_JAR_DIR}
                       COMMAND cmake -E echo "Compiling Java files..."
                       COMMAND ${JAVAC_EXECUTABLE} -classpath .:${${COMPONENT}_CLASSPATH} -g -d ${LIB_JAR_DIR} ${SHEAFSCOPE_SRCS}
    	               COMMAND mkdir -p ${LIB_JAR_DIR}/tools/common/gui/resources
    	               COMMAND mkdir -p ${LIB_JAR_DIR}/tools/viewer/resources/docs
    	               COMMAND mkdir -p ${LIB_JAR_DIR}/tools/SheafScope/resources/docs
    	               COMMAND ln -sf ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/common/gui/resources/*.png    ${LIB_JAR_DIR}/tools/common/gui/resources
    	               COMMAND ln -sf ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/viewer/resources/*.png        ${LIB_JAR_DIR}/tools/viewer/resources
    	               COMMAND ln -sf ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/viewer/resources/docs/*.*     ${LIB_JAR_DIR}/tools/viewer/resources/docs
    	               COMMAND ln -sf ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/SheafScope/resources/*.png    ${LIB_JAR_DIR}/tools/SheafScope/resources
    	               COMMAND ln -sf ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/SheafScope/resources/docs/*.* ${LIB_JAR_DIR}/tools/SheafScope/resources/docs 
                       COMMAND cmake -E echo "Creating jar file..."
                       COMMAND ${JAR_EXECUTABLE} cvMf ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/SheafScope.jar -C ${LIB_JAR_DIR} .
                       DEPENDS ${${COMPONENT}_JAVA_BINDING_LIB}
        )
        
        # Java documentation
        add_custom_target(${PROJECT_NAME}-java-docs 
                    COMMAND ${JDK_BIN_DIR}/javadoc -quiet -classpath .:${${COMPONENT}_CLASSPATH} 
                    -d  ${CMAKE_BINARY_DIR}/documentation/java/${PROJECT_NAME}  
                    -sourcepath ${CMAKE_CURRENT_BINARY_DIR} bindings.java *.java
                    DEPENDS ${${COMPONENT}_JAVA_BINDING_LIB})
            
        # bindings target aliases already declared at system level. Add dependencies here.
        add_dependencies(${PROJECT_NAME}-bindings ${${COMPONENT}_JAVA_BINDING_LIB} SheafScope)
        add_dependencies(${PROJECT_NAME}-java-binding ${${COMPONENT}_JAVA_BINDING_LIB} SheafScope)
 

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
        
        # Install command for the 'Scope
        install(FILES ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/SheafScope.jar DESTINATION ${CMAKE_BUILD_TYPE}/lib)
                     
endfunction(add_install_target)