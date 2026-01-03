# Install script for directory: /home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/sdl3.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3.so.0.2.24"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/libSDL3.so.0.2.24"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/libSDL3.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3.so.0.2.24"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/libSDL3.so")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/libSDL3_test.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3headersTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3headersTargets.cmake"
         "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3headersTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3headersTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3headersTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3headersTargets.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3sharedTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3sharedTargets.cmake"
         "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3sharedTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3sharedTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3sharedTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3sharedTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3sharedTargets-relwithdebinfo.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3testTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3testTargets.cmake"
         "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3testTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3testTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3testTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3testTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3testTargets-relwithdebinfo.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/SDL3Config.cmake"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/SDL3ConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL3" TYPE FILE FILES
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_assert.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_asyncio.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_atomic.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_audio.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_begin_code.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_bits.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_blendmode.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_camera.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_clipboard.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_close_code.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_copying.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_cpuinfo.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_dialog.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_egl.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_endian.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_error.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_events.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_filesystem.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_gamepad.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_gpu.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_guid.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_haptic.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_hidapi.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_hints.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_init.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_intrin.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_iostream.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_joystick.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_keyboard.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_keycode.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_loadso.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_locale.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_log.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_main.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_main_impl.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_messagebox.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_metal.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_misc.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_mouse.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_mutex.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_oldnames.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_opengl.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_opengl_glext.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_opengles.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_opengles2.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_opengles2_gl2.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_opengles2_gl2ext.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_opengles2_gl2platform.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_opengles2_khrplatform.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_pen.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_pixels.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_platform.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_platform_defines.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_power.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_process.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_properties.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_rect.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_render.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_scancode.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_sensor.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_stdinc.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_storage.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_surface.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_system.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_thread.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_time.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_timer.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_touch.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_tray.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_version.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_video.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_vulkan.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/include-revision/SDL3/SDL_revision.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL3" TYPE FILE FILES
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_test.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_test_assert.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_test_common.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_test_compare.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_test_crc32.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_test_font.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_test_fuzzer.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_test_harness.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_test_log.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_test_md5.h"
    "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/include/SDL3/SDL_test_memory.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/SDL3" TYPE FILE FILES "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/LICENSE.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/kyoraku/Desktop/c/tp/sdl/SDL3-3.2.24/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
