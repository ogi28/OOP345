// Workshop 5 - Functions and Error Handling
// 2020/02 - Cornel
// 2021/01/19 - Chris
// 2021/02/12 - Cornel

#include "Book.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace sdds;

using std::cout;
enum AppErrors {
  CannotOpenFile = 1,   // An input file cannot be opened
  BadArgumentCount = 2, // The application didn't receive anough parameters
};

// ws books.txt
int main(int argc, char **argv) {
  using std::ifstream;
  std::cout << "Command Line:\n";
  std::cout << "--------------------------\n";
  for (int i = 0; i < argc; i++)
    std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
  std::cout << "--------------------------\n\n";

  // get the books
  sdds::Book library[7];
  if (argc == 2) {
    // TODO: load the collection of books from the file "argv[1]".
    //       - read one line at a time, and pass it to the Book constructor
    //       - store each book read into the array "library"
    //       - lines that start with "#" are considered comments and should be
    //       ignored
    //       - if the file cannot be open, print a message to standard error
    //       console and
    //           exit from application with error code
    //           "AppErrors::CannotOpenFile"
    ifstream file(argv[1]);
    if (!file.is_open()) {
      std::cerr << "ERROR: Cannot open file.\n";
      exit(AppErrors::CannotOpenFile);
    }
    string line;
    size_t index = 0;
    while (getline(file, line)) {
      if (line[0] != '#') {
        Book B(line);
        library[index] = B;
        index++;
      }
    }
    file.close();
  } else {
    std::cerr << "ERROR: Incorrect number of arguments.\n";
    exit(AppErrors::BadArgumentCount);
  }

  double usdToCadRate = 1.3;
  double gbpToCadRate = 1.5;

  // TODO: create a lambda expression that fixes the price of a book accoding to
  // the rules
  //       - the expression should receive a single parameter of type "Book&"
  //       - if the book was published in US, multiply the price with
  //       "usdToCadRate"
  //            and save the new price in the book object
  //       - if the book was published in UK between 1990 and 1999 (inclussive),
  //            multiply the price with "gbpToCadRate" and save the new price in
  //            the book object

  auto fixprice = [&usdToCadRate, &gbpToCadRate](Book &B) {
    if (B.country() == "US") {
      B.price() *= usdToCadRate;
    } else if (B.country() == "UK" && 1990 <= B.year() && B.year() <= 1999) {
      B.price() *= gbpToCadRate;
    }
    // body
  };

  std::cout << "-----------------------------------------\n";
  std::cout << "The library content\n";
  std::cout << "-----------------------------------------\n";
  // TODO: iterate over the library and print each book to the screen
  for (size_t i = 0; i < 7; ++i) {
    cout << library[i];
  }

  std::cout << "-----------------------------------------\n\n";

  // TODO: iterate over the library and update the price of each book
  //         using the lambda defined above.
  for (size_t i = 0; i < 7; ++i) {
    fixprice(library[i]);
  }

  std::cout << "-----------------------------------------\n";
  std::cout << "The library content (updated prices)\n";
  std::cout << "-----------------------------------------\n";
  // TODO: iterate over the library and print each book to the screen
  for (size_t i = 0; i < 7; ++i) {
    cout << library[i];
  }

  std::cout << "-----------------------------------------\n";

  return 0;
}
