void longestPath() //Beware this is pseudocode
{
    this->unmarkAll(); //unmarkAll the node
    list<node *> l_sorted; //will store the sorted node
    bool unmarked_node_exist=true; 
    node* elected_node=this->first; //when we find an unmarked node the pointer will be stored here for the next iteration of the while to be used for the call of traverse
    while(unmarked_node_exist)
    {
        if(this->traverse(elected_node,l_sorted)==false)
            return; //the graph is not a dag else the traverse suceeded and we need to elect a new node or get out of the loop
        foreach(node *n:this->node_in_the _graph) //election d'un node 
          if(!n->isMarked())
            elected_node=n;
    }
    
    foreach (node *p:l_sorted)
      foreach (node *o:p->succesors)
            if (o->dist <= p->dist +1) //the weight of our edge is always 1 so +1 but 1 can bre replaced by weight of edges
            {
                o->dist=p->dist+1;
                o->predecessor=p;
            }
            
    //we traverse the graph to find the higest distance
    node *end_of_longestpath;
    int max_dist=0;
    foreach(node *v:this->node_in_the _graph)
        if(v->dist>max_dist)
        {
            max_dist=v->dist;
            end_of_longestpath=v;
        }
        
    this->print(this->reconstruct(end_of_longestpath))
    this->unmarkAll(); //we go back to a stable state for the graph
}

stack graph::reconstruct(node *end_of_longestpath)
{
  //from the end_of_longestpath we get each of his predecessors:
  stack path;
  while(end_of_longestpath->predecessor != NULL)
  {
    path.push(end_of_longestpath);
    end_of_longestpath=end_of_longestpath->predecessor;
    for(node* to_test:path)
      if(to_test == end_of_longestpath)
	end_of_longestpath->predecessor=NULL;
  }
}

void graph::print(stack path)
{
  //then we show the result while popping the stack
  printline("A longest path is found of size " << max_dist << ": ");
  while(!path.empty())
  {
    print(path.back() << ";";
    path.pop_back();
  }
  cout<< endl;
}

bool graph::traverse(node *n, list<node *> &l_sorted)
{
    if(n->marked)
        return false; //if it is marked temporarly then it was also a n in a upper call of traverse, there fore we hav a cycle

    if(!n->isMarkedN))
    {
        n->marked=true;
        foreach(node *m:n->succesors)
            this->traverse(m,l_sorted); //for each child of n we call recursivly
        n->markNode(); //we mark the node n because all operation are finished with him
        n->marked=false; //
        l_sorted.push_front(n); //we add n to the list of sorted node
    }
    return true;
}
