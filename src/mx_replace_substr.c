#include <libmx.h>

char *mx_replace_substr(const char *str, const char *sub, const char *replace)
{
	if (!str || !sub || !replace || mx_strlen(str) <= mx_strlen(sub))
		return NULL;

	int len = mx_strlen(str) + mx_count_substr(str, sub) * (mx_strlen(replace) - mx_strlen(sub));
	char *res = mx_strnew(len);
	int i = 0;

	while (*str)
	{
		if (!mx_strcmp(str, sub))
		{
			str += mx_strlen(sub);
			for (int j = 0; replace[j]; j++)
			{
				res[i++] = replace[j];
			}
		}
		else
		{
			res[i++] = *str++;
		}
	}

	return res;
}
