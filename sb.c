#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <strings.h>
#include "sb.h"

StringBuilder *sb_create()
{
	StringBuilder *sb = (StringBuilder*) malloc(sizeof(StringBuilder));
	sb->root = NULL;
	sb->trunk = NULL;
	sb->length = 0;

	return sb;
}

int sb_append(StringBuilder *sb, const char *str)
{
	int				i = 0;
	int				length = 0;
	StringFragment	*frag = NULL;

	if (NULL == str || '\0' == *str)
		return sb->length;

	length = strlen(str);
	frag = (StringFragment*) malloc(sizeof(StringFragment) + (sizeof(char) * length));
	if (NULL == frag)
		return SB_FAILURE;

	frag->next = NULL;
	frag->length = length;
	memcpy((void*) &frag->str, (const void*) str, sizeof(char) * (length + 1));

	sb->length += length;
	if (NULL == sb->root)
		sb->root = frag;
	else
		sb->trunk->next = frag;

	sb->trunk = frag;

	return sb->length;
}

int sb_appendf(StringBuilder *sb, const char *format, ...)
{
	int			rc = 0;
	char		buf[SB_MAX_FRAG_LENGTH];
	va_list		args;

	va_start (args, format);
	rc = vsnprintf(&buf[0], SB_MAX_FRAG_LENGTH, format, args);
	va_end(args);

	if (0 > rc)
		return SB_FAILURE;

	return sb_append(sb, buf);
}

char *sb_concat(StringBuilder *sb)
{
	char			*buf = NULL;
	char			*c = NULL;
	StringFragment	*frag = NULL;

	buf = (char *) malloc((sb->length + 1) * sizeof(char));
	if (NULL == buf)
		return NULL;

	c = buf;
	for (frag = sb->root; frag; frag = frag->next) {
		memcpy(c, &frag->str, sizeof(char) * frag->length);
		c += frag->length;
	}

	*c = '\0';

	return buf;
}

void sb_free(StringBuilder *sb)
{
	StringFragment *frag = NULL;
	StringFragment *next = NULL;

	frag = sb->root;
	while(frag) {
		next = frag->next;
		free(frag);
		frag = next;
	}

	free(sb);
}
