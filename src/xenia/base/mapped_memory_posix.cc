/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2014 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "xenia/base/mapped_memory.h"
#include "xenia/base/assert.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <cstdio>
#include <memory>

#include "xenia/base/string.h"

namespace xe {

class PosixMappedMemory : public MappedMemory {
 public:
  PosixMappedMemory(const std::wstring& path, Mode mode)
      : MappedMemory(path, mode) {
  }

  ~PosixMappedMemory() override {
    if (data_) {
      munmap(data_, size_);
    }
  }
};

std::unique_ptr<MappedMemory> MappedMemory::Open(const std::wstring& path,
                                                 Mode mode, size_t offset,
                                                 size_t length) {
  const char* mode_str;
  int open_mode;
  int prot;
  switch (mode) {
    case Mode::kRead:
      mode_str = "rb";
      open_mode = O_RDONLY;
      prot = PROT_READ;
      break;
    case Mode::kReadWrite:
      mode_str = "r+b";
      open_mode = O_RDWR;
      prot = PROT_READ | PROT_WRITE;
      break;
  }

  auto mm =
      std::unique_ptr<PosixMappedMemory>(new PosixMappedMemory(path, mode));

  auto fd = fopen(xe::to_string(path).c_str(), mode_str);
  if (!fd) {
    fprintf(stderr, "POSIX error: %s\n", strerror(errno));
    return nullptr;
  }

  size_t map_length;
  map_length = length;
  if (!length) {
    struct stat file_state;
    fstat(fileno(fd), &file_state);
    map_length = file_state.st_size;
  }
  mm->size_ = map_length;

  mm->data_ =
      mmap(0, map_length, prot, MAP_SHARED, fileno(fd), offset);
  fclose(fd);
  if (!mm->data_) {
    fprintf(stderr, "POSIX error: %s\n", strerror(errno));
    return nullptr;
  }

  return std::move(mm);
}

std::unique_ptr<ChunkedMappedMemoryWriter> ChunkedMappedMemoryWriter::Open(
    const std::wstring& path, size_t chunk_size, bool low_address_space) {
  // TODO(DrChat)
  assert_always();
  return nullptr;
}

}  // namespace xe
