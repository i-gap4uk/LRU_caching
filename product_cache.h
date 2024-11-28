#ifndef PRODUCT_CACHE_H
#define PRODUCT_CACHE_H

#include "cache_implementation.h"
#include "fake_database.h"

template <typename Key, typename P, std::size_t Capacity>
class ProductCache {
 public:
  ProductCache(FakeDataBase& db) : _db(db), _cache(Capacity) {}

  std::optional<P> getProduct(const Key& key) {
    const auto cached_product = _cache.get(key);
    if (cached_product.has_value()) {
      return cached_product;
    }

    auto fetched_product = _db.fetchProductDetails(key);
    if (fetched_product.has_value()) {
      const auto tmp = fetched_product.value();
      _cache.put(tmp.id, tmp);
    }

    return fetched_product;
  }

  std::uint64_t getProductAmountByCategory(std::uint32_t category_id) {
    return _db.fetchTotalNumbersByCategory(category_id);
  }

 private:
  CacheImpl<Key, P> _cache;
  FakeDataBase& _db;
};

#endif  // PRODUCT_CACHE_H
