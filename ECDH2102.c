#include<stdio.h>
#include<stdlib.h>


void Addition(long int *a, long int *b, long int *d); //Function for Integer Addition
void Sub(long int *a, long int *b, long int *c1); //Function for Integer Substraction
void multiplication(long int *a, long int *b, long int *answer); //Function for Integer Multiplication
void Barrett(long int *x, long int *r1); //Function for Barrett Reduction
int inverse(long int *x, long int *x1); //Function for Findiong Inverse in Finite Field
void F_add(long int *a, long int *b, long int *c); //Function for Finite Field Addition
void F_sub(long int *a, long int *b, long int *c); //Function for Finite Field Substraction
void F_mul(long int *a, long int *b, long int *c); //Function for Finite Field Multiplication
void ecc_add(long int *a1, long int *a2, long int *b1, long int *b2,  long int *c1, long int *c2); //Function for Elliptic Curve Addition
void ecc_scaler_mult(long int *a1, long int *a2, long int *n, long int *b1, long int *b2); //Function for Elliptic Curve Scaler Multiplication
void show(long int *a, int digits); //Function for Printing an Array
void empty(long int *a, int size); //Function for vacate an Array
int compare(long int *r, long int *p); //Function for comparing two number.


void ecdh()
{
	//Function for Generating the Key for both the parties

	long int alice_a[11];
	long int bob_b[11];
	int i;
	
	for(i=7;i<11;i++) alice_a[i]=rand()%1000;
	
	for(i=7;i<11;i++) bob_b[i]=rand()%1000;
	
	long int ag1[11], ag2[11], bg1[11], bg2[11], abg1[11], abg2[11], bag1[11], bag2[11], temp[22];
	long int G1[11]={0, 0, 27415, 880588875, 69500811, 865834382, 608236151, 14639179, 515062287, 310699287, 412664470};
	long int G2[11]={0, 0, 20451, 280543110, 670677230, 531442160, 262018603, 864867802, 857074924, 785973664, 935285237};
	long int n[11]={0, 0, 65535, 1073725440, 4095, 1073741823, 1073741756, 968797033, 830072911, 250030859, 1013130577};
	

	ecc_scaler_mult(G1, G2, alice_a, ag1, ag2);
	ecc_scaler_mult(G1, G2, bob_b, bg1, bg2);
	ecc_scaler_mult(ag1, ag2, bob_b, bag1, bag2);
	ecc_scaler_mult(bg1, bg2, alice_a, abg1, abg2);


	printf("Bob key:  ");
	printf("\n");
	printf("bag1 : ");
	show(bag1, 11);
	printf("\n");
	printf("bag2 : ");
	show(bag2, 11);
	
	printf("\n\n");
	
	printf("Alice key:  ");
	printf("\n");
	printf("abg1 : ");
	show(abg1, 11);
	printf("\n");
	printf("abg2 : ");
	show(abg2, 11);
	
}

void empty(long int *a, int size)
{
	//Function for vacate an Array
	
	int i;
	for(i=0; i<size; i++) a[i]=0;
}

void ecc_scaler_mult(long int *a1, long int *a2, long int *n, long int *b1, long int *b2)
{
	//Function for Elliptic Curve Scaler Multiplication

    	long int ans1[11], ans2[11];
	int i=0, j=29, k=0, l;
	while((n[k]>>j) & 1 == 0)
	{
	    j--;
	    if(j== -1)
	    {
		k++;
		j=29;
	    }
	    i++;
	    if(k==11) break;
	}
	j--; if(j == -1) { k++; j=29; } i++;
	ecc_add(a1, a2, a1, a2, ans1, ans2);


	while(i<330)
	{
	    //printf("scaler mult i: %d\n", i);

	    if((n[k]>>(j--)) & 1)
	    {
		ecc_add(ans1, ans2, a1, a2, ans1, ans2);

	    }
	    ecc_add(ans1, ans2, ans1, ans2, ans1, ans2);

	    if(j==-1)
	    {
			k++;
			j = 29;
	    }
	    i++;
	}
	for(i=0; i<11; i++) b1[i]=ans1[i];
	for(i=0; i<11; i++) b2[i]=ans2[i];

}

