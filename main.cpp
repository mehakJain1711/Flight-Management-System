#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <list>
#include<string>
#include<bits/stdc++.h>
using namespace std;
int dp[5001][5011];
int mn[5001];
int N;
vector<int> A;
class Airport {
public:
    string name;

    Airport(string name) {
        this->name = name;
    }
};

typedef Airport* PAirport;
typedef pair<int, PAirport> myPair;
int flag = 0;
int bo = 0;

map<PAirport, int> dist;
map<PAirport, PAirport> parent;

class Graph
{
    map<PAirport, vector<pair<PAirport, int>>> adj;
    void printAllUtils(PAirport src, PAirport dest, map<PAirport, bool> &visit, vector<string> &path, int &);

public:
    vector<PAirport> listOfAirports;

    void addFlight(PAirport u, PAirport v, int w, bool bidirected);
    void shortestPath(PAirport s, PAirport d);
    void addAirport(PAirport a);
    void printPaths(PAirport a, PAirport b);
    void viewMap();
    void PrintAllPaths(PAirport src, PAirport dest);
    PAirport SearchAirport(string abc);
};

void Graph::PrintAllPaths(PAirport src, PAirport dest)
{
    map<PAirport, bool>visit;
    vector<string>path(100);
    int path_index = 0;

    for (auto itr : listOfAirports)
    {
        visit[itr] = false;
    }
    printAllUtils(src, dest, visit, path, path_index);
}

void Graph::printAllUtils(PAirport src, PAirport dest, map<PAirport, bool> &visit, vector<string> &path, int &path_index)
{
    visit[src] = true;
    path[path_index] = src->name;
    path_index++;


    if (src->name.compare(dest->name) == 0)
    {
        //flag++;
        for (int i = 0; i < path_index; i++)
            cout << path[i] << "->";
        cout << endl;
    }
    else
    {
        for (pair<PAirport, int> i : adj[src])
        {
            if (visit[i.first] == false)
            {
                printAllUtils(i.first, dest, visit, path, path_index);
            }
        }

    }
    path_index--;
    visit[src] = false;

}

PAirport Graph::SearchAirport(string abc)
{
    int flag = 0;
    for (auto itr : listOfAirports)
    {

        if (itr->name.compare(abc) == 0)
        {
            flag = 1;
            return itr;
        }
    }
    if (flag == 0)
    {
        return NULL;
    }
    return NULL;
}

void Graph::addFlight(PAirport u, PAirport v, int w, bool bidirected = true)
{
    if (bidirected) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    } else {
        adj[u].push_back(make_pair(v, w));
    }

}

void Graph::addAirport(PAirport a) {
    listOfAirports.push_back(a);
}

void printPath(PAirport p) {
    if (parent[p] == nullptr) {
        return;
    }

    printPath(parent[p]);

    cout << p->name << "->";
}

bool doesPathExist(PAirport dest){

    //cout<<dist[dest]<<"\n";
    return dist[dest] != INT_MAX;
}

void Graph::shortestPath(PAirport src, PAirport dest)
{
    for (auto v : listOfAirports) {
        dist[v] = INT_MAX;
    }


    priority_queue<myPair, vector<myPair>, greater<myPair>> pq;

    pq.push(make_pair(0, src));
    dist[src] = 0;
    parent[src] = nullptr;

    while (!pq.empty())
    {
        PAirport u = pq.top().second;
        pq.pop();

        for (pair<PAirport, int> i : adj[u]) {


            PAirport v = i.first;
            int weight = i.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                parent[v] = u;
            }
        }
    }

    if(doesPathExist(dest)){
        cout << endl << "Shortest Flight Distance between " << src->name << " and " << dest->name << " is " << dist[dest] << endl << endl;

        cout << "Shortest Route is: " << src->name << "->";
        printPath(dest);
        cout << endl;
    }else{
        cout << "No Path Exist between " << src->name << " and " << dest->name << endl << endl;
    }

}

void Graph::viewMap()
{
    for (auto itr : listOfAirports)
    {
        cout << "\n\n" << itr->name << "\n" << endl;
    }
}

