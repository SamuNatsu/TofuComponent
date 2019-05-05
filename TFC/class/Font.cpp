#include "Font.h"

namespace TFC {

Font::Font() {}

Font::~Font() {
  Release();
}

bool Font::Load(const char *file, int fSize) {
  font = TTF_OpenFont(file, fSize);
  if (font == nullptr) {
    error = TTF_GetError();
    return false;
  }
  return true;
}

void Font::Release() {
  if (font != nullptr) {
    TTF_CloseFont(font);
    font = nullptr;
  }
}

TTF_Font* Font::GetFont() const {
  return font;
}

}
