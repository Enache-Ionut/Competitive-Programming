#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream inputStream("bleach.in");
long numberOfEnemies;
int maximumDistanceOfMovement;
long long power = 0;
long long initialPower = 0;
priority_queue<long long, vector<long long>, greater<long long>> enemies;

void AddEnemies()
{
    long long enemy;
    for( int i = 0; i < maximumDistanceOfMovement + 1; ++i )
    {
        inputStream >> enemy;
        enemies.push(enemy);
    }
}

void AddNewEnemy()
{
    long long enemy;
    inputStream>> enemy;
    enemies.push(enemy);
}

void IncreasePower()
{
    if( power < enemies.top() )
    {
        initialPower += enemies.top() - power;
        power = enemies.top() * 2;
    }
    else
        power += enemies.top();
}

void RemoveWeakestEnemy()
{
    enemies.pop();
}

long long FindInitialPower()
{
    long enemiesLeft = numberOfEnemies - maximumDistanceOfMovement - 1;

    AddEnemies();
    while( !enemies.empty() )
    {
        IncreasePower();
        RemoveWeakestEnemy();
        if( enemiesLeft-- > 0 )
            AddNewEnemy();
    }
    return initialPower;
}

void DisplayInitialPower(long long initialPower)
{
    ofstream outputStream("bleach.out");
    outputStream<< initialPower;
    outputStream.close();
}

int main()
{
    std::ios::sync_with_stdio(false);
    inputStream>> numberOfEnemies>> maximumDistanceOfMovement;
    DisplayInitialPower(FindInitialPower());

    inputStream.close();
    return 0;
}
