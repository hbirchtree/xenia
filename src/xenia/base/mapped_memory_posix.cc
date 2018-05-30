/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2014 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "xenia/base/mapped_memory.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <memory>

#include "xenia/base/string.h"

namespace xe {

class PosixMappedMemory : public MappedMemory {
 public:
  PosixMappedMemory(const std::wstring& path, Mode mode)
      : MappedMemory(path, mode), file_handle(nullptr) {
    int open_flags = 0;
    int protection = 0;
    int mapping = MAP_PRIVATE;
    struct stat file_state;
    std::string posix_path(path.begin(), path.end());

    switch(mode)
    {
    case Mode::kReadWrite:
      open_flags = O_RDWR;
      protection = PROT_READ | PROT_WRITE;
        break;
    case Mode::kRead:
      open_flags = O_RDONLY;
      protection = PROT_READ;
      break;
    default:
      abort();
      break;
    }

    int fd = open(posix_path.c_str(), open_flags);

    if(fd == -1 || fstat(fd, &file_state) != 0)
      abort();

    data_ = mmap(nullptr, file_state.st_size, protection, mapping, fd, 0);

    close(fd);
  }

  ~PosixMappedMemory() override {
    if (data_) {
      munmap(data_, size_);
    }
    if (file_handle) {
      fclose(file_handle);
    }
  }

  FILE* file_handle;
};

std::unique_ptr<MappedMemory> MappedMemory::Open(const std::wstring& path,
                                                 Mode mode, size_t offset,
                                                 size_t length) {
  const char* mode_str;
  int prot;
  switch (mode) {
    case Mode::kRead:
      mode_str = "rb";
      prot = PROT_READ;
      break;
    case Mode::kReadWrite:
      mode_str = "r+b";
      prot = PROT_READ | PROT_WRITE;
      break;
  }

  auto mm =
      std::unique_ptr<PosixMappedMemory>(new PosixMappedMemory(path, mode));

  mm->file_handle = fopen(xe::to_string(path).c_str(), mode_str);
  if (!mm->file_handle) {
    return nullptr;
  }

  size_t map_length;
  map_length = length;
  if (!length) {
    fseeko(mm->file_handle, 0, SEEK_END);
    map_length = ftello(mm->file_handle);
    fseeko(mm->file_handle, 0, SEEK_SET);
  }
  mm->size_ = map_length;

  mm->data_ =
      mmap(0, map_length, prot, MAP_SHARED, fileno(mm->file_handle), offset);
  if (!mm->data_) {
    return nullptr;
  }

  return std::move(mm);
}

std::unique_ptr<ChunkedMappedMemoryWriter> ChunkedMappedMemoryWriter::Open(
    const std::wstring& path, size_t chunk_size, bool low_address_space) {
  // TODO(DrChat)
  return nullptr;
}

}  // namespace xe
