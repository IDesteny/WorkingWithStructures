#include <stdio.h>
#include <assert.h>
#include <windows.h>

struct aircraft
{
	char name[128];
	char type[128];
	char created_in[128];

	double takeoff_m;
	double takeoff_km;
};

void set_cursor_position(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { x, y });
}

COORD get_cursor_position()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);
	return cbsi.dwCursorPosition;
}

void show_table(struct aircraft *aircrafts, int size)
{
	set_cursor_position(get_cursor_position().X, get_cursor_position().Y);

	puts("+----------+-----------------+---------------------+-------------------+----------------+");
	puts("|          |                 |                  Takeoff                |                |");
	puts("|   Name   |  Aircraft type  +---------------------+-------------------+   Created in   |");
	puts("|          |                 |      kilometers     |      meters       |                |");
	puts("+----------+-----------------+---------------------+-------------------+----------------+");

	for (int i = 0; i < size; ++i)
	{
		COORD current_pos = get_cursor_position();

		printf("| ");
		printf("%s", aircrafts[i].name);
		set_cursor_position(current_pos.X + 11, current_pos.Y);
		printf("| ");
		printf("%s", aircrafts[i].type);
		set_cursor_position(current_pos.X + 29, current_pos.Y);
		printf("| ");
		printf("%lf", aircrafts[i].takeoff_km);
		set_cursor_position(current_pos.X + 51, current_pos.Y);
		printf("| ");
		printf("%lf", aircrafts[i].takeoff_m);
		set_cursor_position(current_pos.X + 71, current_pos.Y);
		printf("| ");
		printf("%s", aircrafts[i].created_in);
		set_cursor_position(current_pos.X + 88, current_pos.Y);
		puts("|");
	}

	puts("+----------+-----------------+---------------------+-------------------+----------------+");
}

void swap_table(struct aircraft *aircrafts, int size)
{
	struct aircraft tmp;

	memcpy(&tmp, aircrafts, sizeof(struct aircraft));
	memcpy(aircrafts, &aircrafts[size - 1], sizeof(struct aircraft));
	memcpy(&aircrafts[size - 1], &tmp, sizeof(struct aircraft));
}

int main()
{
	puts("+----------+-----------------+---------------------+-------------------+----------------+");
	puts("|          |                 |                  Takeoff                |                |");
	puts("|   Name   |  Aircraft type  +---------------------+-------------------+   Created in   |");
	puts("|          |                 |      kilometers     |      meters       |                |");
	puts("+----------+-----------------+---------------------+-------------------+----------------+");

	struct aircraft aircrafts[2] = { 0 };
	int size = sizeof(aircrafts) / sizeof(*aircrafts);

	for (int i = 0; i < size; ++i)
	{
		printf("| ");
		scanf_s("%s", aircrafts[i].name, (unsigned int)sizeof(aircrafts[i].name));
		set_cursor_position(get_cursor_position().X + 11, get_cursor_position().Y - 1);
		printf("| ");
		scanf_s("%s", aircrafts[i].type, (unsigned int)sizeof(aircrafts[i].type));
		set_cursor_position(get_cursor_position().X + 29, get_cursor_position().Y - 1);
		printf("| ");
		scanf_s("%lf", &aircrafts[i].takeoff_km);
		set_cursor_position(get_cursor_position().X + 51, get_cursor_position().Y - 1);
		printf("| ");
		scanf_s("%lf", &aircrafts[i].takeoff_m);
		set_cursor_position(get_cursor_position().X + 71, get_cursor_position().Y - 1);
		printf("| ");
		scanf_s("%s", aircrafts[i].created_in, (unsigned int)sizeof(aircrafts[i].created_in));
		set_cursor_position(get_cursor_position().X + 88, get_cursor_position().Y - 1);
		puts("|");
	}

	puts("+----------+-----------------+---------------------+-------------------+----------------+");

	swap_table(aircrafts, size);
	show_table(aircrafts, size);
}