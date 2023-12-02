#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_COUNT 3
#define COLOR_RED 0
#define COLOR_GREEN 1
#define COLOR_BLUE 2
#define MAX_SET_COUNT 10

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

const char* colors[] = {
	"red",
	"green",
	"blue"
};

typedef struct set_s {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} set_t;

typedef struct game_s {
	int id;
	size_t num_sets;
	set_t sets[MAX_SET_COUNT];
} game_t;

void print_set(const set_t* set) {
	printf("Red %d, Green: %d, Blue: %d\n",
			set->red,
			set->green,
			set->blue
	);
}

void print_game(const game_t* game) {
	printf("Game %d:\n", game->id);
	for (int i = 0; i < game->num_sets; i++) {
		print_set(game->sets + i);
	}
}


uint8_t color_id(const char* s) {

	for (uint8_t i = 0; i < COLOR_COUNT; i++) {
		if (strncmp(s, colors[i], strlen(colors[i])) == 0) {
			return i;
		}
	}

	return -1;
}

uint16_t color_and_count(const char* s, size_t s_len) {
	uint8_t count = 0;
	char color[16] = {0};

	sscanf(s, "%hhu %s", &count, color);

	uint8_t id = color_id(color);

	return (uint16_t) (id << 8) | count;
}

set_t parse_set(const char* s, size_t s_len) {
	char temp[80] = {0};
	strncpy(temp, s, 80);

	char* token = NULL;
	char* ctx = NULL;

	//Ex:3 blue, 4 red
	set_t ret = {0};
	for(token = strtok_r(temp, ",", &ctx);
			token;
			token = strtok_r(NULL, ",", &ctx)) {
		uint16_t cc = color_and_count(token, strlen(token));

		uint8_t id = cc >> 8 & 0xFF;
		uint8_t v = cc & 0xFF;

		switch(id) {
			case COLOR_RED:
				ret.red = v;
				break;
			case COLOR_GREEN:
				ret.green = v;
				break;
			case COLOR_BLUE:
				ret.blue = v;
				break;
		}
	}

	return ret;
}

game_t parse_game(const char* s, size_t s_len) {
	// Ex:Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
	game_t ret = {0};

	// Find Game ID
	sscanf(s, "Game %d:", &ret.id);

	// Loop through sets
	char* sets = strstr(s, ":") + 1;
	char temp[256] = {0};
	strncpy(temp, sets, 256);

	char* token = NULL;
	char* ctx = NULL;
	int count = 0;
	for(token = strtok_r(temp, ";", &ctx);
			token;
			token = strtok_r(NULL, ";", &ctx)) {
		set_t set = parse_set(token, strlen(token));
		ret.sets[count] = set;
		count++;
	}

	ret.num_sets = count;
	
	return ret;
}

int game_valid(const game_t* game) {

	for (int i = 0; i < game->num_sets; i++) {
		if ( 
				game->sets[i].red > MAX_RED ||
				game->sets[i].green > MAX_GREEN ||
				game->sets[i].blue > MAX_BLUE ) {
			return 0;
		}
	}

	return 1;
}

int main(int argc, char** argv) {

	FILE* f = fopen(argv[1], "r");

	int sum = 0;
	char buf[256] = {0};
	while(!feof(f) && fgets(buf, sizeof buf, f) != NULL) {
		if (strlen(buf) < 1) {
			continue;
		}

		game_t g = parse_game(buf, strlen(buf));

		print_game(&g);
		sum += game_valid(&g) ? g.id : 0;
	}

	printf("%d\n", sum);

	return 0;
}
