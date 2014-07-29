class China{
    LL a[15],b[15];
    
    LL gcd(LL a,LL b){
        return b==0?a:gcd(b,a%b);
    }
    
    void ex_gcd(LL a,LL b,LL &d,LL &x,LL &y){
        if(!b){d = a;x = 1;y = 0;}
        else{ex_gcd(b,a%b,d,y,x);y-=x*(a/b);}
    }
    
    LL getinv(LL a,LL n){
        LL d,x,y;
        ex_gcd(a,n,d,x,y);
        return d==1?(x+n)%n:-1;
    }
    
    
    //剩余定理不互质
    //两两合并
    //x = a1 mod b1
    //x = a2 mod b2
    //合并后成为
    //g = gcd(b1,b2)
    //x = b1*((a2-a1)/g*inv(b1/g,b2/g)%(b2/g))+a1  mod b1*b2/g
    LL china_merge(LL n){
        LL a1 = a[0],b1 = b[0];
        for(int i = 1;i<n;i++){
            LL a2 = a[i],b2 = b[i];
            LL d = gcd(b1,b2);
            if((a1-a2)%d) return -1;
            LL inv = getinv(b1/d,b2/d);
            LL c = inv*(a2-a1)/d%(b2/d);
            a1 = b1*c+a1;
            b1 = b1/d*b2;
            a1 = (a1%b1+b1)%b1;
        }
        if(a1==0) a1 = b1;
        return a1;
    }
};