file(GLOB_RECURSE HEADERS ./include/uuid.h ./gsl/.*)
add_library(stduuid INTERFACE ${HEADER})
target_include_directories(stduuid INTERFACE ./include/)
