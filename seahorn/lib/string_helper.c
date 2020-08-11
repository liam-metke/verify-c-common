#include <seahorn/seahorn.h>
#include <string_helper.h>
#include <proof_allocators.h>

struct aws_string *ensure_string_is_allocated(size_t len) {
    struct aws_string *str = bounded_malloc(sizeof(struct aws_string) + MAX_STRING_LEN + 1);
    assume(len <= MAX_STRING_LEN);

    /* Fields are declared const, so we need to copy them in like this */
    *(struct aws_allocator **)(&str->allocator) = nd_bool() ? nd_voidp() : NULL;
    *(size_t *)(&str->len) = len;
    *(uint8_t *)&str->bytes[len] = '\0';
    return str;
}

struct aws_string *ensure_string_is_allocated_bounded_length(size_t max_size) {
    size_t len = nd_size_t();
    assume(len < max_size);
    return ensure_string_is_allocated(len);
}