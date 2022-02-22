#pragma once

#include <stdio.h>
#include <string.h>



#include <minizip/unzip.h>
#include "infoProgress.h"


class Zipfile {
public:
  Zipfile(const std::string zip_path);
  ~Zipfile();

  int Unzip(const std::string outpath, InfoProgress progress);
  int Unzip(const std::string outpath, InfoProgress *progress = nullptr);

  int UncompressedSize(InfoProgress progress);
  int UncompressedSize(InfoProgress *progress = nullptr);

private:
  unzFile zipfile_;
  uint64_t uncompressed_size_ = 0;
  unz_global_info global_info_;
};
