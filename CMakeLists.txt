PROJECT ( Xenia C CXX )
CMAKE_MINIMUM_REQUIRED ( VERSION 3.1 )
CMAKE_POLICY ( SET CMP0037 OLD )

SET ( CMAKE_CXX_STANDARD 14 )

FIND_PACKAGE(PkgConfig REQUIRED)

SET ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx -msse4.1" CACHE STRING "" )
SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -msse4.1" CACHE STRING "" )

# Build options
if(NOT DEFINED CMAKE_BUILD_TYPE)
#    set ( CMAKE_BUILD_TYPE Debug CACHE STRING )
endif()

# GTK3 inclusion
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0 gtk+-x11-3.0)
INCLUDE_DIRECTORIES ( ${GTK3_INCLUDE_DIRS} )
LINK_DIRECTORIES ( ${GTK3_LIBRARY_DIRS} )
ADD_DEFINITIONS( ${GTK3_CFLAGS_OTHER} )

# Dependencies

add_subdirectory ( third_party )

add_library ( xenia-apu STATIC
    src/xenia/apu/apu_flags.cc
    src/xenia/apu/audio_driver.cc
    src/xenia/apu/audio_system.cc
#    src/xenia/apu/xaudio2/xaudio2_apu_flags.cc
#    src/xenia/apu/xaudio2/xaudio2_audio_driver.cc
#    src/xenia/apu/xaudio2/xaudio2_audio_system.cc
    src/xenia/apu/xma_context.cc
    src/xenia/apu/xma_decoder.cc
    )

add_library ( xenia-apu-nop STATIC
    src/xenia/apu/nop/nop_apu_flags.cc
    src/xenia/apu/nop/nop_audio_system.cc
    )

add_library ( xenia-base STATIC
    src/xenia/base/arena.cc
    src/xenia/base/bit_map.cc
    src/xenia/base/bit_stream.cc
    src/xenia/base/byte_stream.cc
    src/xenia/base/clock.cc
    src/xenia/base/clock_posix.cc
#    src/xenia/base/clock_win.cc
#    src/xenia/base/debugging_mac.cc
    src/xenia/base/debugging_posix.cc
#    src/xenia/base/debugging_win.cc
    src/xenia/base/exception_handler_linux.cc
#    src/xenia/base/exception_handler_posix.cc
#    src/xenia/base/exception_handler_win.cc
    src/xenia/base/filesystem.cc
    src/xenia/base/filesystem_posix.cc
    src/xenia/base/filesystem_wildcard.cc
#    src/xenia/base/filesystem_win.cc
    src/xenia/base/logging.cc
    src/xenia/base/main_posix.cc
#    src/xenia/base/main_win.cc
    src/xenia/base/mapped_memory_posix.cc
#    src/xenia/base/mapped_memory_win.cc
    src/xenia/base/math.cc
    src/xenia/base/memory.cc
    src/xenia/base/memory_posix.cc
#    src/xenia/base/memory_win.cc
    src/xenia/base/mutex.cc
    src/xenia/base/platform_linux.cc
#    src/xenia/base/platform_win.cc
    src/xenia/base/profiling.cc
    src/xenia/base/ring_buffer.cc
#    src/xenia/base/socket_win.cc
    src/xenia/base/string_buffer.cc
    src/xenia/base/string.cc
    src/xenia/base/threading.cc
    src/xenia/base/threading_linux.cc
#    src/xenia/base/threading_mac.cc
    src/xenia/base/threading_posix.cc
#    src/xenia/base/threading_win.cc
    src/xenia/base/x64_context.cc
    )

#    src/xenia/base/testing/memory_test.cc

add_library ( xenia-cpu STATIC

    src/xenia/cpu/breakpoint.cc
    src/xenia/cpu/compiler/compiler.cc
    src/xenia/cpu/compiler/compiler_pass.cc
    src/xenia/cpu/compiler/passes/constant_propagation_pass.cc
    src/xenia/cpu/compiler/passes/context_promotion_pass.cc
    src/xenia/cpu/compiler/passes/control_flow_analysis_pass.cc
    src/xenia/cpu/compiler/passes/control_flow_simplification_pass.cc
    src/xenia/cpu/compiler/passes/data_flow_analysis_pass.cc
    src/xenia/cpu/compiler/passes/dead_code_elimination_pass.cc
    src/xenia/cpu/compiler/passes/finalization_pass.cc
    src/xenia/cpu/compiler/passes/memory_sequence_combination_pass.cc
    src/xenia/cpu/compiler/passes/register_allocation_pass.cc
    src/xenia/cpu/compiler/passes/simplification_pass.cc
    src/xenia/cpu/compiler/passes/validation_pass.cc
    src/xenia/cpu/compiler/passes/value_reduction_pass.cc
    src/xenia/cpu/cpu_flags.cc
    src/xenia/cpu/elf_module.cc
    src/xenia/cpu/entry_table.cc
    src/xenia/cpu/export_resolver.cc
    src/xenia/cpu/function.cc
    src/xenia/cpu/function_debug_info.cc
    src/xenia/cpu/hir/block.cc
    src/xenia/cpu/hir/hir_builder.cc
    src/xenia/cpu/hir/instr.cc
    src/xenia/cpu/hir/opcodes.cc
    src/xenia/cpu/hir/value.cc
    src/xenia/cpu/mmio_handler.cc
    src/xenia/cpu/module.cc

    src/xenia/cpu/processor.cc
    src/xenia/cpu/raw_module.cc
    src/xenia/cpu/stack_walker_posix.cc
#    src/xenia/cpu/stack_walker_win.cc
    src/xenia/cpu/test_module.cc
    src/xenia/cpu/thread.cc
    src/xenia/cpu/thread_state.cc
    src/xenia/cpu/xex_module.cc
    )