void ecc_add(long int *a1, long int *a2, long int *b1, long int *b2, long int *cc1, long int *cc2)
{
	//Function for Elliptic Curve Addition
	
	long int A[11]={0, 0, 65535, 1073725440, 4096, 0, 0, 63, 1073741823, 1073741823, 1073741820};
	long int B[11]={0, 0, 23238, 225847950, 691960638, 787830234, 411483237, 121744435, 87756643, 792260856, 668098635};
	long int p[11]={0, 0, 65535, 1073725440, 4096, 0, 0, 63, 1073741823, 1073741823, 1073741823};
	int i, tem=0;
	
	long int temp[11], temp1[22], temp2[11], lambda[11];
	long int c1[11], c2[11];
	
	
	for(i=0; i<11; i++)
	{
		if(a1[i] != b1[i])
		{
			tem=1;
			break;
		}
	}
	
	if(tem==0)
	{
		for(i=0; i<11; i++)
		{
			if(a2[i] != b2[i])
			{
				tem=1;
				break;
			}
		}
		
	}
	
	if(tem ==0)
	{
		
		F_mul(a1, a1, temp);
		F_add(temp, temp, temp2);
		F_add(temp2, temp, temp);
		F_add(temp, A, temp);
		F_add(a2, a2, temp2);
		inverse(temp2, temp2);
		F_mul(temp, temp2, lambda);
	}
	
	if(tem==1)
	{
		
		F_sub(b2, a2, temp2);
		F_sub(b1, a1, temp);
		inverse(temp, temp);
		F_mul(temp, temp2, lambda);
	}
	
	
	F_mul(lambda, lambda, temp2);
	F_add(a1, b1, temp);
	F_sub(temp2, temp, c1);
	
	
	F_sub(a1, c1, temp);
	F_mul(temp, lambda, temp2);
	F_sub(temp2, a2, c2);
	
	
	for(i=0; i<11; i++)
	{
		cc1[i] = c1[i];
		cc2[i] = c2[i]; 
	}
}

int inverse(long int *x, long int *x1)
{
	//Function for Findiong Inverse in Finite Field
	
	long int p[11]={0, 0, 65535, 1073725440, 4096, 0, 0, 63, 1073741823, 1073741823, 1073741823}, z[11]={0}, z1[22]={0}, p1[11]={0};
	z[10]=1;
	p1[10]=2;
	Sub(&p[0], &p1[0], &p1[0]);
	int i=0,k=0,j=29;	
	while (i <330)
	{
		multiplication(&z[0], &z[0], &z1[0]);
		Barrett(&z1[0], &z[0]);
		if((p1[k]>>(j--)) & 1)
		{
			multiplication(&z[0], &x[0], &z1[0]);
			Barrett(&z1[0], &z[0]);
		}
		if(j==-1)
		{
			k++;
			j = 29;
		}
		i++;
	}
	
	for(i=0; i<11; i++)
	x1[i]=z[i];
  
}

int compare(long int *r, long int *p)
{
	//Function for comparing two number. it return one if return korbe 1 if r >= p 
	
	int temp=0, i;
	for(i=0; i<11; i++)
	{
		if(r[i] < p[i])
		return 0;
		
		if(r[i] > p[i])
		return 1;
	}
	return 1;
}

void Barrett(long int *x, long int *r1)
{
	//Function for Barrett Reduction
	
	long int t[11]={0, 16384, 4095, 1073741823, 1073741567, 1073741759, 1073741807, 1073741820, 0, 0, 805306368};
	int k=9,i=0;
	long int p[11]={0, 0, 65535, 1073725440, 4096, 0, 0, 63, 1073741823, 1073741823, 1073741823};
	long int q[22]={0}, r[11]={0};
	long int b_k[11]={0};
	long int x1[22]={0};
	for(i=0; i<22; i++) x1[i]=x[i];
	b_k[0]=1;
	for(i=21; i>=8; i--)
	{
		q[i]=x1[i-8];
	}
	multiplication(&q[11], &t[0], &q[0]);


	for(i=21; i>=10; i--)
	{
		q[i]=q[i-10];
	}
	for(i=9; i>=0; i--)
	q[i]=0;

	for(i=0; i<=11; i++)
	x1[i]=0;
	
	multiplication(&q[11], &p[0], &q[0]);
	
	for(i=0; i<=11; i++)
	q[i]=0;

	Sub(&x1[11], &q[11], &r[0]);

	if(((r[0]>>29) & 1)==1)
	{
		Addition(&r[0], &b_k[0], &r[0]);
	}

	if(compare(&r[0], &p[0]))
	{
		Sub(&r[0], &p[0], &r[0]);
	}

	if(compare(&r[0], &p[0]))
	{
		Sub(&r[0], &p[0], &r[0]);
	}

	for(i=0; i<11; i++)
	r1[i]=r[i];
}

