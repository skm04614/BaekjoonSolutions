#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Mob
{
	char name[22];
	int key;
	Mob* next;

	bool has_name(const char* name) const
	{
		const char* name_ptr = this->name;
		while (*name && *name_ptr && *name == *name_ptr)
		{
			name++;
			name_ptr++;
		}

		return !*name && !*name_ptr;
	}
};

struct MobDict
{
	static constexpr int MAX_SIZE = 100003;

	Mob* hash_map[MAX_SIZE];

	void insert(Mob* ptr)
	{
		unsigned long long hash = get_hash(ptr->name);

		if (hash_map[hash] == nullptr)
		{
			hash_map[hash] = ptr;
		}
		else
		{
			for (Mob* current = hash_map[hash]; ; current = current->next)
			{
				if (current->has_name(ptr->name))
				{
					return;
				}
				
				if (current->next == nullptr)
				{
					current->next = ptr;
					return;
				}
			}
		}
	}

	Mob* get(const char *name)
	{
		unsigned long long hash = get_hash(name);

		if (hash_map[hash] == nullptr)
		{
			return nullptr;
		}
		else
		{
			for (Mob* current = hash_map[hash]; ; current = current->next)
			{
				if (current->has_name(name))
				{
					return current;
				}

				if (current->next == nullptr)
				{
					return nullptr;
				}
			}
		}
	}

	static unsigned long long get_hash(const char* name)
	{
		unsigned long long hash = 5381;

		while (*name)
		{
			hash = ((hash << 5) + hash + *name++) % MAX_SIZE;
		}

		return hash % MAX_SIZE;
	}
};

MobDict MOB_DICT;
Mob MOBS[100010];
int N;
int M;


int stoi(const char* str)
{
	int ret = 0;
	for (; *str; str++)
	{
		if (*str >= '0' && *str <= '9')
		{
			ret = 10 * ret + (*str - '0');
		}
		else
		{
			return -1;
		}
	}
	return ret;
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M;

	for (int i = 1; i <= N; i++)
	{
		std::cin >> MOBS[i].name;
		MOBS[i].key = i;
		MOBS[i].next = nullptr;

		MOB_DICT.insert(&MOBS[i]);
	}

	char buf[22];
	for (int j = 0; j < M; j++)
	{
		std::cin >> buf;

		int ret = stoi(buf);
		if (ret == -1)
		{
			std::cout << MOB_DICT.get(buf)->key << '\n';
			
		}
		else
		{
			std::cout << MOBS[ret].name << '\n';
		}
	}

	return 0;
}