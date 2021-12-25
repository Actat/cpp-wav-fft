#include "wav.hpp"
#include <iostream>
#include <fstream>
#include <vector>

namespace wav
{
  Chunk::Chunk(unsigned int pos, std::string id, unsigned int size)
  {
    pos_ = pos;
    id_ = id;
    size_ = size;
  };

  void Chunk::setType(std::string type)
  {
    if (!isParent())
    {
      return;
    }
    type_ = type;
  };

  void Chunk::pushChild(Chunk *child)
  {
    children_.push_back(child);
  }

  std::string Chunk::toString()
  {
    std::string str = "{pos: " + std::to_string(pos_) + ", id: " + id_ + ", size: " + std::to_string(size_);
    if (isParent())
    {
      str = str + ", type: " + type_;
    }
    return str + "}";
  };

  WAVE::WAVE(char *file_name)
  {
    file_ = file_name;
    std::ifstream fin(file_, std::ios::in | std::ios::binary);
    if (!fin)
    {
      std::cout << "Can not open the file." << std::endl;
      throw;
    }
    fin_ = &fin;
    index_ = loadIndex(0);
  };

  Chunk *WAVE::loadIndex(unsigned int pos)
  {
    fin_->seekg(pos, std::ios::beg);
    char *id = new char[4];
    fin_->read(id, 4);
    char *tmp = new char[4];
    fin_->read(tmp, 4);
    unsigned int size = (unsigned int)((tmp[3] << 24) | (tmp[2] << 16) | (tmp[1] << 8) | tmp[0]);
    Chunk *c = new Chunk(pos, id, size);

    if (c->isParent())
    {
      char *type = new char[4];
      fin_->read(type, 4);
      c->setType(type);

      unsigned int chunk_end = c->getPos() + 8 + c->getSize();
      unsigned int next_child_pos = c->getPos() + 12;
      while (next_child_pos < chunk_end)
      {
        Chunk *child = loadIndex(next_child_pos);
        c->pushChild(child);

        next_child_pos += 8 + child->getSize();
      }
    }
    return c;
  };
}
