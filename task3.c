#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_SIZE 64

struct system_t {
	int n;
	void *array;
	int *positions;
	int array_size, indices_size;
};

void resize_array(struct system_t *system, int new_size)
{
	int size = system->array_size;
	if (size < new_size) {
		void *temp = realloc(system->array, 2 * new_size * sizeof(char));
		if (temp)
			system->array = temp;
	}
}

void print(struct system_t *system, int index)
{
	int current = system->positions[index];
	unsigned char *array = (unsigned char *)system->array;
	unsigned char type = array[current];
	current++;
	switch (type) {
	// print char
	case 1:
		printf("%c\n", array[current]);
		return;
	// print signed int
	case 2:
		printf("%d\n", *(int *)&array[current]);
		return;
	// print string
	case 3:
		printf("\"%s\"\n", &array[current]);
		return;
	// print 8 bit hexa
	case 4:
		printf("0x%02X\n", *(uint8_t *)&array[current]);
		return;
	// print 16 bit hexa
	case 5:
		printf("0x%04X\n", *(uint16_t *)&array[current]);
		return;
	default:
		return;
	}
}

struct system_t *initialize()
{
	struct system_t *system;
	system = malloc(1 * sizeof(struct system_t));
	system->array = malloc(INITIAL_SIZE * sizeof(char));
	system->array_size = INITIAL_SIZE;
	return system;
}

void read_values(struct system_t *system)
{
	int current = 0;
	unsigned char *array = system->array;
	for (int i = 0; i < system->n; i++) {
		system->positions[i] = current;
		unsigned char type;
		scanf("%hhu", &type);
		scanf(" ");
		resize_array(system, system->array_size + 1);
		array = system->array;
		array[current++] = type;
		// i declare here since apparently declaration
		// after a label is a C23 extension
		int a, size;
		switch (type) {
		// read char
		case 1:
			resize_array(system, system->array_size + 1);
			array = system->array;
			scanf("%c", &array[current]);
			system->array_size++;
			current++;
			break;
		// read signed int
		case 2:
			scanf("%d", &a);
			resize_array(system, system->array_size + 4);
			array = system->array;
			memcpy(&array[current], &a, 4);
			system->array_size += 4;
			current += 4;
			break;
		// string
		case 3:
			scanf("%d", &size);
			scanf(" ");
			if (size == 0) {
				scanf("\"\"");
				array[current++] = '\0';
				system->array_size++;
				break;
			}
			resize_array(system, system->array_size + size + 1);
			array = system->array;
			for (int i = 0; i < size; i++)
				scanf("%c", &array[current++]);
			array[current++] = '\0';
			system->array_size += size + 1;
			break;
		// 8 bit hexa
		case 4:
			resize_array(system, system->array_size + 1);
			array = system->array;
			scanf("%hhx", &array[current++]);
			system->array_size++;
			break;
		// 16 bit hexa
		case 5:
			resize_array(system, system->array_size + 2);
			array = system->array;
			scanf("%hx", (short int *)&array[current]);
			system->array_size += 2;
			current += 2;
			break;
		default:
			break;
	}
	}
}

void free_memory(struct system_t *system)
{
	free(system->positions);
	free(system->array);
	free(system);
}

int main()
{
	struct system_t *system;
	int num_indices, index;
	system = initialize();
	scanf("%d", &system->n);
	system->positions = malloc(system->n * sizeof(int));
	read_values(system);
	scanf("%d", &num_indices);
	for (int i = 0; i < num_indices; i++) {
		scanf("%d", &index);
		print(system, index);
	}
	free_memory(system);
	return 0;
}
