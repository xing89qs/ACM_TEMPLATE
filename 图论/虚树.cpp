int buildVirtualTree(int m){
    sort(b,b+m,cmp);//cmp是按dfs序排
    int top = 0;
    int num = m;
    b[num++] = 1;//先把root加进去
    stack[++top] = 1;
    for(int i = 0;i<m;i++){
        int u = b[i],pa = lca.LCA(b[i],stack[top]);
        for(;lca.dis[stack[top]]>lca.dis[pa];--top)
            if(lca.dis[stack[top-1]]<=lca.dis[pa])
                fa[stack[top]] = pa;
        if(stack[top]!=pa){
            b[num++] = pa;
            fa[pa] = stack[top];
            stack[++top] = pa;
        }
        fa[u] = pa;
        stack[++top] = u;
    }
    fa[1] = -1;
    sort(b,b+num,cmp);
    num = unique(b,b+num)-b;
    return num;
}