add_library ( xenia-cpu-ppc STATIC
    src/xenia/cpu/ppc/ppc_context.cc
    src/xenia/cpu/ppc/ppc_emit_altivec.cc
    src/xenia/cpu/ppc/ppc_emit_alu.cc
    src/xenia/cpu/ppc/ppc_emit_control.cc
    src/xenia/cpu/ppc/ppc_emit_fpu.cc
    src/xenia/cpu/ppc/ppc_emit_memory.cc
    src/xenia/cpu/ppc/ppc_frontend.cc
    src/xenia/cpu/ppc/ppc_hir_builder.cc
    src/xenia/cpu/ppc/ppc_opcode_disasm.cc
    src/xenia/cpu/ppc/ppc_opcode_info.cc
    src/xenia/cpu/ppc/ppc_opcode_lookup.cc
    src/xenia/cpu/ppc/ppc_opcode_table.cc
    src/xenia/cpu/ppc/ppc_scanner.cc
    src/xenia/cpu/ppc/ppc_translator.cc
    )

add_library ( xenia-cpu-backend STATIC
    src/xenia/cpu/backend/assembler.cc
    src/xenia/cpu/backend/backend.cc
    )

add_library ( xenia-cpu-backend-x64 STATIC
    src/xenia/cpu/backend/x64/x64_assembler.cc
    src/xenia/cpu/backend/x64/x64_backend.cc
    src/xenia/cpu/backend/x64/x64_code_cache.cc
    src/xenia/cpu/backend/x64/x64_code_cache_posix.cc
#    src/xenia/cpu/backend/x64/x64_code_cache_win.cc
    src/xenia/cpu/backend/x64/x64_emitter.cc
    src/xenia/cpu/backend/x64/x64_function.cc
    src/xenia/cpu/backend/x64/x64_sequences.cc
    src/xenia/cpu/backend/x64/x64_tracers.cc
    )

#    src/xenia/cpu/ppc/testing/ppc_testing_main.cc
#    src/xenia/cpu/ppc/testing/ppc_testing_native_main.cc

add_library ( xenia-debug STATIC
    src/xenia/debug/ui/debug_window.cc
    )

add_library ( xenia-gpu STATIC
    src/xenia/gpu/command_processor.cc
    src/xenia/gpu/glsl_shader_translator.cc
    src/xenia/gpu/gpu_flags.cc
    src/xenia/gpu/graphics_system.cc
    src/xenia/gpu/null/null_command_processor.cc
    src/xenia/gpu/null/null_graphics_system.cc
    src/xenia/gpu/packet_disassembler.cc
    src/xenia/gpu/register_file.cc
    src/xenia/gpu/sampler_info.cc
    src/xenia/gpu/shader.cc
    src/xenia/gpu/shader_translator.cc
    src/xenia/gpu/shader_translator_disasm.cc
    src/xenia/gpu/spirv/compiler.cc
    src/xenia/gpu/spirv_shader_translator.cc
    src/xenia/gpu/texture_conversion.cc
    src/xenia/gpu/texture_dump.cc
    src/xenia/gpu/texture_extent.cc
    src/xenia/gpu/texture_info.cc
    src/xenia/gpu/texture_info_formats.cc
    src/xenia/gpu/trace_player.cc
    src/xenia/gpu/trace_reader.cc
    src/xenia/gpu/trace_writer.cc
    )
#    src/xenia/gpu/spirv/passes/control_flow_simplification_pass.cc

#    src/xenia/gpu/shader_compiler_main.cc
#    src/xenia/gpu/trace_dump.cc
#    src/xenia/gpu/trace_viewer.cc

