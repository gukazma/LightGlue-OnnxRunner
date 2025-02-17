
# libs should be static
set(BUILD_SHARED_LIBS OFF)

# use PIC code for link into shared lib
if(UNIX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif(UNIX)

if(NOT USE_SSE2)
  add_definitions(-DVL_DISABLE_SSE2)
endif()

add_definitions(-DVL_DISABLE_THREADS)

include_directories(./vl)
set(FEATS
  vl/generic.c
  vl/imopv_sse2.c
  vl/sift.c
  vl/imopv.c
  vl/mathop_sse2.c
  vl/sift.c
  vl/host.c
  vl/mathop.c
  vl/random.c)
set_source_files_properties(${FEATS} PROPERTIES LANGUAGE C)
add_library(vlsift ${FEATS})
set_property(TARGET vlsift PROPERTY FOLDER OpenMVG/nonFree)

target_include_directories(vlsift PUBLIC 
  ${CMAKE_SOURCE_DIR}/Modules

)