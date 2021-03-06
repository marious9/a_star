#include <iostream>
#include <fstream>

using namespace std;


double calcH(int x, int y)
{
	return sqrt(pow((x - 20), 2) + pow((y - 20), 2));
}

int main()
{
	string namegrid = "grid.txt";
	const int rows = 22;
	const int cols = 22;
	int grid[rows][cols];
	int minX = 0;
	int	minY = 0;
	int opened[rows][cols];
	int closed[rows][cols];
	int parents[rows][cols];//NESW1234
	double Fvalues[rows][cols];
	double Gvalues[rows][cols];

	//Wczytywanie danych z pliku
	ifstream file(namegrid.c_str());

	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			file >> grid[i][j];
		}
	}
	file.close();

	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			opened[i][j] = 0;
			closed[i][j] = 0;
			parents[i][j] = 0;
			Gvalues[i][j] = 0;
			Fvalues[i][j] = 0;
		}
	}
	closed[1][1] = 1;

	int x = 1;
	int y = 1;

	while (!(x == 20 && y == 20))
	{

		if (closed[x + 1][y] == 0 && (grid[x + 1][y] == 0))
		{
			opened[x + 1][y] = 1;
			Gvalues[x + 1][y] = Gvalues[x][y] + 1;
			Fvalues[x + 1][y] = Gvalues[x + 1][y] + calcH(x + 1, y);
			parents[x + 1][y] = 1;
		}
		if (closed[x][y + 1] == 0 && grid[x][y + 1] == 0)
		{
			opened[x][y + 1] = 1;
			Gvalues[x][y + 1] = Gvalues[x][y] + 1;
			Fvalues[x][y + 1] = Gvalues[x][y + 1] + calcH(x, y + 1);
			parents[x][y + 1] = 4;
		}
		if (closed[x - 1][y] == 0 && grid[x - 1][y] == 0)
		{
			opened[x - 1][y] = 1;
			Gvalues[x - 1][y] = Gvalues[x][y] + 1;
			Fvalues[x - 1][y] = Gvalues[x - 1][y] + calcH(x - 1, y);
			parents[x - 1][y] = 3;
		}
		if (closed[x][y - 1] == 0 && grid[x][y - 1] == 0)
		{
			opened[x][y - 1] = 1;
			Gvalues[x][y - 1] = Gvalues[x][y] + 1;
			Fvalues[x][y - 1] = Gvalues[x][y - 1] + calcH(x, y - 1);
			parents[x][y - 1] = 2;
		}
		// wybiera najmniejsze, pierwsze napotkane F
		double minF = 666.00;
		for (int i = 1; i < rows - 1; i++)
		{
			for (int j = 1; j < cols - 1; j++)
			{
				if (Fvalues[i][j] < minF && opened[i][j] == 1)
				{
					minF = Fvalues[i][j];
					minX = i;
					minY = j;
				}
			}
		}

		opened[minX][minY] = 0;
		closed[minX][minY] = 1;

		x = minX;
		y = minY;
		// sprawdza czy sciezka jest zablokowana
		int opensCounter = 0;
		for (int i = 1; i < 21; i++)
		{
			for (int j = 1; j < 21; j++)
			{
				if (opened[i][j] != 0) opensCounter++;
			}
		}
		if (opensCounter == 0)
		{
			cout << "Sciezka zablokowana." << endl;
			getchar();
			return 0;
		}
	}
	//zapisuje sciezke na gridzie
	x = 20;
	y = 20;
	while (!(x == 1 && y == 1 && grid[1][1] != 0))
	{
		grid[x][y] = 3;
		if (parents[x][y] == 1) //N
		{
			x -= 1;
		}
		else if (parents[x][y] == 2) //E
		{
			y += 1;
		}
		else if (parents[x][y] == 3) //S
		{
			x += 1;
		}
		else if (parents[x][y] == 4) //W
		{
			y -= 1;
		}
	}
	//wyswietla grida ze sciezka
	int steps = 0;
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (grid[i][j] == 3)
			{
				cout << " " << grid[i][j];
				steps += 1;
			}
			if (grid[i][j] == 5)
			{
				cout << " " << grid[i][j];
			}
			if (grid[i][j] == 0)
			{
				cout << " " << grid[i][j];
			}
		}
		cout << endl;
	}
	cout << "Liczba krokow: " << steps << endl;

	getchar();
	return 0;
}











