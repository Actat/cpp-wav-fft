#ifndef WAV
#define WAV

#include <iostream>
#include <fstream>
#include <vector>

namespace wav
{
  class Chunk
  {
  private:
    unsigned int pos_;
    std::string id_;
    unsigned int size_;
    std::string type_;

  protected:
    std::vector<Chunk *> children_;

  public:
    Chunk(unsigned int pos, std::string id, unsigned int size);
    unsigned int getPos() { return pos_; };
    std::string getID() { return id_; };
    unsigned int getSize() { return size_; };
    void setType(std::string type);
    bool isParent() { return id_ == "RIFF" || id_ == "LIST"; };
    void pushChild(Chunk *child);
    std::string toString();
  };

  class WAVE
  {
  private:
    Chunk *loadIndex(unsigned int pos);

  protected:
    char *file_;
    Chunk *index_;
    std::ifstream *fin_;

  public:
    WAVE(char *file_name);
    Chunk *getIndex() { return index_; };
  };
}

#endif
