# Task: Implement LRU (Least-Recently-Used) Caching

Clients visit e-commerce website to browse the products. For each product, the website stores the following details:

- **uint64** id  
- **uint32** category  
- **string** name  
- **string** description  
- **bytes** thumbnail image  

Products are stored in a database through a class that has the following interface. Both methods may return the requested data if the ID exists or indicate an error when the ID does not exist or the database is unavailable:

1. A method to fetch product details given a product ID.  
2. A method to fetch the total number of products given a category ID.

## Problem Context

Profiling shows that fetching product details (1) is an expensive operation. Furthermore, was observed that clients tend to focus on the same products on a particular day or keep browsing back and forth between the same products. For this reason, it was made a solution to create a cache that will hold the frequently browsed product details.

## Requirements

1. **Create an in-memory cache** with an **LRU (least-recently-used) replacement policy** and a predetermined capacity in terms of item count.  
2. The cache can hold only up to a maximum number of items, so when the cache is full and a new item needs to be cached, the least-recently-used item must be evicted, i.e., the one that has been unused for a longer period of time than the others.  
3. The cache component needs to expose:
   - A retrieval method that requests a cached item, which may or may not exist.  
   - An insertion method that caches an item.  
4. The cache implementation should be **generic** so that it can be reused for other use cases in the future with possibly different data types for keys or values. For example, to cache a list of product IDs per category.  
5. Using the LRU cache implementation, create a class that routes the fetch product details queries either to the cache or to the database.  
6. Assume that the fetch product details queries will be done from **multiple threads**.  
7. The actual database can be **faked with hardcoded data** as we are not focused on this part, and the database component is **thread-safe** by itself.

---
