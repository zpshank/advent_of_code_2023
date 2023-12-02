#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_VALUES 10

const char* str_numbers[10] = {
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

int number_value(const char* s, int s_len) {
	for(int i = 0; i < 10; i++) {
		if (strncmp(s, str_numbers[i], strlen(str_numbers[i])) == 0) {
			return i;
		}
	}

	return -1;
}

int parse_numbers(const char* line, int line_len, int* out) {

	int found = 0;

	for (int i = 0; i < line_len; i++) {
		char c = line[i];

		if (isdigit(c)) {

			// Compute digit value
			out[found] = c - '0';
			found++;

		} else if (isalpha(c)) {

			// Compute potential string value
			int v = number_value(line + i, line_len - i);
			if (v >= 0) {
				out[found] = v;
				found++;
			}
		}
	}

	return found;

}

int parse_calibration(const char* line, size_t len) {

	int values[MAX_VALUES] = {0};
	int count = parse_numbers(line, len, values);
	if (count == 0) {
		return 0;
	}

	int first = values[0];
	int second = values[count - 1];

	return (first * 10) + second;
}

int main(int argc, const char** argv) {

	FILE* f = fopen(argv[1], "r");

	int sum = 0;

	char* line = NULL;
	size_t s = 0;
	while(!feof(f)) {
		int line_len = getline(&line, &s, f);
		
		int c = parse_calibration(line, line_len);
		sum += c;

	}

	printf("%d\n", sum);

	return 0;
}
