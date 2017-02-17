#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

#define MAXIMUM_NUMBER_OF_BARS 100001

using namespace std;

vector<int> binaryIndexedTree(200005);
int numberOfBars;

int GetParent(int index)
{
    return index - (index & -index);
}

int GetNext(int index)
{
    return index + (index & -index);
}

void UpdateBinaryIndexedTree(int value, int index)
{
    while( index <= numberOfBars )
    {
        binaryIndexedTree[index] += value;
        index = GetNext(index);
    }
}

void BuildBinaryIndexedTree(vector<int> &friendsInBars)
{
    for( int i = 1; i<=numberOfBars; ++i )
    {
        UpdateBinaryIndexedTree(friendsInBars[i], i);
    }
}

int GetSum( int index )
{
    int sum = 0;
    while( index > 0 )
    {
        sum += binaryIndexedTree[index];
        index = GetParent(index);
    }
    return sum;
}

void FriendsLeaveBar(vector<int> &friendsInBars, int numberFriends, int bar)
{
    friendsInBars[bar] -= numberFriends;
    UpdateBinaryIndexedTree(-numberFriends , bar);
}

void FriendsGetInBar(vector<int> &friendsInBars, int numberFriends, int bar)
{
    friendsInBars[bar] += numberFriends;
    UpdateBinaryIndexedTree(numberFriends, bar);
}

void FriendsMoveFromOneBarToAnother(vector<int> &friendsInBars, ifstream &inputStream)
{
    int numberFriends;
    int barOut;
    int barIn;
    inputStream>> numberFriends>> barOut>> barIn;

    FriendsLeaveBar(friendsInBars, numberFriends, barOut);
    FriendsGetInBar(friendsInBars, numberFriends, barIn);
}

int GetNumberOfFriendsAround(vector<int> &friendsInBars, int bar, int distance)
{
    return GetSum(min(bar + distance, numberOfBars)) - GetSum(max(bar - distance - 1, 0)) - friendsInBars[bar];
}

void ProcessingQueries(vector<int> &friendsInBars, ifstream &inputStream, ofstream &outputStream)
{
    short queryType;
    int numberOfQueris;
    inputStream>> numberOfQueris;

    while( numberOfQueris-- )
    {
        inputStream>> queryType;
        if( queryType == 3 )
            FriendsMoveFromOneBarToAnother(friendsInBars, inputStream);
        else
        {
            int aux1;
            int aux2;
            inputStream>> aux1>> aux2;

            if(queryType == 0)
                outputStream<< GetNumberOfFriendsAround(friendsInBars, aux1, aux2)<< "\n";
            else
                queryType == 1 ? FriendsGetInBar(friendsInBars, aux1, aux2) :
                                FriendsLeaveBar(friendsInBars, aux1, aux2);
        }
    }
}

void ProcessingTests()
{
    ifstream inputStream("baruri.in");
    ofstream outputStream("baruri.out");
    int numberOfTests;

    inputStream>> numberOfTests;
    while( numberOfTests-- )
    {
        inputStream>> numberOfBars;
        vector<int> friendsInBars;

        friendsInBars.reserve(MAXIMUM_NUMBER_OF_BARS);
        friendsInBars.push_back(0);

        fill(binaryIndexedTree.begin(), binaryIndexedTree.end(), 0);
        copy_n(istream_iterator<int>(inputStream), numberOfBars, back_inserter(friendsInBars));

        BuildBinaryIndexedTree(friendsInBars);
        ProcessingQueries(friendsInBars, inputStream, outputStream);
    }
    inputStream.close();
    outputStream.close();
}

int main()
{
    ProcessingTests();
    return 0;
}
