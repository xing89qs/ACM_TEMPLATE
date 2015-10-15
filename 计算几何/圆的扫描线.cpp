
const int UP = 1;
const int DOWN = -1;

double Time;

struct Circle{
    int x,y;
    int r;
    double getY(int flag){
        double ret = sqrt(1ll*r*r-(Time-x)*(Time-x));
        return y+flag*ret;
    }
} c[MAXN];

struct Node{
    int flag;
    int idx;
    Node(int flag,int idx):flag(flag),idx(idx){}
    bool operator<(const Node & p) const{
        double y1 = c[idx].getY(flag);
        double y2 = c[p.idx].getY(p.flag);
        return sign(y1-y2)?y1<y2:flag<p.flag;
    }
};

struct Event{
    int x,y;
    int type,idx;
    Event(int x,int y,int type,int idx):x(x),y(y),type(type),idx(idx){}
    Event(){}
    bool operator<(const Event& e) const{
        return x<e.x||(x==e.x&&type<e.type);
    }
} e[MAXN<<2];

int dep[MAXN];
int fa[MAXN];
vector<int> g[MAXN];

void build(int n){
    //圆标号0~n-1
    //n虚拟根，包含所有dep为1的圆
    for(int i = 0;i<=n;i++) g[i].clear(),fa[i] = n,dep[i] = 0;
    int cnt = 0;
    for(int i = 0;i<n;i++){
        e[cnt++] = Event(c[i].x-c[i].r,c[i].y,0,i);
        e[cnt++] = Event(c[i].x+c[i].r,c[i].y,1,i);
    }
    sort(e,e+cnt);
    set<Node> st;
    for(int i = 0;i<cnt;i++){
        int pos = e[i].idx;
        Time = e[i].x;
        if(e[i].type==0){
            Node up = Node(UP,pos),down = Node(DOWN,pos);
            set<Node>::iterator it_up = st.lower_bound(up);
            set<Node>::iterator it_down = it_up;
            if(it_down==st.begin()||it_up==st.end()){
                dep[pos] = 1;
                g[n].PB(pos);
                fa[pos] = n;
            }else{
                it_down--;
                int idA = it_up->idx,idB = it_down->idx;
                if(dep[idA]>dep[idB]) swap(idA,idB);
                if(idA==idB){
                    dep[pos] = dep[idA]+1;
                    g[idA].PB(pos);
                    fa[pos] = idA;
                }else if(dep[idA]!=dep[idB]){
                    dep[pos] = dep[idA]+1;
                    g[idA].PB(pos);
                    fa[pos] = idA;
                }else{
                    dep[pos] = dep[idA];
                    g[fa[idA]].PB(pos);
                    fa[pos] = fa[idA];
                }
            }
            st.insert(up);
            st.insert(down);
        }else{
            st.erase(Node(DOWN,pos));
            st.erase(Node(UP,pos));
        }
    }
}
