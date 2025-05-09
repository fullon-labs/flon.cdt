if(CDT_ROOT STREQUAL "" OR NOT CDT_ROOT)
   set(CDT_ROOT "@CDT_ROOT_DIR@")
endif()

if(CDT_TOOLCHAIN_FILE STREQUAL "" OR NOT CDT_TOOLCHAIN_FILE)
   set(CDT_TOOLCHAIN_FILE "${CDT_ROOT}/lib/cmake/@PROJECT_NAME@/CDTWasmToolchain.cmake")
endif()

set(CDT_VERSION "@VERSION_FULL@")

list(APPEND CMAKE_MODULE_PATH ${CDT_ROOT}/lib/cmake/@PROJECT_NAME@)

include(CDTMacros)

function(EXTRACT_MAJOR_MINOR_FROM_VERSION version success major minor)
   string(REGEX REPLACE "^([0-9]+)\\..+$" "\\1" _major "${version}")
   if("${_major}" STREQUAL "${version}")
      set(${success} FALSE PARENT_SCOPE)
      return()
   endif()

   string(REGEX REPLACE "^[0-9]+\\.([0-9]+)(\\..*)?$" "\\1" _minor "${version}")
   if("${_minor}" STREQUAL "${version}")
      set(success FALSE PARENT_SCOPE)
      return()
   endif()

   set(${major}   ${_major} PARENT_SCOPE)
   set(${minor}   ${_minor} PARENT_SCOPE)
   set(${success} TRUE      PARENT_SCOPE)
endfunction(EXTRACT_MAJOR_MINOR_FROM_VERSION)

function(CDT_CHECK_VERSION output version hard_min soft_max hard_max) # optional 6th argument for error message
   set(${output} "INVALID" PARENT_SCOPE)

   EXTRACT_MAJOR_MINOR_FROM_VERSION("${version}" success major minor)
   if(NOT success)
      if(${ARGC} GREATER 5)
         set(${ARGV5} "version '${version}' is invalid" PARENT_SCOPE)
      endif()
      return()
   endif()

   EXTRACT_MAJOR_MINOR_FROM_VERSION("${hard_min}" success hard_min_major hard_min_minor)
   if(NOT success)
      if(${ARGC} GREATER 5)
         set(${ARGV5} "hard minimum version '${hard_min}' is invalid" PARENT_SCOPE)
      endif()
      return()
   endif()

   if( "${major}.${minor}" VERSION_LESS "${hard_min_major}.${hard_min_minor}" )
      set(${output} "MISMATCH" PARENT_SCOPE)
      if(${ARGC} GREATER 5)
         set(${ARGV5} "version '${version}' does not meet hard minimum version requirement of ${hard_min_major}.${hard_min_minor}" PARENT_SCOPE)
      endif()
      return()
   endif()

   if(NOT hard_max STREQUAL "")
      EXTRACT_MAJOR_MINOR_FROM_VERSION("${hard_max}" success hard_max_major hard_max_minor)
      if(NOT success)
         if(${ARGC} GREATER 5)
            set(${ARGV5} "hard maximum version '${hard_max}' is invalid" PARENT_SCOPE)
         endif()
         return()
      endif()

      if( "${major}.${minor}" VERSION_GREATER "${hard_max_major}.${hard_max_minor}" )
         set(${output} "MISMATCH" PARENT_SCOPE)
         if(${ARGC} GREATER 5)
            set(${ARGV5} "version '${version}' does not meet hard maximum version requirement of ${hard_max_major}.${hard_max_minor}" PARENT_SCOPE)
         endif()
         return()
      endif()
   endif()

   EXTRACT_MAJOR_MINOR_FROM_VERSION("${soft_max}" success soft_max_major soft_max_minor)
   if(NOT success)
      set(${output} "MISMATCH" PARENT_SCOPE)
      if(${ARGC} GREATER 5)
         set(${ARGV5} "soft maximum version '${soft_max}' is invalid" PARENT_SCOPE)
      endif()
      return()
   endif()

   if( ${major} GREATER ${soft_max_major} )
      set(${output} "MISMATCH" PARENT_SCOPE)
      if(${ARGC} GREATER 5)
         set(${ARGV5} "version '${version}' must have the same major version as the soft maximum version (${soft_max_major})" PARENT_SCOPE)
      endif()
      return()
   endif()

   if( "${major}.${minor}" VERSION_GREATER "${soft_max_major}.${soft_max_minor}" )
      set(${output} "WARN" PARENT_SCOPE)
      if(${ARGC} GREATER 5)
         set(${ARGV5} "version '${version}' matches requirements but is greater than the soft maximum version of ${soft_max_major}.${soft_max_minor}" PARENT_SCOPE)
      endif()
      return()
   endif()

   set(${output} "MATCH" PARENT_SCOPE)
endfunction(CDT_CHECK_VERSION)
