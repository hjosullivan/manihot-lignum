#ifndef CTEXTURE_H
#define CTEXTURE_H

class CTexture {
public:
  char *data;
  int  w, h;
  GLuint texturenum;
  void Load(const char *filename, int fw, int fh);
  void use();
  void do_not_use();
};



#endif
