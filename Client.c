#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include "encryptdecr.h"


void error(const char *err){
	perror(err);
	exit(1);
}

int main(int argc,char *argv[])
{
      if(argc<3){
    	fprintf(stderr,"Not enough Agruments!!\nUsage %s hostname port number\n",argv[0]);    
    	exit(1);
       }
       
       int portno,len;
       char buffer[1024];  //to store strings
       struct sockaddr_in server_addr;
       struct hostent *server;
       
       //creating socket
       int sockfd=socket(AF_INET,SOCK_STREAM,0);
       if(sockfd<0)
	       error("Error opening socket!!");
       
       server=gethostbyname(argv[1]);
       
       if(server==NULL)
       	fprintf(stderr,"Error no such host present");
       	
       bzero((char *)&server_addr,sizeof(server_addr));
       
       portno=atoi(argv[2]);
       
       server_addr.sin_family=AF_INET;
       bcopy((char *)server->h_addr,(char *)&server_addr.sin_addr.s_addr,server->h_length);
       server_addr.sin_port=htons(portno);
       
       printf("Establishing connection..");
       if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0 )
       	error("Attention: Connection Failed!!\n");
       printf("\nConnection Established successfully!!!!!\n");
	long int ns,es;
	int i;
	//p=53l;
	//q=59l;
	/*printf("\n\n>>>ENTER THE FIRST PRIME NUMBER: ");
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
		 */
	p=61l;
	q=71l;	 
			
	n=p*q;
	t=(p-1)*(q-1);        //totient
	ce();             //public key(n,e)
	d=cd(); 		//private key(n,d)
	//Preserving values
	n1=n;
	e1=e;
      
       sprintf(buffer,"%ld",n);
       len=write(sockfd,buffer,strlen(buffer));
	bzero(buffer,256);
	
	//reading server 
	len=read(sockfd,buffer,1024);
	if(len<0)
        	error("Error Reading from server!!");
       n=atoi(buffer);
       
       bzero(buffer,255);
       sprintf(buffer,"%ld",e);
       len=write(sockfd,buffer,strlen(buffer));
        
       len=read(sockfd,buffer,1024);
       if(len<0)
        	error("Error Reading from server!!");
       e=atoi(buffer);
       
       printf("SERVER: *****PUBLIC KEY:(%ld,%ld)*****\n",n,e);
       //printf("%s",buffer);
          bzero(buffer,256);
          ns=n;
          es=e;
          FILE *fp_client;
          fp_client=fopen("ClientFile.txt","w");
       while(1){
	        bzero(buffer,1024);
		printf(">>> ");
		bzero(buffer,1024);
		       
		fgets(buffer,1024,stdin);
		//printf("Client: ");
		       	
		n=ns;
		e=es;
		bzero(enc,1024);
		strncpy(enc,buffer,1024);		      

		encrypt();
		//printf("\n\t--------------------------------------------------------------------------");
		//printf("\n     ^^^^^^The Encrypted Message is: ");
		for(i=0;en[i]!=-1;i++){
		//	printf("%c",en[i]);
			buffer[i]=en[i];
		}
		//printf("^^^^^^\n");
		//printf("\t--------------------------------------------------------------------------");
		//i=i+1;
		len=write(sockfd,en,(i+1)*8);  
		
		fputs("Client:",fp_client);
		if(len<0)
			error("Error Writing to server!!");
			
		i=0;
		while(en[i]!=-1){
			putc(en[i],fp_client);
			i++;
		}
		//fputs(en,fp_server);
		fprintf(fp_client,"\n");
		
		bzero(buffer,1024);
		bzero(en,1024);

		len=read(sockfd,en,1024);
		
		fputs("Server: ",fp_client);
		i=0;
		while(en[i]!=-1){
			putc(en[i],fp_client);
			i++;
		}
		//fputs(en,fp_server);
		fprintf(fp_client,"\n");

		i=0;
		//printf("\n>>>SERVER:");
		//printf("\n     ^^^^^^  Original Message(Actual Message Recieved): ");
			
		//while(en[i]!=-1)
		//printf("%c",en[i++]);
		//printf("  ^^^^^^\n");
		//Decrypting the message recieved
		n=n1;
		e=e1;
		decrypt();   //Actual Message stored in msg array
		    
		if(len<0)
			error("Error Reading from server!!");
		       
		bzero(en,1024);
		strncpy(buffer,msg,1024);
		bzero(msg,1024);
		printf(">>>SERVER: %s\n",buffer);
		//printf("     Decrypted Message: %s\n",buffer);
		//printf("\t--------------------------------------------------------------------------");
		i=strncmp("bye",buffer,3);

		if(i==0){
			printf("\n Successfully!!Disconnected from server\n");
			break;
		}
		}
		fclose(fp_client);

close(sockfd);
return(0);
}