void multiplication(long int *a, long int *b, long int *answer)
{
	//Function for Integer Multiplication
	
	long int m1[22] = {0}, answer1[22] = {0};
	int i, j, k=21, carry, l;
	for(i=10; i>=0; i--)
	{
		for(j=10; j>=0; j--)
		{
			m1[k] += b[i]*a[j];
			carry = m1[k]>>30;
			m1[k] = m1[k] & 0x3fffffff;
			m1[k-1]+=carry;
			k--;
		}
		for(l=21; l>=0; l--)
		{
			answer1[l]+=m1[l];
			if((answer1[l]>>30)&1 == 1)
			{
				answer1[l]=answer1[l] & 0X3fffffff;
				if(l>0) answer1[l-1]+=1;
			}
		}
		
		
		for(l=0; l<22; l++)
		m1[l]=0;
		
		k=i+10;
	}
	for(i=0; i<22; i++)
	answer[i]=answer1[i];
}

void Sub(long int *a, long int *b, long int *c1)
{
	//Function for Integer Substraction
	
	long int b1[11]={0};
	long int c[11] = {0};
	int i, carry;
	for(i=0; i<11; i++) b1[i]=b[i];
	for(i=0; i<=10; i++)
		b1[i] = b1[i] ^ 0X3fffffff;
	
	b1[10]+=1;
	carry=(b1[10]>>30)&1;
	b1[10]=b1[10] & 0X3fffffff;
	i=9;
	while(carry != 0 && i>=0)
	{
		
		b1[i]+=1;
		carry = (b1[i]>>30)&1;
		b1[i]=b1[i] & 0X3fffffff;
		i--;	
	}
	
		
	for(i=10; i>=0; i--)
	{
		c[i]+=a[i]+b1[i];
		if((c[i]>>30)&1 == 1)
		{
			c[i]=c[i] & 0X3fffffff;
			if(i > 0) c[i-1]+=1;
		}
	}
	
	for(i=0; i<11; i++)
	c1[i]=c[i];
}

void Addition(long int *a, long int *b, long int *d)
{
	//Function for Integer Addition
	
	long int c[11]={0};
	int i;
	for(i=10; i>=0; i--)
	{
		c[i]+=a[i]+b[i];
		if((c[i]>>30)&1 == 1)
		{
			c[i]=c[i] & 0X3fffffff;
			if(i>0) c[i-1]+=1;
		}
	}
	for(i=0; i<11; i++)
	d[i]=c[i];
}

void show(long int *a, int digits)
{
	//Function for Printing an Array
	
	int i;
	for( i=0; i<digits; i++)
		printf("%ld ",  a[i]);
}

void F_add(long int *a, long int *b, long int *c)
{
	//Function for Finite Field Addition
	
	int i;
	long int p[11]={0, 0, 65535, 1073725440, 4096, 0, 0, 63, 1073741823, 1073741823, 1073741823};
	long int temp1[22]={0}, temp[11]={0};
	Addition(a, b, temp);
	for(i=11; i<22; i++) temp1[i]=temp[i-11];
	Barrett(temp1, c);
}

void F_sub(long int *a, long int *b, long int *c)
{
	//Function for Finite Field Substraction
	
	int i;
	long int p[11]={0, 0, 65535, 1073725440, 4096, 0, 0, 63, 1073741823, 1073741823, 1073741823};
	long int temp1[22]={0}, temp[11]={0};
	Sub(a, b, temp);
	if(((temp[0])>>29) & 1)
	{
		Addition(temp, p, temp);
	}
	for(i=11; i<22; i++) temp1[i]=temp[i-11];
	Barrett(temp1, c);	
}

void F_mul(long int *a, long int *b, long int *c)
{
	//Function for Finite Field Multiplication
	
	long int temp1[22]={0}, temp[11]={0};
	long int p[11]={0, 0, 65535, 1073725440, 4096, 0, 0, 63, 1073741823, 1073741823, 1073741823};
	multiplication(a, b, temp1);
	Barrett(temp1, c);
}

int main()
{
    ecdh();
    printf("\n\n");
    return 0;
}
