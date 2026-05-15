#include "rb_tree.hpp"

rb_node::rb_node(flat* here, rb_node* parent, rb_node* left, rb_node* right,
                 Color color)
    : parent_(parent), left_(left), right_(right), color_(color), count_(0) {
  if (here) {
    here_ = new flat[1];
    here_[0] = *here;
    count_ = 1;
  }
};

rb_node::~rb_node() {
  delete[] here_;
  here_ = nullptr;
}

bool rb_node::right_free() const { return !right_; }

bool rb_node::left_free() const { return !left_; }

rb_node* rb_node::get_parent() const { return parent_; }

void rb_node::set_parent(rb_node* parent) { parent_ = parent; }

flat* rb_node::get_here() const { return here_; }

void rb_node::set_here(flat* here) { here_ = here; }

rb_node* rb_node::get_left() const { return left_; }

void rb_node::set_left(rb_node* left) { left_ = left; }

rb_node* rb_node::get_right() const { return right_; }

void rb_node::set_right(rb_node* right) { right_ = right; }

Color rb_node::get_color() const { return color_; }

void rb_node::set_color(Color color) { color_ = color; }

size_t rb_node::get_count() const { return count_; }

bool rb_node::operator<(flat* other) const {
  if (!other || !this->count_) return false;
  return this->here_->get_owner() < other->get_owner();
}

bool rb_node::operator<(const string& key) const {
  if (!this->count_) return false;
  return this->here_->get_owner() < key;
}

bool rb_node::operator>=(flat* other) const {
  if (!other || !this->count_) return false;
  return this->here_->get_owner() >= other->get_owner();
}

bool rb_node::operator>=(const string& key) const {
  if (!this->count_) return false;
  return this->here_->get_owner() >= key;
}

bool rb_node::operator==(flat* other) const {
  if (!other || !this->count_) return false;
  return this->here_->get_owner() == other->get_owner();
}

bool rb_node::operator==(const string& key) const {
  if (!this->count_) return false;
  return this->here_->get_owner() == key;
}

void rb_node::add_flat(flat* f) {
  flat* new_data = new flat[count_ + 1];
  for (size_t i = 0; i < count_; ++i) new_data[i] = here_[i];
  new_data[count_] = *f;
  delete[] here_;
  here_ = new_data;
  ++count_;
}

rb_tree::rb_tree() : root_(nullptr), size_(0) {}

rb_tree::~rb_tree() { clear_rb_subtree(root_); }

rb_node* rb_tree::get_root() const { return root_; }

void rb_tree::set_root(rb_node* root) { root_ = root; }

size_t rb_tree::get_size() const { return size_; }

rb_node* rb_tree::insert(flat* new_elem) {
  if (!new_elem) return nullptr;
  if (!size_) {
    rb_node* p = new rb_node(new flat(*new_elem));
    set_root(p);
    root_->set_color(Color::BLACK);
    ++size_;
    return root_;
  }
  rb_node* cur = root_;
  while (true) {
    if (*cur == new_elem) {
      cur->add_flat(new_elem);
      ++size_;
      return cur;
    }
    if (*cur < new_elem) {
      if (cur->right_free()) {
        rb_node* p = new rb_node(new flat(*new_elem), cur);
        cur->set_right(p);
        ++size_;
        insert_fix(p);
        return p;
      }
      cur = cur->get_right();
    } else {
      if (cur->left_free()) {
        rb_node* p = new rb_node(new flat(*new_elem), cur);
        cur->set_left(p);
        ++size_;
        insert_fix(p);
        return p;
      }
      cur = cur->get_left();
    }
  }
}

void rb_tree::insert_fix(rb_node* son) {
  while (son != root_ && son->get_parent()->get_color() == Color::RED) {
    rb_node* parent = son->get_parent();
    rb_node* grandparent = parent->get_parent();
    if (parent == grandparent->get_left()) {
      rb_node* uncle = grandparent->get_right();
      if (uncle && uncle->get_color() == Color::RED) {
        parent->set_color(Color::BLACK);
        uncle->set_color(Color::BLACK);
        grandparent->set_color(Color::RED);
        son = grandparent;
      } else {
        if (son == parent->get_right()) {
          son = parent;
          rotate_left(son);
          parent = son->get_parent();
          grandparent = parent->get_parent();
        }
        parent->set_color(Color::BLACK);
        grandparent->set_color(Color::RED);
        rotate_right(grandparent);
        break;
      }
    } else {
      rb_node* uncle = grandparent->get_left();
      if (uncle && uncle->get_color() == Color::RED) {
        parent->set_color(Color::BLACK);
        uncle->set_color(Color::BLACK);
        grandparent->set_color(Color::RED);
        son = grandparent;
      } else {
        if (son == parent->get_left()) {
          son = parent;
          rotate_right(son);
          parent = son->get_parent();
          grandparent = parent->get_parent();
        }
        parent->set_color(Color::BLACK);
        grandparent->set_color(Color::RED);
        rotate_left(grandparent);
        break;
      }
    }
  }
  root_->set_color(Color::BLACK);
}

rb_node* rb_tree::rotate_left(rb_node* subroot) {
  rb_node* new_subroot = subroot->get_right();
  if (!new_subroot) return subroot;
  bool new_has_left = !new_subroot->left_free();
  subroot->set_right(new_subroot->get_left());
  if (new_has_left) subroot->get_right()->set_parent(subroot);
  new_subroot->set_left(subroot);
  rb_node* parent = subroot->get_parent();
  subroot->set_parent(new_subroot);
  bool has_parent = (parent);
  if (has_parent) {
    new_subroot->set_parent(parent);
    bool was_left = (parent->get_left() == subroot);
    if (was_left)
      parent->set_left(new_subroot);
    else
      parent->set_right(new_subroot);
  } else {
    set_root(new_subroot);
    new_subroot->set_parent(nullptr);
  }
  return new_subroot;
}

rb_node* rb_tree::rotate_right(rb_node* subroot) {
  rb_node* new_subroot = subroot->get_left();
  if (!new_subroot) return subroot;
  bool new_has_right = !new_subroot->right_free();
  subroot->set_left(new_subroot->get_right());
  if (new_has_right) subroot->get_left()->set_parent(subroot);
  new_subroot->set_right(subroot);
  rb_node* parent = subroot->get_parent();
  subroot->set_parent(new_subroot);
  bool has_parent = (parent);
  if (has_parent) {
    new_subroot->set_parent(parent);
    bool was_left = (parent->get_left() == subroot);
    if (was_left)
      parent->set_left(new_subroot);
    else
      parent->set_right(new_subroot);
  } else {
    set_root(new_subroot);
    new_subroot->set_parent(nullptr);
  }
  return new_subroot;
}
flat* rb_tree::find(const string& key, size_t& out_size) const {
  out_size = 0;
  if (!root_) return nullptr;

  rb_node* cur = root_;
  while (cur) {
    if (*cur == key)
      break;
    else if (*cur < key)
      cur = cur->get_right();
    else
      cur = cur->get_left();
  }
  if (!cur) return nullptr;

  out_size = cur->get_count();
  flat* res = new flat[out_size];
  for (size_t i = 0; i < out_size; ++i) res[i] = cur->get_here()[i];
  return res;
}
void fill_rb_tree(rb_tree* tr, flat* flats, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    tr->insert(flats + i);
  }
}

void clear_rb_subtree(rb_node* l) {
  if (!l) return;
  clear_rb_subtree(l->get_left());
  clear_rb_subtree(l->get_right());
  delete l;
}