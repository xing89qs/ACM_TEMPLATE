//计算x*y对z取模
long long mul(long long x,long long y,long long z){
    return (x*y - (long long)(x/(long double)z*y+1e-3)*z+z)%z;
}