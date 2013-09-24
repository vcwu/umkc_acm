/**
1991 ACM ICPC Finals 
Problem A Firetruck

Algorithm-ed by: Marvin Bellamy, Tony Sommer
Written by Victoria Wu 
10/12/12


Problem:
Firestation is in sector 1, there is a fire in target sector. Generate 
a list of all possible paths from firestation to the fire without cycles.

Algy
1. Build an adjacency list representation.

2. Use a modified depth first search to find 
all possible paths from 1 to target node. (move())

3. Increment case, rinse and repeat.


Note: Because of the way the adjacency list is built (in numerical order), 
the unedited output of the depth first search matches specifications.

File Input:
6
1 2
1 3
3 4
3 5
4 6
5 6
2 3
2 4
0 0
4
2 3
3 4
5 1
1 6
7 8
8 9
2 5
5 7
3 1
1 8
4 6
6 9
0 0
-1
*/

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <stack>

using namespace std;

typedef vector<int> path;	
vector < vector<int> > validPaths;		//store all validPaths paths- global for ease.

static void move(map <int, set <int> >* g, path currentPath, set<int> allNodes, int target);

int main()	{

	//Initializing Variables
	//----------------------
	int target;
	int caseNum = 1;	
	cin >> target;		//this is our destination node	

	while(target != -1)	{

		//Building our adjacency list rep of graph
		//---------------------------------------------------
		
		map <int, set <int> >	adjList;
		map <int, set <int> >:: iterator it;
		set<int> ::iterator neigh;
		
		int node1, node2;
		cin >> node1 >> node2;
		while( (node1 !=0) || (node2 != 0))	{
			//Inserting neighbors into Node 1's list
			if(adjList.find(node1) == adjList.end())	{	//there is NO node1 entry
				set<int> neighbors;
				neighbors.insert(node2);
				adjList[node1] = neighbors;
			}
			else 		
				//insert function takes care of duplicates
				adjList[node1].insert(node2);	
			
			//Inserting neighbors into Node 2s list
			if(adjList.find(node2) == adjList.end())	{	//there is no node2 entry
				set<int> neighbors;
				neighbors.insert(node1);
				adjList[node2] = neighbors;
			}
			else	
				adjList[node2].insert(node1);
			cin >> node1 >> node2;
		}

		/*
		//Print out the graph for testing purposes
		for(it = adjList.begin(); it!= adjList.end(); it++)	{
               	//print out the key
               	cout << "[" << it->first  << "]"<< " ->";
               	for(neigh = it->second.begin(); neigh != it->second.end(); neigh++)
                    cout << " " << *neigh;
                cout << endl;
		}
		*/
		
		//Starting the Printout
		//---------------------------------------------------
		cout << "CASE " << caseNum << ":" <<endl;
	
		//Finding all possible paths from 1 to target node
		//---------------------------------------------------

		path currentPath;				//store our current path's order
		set<int> pathNodes;				//store current path nodes - used for the find() function
		currentPath.push_back(1);		//always start at node 1 (given)
		pathNodes.insert(1);			//starting at node 1

		move(&adjList, currentPath, pathNodes, target);	//going to use recursion. Much easier conceptually.

		//Printing off # of routes
		//---------------------------------------------------
		cout << "There are " << validPaths.size() << " routes from the firestation to streetcorner " 
			<< target << ".\n";


		//Prepping for next case
		//---------------------------------------------------
		validPaths.clear();		//clear the validPaths vector for next case
		++caseNum;				
		cin >> target;

	}

}

/**
move

A modified depth -first search of a graph to find all possible paths from a start node
to a target node. The start node is given as the first element in currentPath, and already included
in set allNodes.

algy:
base case: arrived at target node (last element in currentPath)
recuse:
	Set curret node as last node in currentPath.
	For each neighbor of current node:
		If the neighbor hasn't been visited
			Mark the neighbor as visited.
			Call move on the neighbor.
		If it has already been visited
			Pass. Don't want to revisit nodes, would end in cycling.


*/
static void move(map <int, set <int> > *g, path currentPath, set<int> allNodes, int target)	{
	
	//Base Case
	//---------------------------------------------------	

	//if last node in path is target, successful path. stop.
	if(currentPath[currentPath.size()-1] == target)
	{
		//Print out the successfull path!
		vector<int>::iterator it;
		for(it = currentPath.begin(); it != currentPath.end(); it++)	{
			cout << "\t" << *it;	//print out tab to match output
		}
		cout << endl;

		//Add successful path into the validPaths vector - used to count # of paths.
		validPaths.push_back(currentPath);
	}
	
	//Recursvive Case
	//---------------------------------------------------	

	//Current node is the last node in the path.
	int currentNode = currentPath[currentPath.size()-1];

	//For each neighbor that HASN"T been visited already, go there.
	set<int> neighbors = (*g)[currentNode];	//will this copy the whole set? or just the ref?
	set<int>::iterator n;
	for(n = neighbors.begin(); n!= neighbors.end(); n++ )	{
		
		//if we haven't visited the node...
		if(allNodes.find(*n) == allNodes.end())	
		{
			//Visit it and recuse! 
			allNodes.insert(*n);
			currentPath.push_back(*n);
			move(g, currentPath, allNodes, target);	//passing by value
			allNodes.erase(*n);
			currentPath.pop_back();
		}
		//Don't want to continue if already visited.
	}
}
