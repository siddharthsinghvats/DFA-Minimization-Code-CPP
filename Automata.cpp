// by - Siddharth Singh
//THEORY OF AUTOMATA
//CODE ASSIGNMENT



#include <bits/stdc++.h>
#include<cstdlib>
#define pb push_back
using namespace std;



//BFS= Breadth First Search ,being used here to cut down the states given in the input DFA that are unreachable from the initial state
//Can be seen as disconnected component in the transition graph

void bfs(string s,map<string,bool> &reach, map<string,vector<string> > & m)
{
    queue<string> q;
    q.push(s);
    reach[s]=true;
    while(q.size()){
    string p =q.front();
    q.pop();
    for( int i =0; i<m[p].size(); i++)
        {
            if(reach[m[p][i]]==false)
                {
                    reach[m[p][i]]=true;
                    q.push(m[p][i]);
                }
        }
    }
}

int main()
{

    system("Color 5F");
    cout<<"\n\n                                            STATE MINIMISATION PROGRAM FOR A DFA\n";
    cout<<"                                          _________________________________________\n\n";
    cout<<"========================================================================================================================\n\n\n";


//    A vector of string to store the input states(Accepts states in any form like q1,q2....or a, b...)
    vector<string> input_states;



//    A vector of string to store the final states after removing the unreachable states from start state
    vector<string> states;



//    A vector of string to store the alphabets (accepts any input of the form a,b,c..or 1,2,3...)
    vector<string> alphabets;



//    A map to store the transition table of the input DFA
// stores as- map[(q1,a)] gives the state achieved after providing input a at the state q1
    map< pair<string,string>,string> transition_table;



//holds the start state
    string start_state;


// stores all the states which are non-final
    vector<string> non_final_states;


// stores all the state which are final
    vector<string> final_states;


// A map marking if a state is reachable from the start state
    map<string, bool> is_reachable;


//Taking input the number of states in the input DFA
    int number_of_states ;
    cout<<"Enter Number Of States:\n";
    cin>>number_of_states;


//Taking input the states
    cout<<"Enter "<< number_of_states <<" Number Of State(s)\n";
    for(int i=0; i<number_of_states; i++)
        {
            string state;
            cin>>state;
            input_states.pb(state);
            is_reachable[state]=false;
        }


//Taking inputs the alphabets for the DFA
    cout<<"Enter number of alphabets\n";
    int number_of_alphabets;
    cin>>number_of_alphabets;
    cout<<"Enter "<<number_of_alphabets<<" number of alphabet(s)\n";

    for(int i=0; i<number_of_alphabets; i++)
        {
            string alphabet;
            cin>>alphabet;
            alphabets.pb(alphabet);

        }


//Taking input the start state
    cout<<"Enter initial state\n";
    cin>>start_state;


//Taking input final states of the DFA
    cout<<"Enter number of final states\n";
    int number_of_final_states;
    cin>>number_of_final_states;

    cout<<"Enter "<<number_of_final_states<<" number of final state(s)\n";
    for(int i =0; i<number_of_final_states; i++)
        {
            string final_state;
            cin>>final_state;
            final_states.pb(final_state);

        }


// A map acting as adjacency list for the dfs method (stores the states that can be reached from the gin state)
// Like m[q1] gives the list of the states that can be reached directly through q1 on taking an alphabet
    map<string,vector<string> > transition_rows_in_a_map;


//Taking input the transition table
    for(int i=0; i<number_of_states; i++)
        {
            cout<<"For state: '"<<input_states[i]<<"' input the transition row\n\n";
            for(int j=0; j<number_of_alphabets; j++)
                {
                    cout<<"For alphabet '"<<alphabets[j]<<"' input next state\n";
                    string next_state;
                    cin>> next_state;
                    transition_rows_in_a_map[input_states[i]].pb(next_state);
                    cout<<"\n";
                    transition_table[make_pair(input_states[i], alphabets[j])]= next_state;
                }
        }


    system("cls");
    system("Color E4");

    cout<<"\n\n                                            STATE MINIMISATION PROGRAM FOR A DFA\n";
    cout<<"                                          _________________________________________\n\n";
    cout<<"======================================================================================================================\n\n\n";


//   DFS called here to remove unreachable states
    bfs(start_state,is_reachable,transition_rows_in_a_map);

//        Storing the reachable states in the vector named states and simultaneously printing unreachable states
    for(auto it= is_reachable.begin(); it!=is_reachable.end(); it++)
        {
            if(it->second)
                states.pb(it->first);
            else
                cout<<"Removing state "<<it->first<<" as it is unreachable from the initial state\n\n";
        }


//Storing the non-final states in the vector non_final
    for(int i= 0; i<states.size(); i++)
        {

            if(find(final_states.begin(),final_states.end(),states[i])==final_states.end()) // if a particular state is not found in final states list
                // then it is non final
                {
                    non_final_states.pb(states[i]);
                }
        }



//This is a vector of vectors of vectors of string each row in the vector equivalence class represents ith class
//Each row of this vector is itself a vector that holds the partitions for that equivalence class
// equivalence_classes[0] represents the 0th equivalence class
//equivalence_classes[0][0] represents 0th partition of the 0th equivalence class
//equivalence_classes[0][0][0] epresents 0th element of the 0th partition of the 0th equivalence class
    vector< vector< vector <string> > > equivalence_classes;



//storing the 0th equivalence class as it consists of two partitions set of final and non-final states
    vector< vector<string> >zero_equivalence;
    zero_equivalence.pb(non_final_states);
    zero_equivalence.pb(final_states);
    equivalence_classes.pb(zero_equivalence);




//this is the major logic of the program
//here we use the equivalence theorem for minimisation
//we already have the 0th equivalence class
//for each subsequent equivalence classes we check for the partitions in the previous class
//after generating the ith equivalence class we compare it with (i-1)th equivalence class if it comes same we break otherwise we continue repeating
    for( int i=1;; i++)
        {
            map<string,bool> visited;
            for(int u = 0; u<states.size(); u++)
                visited[states[u]]=false;
            vector<vector<string> > equivalence_row;


            for(int j=0; j<equivalence_classes[i-1].size(); j++ )
                {


                    for(int k=0; k<equivalence_classes[i-1][j].size(); k++)
                        {
                            if(   visited[equivalence_classes[i-1][j][k]]== false)
                                {
                                    vector<string> equivalence;
                                    equivalence.pb(equivalence_classes[i-1][j][k]);
                                    visited[equivalence_classes[i-1][j][k]]= true;
                                    for(int l= k+1; l<equivalence_classes[i-1][j].size(); l++)
                                        {
                                            if( visited[equivalence_classes[i-1][j][l]]== false)
                                                {

                                                    bool flag =false;
                                                    for(int m =0; m<alphabets.size(); m++)
                                                        {
                                                            flag = false;

                                                            for(int b=0; b<equivalence_classes[i-1].size(); b++ )
                                                                {
                                                                    if(find(equivalence_classes[i-1][b].begin(),equivalence_classes[i-1][b].end(),transition_table[make_pair(equivalence_classes[i-1][j][k],alphabets[m])])!=equivalence_classes[i-1][b].end()
                                                                            &&
                                                                            find(equivalence_classes[i-1][b].begin(),equivalence_classes[i-1][b].end(),transition_table[make_pair(equivalence_classes[i-1][j][l],alphabets[m])])!=equivalence_classes[i-1][b].end() )
                                                                        {
                                                                            flag = true;
                                                                            break;
                                                                        }
                                                                }
                                                            if(!flag)
                                                                break;
                                                        }
                                                    if(flag==true)
                                                        {
                                                            equivalence.pb(equivalence_classes[i-1][j][l]);
                                                            visited[equivalence_classes[i-1][j][l]]= true;
                                                        }
                                                }
                                        }
                                    if(equivalence.size()>0)
                                        equivalence_row.pb(equivalence);
                                }
                        }
                }
            if(equivalence_row.size()>0)
                equivalence_classes.pb(equivalence_row);


//checking ith equivalence if it is equal to (i-1)th equivalence class
            if(equivalence_classes[i-1].size()==equivalence_classes[i].size())
                {
                    bool flag = true;
                    for(int z =0; z<equivalence_classes[i-1].size(); z++)
                        {
                            if(equivalence_classes[i-1][z].size()!=equivalence_classes[i][z].size())
                                {
                                    flag=false;
                                    break;
                                }
                        }
                    if(flag)
                        {
                            for(int z =0; z<equivalence_classes[i-1].size(); z++)
                                {
                                    for(int x =0; x<equivalence_classes[i-1][z].size(); x++)
                                        {
                                            if(equivalence_classes[i-1][z][x]!=equivalence_classes[i][z][x])
                                                {
                                                    flag=false;
                                                }
                                        }
                                }
                        }

                    if(flag)
                        break;

                }
        }




//printing the final equivalence class with all the partitions

    cout<<"Final equivalence class is: \n";
    int g = equivalence_classes.size()-1;
    cout<<"Equivalence class number: "<<g-1<<"\n";
    for(int v = 0; v<equivalence_classes[g].size(); v++)
        {
            cout<<"\nPartition number:- "<<v<<"\n\n";
            cout<<"{ ";
            for(int p = 0; p<equivalence_classes[g][v].size(); p++)
                {
                    cout<<equivalence_classes[g][v][p];
                    if(p!=equivalence_classes[g][v].size()-1)
                        cout<<", ";
                }
            cout<<" }\n";
        }


    cout<<"\n\n\n                                          TRANSITION TABLE FOR MINIMIZED DFA\n";
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";



// printing the transition table for the minimised dfa
// each partition in the final equivalence class represents one state
    for(int i =0; i<equivalence_classes[g].size(); i++)
        {
            if(find(equivalence_classes[g][i].begin(),equivalence_classes[g][i].end(),start_state)!=equivalence_classes[g][i].end())
                {
                    string curr="[";
                    for(int j = 0; j<equivalence_classes[g][i].size(); j++)
                        {
                            if(j!=equivalence_classes[g][i].size()-1)
                                curr=curr+equivalence_classes[g][i][j]+" ";
                            else
                                curr=curr+equivalence_classes[g][i][j];
                        }
                    curr+="]";
                    cout<<"Initial state of the minimized DFA is :- "<<curr<<"\n\n";
                    break;
                }
        }


    cout<<"Final states of the minimized DFA is/are :- ";
    for(int i =0; i<equivalence_classes[g].size(); i++)
        {


            for(int k= 0; k<final_states.size(); k++)
                {
                    if(find(equivalence_classes[g][i].begin(),equivalence_classes[g][i].end(),final_states[k])!=equivalence_classes[g][i].end())
                        {
                            string curr="[";
                            for(int j = 0; j<equivalence_classes[g][i].size(); j++)
                                {
                                    if(j!=equivalence_classes[g][i].size()-1)
                                        curr=curr+equivalence_classes[g][i][j]+" ";
                                    else
                                        curr=curr+equivalence_classes[g][i][j];
                                }
                            curr+="]";
                            cout<<curr<<"  ";
                            break;
                        }
                }

        }
    cout<<"\n________________________________________________________\n\n";





//transition table printing starts here

    cout<<setw(14)<<"State"<<setw(28)<<"Inputs\n";
    cout<<"________________________________________________________\n\n";
    cout<<setw(30)<<" ";
    for(int i = 0; i<alphabets.size(); i++)
        {
            cout<<alphabets[i]<<setw(23);
        }
    cout<<"\n________________________________________________________\n\n";

    for(int i =0; i<equivalence_classes[g].size(); i++)
        {
            string curr="[";
            for(int j = 0; j<equivalence_classes[g][i].size(); j++)
                {
                    if(j!=equivalence_classes[g][i].size()-1)
                        curr=curr+equivalence_classes[g][i][j]+" ";
                    else
                        curr=curr+equivalence_classes[g][i][j];
                }
            curr+="]";
            cout<<setw(13)<<curr;
            for(int j=0; j<alphabets.size(); j++)
                {
                    for(int m = 0; m<equivalence_classes[g].size(); m++)
                        {

                            if(find(equivalence_classes[g][m].begin(),equivalence_classes[g][m].end(),transition_table[make_pair(equivalence_classes[g][i][0],alphabets[j])])!=equivalence_classes[g][m].end())
                                {
                                    string transited = "[";
                                    for(int x=0; x<equivalence_classes[g][m].size(); x++)
                                        {
                                            if(x!=equivalence_classes[g][m].size()-1)
                                                transited= transited+equivalence_classes[g][m][x]+" ";
                                            else
                                                transited= transited+equivalence_classes[g][m][x];
                                        }
                                    transited+="]";
                                    cout<<setw(21)<<transited;
                                    break;
                                }
                        }
                }
            cout<<"\n________________________________________________________\n\n";
        }
}
