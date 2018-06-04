add_subdirectory( spirv-headers )
add_subdirectory( xbyak )
add_subdirectory( yaml-cpp )

add_library ( capstone STATIC )
target_compile_options ( capstone PRIVATE
    -Wno-error=write-strings
    -Wno-write-string
    -Wno-deprecated
    -w
    )
target_compile_definitions ( capstone PRIVATE
    -DCAPSTONE_X86_ATT_DISABLE
    -DCAPSTONE_DIET_NO
    -DCAPSTONE_X86_REDUCE_NO
    -DCAPSTONE_HAS_X86
    -DCAPSTONE_USE_SYS_DYN_MEM
    -D_LIB
    )
target_include_directories ( capstone PUBLIC
    capstone/include
    capstone
    )

set ( GFLAGS_DIR third_party/gflags )
add_library ( gflags STATIC )
target_compile_definitions ( gflags PRIVATE
    -DGFLAGS_DLL_DECL=
    -DGFLAGS_DLL_DEFINE_FLAG=
    -DGFLAGS_DLL_DECLARE_FLAG=
    -D_LIB
    )
target_include_directories ( gflags PUBLIC
    gflags/src
    )

add_library ( glslang-spirv STATIC )
target_compile_definitions ( glslang-spirv PRIVATE
    -D_LIB
    )

add_library ( imgui STATIC )
target_include_directories ( imgui PUBLIC
    imgui
    )
target_compile_definitions ( imgui PRIVATE
    -D_LIB
    )

add_library ( libav STATIC )
target_compile_options ( libav PRIVATE
    -Wno-incompatible-pointer-types-discards-qualifiers
    -Wno-switch
    -Wno-incompatible-pointer-types
    -Wno-logical-op-parentheses
    -Wno-pointer-sign
    -Wno-parentheses
    )
target_compile_definitions ( libav PRIVATE
    -D_USE_MATH_DEFINES
    )
target_include_directories ( libav PUBLIC
    libav
    )

add_library ( snappy STATIC )
target_compile_definitions ( snappy PRIVATE
    -D_LIB
    )

add_library ( spirv-tools STATIC )
target_compile_definitions ( spirv-tools PRIVATE
    -D_LIB
    )
target_include_directories ( spirv-tools PUBLIC
    spirv-headers/include
    spirv-tools/include
    spirv-tools/source
    )

add_library ( volk STATIC
    volk/volk.c
    volk/volk.h
    )
target_compile_definitions ( volk PRIVATE
    -D_LIB
    )
target_include_directories ( volk PUBLIC
    volk
    )
target_compile_definitions ( volk PUBLIC
    VK_USE_PLATFORM_XCB_KHR
    )

add_library ( xxhash STATIC )
target_compile_definitions ( xxhash PRIVATE
    -D_LIB
    )
target_include_directories ( xxhash PUBLIC
    xxhash
    )

#
# Down here you find the lengthy source lists
#
#

target_sources ( capstone PRIVATE
    capstone/cs.c
    capstone/cs_priv.h
    capstone/LEB128.h
    capstone/MathExtras.h
    capstone/MCDisassembler.h
    capstone/MCFixedLenDisassembler.h
    capstone/MCInst.c
    capstone/MCInst.h
    capstone/MCInstrDesc.c
    capstone/MCInstrDesc.h
    capstone/MCRegisterInfo.c
    capstone/MCRegisterInfo.h
    capstone/myinttypes.h
    capstone/SStream.c
    capstone/SStream.h
    capstone/utils.c
    capstone/utils.h

    capstone/arch/X86/X86ATTInstPrinter.c
    capstone/arch/X86/X86BaseInfo.h
    capstone/arch/X86/X86Disassembler.c
    capstone/arch/X86/X86DisassemblerDecoder.c
    capstone/arch/X86/X86DisassemblerDecoderCommon.h
    capstone/arch/X86/X86DisassemblerDecoder.h
    capstone/arch/X86/X86Disassembler.h
    capstone/arch/X86/X86GenAsmWriter1.inc
    capstone/arch/X86/X86GenAsmWriter1_reduce.inc
    capstone/arch/X86/X86GenAsmWriter.inc
    capstone/arch/X86/X86GenAsmWriter_reduce.inc
    capstone/arch/X86/X86GenDisassemblerTables.inc
    capstone/arch/X86/X86GenDisassemblerTables_reduce.inc
    capstone/arch/X86/X86GenInstrInfo.inc
    capstone/arch/X86/X86GenInstrInfo_reduce.inc
    capstone/arch/X86/X86GenRegisterInfo.inc
    capstone/arch/X86/X86InstPrinter.h
    capstone/arch/X86/X86IntelInstPrinter.c
    capstone/arch/X86/X86Mapping.c
    capstone/arch/X86/X86Mapping.h
    capstone/arch/X86/X86Module.c
    )

