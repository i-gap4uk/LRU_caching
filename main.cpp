#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

#include "fake_database.h"
#include "product.h"
#include "product_cache.h"

void fake_activity(ProductCache<std::uint64_t, Product, 5>& cache,
                   std::size_t thread_id, std::size_t time_interval,
                   std::size_t max_iterations, std::size_t iteration) {
  while (iteration <= max_iterations) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time_interval));

    const std::uint64_t product_id = rand() % 30 + 1;
    const auto product = cache.getProduct(product_id);
    const auto total_amount =
        cache.getProductAmountByCategory(product->category);
    std::cout << "Thread" << thread_id << std::endl
              << "Remaining iterations: " << (max_iterations - iteration)
              << std::endl
              << "Time interval: " << time_interval << std::endl
              << "Product:" << product.value() << std::endl
              << "Total amount: " << total_amount << std::endl
              << std::endl;
    ++iteration;
  }
}

int main() {
  std::srand(std::time(0));
  FakeDataBase db;
  for (std::size_t i = 1; i < 31; ++i) {
    auto category_id = rand() % 5 + 1;
    db.addProduct(
        {i, static_cast<uint32_t>(category_id), "product description", {}});
  }

  ProductCache<std::uint64_t, Product, 5> cache(db);

  std::thread t1([&cache]() {
    std::size_t iteration = 1;
    const std::size_t max_iterations = 10;
    const std::size_t time_interval = 100;

    fake_activity(cache, 1, time_interval, max_iterations, iteration);
  });

  std::thread t2([&cache]() {
    std::size_t iteration = 1;
    const std::size_t max_iterations = 30;
    const std::size_t time_interval = 500;

    fake_activity(cache, 2, time_interval, max_iterations, iteration);
  });

  std::thread t3([&cache]() {
    std::size_t iteration = 1;
    const std::size_t max_iterations = 20;
    const std::size_t time_interval = 1000;

    fake_activity(cache, 3, time_interval, max_iterations, iteration);
  });

  std::thread t4([&cache]() {
    std::size_t iteration = 1;
    const std::size_t max_iterations = 15;
    const std::size_t time_interval = 300;

    fake_activity(cache, 4, time_interval, max_iterations, iteration);
  });

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  return 0;
}
