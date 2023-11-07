#include <libmx.h>

unsigned long mx_hex_to_nbr(const char *hex) {
	if (hex == 0) {
		return 0;
	}

	unsigned long result = 0;

	for (int i = 0; hex[i] != '\0'; i++) {
		char c = hex[i];
		int isHexDigit = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');

		if (isHexDigit) {
			if (c >= '0' && c <= '9') {
				result = result * 16 + (c - '0');
			}
			else if (c >= 'a' && c <= 'f') {
				result = result * 16 + (c - 'a' + 10);
			}
			else {
				result = result * 16 + (c - 'A' + 10);
			}
		}
		else {
			return result;
		}
	}

	return result;
}
