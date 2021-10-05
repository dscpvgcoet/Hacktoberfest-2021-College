/*

Maitreya Kanitkar
TE-IT  8084

DAA Assignment 3  (Bellman-Ford algorithm)

*/


#include<iostream>
#include <bits/stdc++.h>
using namespace std;

struct Edge
{
	int src, dest, weight;
};

struct Graph
{
	int V, E;
	struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
	struct Graph* graph=new Graph;
	graph->V=V;
	graph->E=E;
	graph->edge=new Edge[E];
	return graph;
}

void print(int dist[], int n)
{
	cout<<endl<<endl<<"Vertex\t\t"<<"Distance from source : "<<endl;
	
	for(int i=0;i<n;i++)
    cout<<i<<"\t\t"<<dist[i]<<endl;
}

void BellmanFord(struct Graph* graph, int src)
{
	int V, E, u, v, weight, dist[V];
	V=graph->V;
	E=graph->E;

	for (int i=0;i<V;i++)
	dist[i]=INT_MAX;
	
	dist[src]=0;

	for (int i=0;i<V;i++)
	{
	    for(int j=0;j<E;j++)
		{
			u=graph->edge[j].src;
			v=graph->edge[j].dest;
			weight=graph->edge[j].weight;
		    
			if(dist[u]!=INT_MAX && dist[u]+weight<dist[v])
			dist[v]=dist[u]+weight;
		}
	}

	for (int i=0;i<E;i++)
	{
		u=graph->edge[i].src;
		v=graph->edge[i].dest;
		weight=graph->edge[i].weight;
		
		if(dist[u]!=INT_MAX && dist[u]+weight<dist[v])
		{
			cout<<"Graph contains a negative edge";
			return; 
		}
	}

	print(dist, V);

	return;
}

int main()
{
	int V, E;

	cout<<"Enter number of vertices of the graph : ";
	cin>>V;
	cout<<"Enter number of edges of the graph : ";
	cin>>E;

	struct Graph* graph=createGraph(V, E);

    cout<<endl<<"Enter the source,destination and weight :- "<<endl;

	for(int i=0;i<E;i++)
	{
		cout<<endl<<"Source : ";
		cin>>graph->edge[i].src;

		cout<<"Destination : ";
		cin>>graph->edge[i].dest;

		cout<<"Weight : ";
		cin>>graph->edge[i].weight;
	}

	BellmanFord(graph, 0);

	return 0;
}



/*

OUTPUT:-

Enter number of vertices of the graph : 5
Enter number of edges of the graph : 8

Enter the source,destination and weight :-

Source : 0
Destination : 1
Weight : 1

Source : 0
Destination : 2
Weight : 4

Source : 1
Destination : 2
Weight : 3

Source : 1
Destination : 3
Weight : 2

Source : 1
Destination : 4
Weight : 2

Source : 3
Destination : 2
Weight : 5

Source : 3
Destination : 1
Weight : 1

Source : 4
Destination : 3
Weight : 3


Vertex          Distance from source :
0               0
1               1
2               3
3               3
4               4

*/