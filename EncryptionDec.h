#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
long int p,q,n,n1,e1,t,flag,e,d,temp[1024],j,i,m[1024],en[1024];
char enc[1024],dec[1024]={0},msg[1024];

int prime(long int pr) {
 	int i;
 	j=sqrt(pr);
	for (i=2;i<=j;i++) {
		if(pr%i==0)
		   return 0;
	}
	return 1;
}

long int cd() { 
		long int k=1;
		while(1) {
			k=k+t;
			if(k%e==0)
			   return(k/e);
		}
	}

int gcd(int a, int h)
{
    int temp;
    while(1)
    {
        temp = a%h;
        if(temp==0)
        return h;
        a = h;
        h = temp;
    }
}
		
void ce() {
	e = 2;
	while(e<t)
	{
	    int count = gcd(e,t);
	    if(count==1)
	    {
	        break;
	    }
	    else
	    {
	        e++;
    }

	}
}
	
void input(){
	printf("\n\n********************************************PERFORMING ENCRYPTION AND DECRYPTION**************************************************");
	printf("\n\n>>>ENTER THE FIRST PRIME NUMBER: ");
	scanf("%ld",&p);
 	//checking for prime numbers
	flag=prime(p);
	if(flag==0) {
		printf("\nWRONG INPUT:\nAttention:Prime Number Required!!\n");
		exit(1);
	}
	
	printf("\n>>>ENTER THE ANOTHER PRIME NUMBER:");
	scanf("%ld",&q);
	flag=prime(q);
	if(flag==0||p==q) {
		printf("\nWRONG INPUT:\nAttention:Prime Number Required!!\n");
		exit(1);
	}	 
	
	
	}
void encrypt() {
	strcpy(msg,enc);
	//printf("In Encrypt");
		//strcpy(m,msg);
	for(i=0;msg[i]!='\0';i++)
		m[i]=msg[i];
	long int pt,ct,key=e,k,len;
	i=0;
	len=strlen(msg);

	while(i!=len) {
		pt=m[i];
		pt=pt-96;
		k=1;
		for (j=0;j<key;j++) {
			k=k*pt;
			k=k%n;
		}
		//temp[i]=k;
		ct=k+96;
		en[i]=ct;
		i++;
		}
		en[i]=-1;
		//temp[i]=-1;
}
void decrypt() {
	long int pt,ct,key=d,k;
	i=0;
	while(en[i]!=-1) {
	//printf();
	temp[i]=en[i]-96;
		ct=temp[i];
		k=1;
		for (j=0;j<key;j++) {
			k=k*ct;
			k=k%n;
	}
		pt=k+96;
		m[i]=pt;
		msg[i]=m[i];
		i++;
		//printf("%ld :::: %ld  ",en[i],m[i]);
	}
	m[i]=-1;
	
	msg[i]='\0';
		
}
