# C String Builder

There are many use cases for a String Builder in C, especially when iteratively
constructing highly interpolated strings. For example, building a complex SQL
query, or rendering HTML.

This brief implementation uses a dynamically allocated, linked-list to store
string fragments in `O(k)` - where `k` is the length of the inserted string
fragment.

A concatenated output string can be generated or regenerated at any point in
`O(n)` - where `n` is the total length of all appended string fragments.

This substancially defeats traditional, iterative concatentation which runs in
`O(n^2)`.

This implementation is not thread-safe.

## Example

```c
// create an empty string builder
StringBuilder *sb = sb_create();
char *str = NULL;

// append some strings
sb_appendf(sb, "What is your name?\n -> %s\n\n", "Sir Lancelot, of Camelot");
sb_appendf(sb, "What is your quest?\n -> %s\n\n", "To seek the Holy Grail");
sb_appendf(sb, "What is your favorite color?\n -> %s\n\n", "Blue");
sb_append(sb, "Right, off you go");

// print
str = sb_concat(sb)
puts(str);

// clean up
free(str);
sb_free(sb);
```

Output:

```plain
What is your name?
 -> Sir Lancelot, of Camelot

What is your quest?
 -> To seek the Holy Grail

What is your favorite color?
 -> Blue

Right, off you go
```
