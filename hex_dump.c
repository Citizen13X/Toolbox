#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "toolbox/common.h"
#include "toolbox/hex_dump.h"
#include "toolbox/log.h"

#define DEFAULT_DB_NB_COLUMNS          16
#define DEFAULT_DB_NB_COLUMNS_PER_PACK 4
#define DEFAULT_DB_PACK_SEPARATOR      "   "
#define DEFAULT_DD_NB_COLUMNS          4
#define DEFAULT_DQ_NB_COLUMNS          2
#define DEFAULT_DW_NB_COLUMNS          8

void db(void* data, uint32_t num_bytes)
{
  db_custom(data,
            num_bytes,
            DEFAULT_DB_NB_COLUMNS,
            DEFAULT_DB_NB_COLUMNS_PER_PACK,
            DEFAULT_DB_PACK_SEPARATOR);
}

void db_custom(
  void*    data,
  uint32_t num_bytes,
  uint32_t num_columns,
  uint32_t num_columns_per_pack,
  char*    separator)
{
  char     c         = 0;
  char     value[3]  = { 0 };
  char*    Ascii     = NULL;
  char*    Hex       = NULL;
  uint32_t HexLength = 0;

  if (!IS_VALID_POINTER(data) || IS_ZERO(num_bytes))
  {
    return;
  }

  if (IS_ZERO(num_columns))
  {
    num_columns = DEFAULT_DB_NB_COLUMNS;
  }
  if (IS_ZERO(num_columns_per_pack))
  {
    num_columns_per_pack = DEFAULT_DB_NB_COLUMNS_PER_PACK;
  }
  if (!IS_VALID_POINTER(separator))
  {
    separator = DEFAULT_DB_PACK_SEPARATOR;
  }

  Ascii = (char*)malloc(2 * num_columns + 1);
  if (!IS_VALID_POINTER(Ascii))
  {
    goto CLEANUP;
  }
  HexLength =
    (num_columns * sizeof(value)) +
    ((uint32_t)strlen(separator) * (num_columns / num_columns_per_pack)) + 1;
  Hex = (char*)malloc(HexLength);
  if (!IS_VALID_POINTER(Hex))
  {
    goto CLEANUP;
  }

  for (uint32_t row_index = 0; row_index < num_bytes; row_index += num_columns)
  {
    memset(Ascii, 0, num_columns + 1);
    memset(Hex, 0, HexLength);
    for (uint32_t column_index = 0, adjust = 0; column_index < num_columns;
         ++column_index)
    {
      // Process HEX view
      if ((row_index + column_index) < num_bytes)
      {
        sprintf(value,
                "%02X",
                (uint8_t)(uintptr_t)POI(data, row_index + column_index) &
                  UINT8_MAX);
        strcat(Hex, value);
      }
      else
      {
        strcat(Hex, "  ");
      }
      if (!IS_ZERO((column_index + 1) % num_columns_per_pack) ||
          (column_index == (num_columns - 1)))
      {
        strcat(Hex, " ");
      }
      else
      {
        strcat(Hex, separator);
      }

      // Process ASCII view
      if ((row_index + column_index) >= num_bytes)
      {
        continue;
      }
      c = (char)(uintptr_t)POI(data, row_index + column_index) & UINT8_MAX;
      if (' ' > c || '~' < c)
      {
        Ascii[column_index + adjust] = '.';
      }
      else
      {
        if ('%' == c)
        {
          Ascii[column_index + adjust] = '%';
          adjust++;
        }
        Ascii[column_index + adjust] = c;
      }
    }

    LOG_RAW(PFx " | %s |%s|", FP(PTR(data, row_index)), Hex, Ascii);
  }

CLEANUP:
  free(Ascii);
  free(Hex);

  return;
}

void dd(void* data, uint32_t num_bytes)
{
  dd_custom(data, num_bytes, DEFAULT_DD_NB_COLUMNS);
}