add_library ( xenia-gpu-vulkan STATIC
    src/xenia/gpu/vulkan/buffer_cache.cc
    src/xenia/gpu/vulkan/pipeline_cache.cc
    src/xenia/gpu/vulkan/render_cache.cc
    src/xenia/gpu/vulkan/texture_cache.cc
    src/xenia/gpu/vulkan/texture_config.cc
    src/xenia/gpu/vulkan/vulkan_command_processor.cc
    src/xenia/gpu/vulkan/vulkan_gpu_flags.cc
    src/xenia/gpu/vulkan/vulkan_graphics_system.cc
    src/xenia/gpu/vulkan/vulkan_shader.cc
    )

#    src/xenia/gpu/vulkan/vulkan_trace_dump_main.cc
#    src/xenia/gpu/vulkan/vulkan_trace_viewer_main.cc

add_library ( xenia-hid STATIC
#    src/xenia/hid/hid_demo.cc
    src/xenia/hid/hid_flags.cc
    src/xenia/hid/input_driver.cc
    src/xenia/hid/input_system.cc
    src/xenia/hid/nop/nop_hid.cc
    src/xenia/hid/nop/nop_input_driver.cc
#    src/xenia/hid/winkey/winkey_hid.cc
#    src/xenia/hid/winkey/winkey_input_driver.cc
#    src/xenia/hid/xinput/xinput_hid.cc
#    src/xenia/hid/xinput/xinput_input_driver.cc
    )

add_library ( xenia-kernel STATIC
    src/xenia/kernel/kernel_module.cc
    src/xenia/kernel/kernel_state.cc
    src/xenia/kernel/notify_listener.cc
    src/xenia/kernel/user_module.cc
    src/xenia/kernel/util/gameinfo_utils.cc
    src/xenia/kernel/util/native_list.cc
    src/xenia/kernel/util/object_table.cc
    src/xenia/kernel/util/shim_utils.cc
    src/xenia/kernel/util/xdbf_utils.cc
    src/xenia/kernel/util/xex2.cc
    src/xenia/kernel/xam/app_manager.cc
    src/xenia/kernel/xam/apps/xgi_app.cc
    src/xenia/kernel/xam/apps/xlivebase_app.cc
    src/xenia/kernel/xam/apps/xmp_app.cc
    src/xenia/kernel/xam/content_manager.cc
    src/xenia/kernel/xam/user_profile.cc
    src/xenia/kernel/xam/xam_avatar.cc
    src/xenia/kernel/xam/xam_content.cc
    src/xenia/kernel/xam/xam_info.cc
    src/xenia/kernel/xam/xam_input.cc
    src/xenia/kernel/xam/xam_module.cc
    src/xenia/kernel/xam/xam_msg.cc
    src/xenia/kernel/xam/xam_net.cc
    src/xenia/kernel/xam/xam_notify.cc
    src/xenia/kernel/xam/xam_nui.cc
    src/xenia/kernel/xam/xam_ui.cc
    src/xenia/kernel/xam/xam_user.cc
    src/xenia/kernel/xam/xam_video.cc
    src/xenia/kernel/xam/xam_voice.cc
    src/xenia/kernel/xbdm/xbdm_misc.cc
    src/xenia/kernel/xbdm/xbdm_module.cc
    src/xenia/kernel/xboxkrnl/cert_monitor.cc
    src/xenia/kernel/xboxkrnl/debug_monitor.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_audio.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_audio_xma.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_crypt.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_debug.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_error.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_hal.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_io.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_memory.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_misc.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_module.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_modules.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_ob.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_rtl.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_strings.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_threading.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_usbcam.cc
    src/xenia/kernel/xboxkrnl/xboxkrnl_video.cc
    src/xenia/kernel/xenumerator.cc
    src/xenia/kernel/xevent.cc
    src/xenia/kernel/xfile.cc
    src/xenia/kernel/xiocompletion.cc
    src/xenia/kernel/xmodule.cc
    src/xenia/kernel/xmutant.cc
    src/xenia/kernel/xobject.cc
    src/xenia/kernel/xsemaphore.cc
    src/xenia/kernel/xsocket.cc
    src/xenia/kernel/xthread.cc
    src/xenia/kernel/xtimer.cc
    )

