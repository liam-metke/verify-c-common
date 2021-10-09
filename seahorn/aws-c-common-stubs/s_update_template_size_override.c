/**
 * FUNCTION: s_update_template_size
 *
 * Seahorn does not support double/float semantics;
 * This function overrides the original implementation of the
 * s_update_template_size function from hash_table.c by replacing floating
 * point multiplication with nd_size_t;
 * max_load = min { max_load_factor * size, size - 1 }
 * so its ok to just set it to a non-det int such that:
 * max_load < size
 * and max_load > entry_count
 * not that new max_load needs to be strictly greater than current
 * entry_count since it's possible for hash_table functions to increase
 * entry_count after updating template size; in fact, a common use case
 * for this function is to expand the size and max_load of a hash_table,
 * so it's wrong to have max_load >= entry_count as a post-condition
 */

#include <aws/common/hash_table.h>
#include <aws/common/math.h>
#include <aws/common/private/hash_table_impl.h>
#include <nondet.h>
#include <seahorn/seahorn.h>

#include <hash_table_helper.h>
#include <stdlib.h>

int s_update_template_size(struct hash_table_state *template,
                           size_t expected_elements) {
  size_t min_size = expected_elements;

  if (min_size < 2) {
    min_size = 2;
  }

  /* size is always a power of 2 */
  size_t size;
  if (aws_round_up_to_power_of_two(min_size, &size)) {
    return AWS_OP_ERR;
  }

  /* Update the template once we've calculated everything successfully */
#ifdef __SEAHORN__
  template->size = size;
  template->max_load = nd_size_t();
  assume(template->max_load < size);
  assume(template->max_load > template->entry_count);
#else
  template->max_load =
      (size_t)(template->max_load_factor * (double)template->size);
  /* Ensure that there is always at least one empty slot in the hash table */
  if (template->max_load >= size) {
    template->max_load = size - 1;
  }
#endif

  /* Since size is a power of 2: (index & (size - 1)) == (index % size) */
  template->mask = size - 1;

  return AWS_OP_SUCCESS;
}