vector<PAirport> * getSourceAndDestinationAirports(Graph &g) {
    auto len = g.listOfAirports.size();
    bool validInput = false;
    int src = -1, dest = -1;

    while (!validInput) {
        cout << "List of Source Airports" << endl;

        for (int i = 0; i < g.listOfAirports.size(); i++) {
            cout << i + 1 << " " << g.listOfAirports[i]->name << endl;
        }
        cout << "Select Source Airport(1-" << len << ") : " << endl;
        cin >> src;

        cout << "List of Destination Airports" << endl;
        for (int i = 0; i < g.listOfAirports.size(); i++) {
            cout << i + 1 << " " << g.listOfAirports[i]->name << endl;
        }
        cout << "Select Destination Airport(1-" << len << ") : " << endl;
        cin >> dest;

        if (src == dest) {
            cout << "Source and Destination cannot be same" << endl;
            validInput = false;
            continue;
        }

        if (src >= 1 && src <= len && dest >= 1 && dest <= len) {
            validInput = true;
        }
    }



    PAirport srcAirport, destAirport;
    srcAirport = g.listOfAirports[src - 1];
    destAirport = g.listOfAirports[dest - 1];

    vector<PAirport> *srcAndDest = new vector<PAirport>;
    srcAndDest->push_back(srcAirport);
    srcAndDest->push_back(destAirport);

    return srcAndDest;
}
int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        deque<int> q;
        int n = boxes.size();
        vector<int> dp(n + 1);
        dp[n] = 0;
        int cur_box_count = 0;
        int sum_w = 0;
        int r = n - 1;
        cur_box_count += 1;
        sum_w += boxes[n - 1][1];
        dp[n - 1] = 2;
        for (int i = n - 2;  i >= 0; -- i) {
            auto& box = boxes[i];
            cur_box_count += 1;
            sum_w += box[1];
            if (i + 1 <= r && boxes[i][0] != boxes[i + 1][0]) {
                q.push_front(i);
            }
            while (cur_box_count > maxBoxes || sum_w > maxWeight) {
                cur_box_count -= 1;
                sum_w -= boxes[r][1];
                -- r;
                if (!q.empty() && (q.back() + 1) > r) {
                    q.pop_back();
                }

            }
            if (q.size() >= 1) {
                dp[i] = q.size() + 1 + dp[q.back() + 1];
            } else {
                dp[i] = 0x7fffffff;
            }
            dp[i] = min(dp[i], (int)q.size() + 2 + dp[r + 1]);
        }
        return dp[0];
    }
int solve(int i, int mx) {

   if (i==N) return 0;

   if (dp[i][mx] >= 0) return dp[i][mx];

   int mi = mn[i], ret = 0;

   if (A[i] > A[mx]) // A[i] > Y

       ret = max(ret, solve(i+1, mx));

   else if (A[i] > A[mi]) { // X < A[i] <= Y

       ret = max(ret, solve(i+1,mx));

       ret = max(ret, 1+solve(i+1,i));

   } else { // A[i] <= X

       ret = max(ret, 1+solve(i+1, mx));

       ret = max(ret, 1+solve(i+1, mi));

   }

   return dp[i][mx] = ret;

}
int max(int a, int b)
{
    return (a > b) ? a : b;
}