target_sources ( gflags PRIVATE
    gflags/src/gflags.cc
    gflags/src/gflags_completions.cc
    gflags/src/gflags_reporting.cc
    gflags/src/mutex.h
    gflags/src/util.h
    )

target_sources ( glslang-spirv PRIVATE
    glslang-spirv/bitutils.h
    glslang-spirv/disassemble.cpp
    glslang-spirv/disassemble.h
    glslang-spirv/doc.cpp
    glslang-spirv/doc.h
    glslang-spirv/GLSL.ext.AMD.h
    glslang-spirv/GLSL.ext.EXT.h
    glslang-spirv/GLSL.ext.KHR.h
    glslang-spirv/GLSL.ext.NV.h
    glslang-spirv/GLSL.std.450.h
    glslang-spirv/hex_float.h
    glslang-spirv/InReadableOrder.cpp
    glslang-spirv/Logger.cpp
    glslang-spirv/Logger.h
    glslang-spirv/spirv.hpp
    glslang-spirv/SpvBuilder.cpp
    glslang-spirv/SpvBuilder.h
    glslang-spirv/spvIR.h
    glslang-spirv/SPVRemapper.cpp
    glslang-spirv/SPVRemapper.h
    )

target_sources ( imgui PRIVATE
    imgui/imconfig.h
    imgui/imgui.cpp
    imgui/imgui.h
    imgui/imgui_draw.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_internal.h
    imgui/stb_rect_pack.h
    imgui/stb_textedit.h
    imgui/stb_truetype.h
    )

