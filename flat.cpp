#include "flat.hpp"

flat::flat(long home_n, long flat_n, long room_c, double s, string owner,
           long vil_c)
    : home_n_(home_n),
      flat_n_(flat_n),
      room_c_(room_c),
      s_(s),
      owner_(owner),
      vil_c_(vil_c) {
  ;
}

flat::flat(const flat& other) {
  this->flat_n_ = other.flat_n_;
  this->home_n_ = other.home_n_;
  this->owner_ = other.owner_;
  this->room_c_ = other.room_c_;
  this->s_ = other.s_;
  this->vil_c_ = other.vil_c_;
}

bool flat::operator<(const flat& other) const { return owner_ < other.owner_; }

bool flat::operator>(const flat& other) const { return other < *this; }

bool flat::operator>=(const flat& other) const { return !(*this < other); }

bool flat::operator<=(const flat& other) const { return !(*this > other); }

flat& flat::operator=(const flat& other) {
  this->flat_n_ = other.flat_n_;
  this->home_n_ = other.home_n_;
  this->owner_ = other.owner_;
  this->room_c_ = other.room_c_;
  this->s_ = other.s_;
  this->vil_c_ = other.vil_c_;
  return *this;
}

bool flat::operator!=(const flat& other) const {
  if (this->flat_n_ != other.flat_n_) {
    return true;
  } else if (this->home_n_ != other.home_n_) {
    return true;
  } else if (this->owner_ != other.owner_) {
    return true;
  } else if (this->room_c_ != other.room_c_) {
    return true;
  } else if (this->s_ != other.s_) {
    return true;
  } else if (this->vil_c_ != other.vil_c_) {
    return true;
  }
  return false;
}

bool flat::operator==(const string& owner) const {
  return this->owner_ == owner;
}

const string& flat::get_owner() const { return this->owner_; }

void print_flats(flat* flats, size_t size, ostream& os) {
  for (size_t i = 0; i < size; ++i) {
    os << flats[i];
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

ostream& operator<<(ostream& os, const flat& f) {
  os << f.home_n_ << ";" << f.flat_n_ << ";" << f.room_c_ << ";" << f.s_ << ";"
     << f.owner_ << ";" << f.vil_c_ << endl;
  return os;
}