add_library ( xenia-ui STATIC
    src/xenia/ui/file_picker_gtk.cc
#    src/xenia/ui/file_picker_win.cc
    src/xenia/ui/graphics_context.cc
    src/xenia/ui/imgui_dialog.cc
    src/xenia/ui/imgui_drawer.cc
    src/xenia/ui/loop.cc
    src/xenia/ui/loop_gtk.cc
#    src/xenia/ui/loop_win.cc
    src/xenia/ui/menu_item.cc
    src/xenia/ui/microprofile_drawer.cc
    src/xenia/ui/spirv/spirv_assembler.cc
    src/xenia/ui/spirv/spirv_disassembler.cc
    src/xenia/ui/spirv/spirv_util.cc
    src/xenia/ui/spirv/spirv_validator.cc
    src/xenia/ui/vulkan/blitter.cc
    src/xenia/ui/vulkan/circular_buffer.cc
    src/xenia/ui/vulkan/fenced_pools.cc
    src/xenia/ui/vulkan/vulkan.cc
    src/xenia/ui/vulkan/vulkan_context.cc
    src/xenia/ui/vulkan/vulkan_device.cc
    src/xenia/ui/vulkan/vulkan_immediate_drawer.cc
    src/xenia/ui/vulkan/vulkan_instance.cc
    src/xenia/ui/vulkan/vulkan_provider.cc
    src/xenia/ui/vulkan/vulkan_swap_chain.cc
    src/xenia/ui/vulkan/vulkan_util.cc
#    src/xenia/ui/vulkan/vulkan_window_demo.cc
    src/xenia/ui/window.cc
#    src/xenia/ui/window_demo.cc
    src/xenia/ui/window_gtk.cc
#    src/xenia/ui/window_win.cc
    )

add_library ( xenia-vfs STATIC
    src/xenia/vfs/device.cc
    src/xenia/vfs/devices/disc_image_device.cc
    src/xenia/vfs/devices/disc_image_entry.cc
    src/xenia/vfs/devices/disc_image_file.cc
    src/xenia/vfs/devices/host_path_device.cc
    src/xenia/vfs/devices/host_path_entry.cc
    src/xenia/vfs/devices/host_path_file.cc
    src/xenia/vfs/devices/stfs_container_device.cc
    src/xenia/vfs/devices/stfs_container_entry.cc
    src/xenia/vfs/devices/stfs_container_file.cc
    src/xenia/vfs/entry.cc
    src/xenia/vfs/virtual_file_system.cc
    )

add_executable ( xenia
    src/xenia/app/emulator_window.cc
    src/xenia/app/xenia_main.cc

    src/xenia/emulator.cc
    src/xenia/memory.cc
    )
target_link_libraries ( xenia PUBLIC
    xenia-apu
    xenia-apu-nop
    xenia-base
    xenia-cpu
    xenia-cpu-ppc
    xenia-cpu-backend
    xenia-cpu-backend-x64
    xenia-debug
    xenia-gpu
    xenia-gpu-vulkan
    xenia-hid
    xenia-kernel
    xenia-ui
    xenia-vfs
    )

target_link_libraries ( xenia-apu PRIVATE xenia-base )
target_link_libraries ( xenia-apu-nop PRIVATE xenia-base )
target_link_libraries ( xenia-cpu PRIVATE
    xenia-base
    xenia-cpu-ppc
    xenia-cpu-backend
    xenia-kernel
    )
target_link_libraries ( xenia-cpu-ppc PRIVATE xenia-base )
target_link_libraries ( xenia-cpu-backend PRIVATE
    xenia-base
    xenia-cpu-backend-x64
    )
target_link_libraries ( xenia-cpu-backend-x64 PRIVATE xenia-base )
target_link_libraries ( xenia-debug PRIVATE xenia-base )
target_link_libraries ( xenia-gpu PRIVATE
    xenia-base
    xenia-ui
    )
target_link_libraries ( xenia-gpu-vulkan PRIVATE
    xenia-base
    xenia-gpu
    )
target_link_libraries ( xenia-hid PRIVATE xenia-base )
target_link_libraries ( xenia-kernel PRIVATE
    xenia-base
    xenia-cpu
    )
target_link_libraries ( xenia-ui PRIVATE xenia-base )
target_link_libraries ( xenia-vfs PRIVATE xenia-base )

#    src/xenia/tools/api-scanner/api_scanner_loader.cc
#    src/xenia/tools/api-scanner/api_scanner_main.cc

target_include_directories ( xenia-base PUBLIC
    .
    src
    third_party
    third_party/llvm/include
    third_party/yaml-cpp/include
    )
target_link_libraries ( xenia-base PUBLIC
    capstone
    gflags
    glslang-spirv
    imgui
    libav
    snappy
    spirv-tools
    volk
    yaml-cpp

    ${GTK3_LIBRARIES}
    pthread
    dl
    lz4
    rt
    X11
    X11-xcb
    )
target_compile_options ( xenia-base PUBLIC
    -fno-operator-names
    )
target_compile_definitions ( xenia-base PUBLIC
    -D_UNICODE
    -DUNICODE

    -DCAPSTONE_X86_ATT_DISABLE
    -DCAPSTONE_DIET_NO
    -DCAPSTONE_X86_REDUCE_NO
    -DCAPSTONE_HAS_X86
    -DCAPSTONE_USE_SYS_DYN_MEM
    -DXBYAK_NO_OP_NAMES
    -DXBYAK_ENABLE_OMITTED_OPERAND
    )

