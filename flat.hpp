#ifndef FLAT_HPP
#define FLAT_HPP

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

class flat {
 public:
  flat(long home_n = 0, long flat_n = 0, long room_c = 0, double s = 0,
       string owner = "", long vil_c = 0);
  flat(const flat& other);
  ~flat() = default;
  bool operator<(const flat& other) const;
  bool operator>(const flat& other) const;
  bool operator>=(const flat& other) const;
  bool operator<=(const flat& other) const;
  flat& operator=(const flat& other);
  bool operator!=(const flat& other) const;
  bool operator==(const string& owner) const;
  string get_owner() const;

  friend ostream& operator<<(ostream& os, const flat& f);

 private:
  long home_n_;
  long flat_n_;
  long room_c_;
  double s_;
  string owner_;
  long vil_c_;
};

void print_flats(flat* flats, size_t size, ostream& os);

flat* load_from_csv(const string filename, size_t& size);

bool check_correct(flat* flats1, flat* flats2, size_t size);

#endif