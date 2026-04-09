#include <stdio.h>
#include <stdlib.h>

struct system_t {
	int n, m, start_x, start_y, t;
	char **maze, *instructions;
};

void allocate_memory(struct system_t *system)
{
	system->maze = malloc(system->n * sizeof(char *));
	for (int i = 0; i < system->n; i++)
		system->maze[i] = malloc(system->m * sizeof(char));
}

void initialize(struct system_t *system)
{
	scanf("%d", &system->n);
	scanf("%d", &system->m);
	allocate_memory(system);
	int temp;
	for (int i = 0; i < system->n; i++)
		for (int j = 0; j < system->m; j++) {
			scanf("%d", &temp);
			system->maze[i][j] = (char)temp;
		}
	scanf("%d", &system->start_x);
	scanf("%d", &system->start_y);
	scanf("%d", &system->t);
	system->instructions = malloc(system->t * sizeof(char));
	for (int i = 0; i < system->t; i++) {
		scanf("%d", &temp);
		system->instructions[i] = temp;
	}
}

int is_repeat_instr(char instr)
{
	return (instr & 0x80) == 0;
}

char get_repetitions(char instr)
{
	// get only bits 2, 3, 4
	char a = (instr >> 4) & 0x07;
	if (a == 0)
		return 1;
	return (instr >> 4) & 0x07;
}

char get_last_four(char instr)
{
	// get only last four bits
	return instr & 0x0f;
}

unsigned char get_direction(char instr)
{
	char last_four = get_last_four(instr);
	// check for 1000, 0100, 0010, 0001
	if (last_four == 0x08)
		return 0;
	if (last_four == 0x04)
		return 1;
	if (last_four == 0x02)
		return 2;
	return 3;
}

void try_move(int *x, int *y, int n, int m, char instr, char **maze)
{
	int dx[4] = {-1, 0, 1, 0};
	int dy[4] = {0, 1, 0, -1};
	char steps = get_repetitions(instr);
	unsigned char d = get_direction(instr);
	for (char i = 0; i < steps; i++) {
		if (*x + dx[d] >= m || *x + dx[d] < 0)
			return;
		if (*y + dy[d] >= n || *y + dy[d] < 0)
			return;
		// if there is a wall in the direction
		if ((maze[(*y)][(*x)] & 0x0f) & (instr & 0x0f))
			return;
		*x += dx[d];
		*y += dy[d];
	}
}

void follow_instructions(struct system_t *system)
{
	int n = system->n, m = system->m, t = system->t, x, y;
	char **maze = system->maze, *instructions = system->instructions;
	x = system->start_x;
	y = system->start_y;
	int current = 0;
	while (current < t) {
		char *instr = &instructions[current];
		if (is_repeat_instr(*instr)) {
			try_move(&x, &y, n, m, *instr, maze);
			current++;
		} else {
			// repetitions here mean how much to go back
			current -= get_repetitions(*instr);
			if (current < 0)
				current = 0;
			// set first four bits to 0001 (repeat 1 time)
			*instr |= 0x10;
			*instr &= 0x1f;
		}
	}
	printf("(%d, %d)", x, y);
}

void free_system(struct system_t *system)
{
	for (int i = 0; i < system->n; i++)
		free(system->maze[i]);
	free(system->maze);
	free(system->instructions);
	free(system);
}

int main()
{
	struct system_t *system = malloc(sizeof(struct system_t));
	initialize(system);
	follow_instructions(system);
	free_system(system);
	return 1;
}
