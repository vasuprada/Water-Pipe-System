#include<bits/stdc++.h>
using namespace std;

int final_cost, final_dest, found;
#define big_value 1000000007LL
#define buff_size 1024

typedef struct ucs* PIPE_BLOCK;
struct ucs
{	
	int st[60],et[60],n;
};

void dfs(int source, vector< pair<string,int> > v[], int visited[], int cost, int isgoal[], map<string,int>nodes)
{
	int pairs,entry;
	
	visited[source]=1;
	if(isgoal[source])
	{
		if(cost<final_cost)
		{	
			found=1;
			final_cost=cost;
			final_dest=source;
		}
		return;
	}
	
	pairs=v[source].size();
	
	if(found)return;
	
	for(int i=0; i<pairs; i++) 
	{	
			
		if(found)break;
		
		if(!visited[nodes[v[source][i].first]])
		{	
			
			dfs(nodes[v[source][i].first],v,visited,cost+1,isgoal,nodes);
			
		}
	}
	
	return;
}




void bfs(vector< pair<string,int> > v[], int visited[], int start_time, int isgoal[], map<string,int>nodes)
{
	int time_taken[10000]={0},node,pairs,entry;
	queue<int>bfsq;
	
	while(!bfsq.empty())bfsq.pop();
	
	bfsq.push(1);
	visited[1]=1;
	time_taken[1]=start_time;
	
	while(!bfsq.empty() && !found)
	{
		node = bfsq.front();
		pairs = v[node].size();

		for(int i=0;i<pairs;i++)
		{	
			entry = nodes[v[node][i].first];
			
			if(visited[entry])continue;
			visited[entry]=1;
			
			bfsq.push(entry);
			
			time_taken[entry] = time_taken[node]+1;
			
			if(isgoal[entry])
			{
				found = 1;
				final_cost = time_taken[entry];
				final_dest = entry;
				break; 
			}
		}
		bfsq.pop();
	}	
}


int is_valid_block_time(int source, int dest, int cost, vector< pair<int, PIPE_BLOCK> >pipes[])
{
		
	int limit = pipes[source].size(), flag = 0;
	
	PIPE_BLOCK block;
	
	for(int i=0;i<limit;i++)
	{
		if(pipes[source][i].first == dest)
		{
			block = pipes[source][i].second;
			flag = 1;
			break;
		}
	}
	
	if(flag == 0)return 1;
	
	limit = block->n;
	cost = cost%24;
	for(int i=0;i<limit;i++)
	{
				 	
		if(cost >= block->st[i] && cost <= block->et[i])return 0;
	}
	
	return 1;
}

void ucs(vector< pair<string,int> > v[], int visited[], int start_time, int isgoal[], map<string,int>nodes, vector< pair<int, PIPE_BLOCK> >pipes[], map<int, string>rnode)
{
vector< pair<int,string> >open;
int source[10000]={0},time_taken[10000]={big_value},is_inside_open[10000]={0};
int vertex,pairs,entry,flag,temp_cost,temp_source,check_time;

open.push_back(make_pair(start_time,rnode[1]));
source[1]=0;
visited[1]=1;
time_taken[1]=start_time;
is_inside_open[1]=1;
	int n=0;
	
		
	while(!open.empty())
	{
		
		vertex=nodes[open[0].second];
		open.erase(open.begin());
		visited[vertex] = 1;
		
		if(isgoal[vertex])
		{
				found=1;
				final_cost=time_taken[vertex];
				final_dest=vertex;
				return;
		
		
		}
		
		pairs=v[vertex].size();
			
		flag = 0;
		
		for(int i=0;i<pairs;i++)
		{	
			entry = nodes[v[vertex][i].first];
			temp_source= vertex;
			
		
			if(!is_valid_block_time(vertex, entry, time_taken[vertex], pipes))continue;
			
			
			temp_cost = (time_taken[vertex] + v[vertex][i].second);
				
			flag = 1;
		
			if(!visited[entry] && !is_inside_open[entry])
			{
				open.push_back(make_pair(temp_cost, rnode[entry]));
				
				time_taken[entry] = temp_cost;
				is_inside_open[entry]= 1;
			
			}
		
			else if(!visited[entry] && is_inside_open[entry])
			{ 	
			
				if(temp_cost < time_taken[entry]) 
				{
					for(int i=0;i<open.size();i++)
					{
						if(entry==nodes[open[i].second])
						{	
							open[i].first=temp_cost;
							break;
						}
						
					}
				
				time_taken[entry] = temp_cost;
				source[entry]=vertex;		

				}
				
			}
			
		
			else if(visited[entry] && (temp_cost<time_taken[entry]))
			{ 	
				
				visited[entry]=0;
				
				open.push_back(make_pair(temp_cost,rnode[entry]));
				time_taken[entry] = temp_cost;
			}		
			
		}
	
		sort(open.begin(),open.end());	
		
	}
	
}	
	

