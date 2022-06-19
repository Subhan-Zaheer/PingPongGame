#include<iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

const int height = 20;
const int width = 40;

enum ball_direction
{

	Stop = 0, Right = 1, Left = 2, Up_right = 3, Down_right = 4, Up_left = 5, Down_left = 6

} direction;

int ball_x_coordinate;
int ball_y_coordinate;

int pad_1_y_coordinate[4];
int pad_2_y_coordinate[4];

int pad_1_x_coordinate;
int pad_2_x_coordinate;

bool gameOver = false;
bool movement = false;

int player_1_score = 0;
int player_2_score = 0;

void initial();
void structure();
void pad_movement();
void pad_logic();
void ball_movement();
void ball_logic();
void logic();
void pad_hit_logic();

int main()
{

	initial();

	while (!gameOver)

	{

		structure();
		pad_movement();
		logic();
		//Sleep(500) ;

	}

}

void initial()

{

	srand((unsigned)time(0));

	direction = Stop;

	int a = 9;

	ball_x_coordinate = width / 2;
	ball_y_coordinate = height / 2;

	for (int i = 0; i < 4; i++)
	{

		pad_1_y_coordinate[i] = a;
		pad_2_y_coordinate[i] = a++;

	}

	pad_1_x_coordinate = 1;
	pad_2_x_coordinate = width - 1;

}

void structure()

{

	system("cls");

	for (int i = 1; i < width + 2; i++)
		cout << "\xDC";

	cout << endl;

	for (int i = 1; i <= height; i++)

	{

		for (int j = 1; j <= width; j++)

		{

			if (j == 1)
				cout << "\xDD";

			if (i == ball_y_coordinate && j == ball_x_coordinate)
				cout << "O";

			else

			{

				bool print = false;

				for (int k = 0; k < 4; k++)
					if ((i == pad_1_y_coordinate[k] && j == pad_1_x_coordinate) || (i == pad_2_y_coordinate[k] && j == pad_2_x_coordinate))
					{

						cout << "\xB2";
						print = true;

					}

				if (!print)
					cout << " ";

			}

			if (j == width - 1)
				cout << "\xDE";

		}

		cout << endl;

	}

	for (int i = 1; i < width + 2; i++)
		cout << "\xDF";

}

void pad_movement()

{

	if (_kbhit())
		switch (_getch())
		{

		case 'w':
		case 'W':

			for (int i = 0; i < 4; i++)
				pad_1_y_coordinate[i]--;

			if (!movement)

			{

				direction = (ball_direction)((rand() % 6) + 1);
				movement = true;

			}



			break;

		case 's':
		case 'S':

			for (int i = 0; i < 4; i++)
				pad_1_y_coordinate[i]++;

			if (!movement)

			{

				direction = (ball_direction)((rand() % 6) + 1);
				movement = true;

			}

			break;

		case 'i':
		case 'I':

			for (int i = 0; i < 4; i++)
				pad_2_y_coordinate[i]--;

			if (!movement)

			{

				direction = (ball_direction)((rand() % 6) + 1);
				movement = true;

			}

			break;

		case 'k':
		case 'K':

			for (int i = 0; i < 4; i++)
				pad_2_y_coordinate[i]++;

			if (!movement)

			{

				direction = (ball_direction)((rand() % 6) + 1);
				movement = true;

			}

			break;

		default:

			if (!movement)

			{

				direction = (ball_direction)((rand() % 6) + 1);
				movement = true;

			}

			break;

		}

}

void pad_logic()

{

	pad_movement();

	int check_array_down[4] = { 17,18,19,20 };
	int check_array_up[4] = { 1,2,3,4 };

	for (int i = 0; i < 4; i++)

	{

		if (pad_1_y_coordinate[3] < 4)
			pad_1_y_coordinate[i] = check_array_up[i];

		else if (pad_1_y_coordinate[3] > 20)
			pad_1_y_coordinate[i] = check_array_down[i];

		if (pad_2_y_coordinate[3] < 4)
			pad_2_y_coordinate[i] = check_array_up[i];

		else if (pad_2_y_coordinate[3] > 20)
			pad_2_y_coordinate[i] = check_array_down[i];

	}

}