target_sources ( libav PRIVATE

    libav/libavutil/adler32.c
    libav/libavutil/aes.c
    libav/libavutil/atomic.c
    libav/libavutil/audio_fifo.c
    libav/libavutil/avstring.c
    libav/libavutil/base64.c
    libav/libavutil/blowfish.c
    libav/libavutil/buffer.c
    libav/libavutil/channel_layout.c
    libav/libavutil/cpu.c
    libav/libavutil/crc.c
    libav/libavutil/des.c
    libav/libavutil/dict.c
    libav/libavutil/display.c
    libav/libavutil/downmix_info.c
    libav/libavutil/error.c
    libav/libavutil/eval.c
    libav/libavutil/fifo.c
    libav/libavutil/file.c
    libav/libavutil/file_open.c
    libav/libavutil/float_dsp.c
    libav/libavutil/frame.c
    libav/libavutil/hmac.c
    libav/libavutil/imgutils.c
    libav/libavutil/intmath.c
    libav/libavutil/lfg.c
    libav/libavutil/lls.c
    libav/libavutil/log2_tab.c
    libav/libavutil/log.c
    libav/libavutil/lzo.c
    libav/libavutil/mathematics.c
    libav/libavutil/md5.c
    libav/libavutil/mem.c
    libav/libavutil/opt.c
    libav/libavutil/parseutils.c
    libav/libavutil/pixdesc.c
    libav/libavutil/random_seed.c
    libav/libavutil/rational.c
    libav/libavutil/rc4.c
    libav/libavutil/samplefmt.c
    libav/libavutil/sha.c
    libav/libavutil/stereo3d.c
    libav/libavutil/time.c
    libav/libavutil/tree.c
    libav/libavutil/utils.c
    libav/libavutil/xtea.c

    libav/libavutil/adler32.h
    libav/libavutil/aes.h
    libav/libavutil/atomic_gcc.h
    libav/libavutil/atomic.h
    libav/libavutil/atomic_suncc.h
    libav/libavutil/atomic_win32.h
    libav/libavutil/attributes.h
    libav/libavutil/audioconvert.h
    libav/libavutil/audio_fifo.h
    libav/libavutil/avassert.h
    libav/libavutil/avconfig.h
    libav/libavutil/avstring.h
    libav/libavutil/avutil.h
    libav/libavutil/base64.h
    libav/libavutil/blowfish.h
    libav/libavutil/bswap.h
    libav/libavutil/buffer.h
    libav/libavutil/buffer_internal.h
    libav/libavutil/channel_layout.h
    libav/libavutil/colorspace.h
    libav/libavutil/common.h
    libav/libavutil/cpu.h
    libav/libavutil/cpu_internal.h
    libav/libavutil/crc.h
    libav/libavutil/des.h
    libav/libavutil/dict.h
    libav/libavutil/display.h
    libav/libavutil/downmix_info.h
    libav/libavutil/error.h
    libav/libavutil/eval.h
    libav/libavutil/fifo.h
    libav/libavutil/file.h
    libav/libavutil/float_dsp.h
    libav/libavutil/frame.h
    libav/libavutil/hmac.h
    libav/libavutil/imgutils.h
    libav/libavutil/internal.h
    libav/libavutil/intfloat.h
    libav/libavutil/intmath.h
    libav/libavutil/intreadwrite.h
    libav/libavutil/lfg.h
    libav/libavutil/libm.h
    libav/libavutil/lls.h
    libav/libavutil/log.h
    libav/libavutil/lzo.h
    libav/libavutil/macros.h
    libav/libavutil/mathematics.h
    libav/libavutil/md5.h
    libav/libavutil/mem.h
    libav/libavutil/old_pix_fmts.h
    libav/libavutil/opt.h
    libav/libavutil/parseutils.h
    libav/libavutil/pixdesc.h
    libav/libavutil/pixfmt.h
    libav/libavutil/random_seed.h
    libav/libavutil/rational.h
    libav/libavutil/rc4.h
    libav/libavutil/replaygain.h
    libav/libavutil/samplefmt.h
    libav/libavutil/sha.h
    libav/libavutil/stereo3d.h
    libav/libavutil/thread.h
    libav/libavutil/time.h
    libav/libavutil/time_internal.h
    libav/libavutil/timer.h
    libav/libavutil/tree.h
    libav/libavutil/version.h
    libav/libavutil/wchar_filename.h
    libav/libavutil/xtea.h

    libav/libavutil/x86/cpu.c
    libav/libavutil/x86/float_dsp_init.c
    libav/libavutil/x86/lls_init.c

    libav/libavutil/x86/asm.h
    libav/libavutil/x86/bswap.h
    libav/libavutil/x86/cpu.h
    libav/libavutil/x86/emms.h
    libav/libavutil/x86/intreadwrite.h
    libav/libavutil/x86/timer.h
    libav/libavutil/x86/w64xmmtest.h

    libav/libavcodec/allcodecs.c
#    libav/libavcodec/avfft.c
    libav/libavcodec/avpacket.c
    libav/libavcodec/bitstream.c
    libav/libavcodec/bitstream_filter.c
    libav/libavcodec/codec_desc.c
    libav/libavcodec/fft_float.c
    libav/libavcodec/imgconvert.c
    libav/libavcodec/log2_tab.c
    libav/libavcodec/mathtables.c
    libav/libavcodec/mdct_float.c
    libav/libavcodec/options.c
    libav/libavcodec/parser.c
    libav/libavcodec/pthread.c
    libav/libavcodec/pthread_frame.c
    libav/libavcodec/pthread_slice.c
    libav/libavcodec/qsv_api.c
    libav/libavcodec/sinewin.c
    libav/libavcodec/utils.c
    libav/libavcodec/wma.c
    libav/libavcodec/wma_common.c
    libav/libavcodec/wma_freqs.c
    libav/libavcodec/xma2dec.c

    libav/libavcodec/avcodec.h
    libav/libavcodec/avfft.h
    libav/libavcodec/blockdsp.h
    libav/libavcodec/bytestream.h
    libav/libavcodec/error_resilience.h
    libav/libavcodec/fdctdsp.h
    libav/libavcodec/fft.h
    libav/libavcodec/fft-internal.h
    libav/libavcodec/get_bits.h
    libav/libavcodec/h263dsp.h
    libav/libavcodec/hpeldsp.h
    libav/libavcodec/idctdsp.h
    libav/libavcodec/imgconvert.h
    libav/libavcodec/internal.h
    libav/libavcodec/mathops.h
    libav/libavcodec/me_cmp.h
    libav/libavcodec/options_table.h
    libav/libavcodec/parser.h
    libav/libavcodec/pixblockdsp.h
    libav/libavcodec/pixels.h
    libav/libavcodec/pthread_internal.h
    libav/libavcodec/put_bits.h
    libav/libavcodec/qpeldsp.h
    libav/libavcodec/qsv.h
    libav/libavcodec/qsv_internal.h
    libav/libavcodec/ratecontrol.h
    libav/libavcodec/rdft.h
    libav/libavcodec/rl.h
    libav/libavcodec/sbrdsp.h
    libav/libavcodec/sbr.h
    libav/libavcodec/sinewin.h
    libav/libavcodec/sinewin_tablegen.h
    libav/libavcodec/synth_filter.h
    libav/libavcodec/thread.h
    libav/libavcodec/version.h
    libav/libavcodec/videodsp.h
    libav/libavcodec/wma_common.h
    libav/libavcodec/wmadata.h
    libav/libavcodec/wma_freqs.h
    libav/libavcodec/wma.h
    libav/libavcodec/wmaprodata.h
    libav/libavcodec/xma2dec.h

    libav/libavcodec/x86/fdct.c
    libav/libavcodec/x86/fdctdsp_init.c
    libav/libavcodec/x86/fft_init.c

    libav/libavcodec/x86/audiodsp.h
    libav/libavcodec/x86/cabac.h
    libav/libavcodec/x86/constants.h
    libav/libavcodec/x86/dca.h
    libav/libavcodec/x86/fdct.h
    libav/libavcodec/x86/fft.h
    libav/libavcodec/x86/fpel.h
    libav/libavcodec/x86/h264_i386.h
    libav/libavcodec/x86/hpeldsp.h
    libav/libavcodec/x86/idctdsp.h
    libav/libavcodec/x86/inline_asm.h
    libav/libavcodec/x86/mathops.h
    libav/libavcodec/x86/simple_idct.h
    libav/libavcodec/x86/vc1dsp.h
    libav/libavcodec/x86/vp56_arith.h
    libav/libavcodec/x86/xvididct.h
    )

