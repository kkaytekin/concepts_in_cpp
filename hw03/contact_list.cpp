#include "contact_list.h"

#include <algorithm>
#include <numeric>
#include <sstream>
#include <map>

// TODO create implementation here!
namespace contact_list {

/**
 * stores contacts by saving names and numbers.
 * be careful - these vectors have to be kept in sync!
 *
 * you may adjust this struct to store the data differently, or add index structures, ...
 * this is fine as long as the API of the functions below remains the same.
 */



//    struct storage {
//        std::map<std::string,number_t,compare> content;
//    };

/**
 * Given a contact storage, create a new contact entry by name and number.
 */
    bool add(storage &contacts, std::string name, number_t number) {

      if (std::find(contacts.names.begin(), contacts.names.end(), name) != contacts.names.end()
          || name.size() == 0) {
        std::cout << "Duplicate name or empty name not allowed.\n";
        return false;
      }
      contacts.names.push_back(name);
      contacts.numbers.push_back(number);
      return true;
    }
//    bool add(storage& contacts, std::string name, number_t number) {
//      if (contacts.content.find(name) == contacts.content.end()) {
//        contacts.content[name] = number;
//        return true;
//      }
//      std::cout << "Failed: Name already in the list.\n";
//      return false;
//    }


/**
 * Given a contact storage, how many contacts are currently stored?
 */
    size_t size(const storage &contacts) {
      return contacts.names.size();
    }


/**
 * Fetch a contact number from storage given a name.
 */
    // number_t get_number_by_name(storage& contacts, std::string_view name)
    number_t get_number_by_name(storage &contacts, const std::string name) {
      auto found{std::find(contacts.names.begin(), contacts.names.end(), name)};
      if (found == contacts.names.end())
        return -1;
      return contacts.numbers[std::distance(contacts.names.begin(), found)];
    }


/**
 * Return a string representing the contact list.
 */
    std::string to_string(const storage &contacts) {
      // First find the longest name
      uint64_t maxsize{0};
      for (const auto &str: contacts.names) {
        if (str.size() > maxsize) maxsize = str.size();
      }
      std::string out{};
      for (auto it{contacts.names.begin()}; it != contacts.names.end(); ++it) {
        if (it->size() < maxsize) {
          out += std::string(maxsize - it->size(), ' ')
                 + *it
                 + " - "
                 + std::to_string(contacts.numbers[std::distance(contacts.names.begin(), it)])
                 + '\n';
        } else {
          out += *it
                 + " - "
                 + std::to_string(contacts.numbers[std::distance(contacts.names.begin(), it)])
                 + '\n';
        }
      }
      return out;
    }


/**
 * Remove a contact by name from the contact list.
 */
    // bool remove(storage& contacts, std::string_view name)
    bool remove(storage &contacts, std::string name) {
      auto found = std::find(contacts.names.begin(), contacts.names.end(), name);
      if (found == contacts.names.end()) return false;
      contacts.numbers.erase(contacts.numbers.begin() + std::distance(contacts.names.begin(), found));
      contacts.names.erase(found);
      return true;
    }


/**
 * Sort the contact list in-place by name.
 */
    void sort(storage &contacts) {
      auto copy {contacts};
      std::sort(contacts.names.begin(), contacts.names.end());
      for (auto it = contacts.names.begin() ; it!= contacts.names.end() ; ++it) {
        if (*it == copy.names[std::distance(contacts.names.begin(),it)]) continue;
        else {
          auto loc { std::find(copy.names.begin(),copy.names.end(), *it) };
          contacts.numbers[std::distance(contacts.names.begin(),it)] = copy.numbers[std::distance(copy.names.begin(),loc)];
        }
      }
    }


/**
 * Fetch a contact name from storage given a number.
 */
    std::string get_name_by_number(storage &contacts, number_t number) {
      auto found{std::find(contacts.numbers.begin(), contacts.numbers.end(), number)};
      if (found == contacts.numbers.end()) return "";
      return contacts.names[std::distance(contacts.numbers.begin(), found)];
    }
}