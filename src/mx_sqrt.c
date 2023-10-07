#include <libmx.h>

int mx_sqrt(int x) {
	if (x <= 0) {
		return 0;
	}

	int left = 0;
	int right = x;
	int result = 0;

	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (mid <= x / mid) {
            left = mid + 1;
            result = mid;
        } else {
            right = mid - 1;
        }
	}

	if (result * result != x)
		return 0;

	return result;
}
