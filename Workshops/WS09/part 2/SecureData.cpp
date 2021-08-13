// Workshop 9 - Multi-Threading
// SecureData.cpp

#include "SecureData.h"
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

namespace w9 {

void splitText(char *text, int nbytes, char ***parts, int *partSize) {
  if (*parts) {
    delete[] * parts;
  }
  *parts = new char *[4]; // array to hold 4 character pointers(c style strings)
  int divNBytes = nbytes / 4;
  int divRemainder = nbytes % 4;

  size_t i = 0;

  for (; i < 3; i++) {
    (*parts)[i] = new char[divNBytes + 1];
    memcpy((*parts)[i], text + (i * divNBytes), divNBytes);
    (*parts)[i][divNBytes] = '\0';
    partSize[i] = divNBytes;
  }
  (*parts)[i] = new char[divNBytes + 1 + divRemainder];
  memcpy((*parts)[i], text + (i * divNBytes), divNBytes + divRemainder);
  (*parts)[i][divNBytes + divRemainder] = '\0';
  partSize[i] = divNBytes + divRemainder;
}

void mergeText(char *text, char **parts, int *partSize) {
  int offset = 0;
  for (size_t i = 0; i < 4; i++) {
    memcpy(text + offset, parts[i], partSize[i]);
    offset += partSize[i];
  }
}

void converter(char *t, char key, int n, const Cryptor &c) {

  for (int i = 0; i < n; i++)
    t[i] = c(t[i], key);
}

SecureData::SecureData(const char *file, char key, ostream *pOfs) {
  ofs = pOfs;

  // open text file
  fstream input(file, std::ios::in);
  if (!input)
    throw string("\n***Failed to open file ") + string(file) + string(" ***\n");

  // copy from file into memory
  input.seekg(0, std::ios::end);
  nbytes = (int)input.tellg() + 1;

  text = new char[nbytes];

  input.seekg(ios::beg);
  int i = 0;
  input >> noskipws;
  while (input.good())
    input >> text[i++];
  text[nbytes - 1] = '\0';
  *ofs << "\n"
       << nbytes - 1 << " bytes copied from file " << file
       << " into memory (null byte added)\n";
  encoded = false;

  // encode using key
  code(key);
  *ofs << "Data encrypted in memory\n";
}

SecureData::~SecureData() { delete[] text; }

void SecureData::display(std::ostream &os) const {
  if (text && !encoded)
    os << text << std::endl;
  else if (encoded)
    throw std::string("\n***Data is encoded***\n");
  else
    throw std::string("\n***No data stored***\n");
}

void SecureData::code(char key) {

  using namespace std::placeholders;
  char **parts{};
  int partSize[4]{};
  splitText(text, nbytes, &parts, partSize);
  vector<thread> CPU;
  auto fn_convert = bind(converter, _1, key, _2, Cryptor());
  for (size_t i = 0; i < 4; i++) {
    CPU.push_back(thread(fn_convert, parts[i], partSize[i]));
  }
  for (auto &T : CPU) {
    T.join();
  }
  mergeText(text, parts, partSize);
  for (size_t i = 0; i < 4; i++) {
    delete[] parts[i];
  }
  delete[] parts;

  /* converter(text, key, nbytes, Cryptor()); */

  encoded = !encoded;
}

void SecureData::backup(const char *file) {
  if (!text)
    throw std::string("\n***No data stored***\n");
  else if (!encoded)
    throw std::string("\n***Data is not encoded***\n");
  else {
    ofstream F(file, ios::binary);
    if (!F)
      throw string("\n***Failed to open file ") + string(file) +
          string(" ***\n");

    F.write(text, nbytes);
    F.close();
  }
}

void SecureData::restore(const char *file, char key) {
  ifstream F(file, ios::binary);
  if (!F)
    throw string("\n***Failed to open file ") + string(file) + string(" ***\n");

  delete[] text;
  F.seekg(0, std::ios::end);
  nbytes = (int)F.tellg();

  text = new char[nbytes];

  F.seekg(ios::beg);

  F.read(text, nbytes);
  F.close();

  *ofs << "\n"
       << nbytes << " bytes copied from binary file " << file
       << " into memory.\n";

  encoded = true;

  // decode using key
  code(key);

  *ofs << "Data decrypted in memory\n\n";
}

std::ostream &operator<<(std::ostream &os, const SecureData &sd) {
  sd.display(os);
  return os;
}
} // namespace w9
