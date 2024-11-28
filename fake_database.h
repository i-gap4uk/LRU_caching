#ifndef FAKE_DATABASE_H
#define FAKE_DATABASE_H

#include <algorithm>
#include <cstdint>
#include <optional>
#include <unordered_map>

#include "product.h"

// Should be inheritaed from an interface IDataBase, but it's ommited for this
// example
class FakeDataBase {
 public:
  std::optional<Product> fetchProductDetails(std::uint64_t product_id) {
    if (_products.find(product_id) != _products.end()) {
      return _products[product_id];
    }

    return std::nullopt;
  }

  std::uint64_t fetchTotalNumbersByCategory(std::uint32_t category_id) {
    std::uint64_t totalNumber = 0;

    std::for_each(_products.begin(), _products.end(),
                  [&totalNumber,
                   &category_id](std::pair<std::uint64_t, Product> product) {
                    if (product.second.category == category_id) {
                      ++totalNumber;
                    }
                  });

    return totalNumber;
  }

  void addProduct(Product&& product) {
    _products.insert(std::make_pair(product.id, std::move(product)));
  }

 private:
  std::unordered_map<std::uint64_t, Product> _products;
};

#endif  // FAKE_DATABASE_H
