#ifndef __TOOLBOX_HEX_DUMP_H__
#define __TOOLBOX_HEX_DUMP_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void db(
  void*    data,
  uint32_t num_bytes);

void db_custom(
  void*    data,
  uint32_t num_bytes,
  uint32_t num_columns,
  uint32_t num_columns_per_pack,
  char*    separator);

void dd(
  void*    data,
  uint32_t num_bytes);

void dd_custom(
  void*    data,
  uint32_t num_bytes,
  uint32_t num_columns);

void dq(
  void*    data,
  uint32_t num_bytes);

void dq_custom(
  void*    data,
  uint32_t num_bytes,
  uint32_t num_columns);

void dw(
  void*    data,
  uint32_t num_bytes);

void dw_custom(
  void*    data,
  uint32_t num_bytes,
  uint32_t num_columns);

#ifdef __cplusplus
}
#endif

#endif // __TOOLBOX_HEX_DUMP_H__
