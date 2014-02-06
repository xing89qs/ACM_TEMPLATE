inv[1] = 1;
for(int i = 2;i<MAXN;i++)
	inv[i] = 1ll*MOD/i*(MOD-inv[MOD%i])%MOD;
