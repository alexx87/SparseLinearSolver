
cmake_minimum_required(VERSION 3.13)

SET(PROJECT_NAME "SparseLinearSolver")
project(${PROJECT_NAME} LANGUAGES ${TEST_LANG})

file(GLOB_RECURSE HEADER_FILES Include/*.h)
file(GLOB_RECURSE SRC_FILES Source/*.cpp)

include_directories($ENV{BOOST_PATH})
include_directories(${MKL_INCLUDE})

FIND_PACKAGE( OpenMP )

if(OPENMP_FOUND)
    #message("OPENMP_FOUND")	
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4)
    add_compile_options(/MP)
    add_compile_options(/bigobj)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")	
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic)	    
endif()

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME}  $<LINK_ONLY:MKL::MKL> )	

INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION  ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME})
#
install(FILES ${MKL_ROOT}/redist/intel64/mkl_intel_thread.2.dll
			 ${MKL_ROOT}/redist/intel64/mkl_core.2.dll
			 ${MKL_ROOT}/redist/intel64/mkl_def.2.dll
			 ${MKL_ROOT}/redist/intel64/mkl_vml_def.2.dll
			 ${MKL_ROOT}/redist/intel64/libimalloc.dll
			 ${MKL_ROOT}/../../compiler/2023.0.0/windows/redist/intel64_win/compiler/libiomp5md.dll
            DESTINATION  ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME})