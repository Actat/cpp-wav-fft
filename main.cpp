#include <iostream>
#include <fstream>
#include <vector>
#include "wav.hpp"

int main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    std::cout << "Usage: ./a.out filename.wav" << std::endl;
    return 1;
  }

  wav::WAVE *f = new wav::WAVE(argv[argc - 1]);
  std::cout << f->getIndex()->toString() << std::endl;

  return 0;
}
