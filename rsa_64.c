#include <stdio.h>
#include <stdlib.h>,
#include <time.h>
#include <stdint.h>
#define min(a,b) (a < b ? a : b)
#define max(a,b) (a >= b ? a : b)
#define MAX 128

//随机生成素数
uint64_t random_odd( ){
	uint64_t r, i;
	uint64_t flag = 1;
	while(flag){
		flag = 0;
		r = rand()%50 + 2;
		//r = rand();
		for(i = 2; i< r; i++) {
			if(r % i == 0){
				flag++;
			}
		}
		if(!flag){break;}
	}
    return r;
}

//求出最大公因数(默认a >= b)
uint64_t gcd(uint64_t a, uint64_t b){
    uint64_t tmp = a % b;
    while(tmp != 0){
        a = b;
        b = tmp;
        tmp = a % b;
    }
    return b;
}

//求出最小公倍数
uint64_t lcm(uint64_t a, uint64_t b){
    uint64_t x = max(a, b);
    uint64_t y = min(a, b);
    uint64_t gcd_num = gcd(x, y);
    return ((a * b) / gcd_num);
}

//在给定范围内随机选取互质的数e, e < limit
uint64_t random_e(uint64_t limit){
    uint64_t num_e = 2;
    while(1) {
        num_e = rand()%limit + 1;
        if((num_e < limit) && (gcd(limit, num_e) == 1)){
            break;
        }
    }
    return  num_e;
}

//根据加密密钥e和数L计算解密密钥d: e * d mod L = 1
uint64_t cal_d(uint64_t e, uint64_t num_l){
    uint64_t i = 1;
    uint64_t num_d;
    while(1){
        if(((i * num_l + 1) % e) == 0){
            num_d = (num_l * i + 1) / e;
            break;
        } 
        i = i + 1;
    }
    return num_d;
}

//将幂指数转换为二进制，逆向存储在数组里面 
int dec2bin(uint64_t num, int bin_num[]){
    int i = 0,  mod = 0;
    while(num != 0){
        mod = num % 2;
        bin_num[i] = mod;
        num = num/2;
        i++;
    }
    //返回二进制数的位数
    return i;
}

//反复平方求幂 传入的三个参数分别是明文/密文  密钥e/d， 大整数N 
uint64_t pow_with_mod(uint64_t cm, uint64_t key, uint64_t num){
	uint64_t tmp = cm, result = 0;
	int bin_key[MAX]; 
	int bin_num = dec2bin(key, bin_key) - 1;
	//printf("tmp: %llu, cm: %llu, key: %llu, binnum: %d\n",tmp, cm, key, bin_num);
	int i;
	for(i = bin_num - 1; i >= 0; i--){
		result = tmp * tmp;
		if(bin_key[i] == 1){
			result = result * cm; 
		}
		tmp = result % num;
		//printf("bin_key[%d]: %d\t", i, bin_key[i]); 
		//printf("result2: %llu\t", result);
		//printf("tmp: %llu\n", tmp);
	}
	return tmp;
} 

//加密，明文m，加密钥 <n, e> 
uint64_t encrpt(uint64_t m1, uint64_t e1, uint64_t n1){
    uint64_t c1 = pow_with_mod(m1, e1, n1);
    return c1;
}

//解密 ,密文c， 解密钥<p, q, d, l> 
uint64_t decrpt(uint64_t c2, uint64_t d2, uint64_t n2){
    uint64_t m2 = pow_with_mod(c2, d2, n2);
    return m2;
}

int main() {
	//设置随机数种子 
	srand((unsigned)time(NULL));
	uint64_t p, q, N, L, e, d ;
	uint64_t c, m;
	
	//随机求得两个素数p，q 
    p = random_odd();
    q = random_odd();
    printf("p: %d  q: %d\n", p, q);
    
    //根据 p、q计算 N 以及对应的 L = (p - 1) * (q - 1) 
    N = p * q;
    L = (p - 1) * (q - 1);
    printf("N = p * q = %llu\n", N);
    printf("L = (%d - 1) * (%d - 1) = %llu\n", p, q, L);
    
    //根据 L取与 L互质的加密密钥 e ，1<e<L 
    e = random_e(L);
    printf("e: %llu\n", e);
    
    //根据 e 和 L 计算得到 d （e * d） = 1（mod L） 
	d = cal_d(e, L);
    printf("d: %llu\n", d);
    
    //设置明文 
    printf("请输入待加密的明文：\n");
    scanf("%llu", &m);
    
    //进行加密 
    c = encrpt(m, e, N);
    printf("加密后的密文c为：%llu\n", c);
    
    //进行解密
	m = decrpt(c, d, N);
	printf("解密后的明文m为：%llu\n", m);
	
	//test
   	p = 3;
   	q = 11;
   	e = 19;
   	m = 2;
   	N = p * q;
    L = (p - 1) * (q - 1);
	d = cal_d(e, L);
  	c = encrpt(m, e, N);
  	printf("\n");
	m = decrpt(c, d, N);
	printf("\n");
	printf("N = %llu * %llu = %llu\n", p, q, N);
    printf("L = (%d - 1) * (%d - 1) = %d\n", p, q, L);
	printf("d: %llu\n", d);
	printf("加密后的密文c为：%llu\n", c);
	printf("解密后的明文m为：%llu\n", m);

}
