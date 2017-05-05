//最小表示法
int MinRep(char *s,int len)
{
    int i = 0,j = 1,k = 0;
    while(i<len && j<len && k<len)
    {
        if(s[(i+k)%len]==s[(j+k)%len])
            k++;
        else
        {
            if(s[(i+k)%len]>s[(j+k)%len])
                i = max(i+k+1,j);
            else
                j = max(j+k+1,i);
            if(i==j)
                j++;
            k = 0;
        }
    }
    return min(i,j);
}
