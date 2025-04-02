
#ifndef SERVER_REQUEST_HPP
#define SERVER_REQUEST_HPP
#include <random>
#include <string>

namespace server {

  class request {
  public:
    request() : request{0} {}
    request(long id_init) : id_(id_init) {}

    [[nodiscard]] long id() const { return id_; }
    void update_data(int value) { data +=value; }

    void process();
    void reply() const;

  private:
    long id_;
    // Rest of the request fields
    int kind = 0;
    std::string url{}; // NOLINT(*-redundant-member-init)
    int data = 0;
    /*...*/


  };

  request receive_request();

}// namespace server

#endif// SERVER_REQUEST_HPP
