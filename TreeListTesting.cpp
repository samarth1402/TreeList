#include <bits/stdc++.h>
#include "project.hpp"
using namespace std;

template <typename T>
void assertEquals (T x, T y)
{
    if (x != y)     throw "Value not matching.";
}

void testAdd()
{
    TreeList <string> list;
    list.push_back("Monday");
    list.push_back("Tuesday");
    list.push_back("Wednesday");
    list.push_back("Thursday");
    list.push_back("Friday");
    list.push_back("Saturday");
    list.push_back("Sunday");
    list.checkStructure();
    assertEquals(list.size(), static_cast<size_t>(7));
    assertEquals(list[0], string("Monday"));
    assertEquals(list[1], string("Tuesday"));
    assertEquals(list[2], string("Wednesday"));
    assertEquals(list[3], string("Thursday"));
    assertEquals(list[4], string("Friday"));
    assertEquals(list[5], string("Saturday"));
    assertEquals(list[6], string("Sunday"));
}

void testSet1 ()
{
    TreeList <int> list(3, 1);
    assertEquals(list.size(), static_cast<size_t>(3));
    assertEquals(list[0], 1);
    assertEquals(list[1], 1);
    assertEquals(list[2], 1);
}

void testSet2 ()
{
    TreeList <const char*> list (10);
    list[0] = "zero";
	list[1] = "ten";
	list[2] = "twenty";
	list[3] = "thirty";
	list[4] = "forty";
	list[5] = "fifty";
	list[6] = "sixty";
	list[7] = "seventy";
	list[8] = "eighty";
	list[9] = "ninety";
	assertEquals(list.size(), static_cast<size_t>(10));
	assertEquals(list[0], "zero"   );
	assertEquals(list[1], "ten"    );
	assertEquals(list[2], "twenty" );
	assertEquals(list[3], "thirty" );
	assertEquals(list[4], "forty"  );
	assertEquals(list[5], "fifty"  );
	assertEquals(list[6], "sixty"  );
	assertEquals(list[7], "seventy");
	assertEquals(list[8], "eighty" );
	assertEquals(list[9], "ninety" );
}

void testInsertAtStart()
{
	TreeList<char> list;
	list.insert(0, 'a');
	list.insert(0, 'b');
	list.insert(0, 'c');
	assertEquals(list.size(), static_cast<size_t>(3));
	assertEquals(list[0], 'c');
	assertEquals(list[1], 'b');
	assertEquals(list[2], 'a');
}


void testInsertAtEnd()
{
	TreeList<char> list;
	list.insert(0, 'a');
	list.insert(1, 'b');
	list.insert(2, 'c');
	list.insert(3, 'd');
	assertEquals(list.size(), static_cast<size_t>(4));
	assertEquals(list[0], 'a');
	assertEquals(list[1], 'b');
	assertEquals(list[2], 'c');
	assertEquals(list[3], 'd');
}


void testInsertAtMiddle()
{
	TreeList<const char*> list;
	list.insert(0, "Up");
	list.insert(1, "Down");
	list.insert(1, "Left");
	list.insert(2, "Right");
	list.insert(1, "Front");
	list.insert(2, "Back");
	assertEquals(list.size(), static_cast<size_t>(6));
	assertEquals(list[0], "Up"   );
	assertEquals(list[1], "Front");
	assertEquals(list[2], "Back" );
	assertEquals(list[3], "Left" );
	assertEquals(list[4], "Right");
	assertEquals(list[5], "Down" );
}

// Stresses the self-balancing mechanism
void testInsertManyBeginning()
{
	const long N = 100000000;
	TreeList<long> list;
	for (long i = 0; i < N; i++)        list.push_back(i);
	for (long i = 0; i < N; i++)        assertEquals(list[i], i);
    //list.checkStructure();
}


// Stresses the self-balancing mechanism
 void testInsertManyEnd()
 {
	const long N = 300000;
	TreeList<long> list;
	for (long i = N - 1; i >= 0; i--)       list.insert(0, i);
	for (long i = 0; i < N; i++)            assertEquals(list[i], i);
	list.checkStructure();
}

static void testErase()
{
	TreeList<char> list;
    string str = "the quick brown fox jumped over the lazy dog";
    for (int s = 0; s < str.length(); s++)      list.push_back(str[s]);
    assertEquals(list.size(), str.length());

	assertEquals(list[ 2], 'e');  list.erase( 2);
	assertEquals(list[ 4], 'u');  list.erase( 4);
	assertEquals(list[ 3], 'q');  list.erase( 3);
	assertEquals(list[ 2], ' ');  list.erase( 2);
	assertEquals(list[12], 'f');  list.erase(12);
	assertEquals(list[11], ' ');  list.erase(11);
	assertEquals(list[10], 'n');  list.erase(10);
	assertEquals(list[ 9], 'w');  list.erase( 9);
	assertEquals(list[11], ' ');  list.erase(11);
	assertEquals(list[11], 'j');  list.erase(11);
	assertEquals(list[11], 'u');  list.erase(11);
	assertEquals(list[10], 'x');  list.erase(10);
	assertEquals(list[11], 'p');  list.erase(11);
	assertEquals(list[12], 'd');  list.erase(12);
	assertEquals(list[11], 'e');  list.erase(11);
	assertEquals(list[13], 'v');  list.erase(13);
	assertEquals(list[13], 'e');  list.erase(13);
	assertEquals(list[19], 'l');  list.erase(19);
	assertEquals(list[20], 'z');  list.erase(20);
	assertEquals(list[19], 'a');  list.erase(19);
	assertEquals(list[18], ' ');  list.erase(18);
	assertEquals(list[22], 'g');  list.erase(22);

	list.checkStructure();
}


static void testClear()
{
	TreeList<int> list;
	for (int i = 0; i < 20; i++)
		list.push_back(i * i);

	list.clear();
	assertEquals(list.size(), static_cast<size_t>(0));
    list.checkStructure();

	list.push_back(- 1);
	list.push_back(- 8);
	list.push_back(-27);
	assertEquals(list.size(), static_cast<size_t>(3));
	assertEquals(list[0], - 1);
	assertEquals(list[1], - 8);
	assertEquals(list[2], -27);
}

void testIterator ()
{
    TreeList<int> list;
    for (int i = 0; i < 100; i++)   list.push_back(i);

    TreeList<int>::iterator itr;
    int i = 0;
    for (itr = list.begin(); itr != list.end(); ++itr)
    {
        assertEquals(list[i++], *itr);
    }
}


int main()
{
    try
    {
        /*testAdd();
        testSet1();
        testSet2();
        testInsertAtStart();
        testInsertAtEnd();
        testInsertAtMiddle();*/
        testInsertManyBeginning();
        /*testInsertManyEnd();
        testErase();
        testClear();
        testIterator();*/
        cout << "All tests passed\n";
    }
    catch (string text)
    {
        cout << text << '\n';
    }


}
