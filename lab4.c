// Author: Dylan Chohan
// Created on: OCt 11, 2026
//

// #define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 128
#define EXTRA_SIZE 256
#define handle_error(msg)                                                                          \
  do {                                                                                             \
    perror(msg);                                                                                   \
    exit(EXIT_FAILURE);                                                                            \
  } while (0)

// struct for each block
struct header {
  uint64_t size;
  struct header *next;
};

// print function to help print the block
void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len =
      snprintf(buf, BUF_SIZE, format,
               data_size == sizeof(uint64_t) ? (void *)*(uint64_t *)data : *(void **)data);

  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  // increase heap size
  void *start = sbrk(EXTRA_SIZE);

  // create each block
  struct header *first = (struct header *)start;
  struct header *second = (struct head *)((char *)start + BUF_SIZE);

  // initialize each block
  first->size = BUF_SIZE;
  first->next = NULL;

  second->size = BUF_SIZE;
  second->next = first;

  // fill the blocks with byte values
  size_t data_size = BUF_SIZE - sizeof(struct header);
  memset(first + 1, 0, data_size);
  memset(second + 1, 1, data_size);

  // print out the data about each block
  print_out("first block:    %p\n", &first, sizeof(first));
  print_out("second block:    %p\n", &second, sizeof(second));
  print_out("first block size:    %lu\n", &first->size, sizeof(first->size));
  print_out("first block next:    %p\n", &first->next, sizeof(first->next));
  print_out("second block size:    %lu\n", &second->size, sizeof(second->size));
  print_out("second block next:    %p\n", &second->next, sizeof(second->next));

  // starting the data after the header
  uint8_t *data1 = (uint8_t *)(first + 1);
  uint8_t *data2 = (uint8_t *)(second + 1);

  // print out each byte in first block
  for (size_t i = 0; i < data_size; i++) {
    // put the byte in a bigger data type to use print_out()
    uint64_t newData1 = data1[i];
    print_out("%lu\n", &newData1, sizeof(newData1));
  }

  // print out each byte for the second block
  for (size_t i = 0; i < data_size; i++) {
    // same as in the for loop for first block
    uint64_t newData2 = data2[i];
    print_out("%lu\n", &newData2, sizeof(newData2));
  }

  return 0;
}
