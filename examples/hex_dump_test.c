#include <stdint.h>
#include <stdlib.h>

#include "toolbox/hex_dump.h"
#include "toolbox/log.h"

static char __TestString__[] = "Hello dump world!";

int32_t main()
{
  LOG_INFO("db string:");
  db(__TestString__, sizeof(__TestString__));

  LOG_INFO("dw string:");
  dw(__TestString__, sizeof(__TestString__));

  LOG_INFO("dd string:");
  dd(__TestString__, sizeof(__TestString__));

  LOG_INFO("dq string:");
  dq(__TestString__, sizeof(__TestString__));

  LOG_INFO("db main:");
  db((void*)main, 0x20);

  LOG_INFO("dw main:");
  dw((void*)main, 0x20);

  LOG_INFO("dd main:");
  dd((void*)main, 0x20);

  LOG_INFO("dq main:");
  dq((void*)main, 0x20);

  return EXIT_SUCCESS;
}
