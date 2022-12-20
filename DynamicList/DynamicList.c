#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <windows.h>

struct aircraft
{
	char name[128];
	char type[128];
	char created_in[128];

	double takeoff; // in meters
};

struct node
{
	struct node *next;
	struct node *prev;
	struct aircraft _aircraft;
};

struct node *push_list(struct node *head, struct aircraft *item)
{
	struct node *new_head = calloc(1, sizeof(struct node));
	assert(new_head != NULL);

	memcpy(&new_head->_aircraft, item, sizeof(struct aircraft));

	if (head) head->prev = new_head;

	new_head->next = head;
	return new_head;
}

void swap_nodes(struct node *head)
{
	struct node *tail = head;
	for (; tail->next; tail = tail->next);
	
	struct aircraft tmp;
	memcpy(&tmp, &tail->_aircraft, sizeof(struct aircraft));
	memcpy(&tail->_aircraft , &head->_aircraft, sizeof(struct aircraft));
	memcpy(&head->_aircraft, &tmp, sizeof(struct aircraft));
}

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

void display_as_table(struct node *head)
{
	set_cursor_position(get_cursor_position().X, get_cursor_position().Y);

	puts("+----------+-----------------+---------------------+-------------------+----------------+");
	puts("|          |                 |                  Takeoff                |                |");
	puts("|   Name   |  Aircraft type  +---------------------+-------------------+   Created in   |");
	puts("|          |                 |      kilometers     |      meters       |                |");
	puts("+----------+-----------------+---------------------+-------------------+----------------+");

	for (struct node *item = head; item; item = item->next)
	{
		struct aircraft *tmp = &item->_aircraft;
		COORD current_pos = get_cursor_position();

		printf("| ");
		printf("%s", tmp->name);
		set_cursor_position(current_pos.X + 11, current_pos.Y);
		printf("| ");
		printf("%s", tmp->type);
		set_cursor_position(current_pos.X + 29, current_pos.Y);
		printf("| ");
		printf("%lf", tmp->takeoff / 1000);
		set_cursor_position(current_pos.X + 51, current_pos.Y);
		printf("| ");
		printf("%lf", tmp->takeoff);
		set_cursor_position(current_pos.X + 71, current_pos.Y);
		printf("| ");
		printf("%s", tmp->created_in);
		set_cursor_position(current_pos.X + 88, current_pos.Y);
		puts("|");
	}

	puts("+----------+-----------------+---------------------+-------------------+----------------+");
}

int main()
{
	struct node *head = { 0 };
	struct aircraft tmp = { 0 };

	for (int counter = 0;; ++counter)
	{
		printf("Name: ");
		scanf_s("%s", tmp.name, (unsigned int)sizeof(tmp.name));
		printf("Aircraft type: ");
		scanf_s("%s", tmp.type, (unsigned int)sizeof(tmp.type));
		printf("Takeoff (in meters): ");
		scanf_s("%lf", &tmp.takeoff);
		printf("Created in: ");
		scanf_s("%s", tmp.created_in, (unsigned int)sizeof(tmp.created_in));

		puts("==========================");

		head = push_list(head, &tmp);

		if (counter >= 5 - 1)
		{
			int answer;
lp:
			printf("Continue? (1/0): ");
			scanf_s("%i", &answer);

			if (answer == 0)
			{
				break;
			}

			if (answer != 1)
			{
				puts("Incorrect data entered");
				goto lp;
			}
		}
	}

	display_as_table(head);
	puts("Swapping first and last element");
	swap_nodes(head);
	display_as_table(head);
	puts("The program worked correctly");

	return 0;
}