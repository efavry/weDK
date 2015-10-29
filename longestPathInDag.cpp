void graph::longestPath() //BEWARE MUST BE DONE ON A ACYCLIC DI-GRAPH
{
  this->unmarkAll();
  //because we have a dag we can do a topological sort and search with it
  //tarjan made an easy to implement algorithm to do the topological sort
  list<node *> l_sorted; //will store the sorted node
  bool unmarked_node_exist=true;
  node* elected_node=this->first; //when we find an unmarked node the pointer will be stored here for the next iteration of the while to be used for the call of traverse
  cout << "Topological Sort : Starting \n";
  while(unmarked_node_exist) //ugly incomming !
  {
    
    if(this->topologicalSortRec(elected_node,l_sorted)==false)
    {
      cout << "Topological Sort : ERROR : NOT A DAG ! ABORTING \n";
      return;
    }
    unmarked_node_exist=false;
    for(node *n:this->listOfNodes) //told ya
      if(!n->isMarkedNode())
      {
	unmarked_node_exist=true;
	elected_node=n;
      }
  }
  
  this->printTopologicalSort(l_sorted);
  
  //for each node p of the sorted list we search wich node is the farthest from p
  for (node *p:l_sorted)
    for (node *o:p->l_successors)
      if (o->int_dist <= p->int_dist +1) //the weight of our edge is always 1 so +1
      {
	o->int_dist=p->int_dist+1;
	o->predecessor=p;
      }
      
      //we traverse the graph to find the higest distance
      node *end_of_longestpath=NULL;
    int max_dist=0;
  max_dist=this->findMaximumDistance(end_of_longestpath);
  
  //then from the end_of_longestpath we get each of his predecessors and we show the result while popping the stach (a list here, yes a list...)
  this->printLongestPath(this->reconstructFromEnd(end_of_longestpath),max_dist);
  this->unmarkAll();
}

int graph::findMaximumDistance(node *end_of_longestpath=NULL)
{
  int max_dist=0;
  for(node *v:this->listOfNodes)
    if(v->int_dist>max_dist)
    {
      max_dist=v->int_dist;
      end_of_longestpath=v;
    }
    return max_dist;
}

//return false if not a dag
bool graph::topologicalSortRec(node *n, list<node *> &l_sorted)
{
  if(n->b_tempMark) //flemme to do accessors
    return false; //if it is marked temporarly then it was also a n in a upper call of traverse, there fore we hav a cycle
    
    if(!n->isMarkedNode())
    {
      n->b_tempMark=true;
      for(node *m:n->l_successors)
	this->topologicalSortRec(m,l_sorted); //for each child of n we call recursivly
	n->markNode(); //we mark the node n because all operation are finished with him
	n->b_tempMark=false; //
	l_sorted.push_front(n); //we add n to the list of sorted node
    }
    return true;
}

void graph::printTopologicalSort(list<node *> &l_sorted)
{
  cout << "Topological Sort : Sorted list is : ";
  for(node *m:l_sorted)
    cout << m->uint_name << ";";
  cout << "\n";
}

list<unsigned int> graph::reconstructFromEnd(node *end_of_longestpath)
{
  list<unsigned int> path;
  while(end_of_longestpath->predecessor != NULL)
  {
    path.push_back(end_of_longestpath->uint_name);
    end_of_longestpath=end_of_longestpath->predecessor;
    for(unsigned int to_test:path)
      if(to_test == end_of_longestpath->uint_name)
	end_of_longestpath->predecessor=NULL;
  }
  return path;
}

void graph::printLongestPath(list<unsigned int> path, int max_dist)
{
  cout<< "A longest path is found of size "<< max_dist << ": " << endl;
  while(!path.empty())
  {
    cout<< path.back() << ";";
    path.pop_back();
  }
  cout<< endl;
}