int main(int argc,char *argv[])
{
	int T=0, len;
	
	map <string,int> nodes;
	map<int, string> rnodes;
	
	
	char read_dest[10000], read_middle[10000];
	char line[buff_size];	
	char search_type[5];
	
	string algo;
	
	FILE *ifile;
	ofstream ofile("output.txt",ios::out|ios::app);
	
	//ifile = fopen("sample2.txt","r"); 
	ifile = fopen(argv[2],"r");
	fgets(line, buff_size, ifile);
	
	len = strlen(line) - 1;
	for(int i=0;i<len;i++)T = (T*10) + (line[i]-'0');
	
	while(T--)
	{
		vector< pair<int, PIPE_BLOCK> >pipes[10000];
		
		fgets(line, buff_size, ifile);
		
		line[strlen(line) - 1] = '\0';
		strcpy(search_type, line);
		
		algo = string(search_type);

		int isgoal[10000]={0}, visited[10000]={0},vnum=1, cost,result, st, et, index;
		string sname, dname, mname, n_pipes, blocks;
		int np,start_time,b;
		int k;
		vector<pair<string, int> >v[10000];
		

		fgets(line, buff_size, ifile);
		
		line[strlen(line) - 1] = '\0';
		sname = string(line);
		nodes[sname]=vnum;
		rnodes[vnum] = sname;
		++vnum;
	     
		fgets(line, buff_size, ifile);
		
		line[strlen(line) - 1] = '\0';
		dname = string(line);
		
		len = strlen(line);
				
		for(int i = 0; i < len;)
	    {
	       if(line[i] == ' ')
		   {
		   		++i;
		   		continue;
		   }
	       
	       char temp[100];
	       int j=0;
	       
	       for(j=0; line[j+i] != ' ' && j+i < len; j++)temp[j] = line[j+i];
	       temp[j] = '\0';
		   dname = string(temp);
		   
		   nodes[dname]=vnum;
	       rnodes[vnum]=dname;
	       isgoal[vnum]=1;
	       ++vnum;
	       
	       i=i+j;
	    }

		fgets(line, buff_size, ifile);
		
		line[strlen(line) - 1] = '\0';
		mname = string(line);

		len = strlen(line);
				
		for(int i = 0; i < len;)
	    {
	       if(line[i] == ' ')
		   {
		   		++i;
		   		continue;
		   }
	       
	       char temp[100];
	       int j=0;
	       
	       for(j=0; line[j+i] != ' ' && j+i < len; j++)temp[j] = line[j+i];
	       temp[j] = '\0';
		   mname = string(temp);
		   
	       nodes[mname]=vnum;
	       rnodes[vnum]=mname;
	       ++vnum;
	       
	       i=i+j;
	    }
   
		fgets(line, buff_size, ifile);
	
		len = strlen(line) - 1;
		np = 0;
		for(int i=0;i<len;i++)np = (np*10) + (line[i]-'0');
		
	    int legit_pipes=0;
	    PIPE_BLOCK magic_block;
	    
		while(np--)
	    {	
	 		fgets(line, buff_size, ifile);
			line[strlen(line) - 1] = '\0';
			len = strlen(line);
			
				int spaces = 0, start = 0;
		    	for(start = 0; spaces < 3;)
		    	{
		    		if(line[start] == ' ')
		    		{
		    			++spaces;
		    			++start;
		    			continue;
					}
					
					char temp[100];
					int j;
									
					for(j=0; line[j+start] != ' ' && j+start < len; j++)temp[j] = line[j+start];
		       		temp[j] = '\0';
				
					if(spaces == 0)sname = string(temp);
					else if(spaces == 1)dname = string(temp);
					else if(spaces == 2)
					{
						len = strlen(temp);
						cost = 0;
						for(int i=0;i<len;i++)cost = (cost*10) + (temp[i]-'0');
						v[nodes[sname]].push_back(make_pair(dname, cost));
					
					}
									
					start = start + j;
					
				}
				
				
				len = strlen(line);
				b= 0;
				while(line[start] != ' ' && start < len)
				{
					b = (b*10) + (line[start]-'0');
					++start;
				}
				
				if(b == 0)
				{				
					continue;
				}
				
				PIPE_BLOCK var = (PIPE_BLOCK) malloc (sizeof(struct ucs));
				
				var->n=b;
				
				++start;
				index = 0;
				
				while(start < len)
				{
					if(line[start] == ' ')
		    		{
		    			++start;
		    			continue;
					}
				
					char temp[100];
					int j;
				
					for(j=0; line[j+start] != ' ' && j+start < len; j++)temp[j] = line[j+start];
		       		temp[j] = '\0';
				
					st = et = 0;
					for(j=0;temp[j]!='-';j++)st = (st*10) + temp[j]-'0';
					++j;
					for(;temp[j]!='\0';j++)et = (et*10) + temp[j]-'0';
					
					var->st[index] = st;
					var->et[index] = et;
					index++;
					
					start = start + j;
				
				}
				
				pipes[nodes[sname]].push_back(make_pair(nodes[dname],var));
			
		}
		
		fgets(line, buff_size, ifile);
		if(line[strlen(line) - 1] == '\n')line[strlen(line) - 1] = '\0';
		len = strlen(line);
		
		start_time = 0;
		for(int i=0;i<len;i++)start_time = (start_time*10) + (line[i] -'0');
	
		fgets(line, buff_size, ifile);
			
		for(int i=0;i<vnum;i++)
		{	
			sort(v[i].begin(),v[i].end());
		}
		
		
		
		final_cost=999999999LL;
		found=0;
			
		if(algo=="BFS")
		{ 
			bfs(v,visited,start_time,isgoal,nodes);
		}
		
		else if(algo=="DFS") 
		{
			dfs(1,v,visited,start_time,isgoal,nodes);
		
		}
		else
		{	
			ucs(v,visited,start_time,isgoal,nodes, pipes, rnodes);
		}
		
		if(found)
		{	
			final_cost = final_cost%24;
			ofile<<rnodes[final_dest]<<" "<<final_cost<<"\n";
		}
		
		else 
		{
			ofile<<"None\n";
		}
		
	}
	fclose(ifile);
	ofile.close();
	return 0;
}
