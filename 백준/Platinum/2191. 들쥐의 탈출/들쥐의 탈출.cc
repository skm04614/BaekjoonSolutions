#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Adj
{
	int v;
	Adj* next;

	Adj(int v, Adj* next) : v{ v }, next{ next }
	{

	}

	~Adj()
	{
		delete next;
		next = nullptr;
	}
};

struct Coords
{
	double y;
	double x;

	double dist_squared(const Coords& other) const
	{
		double dy = (y - other.y);
		double dx = (x - other.x);

		return dy * dy + dx * dx;
	}

	bool is_dist_to_below(const Coords& other, double max_dist) const
	{
		return dist_squared(other) <= (max_dist * max_dist);
	}
};

double MAX_DIST;

Adj* ADJ[110];
Coords RAT[110];
int N;

Coords ESCAPE[110];
int B[110];
bool VISITED[110];
int M;

int Q[110];
int LP, RP;

void reset()
{
	LP = RP = -1;
	for (int b = 1; b <= M; ++b)
	{
		VISITED[b] = false;
	}
}

int dfs(int a)
{
	for (const Adj* adj = ADJ[a]; adj; adj = adj->next)
	{
		const int b = adj->v;
		if (VISITED[b])
		{
			continue;
		}
		VISITED[b] = true;

		if (!B[b] || dfs(B[b]))
		{
			B[b] = a;
			return true;
		}
	}

	return false;
}

void cleanup()
{
	for (int a = 1; a <= N; ++a)
	{
		delete ADJ[a];
		ADJ[a] = nullptr;
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	
	int S, V;
	std::cin >> N >> M >> S >> V;
	MAX_DIST = S * V;
	for (int a = 1; a <= N; ++a)
	{
		std::cin >> RAT[a].y >> RAT[a].x;
	}

	for (int b = 1; b <= M; ++b)
	{
		std::cin >> ESCAPE[b].y >> ESCAPE[b].x;
		for (int a = 1; a <= N; ++a)
		{
			if (RAT[a].is_dist_to_below(ESCAPE[b], MAX_DIST))
			{
				ADJ[a] = new Adj{ b, ADJ[a] };
			}
		}
	}

	int safe_cnt = 0;
	for (int a = 1; a <= N; ++a)
	{
		reset();
		safe_cnt += dfs(a);
		if (safe_cnt == M)
		{
			break;
		}
	}
	std::cout << N - safe_cnt;

	cleanup();

	return 0;
}