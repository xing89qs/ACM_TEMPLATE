//Manacher算法

char newstr[MAXN<<1];   //转换后的新字符串
int rad[MAXN<<1];  //rad[i]表示i的回文半径

int manacher(char *str)
{
    int j;
    int Max = 0;
    newstr[0] = '$';    //字符串开头增加一个特殊字符，防止越界
    int len;
    //int len = strlen(str);
    //for(int k=0; k<len; k++)
    for(len=0,j=1; str[len]!='\0'; len++)
    {
        newstr[j++] = '#';
        newstr[j++] = str[len];
        //newstr[j++] = str[k];
    }
    newstr[j] = '#';
    newstr[j+1] = '\0';
    if(len == 0)
        return -1;
    int mx = 0,id = 0;  //mx为以newstr[id]为中心的最长回文串的右边界，即mx=id+rad[id]
    //int axis = -1;
    //int l,r;  //最大回文串的左右边界
    for(int i=1; i<=j; i++)
    {
        if(mx > i)
            rad[i] = min(rad[2*id-i],mx-i);    //在rad[j]和mx-i中取值小的
        else
            rad[i] = 1; //若i>=mx，则要重新计算rad[i]
        while(newstr[i+rad[i]] == newstr[i-rad[i]]) //不需边界判断，因为左有'$',右有'\0'
            rad[i]++;
        Max = max(Max,rad[i]);
        /*if(Max < rad[i])
        {
            Max = rad[i];
            axis = i;   //记录最大回文串对称中心（对称轴）
            l = (i - rad[i]) / 2;
            r = (i + rad[i]) / 2 - 2;
        }
        */
        if(rad[i] + i > mx) //若新得到的回文串右端点位置大于mx，则要更新id和mx的值
        {
            mx = rad[i] + i;
            id = i;
        }
    }
    return Max - 1;   //返回rad[i]中的最大值-1即为原串的最长回文子串的长度
}
