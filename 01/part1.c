#include <stdio.h>
#include <ctype.h>

int parse_calibration(const char* line, size_t len) {

	int first = 0;
	int second = 0;

	// Find first digit
	for (int i = 0; i < len; i++) {
		char c = line[i];
		if (isdigit(c)) {
			first = c - '0';
			break;
		}
	}

	// Find last digit
	for (int i = len-1; i >= 0; i--) {
		char c = line[i];
		if (isdigit(c)) {
			second = c - '0';
			break;
		}
	}

	printf("Found: %d%d\n", first, second);

	return (first * 10) + second;

}

int main(const int argc, const char **argv) {

	FILE *f = fopen(argv[1], "r");

	int sum = 0;

	char* line = NULL;
	size_t limit = 0;
	size_t len = getline(&line, &limit, f);
	while (!feof(f)) {
		int v = parse_calibration(line, len);
		sum += v;
		len = getline(&line, &limit, f);
	}

	printf("Sum: %d\n", sum);

	return 0;
}

