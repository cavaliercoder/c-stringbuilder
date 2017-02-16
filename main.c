#include <stdlib.h>
#include <stdio.h>
#include "sb.h"

int main(int argc, char *argv[])
{
	int				i = 0;
	char			*str = NULL;
	StringBuilder	*sb = sb_create();

	for (i = 1; i < argc; i++) {
		if (1 < i)
			sb_append(sb, "->");
		sb_appendf(sb, "[%s]", argv[i]);
		puts(str = sb_concat(sb));
		free(str);
	}
	sb_free(sb);
}