void ball_logic()

{

	pad_hit_logic();
	ball_movement();

	if (ball_x_coordinate == 0)
	{

		initial();
		player_2_score++;
		movement = false;

	}

	else if (ball_x_coordinate == width)

	{

		initial();
		player_1_score++;
		movement = false;

	}

	bool direction_change = false;

	if (ball_y_coordinate == 20 && direction == Down_left)
	{

		direction = Up_left;
		direction_change = true;

	}

	else if (ball_y_coordinate == 20 && direction == Down_right)
	{

		direction = Up_right;
		direction_change = true;

	}

	if (ball_y_coordinate == 1 && direction == Up_left)
	{

		direction = Down_left;
		direction_change = true;

	}

	else if (ball_y_coordinate == 1 && direction == Up_right)
	{

		direction = Down_right;
		direction_change = true;

	}

	if (direction_change)
		pad_hit_logic();

}

void ball_movement()

{

	switch (direction)

	{

	case Right:

		ball_x_coordinate++;

		break;

	case Left:

		ball_x_coordinate--;

		break;

	case Up_right:

		ball_y_coordinate--;
		ball_x_coordinate++;

		break;

	case Down_right:

		ball_y_coordinate++;
		ball_x_coordinate++;

		break;

	case Up_left:

		ball_y_coordinate--;
		ball_x_coordinate--;

		break;

	case Down_left:

		ball_y_coordinate++;
		ball_x_coordinate--;

		break;
	}

}

void pad_hit_logic()

{

	if (ball_x_coordinate - 1 == pad_1_x_coordinate && ball_y_coordinate == pad_1_y_coordinate[0])
	{

		if (direction == Left)
			direction = Up_right;

		else if (direction == Up_left)
			direction = Up_right;

		else
			direction = Up_right;

	}

	else if (ball_x_coordinate - 1 == pad_1_x_coordinate && ball_y_coordinate == pad_1_y_coordinate[1])
	{

		if (direction == Left)
			direction = Right;

		else if (direction == Down_left)
			direction = Right;

		else
			direction = Up_right;

	}

	else if (ball_x_coordinate - 1 == pad_1_x_coordinate && ball_y_coordinate == pad_1_y_coordinate[2])
	{

		if (direction == Left)
			direction = Right;

		else if (direction == Down_left)
			direction = Down_right;

		else
			direction = Right;

	}

	else if (ball_x_coordinate - 1 == pad_1_x_coordinate && ball_y_coordinate == pad_1_y_coordinate[3])
	{

		if (direction == Left)
			direction = Down_right;

		else if (direction == Up_left)
			direction = Down_right;

		else
			direction = Down_right;

	}

	if (ball_x_coordinate + 1 == pad_2_x_coordinate && ball_y_coordinate == pad_2_y_coordinate[0])
	{

		if (direction == Right)
			direction = Up_left;

		else if (direction == Up_right)
			direction = Up_left;

		else
			direction = Up_left;

	}

	else if (ball_x_coordinate + 1 == pad_2_x_coordinate && ball_y_coordinate == pad_2_y_coordinate[1])
	{

		if (direction == Right)
			direction = Left;

		else if (direction == Down_right)
			direction = Left;

		else
			direction = Down_left;

	}

	else if (ball_x_coordinate + 1 == pad_2_x_coordinate && ball_y_coordinate == pad_2_y_coordinate[2])
	{

		if (direction == Right)
			direction = Left;

		else if (direction == Down_right)
			direction = Down_left;

		else
			direction = Left;

	}

	else if (ball_x_coordinate + 1 == pad_2_x_coordinate && ball_y_coordinate == pad_2_y_coordinate[3])
	{

		if (direction == Right)
			direction = Down_left;

		else if (direction == Up_right)
			direction = Down_left;

		else
			direction = Down_left;

	}


}

void logic()

{


	ball_logic();
	pad_logic();
	cout << endl << "Player 1 : " << player_1_score << endl << "Player 2 : " << player_2_score;

}
