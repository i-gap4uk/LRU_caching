#ifndef PRODUCT_H
#define PRODUCT_H

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

struct Product {
  std::uint64_t id;
  std::uint32_t category;
  std::string description;
  std::vector<std::uint8_t> thumbnail_image;

  bool operator==(const Product& other) { return other.id == id; }
};

std::ostream& operator<<(std::ostream& os, const Product& product) {
  os << "{";
  os << "id: " << product.id << "; ";
  os << "category: " << product.category << "; ";
  os << "description: " << product.description << "}";

  return os;
}

#endif  // PRODUCT_H
