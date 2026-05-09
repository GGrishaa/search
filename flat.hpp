#ifndef FLAT_HPP
#define FLAT_HPP

#include <fstream>
#include <iostream>
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
  void print(ostream& os) const;

 private:
  long home_n;
  long flat_n;
  long room_c;
  double s;
  string owner;
  long vil_c;
};

void print_flats(flat* flats, size_t size, ostream& os);

flat* load_from_csv(const string filename, size_t& size);

bool check_correct(flat* flats1, flat* flats2, size_t size);

#endif