void dd_custom(void* data, uint32_t num_bytes, uint32_t num_columns)
{
  char     value[11] = { 0 };
  char*    Hex       = NULL;
  uint32_t HexLength = 0;
  uint32_t ValueSize = 4;

  if (!IS_VALID_POINTER(data))
  {
    return;
  }
  if (IS_ZERO(num_bytes))
  {
    return;
  }

  if (IS_ZERO(num_columns))
  {
    num_columns = DEFAULT_DD_NB_COLUMNS;
  }

  HexLength = (num_columns * sizeof(value)) + 1;
  Hex       = (char*)malloc(HexLength);
  if (!IS_VALID_POINTER(Hex))
  {
    goto CLEANUP;
  }

  for (uint32_t row_index = 0; row_index < num_bytes;
       row_index += (num_columns * ValueSize))
  {
    memset(Hex, 0, HexLength);
    for (uint32_t column_index = 0;
         (column_index < num_columns) &&
         (row_index + (column_index * ValueSize) < num_bytes);
         ++column_index)
    {
      // Process HEX view
      sprintf(
        value,
        "%08X  ",
        (uint32_t)(uintptr_t)
            POI(data, row_index + (column_index * ValueSize)) &
          UINT32_MAX);
      strcat(Hex, value);
    }

    LOG_RAW(PFx " | %s", FP(PTR(data, row_index)), Hex);
  }

CLEANUP:
  free(Hex);

  return;
}

void dq(void* data, uint32_t num_bytes)
{
  dq_custom(data, num_bytes, DEFAULT_DQ_NB_COLUMNS);
}

void dq_custom(void* data, uint32_t num_bytes, uint32_t num_columns)
{
  char     value[20] = { 0 };
  char*    Hex       = NULL;
  uint32_t HexLength = 0;
  uint32_t ValueSize = 8;

  if (!IS_VALID_POINTER(data))
  {
    return;
  }
  if (IS_ZERO(num_bytes))
  {
    return;
  }

  if (IS_ZERO(num_columns))
  {
    num_columns = DEFAULT_DQ_NB_COLUMNS;
  }

  HexLength = (num_columns * sizeof(value)) + 1;
  Hex       = (char*)malloc(HexLength);
  if (!IS_VALID_POINTER(Hex))
  {
    goto CLEANUP;
  }

  for (uint32_t row_index = 0; row_index < num_bytes;
       row_index += (num_columns * ValueSize))
  {
    memset(Hex, 0, HexLength);
    for (uint32_t column_index = 0;
         (column_index < num_columns) &&
         (row_index + (column_index * ValueSize) < num_bytes);
         ++column_index)
    {
      // Process HEX view
      sprintf(
        value,
        PFX64 "  ",
        FP64(*(uint64_t*)PTR(data, row_index + (column_index * ValueSize))));
      strcat(Hex, value);
    }

    LOG_RAW(PFx " | %s", FP(PTR(data, row_index)), Hex);
  }

CLEANUP:
  free(Hex);

  return;
}

void dw(void* data, uint32_t num_bytes)
{
  dw_custom(data, num_bytes, DEFAULT_DW_NB_COLUMNS);
}

void dw_custom(void* data, uint32_t num_bytes, uint32_t num_columns)
{
  char     value[7]  = { 0 };
  char*    Hex       = NULL;
  uint32_t HexLength = 0;
  uint32_t ValueSize = 2;

  if (!IS_VALID_POINTER(data))
  {
    return;
  }
  if (IS_ZERO(num_bytes))
  {
    return;
  }

  if (IS_ZERO(num_columns))
  {
    num_columns = DEFAULT_DW_NB_COLUMNS;
  }

  HexLength = (num_columns * sizeof(value)) + 1;
  Hex       = (char*)malloc(HexLength);
  if (!IS_VALID_POINTER(Hex))
  {
    goto CLEANUP;
  }

  for (uint32_t row_index = 0; row_index < num_bytes;
       row_index += (num_columns * ValueSize))
  {
    memset(Hex, 0, HexLength);
    for (uint32_t column_index = 0;
         (column_index < num_columns) &&
         (row_index + (column_index * ValueSize) < num_bytes);
         ++column_index)
    {
      // Process HEX view
      sprintf(
        value,
        "%04X  ",
        (uint16_t)(uintptr_t)POI(data, row_index + (column_index * ValueSize)) &
          UINT16_MAX);
      strcat(Hex, value);
    }

    LOG_RAW(PFx " | %s", FP(PTR(data, row_index)), Hex);
  }

CLEANUP:
  free(Hex);

  return;
}