target_sources ( snappy PRIVATE
    snappy/snappy-internal.h
    snappy/snappy-sinksource.cc
    snappy/snappy-sinksource.h
    snappy/snappy-stubs-internal.cc
    snappy/snappy-stubs-internal.h
    snappy/snappy-stubs-public.h
    snappy/snappy.cc
    snappy/snappy.h
    )

target_sources ( spirv-tools PRIVATE
    spirv-tools/source/val/basic_block.cpp
    spirv-tools/source/val/basic_block.h
    spirv-tools/source/val/construct.cpp
    spirv-tools/source/val/construct.h
    spirv-tools/source/val/decoration.h
    spirv-tools/source/val/function.cpp
    spirv-tools/source/val/function.h
    spirv-tools/source/val/instruction.cpp
    spirv-tools/source/val/instruction.h
    spirv-tools/source/val/validation_state.cpp
    spirv-tools/source/val/validation_state.h

    spirv-tools/source/util/bit_stream.cpp
    spirv-tools/source/util/bit_stream.h
    spirv-tools/source/util/bitutils.h
    spirv-tools/source/util/hex_float.h
    spirv-tools/source/util/huffman_codec.h
    spirv-tools/source/util/ilist.h
    spirv-tools/source/util/ilist_node.h
    spirv-tools/source/util/move_to_front.h
    spirv-tools/source/util/parse_number.cpp
    spirv-tools/source/util/parse_number.h
    spirv-tools/source/util/string_utils.cpp
    spirv-tools/source/util/string_utils.h

    spirv-tools/source/assembly_grammar.cpp
    spirv-tools/source/binary.cpp
    spirv-tools/source/diagnostic.cpp
    spirv-tools/source/disassemble.cpp
    spirv-tools/source/enum_string_mapping.cpp
    spirv-tools/source/extensions.cpp
    spirv-tools/source/ext_inst.cpp
    spirv-tools/source/id_descriptor.cpp
    spirv-tools/source/libspirv.cpp
    spirv-tools/source/message.cpp
    spirv-tools/source/name_mapper.cpp
    spirv-tools/source/opcode.cpp
    spirv-tools/source/operand.cpp
    spirv-tools/source/parsed_operand.cpp
    spirv-tools/source/print.cpp
    spirv-tools/source/software_version.cpp
    spirv-tools/source/spirv_endian.cpp
    spirv-tools/source/spirv_stats.cpp
    spirv-tools/source/spirv_target_env.cpp
    spirv-tools/source/spirv_validator_options.cpp
    spirv-tools/source/table.cpp
    spirv-tools/source/text.cpp
    spirv-tools/source/text_handler.cpp
    spirv-tools/source/validate_adjacency.cpp
    spirv-tools/source/validate_arithmetics.cpp
    spirv-tools/source/validate_atomics.cpp
    spirv-tools/source/validate_barriers.cpp
    spirv-tools/source/validate_bitwise.cpp
    spirv-tools/source/validate_capability.cpp
    spirv-tools/source/validate_cfg.cpp
    spirv-tools/source/validate_composites.cpp
    spirv-tools/source/validate_conversion.cpp
    spirv-tools/source/validate.cpp
    spirv-tools/source/validate_datarules.cpp
    spirv-tools/source/validate_decorations.cpp
    spirv-tools/source/validate_derivatives.cpp
    spirv-tools/source/validate_ext_inst.cpp
    spirv-tools/source/validate_id.cpp
    spirv-tools/source/validate_image.cpp
    spirv-tools/source/validate_instruction.cpp
    spirv-tools/source/validate_layout.cpp
    spirv-tools/source/validate_literals.cpp
    spirv-tools/source/validate_logicals.cpp
    spirv-tools/source/validate_primitives.cpp
    spirv-tools/source/validate_type_unique.cpp

    spirv-tools/source/assembly_grammar.h
    spirv-tools/source/binary.h
    spirv-tools/source/cfa.h
    spirv-tools/source/DebugInfo.h
    spirv-tools/source/diagnostic.h
    spirv-tools/source/disassemble.h
    spirv-tools/source/enum_set.h
    spirv-tools/source/enum_string_mapping.h
    spirv-tools/source/extensions.h
    spirv-tools/source/ext_inst.h
    spirv-tools/source/id_descriptor.h
    spirv-tools/source/instruction.h
    spirv-tools/source/latest_version_glsl_std_450_header.h
    spirv-tools/source/latest_version_opencl_std_header.h
    spirv-tools/source/latest_version_spirv_header.h
    spirv-tools/source/macro.h
    spirv-tools/source/message.h
    spirv-tools/source/name_mapper.h
    spirv-tools/source/opcode.h
    spirv-tools/source/operand.h
    spirv-tools/source/parsed_operand.h
    spirv-tools/source/print.h
    spirv-tools/source/spirv_constant.h
    spirv-tools/source/spirv_definition.h
    spirv-tools/source/spirv_endian.h
    spirv-tools/source/spirv_stats.h
    spirv-tools/source/spirv_target_env.h
    spirv-tools/source/spirv_validator_options.h
    spirv-tools/source/table.h
    spirv-tools/source/text.h
    spirv-tools/source/text_handler.h
    spirv-tools/source/validate.h

    spirv-tools/source/build-version.inc
    spirv-tools/source/core.insts-1.0.inc
    spirv-tools/source/core.insts-1.1.inc
    spirv-tools/source/core.insts-1.2.inc
    spirv-tools/source/debuginfo.insts.inc
    spirv-tools/source/enum_string_mapping.inc
    spirv-tools/source/extension_enum.inc
    spirv-tools/source/generators.inc
    spirv-tools/source/glsl.std.450.insts-1.0.inc
    spirv-tools/source/glsl.std.450.insts.inc
    spirv-tools/source/opencl.std.insts-1.0.inc
    spirv-tools/source/opencl.std.insts.inc
    spirv-tools/source/operand.kinds-1.0.inc
    spirv-tools/source/operand.kinds-1.1.inc
    spirv-tools/source/operand.kinds-1.2.inc
    spirv-tools/source/spv-amd-gcn-shader.insts.inc
    spirv-tools/source/spv-amd-shader-ballot.insts.inc
    spirv-tools/source/spv-amd-shader-explicit-vertex-parameter.insts.inc
    spirv-tools/source/spv-amd-shader-trinary-minmax.insts.inc

    spirv-tools/include/spirv-tools/libspirv.h
    )

target_sources ( xxhash PRIVATE
    xxhash/xxhash.c
    xxhash/xxhash.h
    )