// Prints the items which are put in a knapsack of capacity W
void printknapSack(int W, int wt[], int n)
{
    int i, w;
    int K[n + 1][W + 1];

    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(wt[i - 1] +
                    K[i - 1][w - wt[i - 1]] , K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
 int res = K[n][W];
    // stores the result of Knapsack
    cout<<"Total weight:"<<res << endl;


    w = W;
    cout<<"Bags allowed:";
    for (i = n; i > 0 && res > 0; i--) {

        if (res == K[i - 1][w])
            continue;
        else {

            // This item is included.
            cout<<" "<<wt[i - 1] ;

            // Since this weight is included its
            // value is deducted
            res = res - wt[i - 1];
            w = w - wt[i - 1];
        }
    }
}


int main()
{
    Graph g;

    PAirport a1 = new Airport("New Delhi");
    PAirport a2 = new Airport("Mumbai");
    PAirport a3 = new Airport("Lucknow");
    PAirport a4 = new Airport("Chennai");
    g.addAirport(a1);
    g.addAirport(a2);
    g.addAirport(a3);
    g.addAirport(a4);

    g.addFlight(a1, a2, 500);
    g.addFlight(a2, a3, 150);
    g.addFlight(a1, a3, 100);
    g.addFlight(a1, a4, 600);

    char choice = 'y';
    do
    {
        int ch;
        cout << "\t\t\t\t WELCOME TO JAYPEE AIRLINES\n" << endl;
        cout << "\t 1. To Get shortest Flight Distance to your destination" << endl;
        cout << "\t 2. To Add a new Airport" << endl;
        cout << "\t 3. To View all Routes" << endl;
        cout << "\t 4  To Add a new Flight" << endl;
        cout << "\t 5. To View the Airport List" << endl;
        cout << "\t 6. To find the number of trips" << endl;
        cout << "\t 7. To find the number of flights to be rescheduled" << endl;
        cout << "\t 8. To find the number of bags allowed with optimal weight"<< endl;
        cout << "\t 9. To Exit\n" << endl;
        cin >> ch;
        if (ch == 9)
        {
            exit(0);
        }
        else
        {
            switch (ch)
            {
                case 1:
                {
                    system("cls");
                    vector<PAirport> *srcAndDest = getSourceAndDestinationAirports(g);
                    PAirport srcAirport = (*srcAndDest)[0];
                    PAirport destAirport = (*srcAndDest)[1];
                    g.shortestPath(srcAirport, destAirport);
                    break;
                }
                case 2:
                {
                    system("cls");
                    cout << "\n\n Enter Name of the New Airport\n" << endl;
                    string st;
                    cin >> st;
                    PAirport a5 = new Airport(st);
                    g.addAirport(a5);
                   dist[a5] = INT_MAX;
                    break;
                }
                case 3:
                {


                    vector<PAirport> *srcAndDest = getSourceAndDestinationAirports(g);
                    PAirport srcAirport = (*srcAndDest)[0];
                    PAirport destAirport = (*srcAndDest)[1];

                    if(doesPathExist(destAirport)){
                            //cout<<doesPathExist(destAirport)<<"\n";
                        g.PrintAllPaths(srcAirport, destAirport);
                    }else{
                        cout << "No Path Exist between " << srcAirport->name << " and " << destAirport->name << endl;
                    }

                    break;
                }
                case 4:
                {

                    vector<PAirport> *srcAndDest = getSourceAndDestinationAirports(g);
                    PAirport srcAirport = (*srcAndDest)[0];
                    PAirport destAirport = (*srcAndDest)[1];

                    int weight;
                    cout << "\n\nEnter Distance \n" << endl;
                    cin >> weight;

                    g.addFlight(srcAirport, destAirport, weight);
                    cout << "\n\nFlight added successfully\n\n" << endl;
                    break;
                }
                case 5:
                {
                    system("cls");
                    g.viewMap();
                    break;
                }
                case 6:
                {
                    system("cls");
                    int num;
                    int n;
                    cout<<"Enter the number of flights:";
                    cin>>n;
                    cout<<"Enter the flight number and the units of luggage:"<<endl;
                    vector<vector<int>>boxes;
                    for(int i=0;i<n;i++)
                        {
                            vector<int>temp;

                    for(int j=0;j<2;j++)
                        {
                            cin>>num;
                    temp.push_back(num);
                    }
                    boxes.push_back(temp);
                    }
                    int maxBoxes,maxWeight,portsCount;
                    cout<<"maxBoxes:"<<endl;
                    cin>>maxBoxes;
                    cout<<"maxWeight:"<<endl;
                    cin>>maxWeight;
                    cout<<"portsCount:"<<endl;
                    cin>>portsCount;
                    int result=boxDelivering( boxes, portsCount, maxBoxes, maxWeight);
                    cout<<result;
                    }
                case 7:
                {
                    system("cls");
                    cout<<"Enter the number of flights:";
                    cin >> N;
                    A.resize(N+1);
                    for (int i=0; i<N; i++){
                            cout<<"Enter the speed of airplane"<<" "<<i+1<<":";
                    cin >> A[i]; A[N] = INT_MAX;
                    }
                    int m = INT_MAX, mi = -1;
                    for (int i=0; i<N; i++) {
                            if (A[i] < m) m = A[i], mi = i;
                    mn[i] = mi;
                    }
                    memset(dp, -1, sizeof dp);
                    int res=1 + solve(1, N);
                    cout <<"No. of flights that need to be rescheduled are :  "<<N-res<<endl;
                    return 0;

                    break;
                }
                case 8:
                {
                    system("cls");
                    int n;
                    cout<<"Enter no. of items: ";
                    cin>>n;
                    cout<<"Enter weights of "<<n<<" items: ";
                    int wt[n];
                    for(int i=0;i<n;i++)
                    {
                            cin>>wt[i];
                    }
                    int W = 30;
                    printknapSack(W, wt, n);
                    break;
                }
            }
        }
        cout << "\n\n\nDo you want to go to the main page or not?(Y/N)\n";
        cin >> choice;
        system("cls");

    } while (choice == 'y' || choice == 'Y');

    for (auto &v : g.listOfAirports) {
        delete v;
    }

    return 0;
}
