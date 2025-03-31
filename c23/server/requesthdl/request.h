#ifndef SERVER_REQUEST_H
#define SERVER_REQUEST_H

struct request {
  long id;
  // Rest of the request fields
  int kind;
  char url[80];
  int data;
  /*...*/
};

typedef struct request request_t;

void receive_request(request_t *req);
void reply_request(request_t *req);

#endif // REQUEST_H
