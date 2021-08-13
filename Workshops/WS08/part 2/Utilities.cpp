// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include "Utilities.h"
#include "Element.h"
#include "List.h"
#include <memory>

using namespace std;

namespace sdds {
List<Product> mergeRaw(const List<Description> &desc,
                       const List<Price> &price) {
  List<Product> priceList;
  // Add your code here to build a list of products
  //         using raw pointers
  for (size_t i = 0; i < desc.size(); i++) {
    for (size_t j = 0; j < price.size(); j++) {
      if (desc[i].code == price[j].code) {
        Product *product = new Product(desc[i].desc, price[j].price);
        product->validate();
        priceList += product;
        // calling destructor
        delete product;
      }
    }
  }

  return priceList;
}

List<Product> mergeSmart(const List<Description> &desc,
                         const List<Price> &price) {
  List<Product> priceList;
  //  Add your code here to build a list of products
  //         using smart pointers
  for (size_t i = 0; i < desc.size(); i++) {
    for (size_t j = 0; j < price.size(); j++) {
      if (desc[i].code == price[j].code) {
        std::unique_ptr<Product> product(
            new Product(desc[i].desc, price[j].price));
        product->validate();
        priceList += product;
      }
    }
  }

  return priceList;
}
} // namespace sdds
