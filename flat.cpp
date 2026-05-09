#include "flat.hpp"

flat::flat(long home_n, long flat_n, long room_c, double s, string owner,
           long vil_c)
    : home_n(home_n),
      flat_n(flat_n),
      room_c(room_c),
      s(s),
      owner(owner),
      vil_c(vil_c) {
  ;
}

flat::flat(const flat& other) {
  this->flat_n = other.flat_n;
  this->home_n = other.home_n;
  this->owner = other.owner;
  this->room_c = other.room_c;
  this->s = other.s;
  this->vil_c = other.vil_c;
}

bool flat::operator<(const flat& other) const {
  // if (s != other.s) return s > other.s;
  // if (home_n != other.home_n) return home_n < other.home_n;
  // if (flat_n != other.flat_n) return flat_n < other.flat_n;
  return owner < other.owner;
}

bool flat::operator>(const flat& other) const { return other < *this; }

bool flat::operator>=(const flat& other) const { return !(*this < other); }

bool flat::operator<=(const flat& other) const { return !(*this > other); }

flat& flat::operator=(const flat& other) {
  this->flat_n = other.flat_n;
  this->home_n = other.home_n;
  this->owner = other.owner;
  this->room_c = other.room_c;
  this->s = other.s;
  this->vil_c = other.vil_c;
  return *this;
}

bool flat::operator!=(const flat& other) const {
  if (this->flat_n != other.flat_n) {
    return true;
  } else if (this->home_n != other.home_n) {
    return true;
  } else if (this->owner != other.owner) {
    return true;
  } else if (this->room_c != other.room_c) {
    return true;
  } else if (this->s != other.s) {
    return true;
  } else if (this->vil_c != other.vil_c) {
    return true;
  }
  return false;
}

bool flat::operator==(const string& owner) const {
  return this->owner == owner;
}

string flat::get_owner() const { return this->owner; }

void flat::print(ostream& os) const {
  os << home_n << ";" << flat_n << ";" << room_c << ";" << s << ";" << owner
     << ";" << vil_c << endl;
}

void print_flats(flat* flats, size_t size, ostream& os) {
  for (size_t i = 0; i < size; ++i) {
    flats[i].print(os);
  }
}

flat* load_from_csv(const string filename, size_t& size) {
  ifstream fin(filename);
  size = 0;
  if (!fin.is_open()) return nullptr;
  string line;
  size_t start_size = 100;
  getline(fin, line);
  flat* flats = new flat[start_size];
  while (getline(fin, line)) {
    istringstream iss(line);
    string token;
    getline(iss, token, ';');
    size_t home_n = stoi(token);
    getline(iss, token, ';');
    size_t flat_n = stoi(token);
    getline(iss, token, ';');
    size_t room_c = stoi(token);
    getline(iss, token, ';');
    double s = stod(token);
    getline(iss, token, ';');
    string owner = token;
    getline(iss, token, ';');
    size_t vil_c = stoi(token);
    if (size >= start_size) {
      start_size *= 2;
      flat* new_flats = new flat[start_size];
      for (size_t i = 0; i < size; i++) new_flats[i] = flats[i];
      delete[] flats;
      flats = new_flats;
    }
    flats[size++] = flat(home_n, flat_n, room_c, s, owner, vil_c);
  }
  fin.close();
  return flats;
}

bool check_correct(flat* flats1, flat* flats2, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (flats1[i] != flats2[i]) {
      return false;
    }
  }
  return true;
}