/**
 * \file
 * Functions and types for CRC checks.
 *
 * Generated on Mon Oct 10 15:32:41 2022
 * by pycrc v0.9.2, https://pycrc.org
 * using the configuration:
 *  - Width         = 32
 *  - Poly          = 0x1edc6f41
 *  - XorIn         = 0xffffffff
 *  - ReflectIn     = True
 *  - XorOut        = 0xffffffff
 *  - ReflectOut    = True
 *  - Algorithm     = table-driven
 *
 * This file defines the functions kafka_crc32c_init(), kafka_crc32c_update() and kafka_crc32c_finalize().
 *
 * The kafka_crc32c_init() function returns the initial \c crc value and must be called
 * before the first call to kafka_crc32c_update().
 * Similarly, the kafka_crc32c_finalize() function must be called after the last call
 * to kafka_crc32c_update(), before the \c crc is being used.
 * is being used.
 *
 * The kafka_crc32c_update() function can be called any number of times (including zero
 * times) in between the kafka_crc32c_init() and kafka_crc32c_finalize() calls.
 *
 * This pseudo-code shows an example usage of the API:
 * \code{.c}
 * kafka_crc32c_t crc;
 * unsigned char data[MAX_DATA_LEN];
 * size_t data_len;
 *
 * crc = kafka_crc32c_init();
 * while ((data_len = read_data(data, MAX_DATA_LEN)) > 0) {
 *     crc = kafka_crc32c_update(crc, data, data_len);
 * }
 * crc = kafka_crc32c_finalize(crc);
 * \endcode
 */
#ifndef CRC_H
#define CRC_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * The definition of the used algorithm.
 *
 * This is not used anywhere in the generated code, but it may be used by the
 * application code to call algorithm-specific code, if desired.
 */
#define CRC_ALGO_TABLE_DRIVEN 1


/**
 * The type of the CRC values.
 *
 * This type must be big enough to contain at least 32 bits.
 */
typedef uint_fast32_t kafka_crc32c_t;


/**
 * Calculate the initial crc value.
 *
 * \return     The initial crc value.
 */
static inline kafka_crc32c_t kafka_crc32c_init(void)
{
    return 0xffffffff;
}


/**
 * Update the crc value with new data.
 *
 * \param[in] crc      The current crc value.
 * \param[in] data     Pointer to a buffer of \a data_len bytes.
 * \param[in] data_len Number of bytes in the \a data buffer.
 * \return             The updated crc value.
 */
kafka_crc32c_t kafka_crc32c_update(kafka_crc32c_t crc, const void *data, size_t data_len);


/**
 * Calculate the final crc value.
 *
 * \param[in] crc  The current crc value.
 * \return     The final crc value.
 */
static inline kafka_crc32c_t kafka_crc32c_finalize(kafka_crc32c_t crc)
{
    return crc ^ 0xffffffff;
}


#ifdef __cplusplus
}           /* closing brace for extern "C" */
#endif

#endif      /* CRC_H */
