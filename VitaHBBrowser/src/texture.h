#pragma once

#include <memory>
#include <unordered_map>
#include <vita2d.h>
#include "shapes.h"

void DeleteTexture(vita2d_texture* tex);

namespace std {
inline std::shared_ptr<vita2d_texture> make_shared(vita2d_texture* tex) {
    return std::shared_ptr<vita2d_texture>(tex, DeleteTexture);
}
}

class Texture {
public:
  enum Status {
      LOADING,
      LOADED,
      FAILED
  };

  explicit Texture(unsigned char *addr, bool caching = true);
  explicit Texture(const std::string &path, bool caching = true);

  Texture(const Texture& that);
  Texture& operator=(const Texture& that);

  int Draw(const Point &pt);
  int DrawExt(const Point &pt, int alpha);
  int DrawResize(const Point &pt1, const Point &dimensions);
  int DrawCentered(const Point &pt);
  int DrawTint(const Point &pt, unsigned int color);

  unsigned int Height();

  static std::unordered_map<std::string, std::shared_ptr<vita2d_texture>> textureCache1;
  static std::unordered_map<unsigned char *, std::shared_ptr<vita2d_texture>> textureCache2;

  std::shared_ptr<vita2d_texture> texture;

private:
  bool caching_;

  Status m_status = LOADING;
};

